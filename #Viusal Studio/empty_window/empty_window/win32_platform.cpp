#include <Windows.h>

/*
Wichtig ist noch zu ändern, dass es sich nicht um ein Konsolen Programm handelt, sondern um eine grafische Applikation:
- Rechtsklick auf das Projekt ("window") und auf Eigenschaften klicken
- Zu 'Konfigurationseigenschaften/Linker/System' navigieren
- Oben Konfiguration und Platform auf 'Alle Plattformen' �ndern
- SubSystem von 'Console' zu 'Window' ändern
*/

bool running = true;

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
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
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
	const wchar_t CLASS_NAME[] = L"Game Window Class";

	// Create Window Class
	WNDCLASS window_class = {};								// leere Window-Class (oft nur mit 'wc' betitelt)
	window_class.style = CS_HREDRAW | CS_VREDRAW;			// stellt sicher das das Fenster Horizontal und Vertikal neu gedrawed wird wann immer n�tig
	window_class.lpszClassName = CLASS_NAME;				// identifier f�r die Window-Class - nicht sichtbar f�r den Enduser
	window_class.lpfnWndProc = window_callback;				// callback function zuweisen

	// Register Class
	RegisterClass(&window_class);							// pointer zur window-class übergeben

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
	HWND window = CreateWindow(window_class.lpszClassName, L"Pong", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);

	// window loop
	while (running) {

		// Input
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		// Simulate

		// Render


	}


}