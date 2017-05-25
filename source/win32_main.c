#include <windows.h>
#include <gl/gl.h>
#include "hoki.h"

typedef void game_update(game_state_t*);
game_update* win32_game_update;

HMODULE game_lib = 0;
int running = 0;
game_state_t game_state = { 0 };

void win32_game_load()
{
    if (game_lib)
    {
        FreeLibrary(game_lib);
        win32_game_update = 0;
    }
    
    CopyFileW(L"game.dll", L"game-run.dll", FALSE);
    
    game_lib = LoadLibraryW(L"game-run.dll");

    win32_game_update = (game_update*)GetProcAddress(game_lib, "game_update");
}

void win32_player_render()
{
    float screen_width = 6;
    float screen_height = 6;

    float real_x = (game_state.player_x / screen_width) * 2 - 1.0f;
    float real_y = (game_state.player_y / screen_height) * 2 - 1.0f;

    float size_x = 0.1f;
    float size_y = 0.1f;

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(real_x, real_y + size_y);
    glVertex2f(real_x - size_x, real_y - size_y);
    glVertex2f(real_x + size_x, real_y - size_y);
    
    glEnd();
    glFlush();
}

LRESULT CALLBACK MainWindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam)
{
    static PAINTSTRUCT ps = { 0 };

    switch (uMsg)
    {
        case WM_CREATE:
        {
        } break;

        case WM_CLOSE:
        {
            running = 0;
        } break;

        case WM_DESTROY:
        {
            running = 0;
        } break;

        case WM_PAINT:
        {
            BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
        } break;

        case WM_KEYDOWN:
        {
            if (wParam == VK_ESCAPE)
            {
                running = 0;
            }
            else if (wParam == 0x41)
            {
                game_state.keyboard_state.a = 1;
            }
            else if (wParam == 0x44)
            {
                game_state.keyboard_state.d = 1;
            }
            else if (wParam == 0x57)
            {
                game_state.keyboard_state.w = 1;
            }
            else if (wParam == 0x53)
            {
                game_state.keyboard_state.s = 1;
            }
        } break;

        case WM_KEYUP:
        {
            if (wParam == 0x41)
            {
                game_state.keyboard_state.a = 0;
            }
            else if (wParam == 0x44)
            {
                game_state.keyboard_state.d = 0;
            }
            else if (wParam == 0x57)
            {
                game_state.keyboard_state.w = 0;
            }
            else if (wParam == 0x53)
            {
                game_state.keyboard_state.s = 0;
            }
        } break;

        default:
        {
            return DefWindowProcW(hwnd, uMsg, wParam, lParam);
        }
    }

    return 0;
}

int CALLBACK WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    int pf = 0;
    HWND hwnd = 0;
    HDC hdc = 0;
    HGLRC hrc = 0;
    WNDCLASSEXW wdx = { 0 };
    PIXELFORMATDESCRIPTOR pfd = { 0 };

    (void)hPrevInstance;
    (void)lpCmdLine;

    wdx.cbSize = sizeof(wdx);
    wdx.style = CS_HREDRAW | CS_VREDRAW;
    wdx.lpfnWndProc = MainWindowProc;
    wdx.hInstance = hInstance;
    wdx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wdx.lpszClassName = L"HokiWindowClass";

    RegisterClassExW(&wdx);

    hwnd = CreateWindowExW(
        0,
        wdx.lpszClassName,
        L"Hoki",
        WS_VISIBLE | WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0,
        0,
        hInstance,
        0
    );

    hdc = GetDC(hwnd);

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;

    pf = ChoosePixelFormat(hdc, &pfd);

    SetPixelFormat(hdc, pf, &pfd);

    DescribePixelFormat(hdc, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

    hrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, hrc);

    ShowWindow(hwnd, nCmdShow);

    game_state.player_x = 3.0f;
    game_state.player_y = 3.0f;

    win32_game_load();

    running = 1;

    FILETIME last_update = { 0 };

    while (running)
    {
        MSG msg;

        while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                running = 0;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        
        WIN32_FILE_ATTRIBUTE_DATA data;
        
        GetFileAttributesExW(L"game.dll", GetFileExInfoStandard, &data);
        
        FILETIME new_time = data.ftLastWriteTime;
        
        if (CompareFileTime(&new_time, &last_update) != 0)
        {
            OutputDebugStringW(L"ALL WORKS\n");
            last_update = new_time;

            win32_game_load();
        }

        win32_game_update(&game_state);

        win32_player_render();

        // TODO: Add better fixed timestep.
        Sleep(16);
    }

    wglMakeCurrent(0, 0);
    wglDeleteContext(hrc);

    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);

    return 0;
}

