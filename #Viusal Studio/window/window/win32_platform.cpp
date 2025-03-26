#include <Windows.h>
#include "utils.cpp"

/*
Wichtig ist noch zu �ndern, dass es sich nicht um ein Konsolen Programm handelt, sondern um eine grafische Applikation:
- Rechtsklick auf das Projekt ("window") und auf Eigenschaften klicken
- Zu 'Konfigurationseigenschaften/Linker/System' navigieren
- Oben Konfiguration und Platform auf 'Alle Plattformen' �ndern
- SubSystem von 'Console' zu 'Window' �ndern
*/

global_variable bool running = true;

struct Render_State {
	int width;
	int height;
	
	void* memory;

	BITMAPINFO bitmapinfo;
};

global_variable Render_State render_state;

#include "platform_common.cpp"
#include "renderer.cpp"
#include "simulate.cpp"

/**
* Die Callback function wird von Windows genutzt um uns Nachrichtigen weiterzugeben wenn etwas wichtiges mit unseren Window passiert:
* - User-Input
* - Window is closed
* - Changed the size of the window
* - Window is minimized
* - Window is active/inactive
*/
LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;
	switch (uMsg) {
		case WM_CLOSE:
		case WM_DESTROY: {
			running = false;
		} break;

		case WM_SIZE: {
			RECT rect;
			GetClientRect(hwnd, &rect);
			render_state.width = rect.right - rect.left;
			render_state.height = rect.bottom - rect.top;

			int buffer_size = render_state.width * render_state.height * sizeof(unsigned int);

			if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);
			render_state.memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			render_state.bitmapinfo.bmiHeader.biSize = sizeof(render_state.bitmapinfo.bmiHeader);
			render_state.bitmapinfo.bmiHeader.biWidth = render_state.width;
			render_state.bitmapinfo.bmiHeader.biHeight = render_state.height;
			render_state.bitmapinfo.bmiHeader.biPlanes = 1;
			render_state.bitmapinfo.bmiHeader.biBitCount = 32;
			render_state.bitmapinfo.bmiHeader.biCompression = BI_RGB;

		}	
		
		default: {
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
	return result;
}

/**
* Entry-point methode um die win32 application zu starten - analog zu 'int main() {}'
*/
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	// Create Window Class
	WNDCLASS window_class = {};								// leere Window-Class (oft nur mit 'wc' betitelt)
	window_class.style = CS_HREDRAW | CS_VREDRAW;			// stellt sicher das das Fenster Horizontal und Vertikal neu gedrawed wird wann immer n�tig
	window_class.lpszClassName = CLASS_NAME;				// identifier f�r die Window-Class - nicht sichtbar f�r den Enduser
	window_class.lpfnWndProc = window_callback;				// callback function zuweisen

	// Register Class
	RegisterClass(&window_class);							// pointer zur window-class �bergeben

	// Create Window
	/*
	Methode um Fenster zu erstellen - kann auch CreateWindowA sein wenn nur ANSI-Characters im Class-Name und Window-Title genutzt werden
	Parameter: (siehe documentation f�r genaue informationen zu den parametern)
	lpClassName												// oben definierter name f�r die Window-Class
	lpWindowsName											// title unseres Windows - f�r enduser sichtbar
	dwStyle,												// style: fullscreen, windowed, visible ...
	x														// x Wert wo das Fenster erstellt werden soll. CW_USEDEFAULT erstellt das Fenster wo Windows denkt es ist am besten
	y														// y Wert wo das Fenster erstellt werden soll. CW_USEDEFAULT erstellt das Fenster wo Windows denkt es ist am besten
	width													// breite des Fenster
	height													// h�he des fensters
	WndParent												// fall es ein parent window gibt welches das neue aufruft. F�r ein Top-Level-Window ist dieser Wert 0/NULL
	Menu													// definiert das Men�. Gibt es keins, ist dieser Wert 0/NULL
	Instance												// instanz in welcher das Fenster l�uft - wert den man aus dem Entry-point erh�lt
	pParam													// vorerst nicht relevant - siehe documentation
	*/
	HWND window = CreateWindow(window_class.lpszClassName, L"Sample Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

	#define process_button(b, vk)\
	case vk: {\
	input.buttons[b].is_down = is_down;\
	input.buttons[b].changed = true;\
	} break;

	Input input = {};

	float delta_time = 0.016666f;
	LARGE_INTEGER frame_begin_time;
	QueryPerformanceCounter(&frame_begin_time);

	float performance_frequency;
	{
		LARGE_INTEGER perf;
		QueryPerformanceFrequency(&perf);
		performance_frequency = (float)perf.QuadPart;
	}

	// window loop
	while (running) {

		// Input
		MSG message;

		for (int i = 0; i < BUTTON_COUNT; i++) {
			input.buttons[i].changed = false;
		}

		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {

			switch (message.message) {
				case WM_KEYUP:
				case WM_KEYDOWN: {
					u32 vk_code = (u32)message.wParam;
					bool is_down = (message.message == WM_KEYDOWN); // '(message.lParam & (1 << 32)) == 0' anstatt 'message.message == WM_KEYDOWN'

					switch (vk_code) {
						process_button(BUTTON_UP, VK_UP);
						process_button(BUTTON_DOWN, VK_DOWN);
						process_button(BUTTON_LEFT, VK_LEFT);
						process_button(BUTTON_RIGHT, VK_RIGHT);
					} break;

				} break;
			
			
				default:
					TranslateMessage(&message);
					DispatchMessage(&message);
			}
		}

		// Simulate
		simulate(&input, delta_time);
		

		// Render
		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmapinfo, DIB_RGB_COLORS, SRCCOPY);


		LARGE_INTEGER frame_end_time;
		QueryPerformanceCounter(&frame_end_time);
		delta_time = (float)(frame_end_time.QuadPart - frame_begin_time.QuadPart) / performance_frequency;
		frame_begin_time = frame_end_time;
	}


}