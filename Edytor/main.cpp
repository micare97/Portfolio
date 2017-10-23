#include <windows.h>

LPSTR NazwaKlasy = "Klasa Okienka";
MSG Komunikat;
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

HWND g_hPrzycisk;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = NazwaKlasy;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "WK odmawia rejestracji!", "Niestety...", MB_ICONEXCLAMATION | MB_OK);
		return 1;
	}

	HWND hwnd;
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, NazwaKlasy, "OTOOKNO", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
				480, 240, NULL, NULL, hInstance, NULL );
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Okno odmówi³o przyjœcia na œwiat!", "Ale kicha...", MB_ICONEXCLAMATION);
		return 1;
	}

	g_hPrzycisk = CreateWindowEx(0, "BUTTON", "Nasz Przycisk", WS_CHILD | WS_VISIBLE, 100, 100, 150, 30, hwnd, NULL,
				hInstance, NULL);

	HWND hText = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
				WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL, 5, 5, 150, 150, hwnd, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&Komunikat, NULL, 0, 0))
	{
		TranslateMessage(&Komunikat);
		DispatchMessage(&Komunikat);
	}

	return Komunikat.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		if((HWND)lParam == g_hPrzycisk)
			MessageBox(hwnd, "Nacisn¹³eœ!", "Ha!", MB_ICONINFORMATION);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
