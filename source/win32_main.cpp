#include <windows.h>

int CALLBACK WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    (void)hInstance;
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;

	MessageBoxA(0, "Is this cool or not? OK OK!", "Test window", MB_OK|MB_ICONINFORMATION);

    return 0;
}

