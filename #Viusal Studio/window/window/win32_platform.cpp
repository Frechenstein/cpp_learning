#include <Windows.h>

/*
Wichtig ist noch zu ändern, dass es sich nicht um ein Konsolen Programm handelt, sondern um eine grafische Applikation:
- Rechtsklick auf das Projekt ("window") und auf Eigenschaften klicken
- Zu 'Konfigurationseigenschaften/Linker/System' navigieren
- Oben Konfiguration und Platform auf 'Alle Plattformen' ändern
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
	LRESULT result;
	switch (uMsg) {
		case WM_CLOSE:
		case WM_DESTROY: {
			running = false;
		} break;
		
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
	window_class.style = CS_HREDRAW | CS_VREDRAW;			// stellt sicher das das Fenster Horizontal und Vertikal neu gedrawed wird wann immer nötig
	window_class.lpszClassName = CLASS_NAME;				// identifier für die Window-Class - nicht sichtbar für den Enduser
	window_class.lpfnWndProc = window_callback;				// callback function zuweisen

	// Register Class
	RegisterClass(&window_class);							// pointer zur window-class übergeben

	// Create Window
	/*
	Methode um Fenster zu erstellen - kann auch CreateWindowA sein wenn nur ANSI-Characters im Class-Name und Window-Title genutzt werden
	Parameter: (siehe documentation für genaue informationen zu den parametern)
	lpClassName												// oben definierter name für die Window-Class
	lpWindowsName											// title unseres Windows - für enduser sichtbar
	dwStyle,												// style: fullscreen, windowed, visible ...
	x														// x Wert wo das Fenster erstellt werden soll. CW_USEDEFAULT erstellt das Fenster wo Windows denkt es ist am besten
	y														// y Wert wo das Fenster erstellt werden soll. CW_USEDEFAULT erstellt das Fenster wo Windows denkt es ist am besten
	width													// breite des Fenster
	height													// höhe des fensters
	WndParent												// fall es ein parent window gibt welches das neue aufruft. Für ein Top-Level-Window ist dieser Wert 0/NULL
	Menu													// definiert das Menü. Gibt es keins, ist dieser Wert 0/NULL
	Instance												// instanz in welcher das Fenster läuft - wert den man aus dem Entry-point erhält
	pParam													// vorerst nicht relevant - siehe documentation

	*/
	HWND window = CreateWindow(window_class.lpszClassName, L"Sample Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);

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