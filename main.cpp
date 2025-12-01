#include "WAVFile.h"
#include <iostream>

int main()
{
	WAVFile wavfile("test.wav");
	wavfile.AddAudioData(440, 4);
	wavfile.WriteToFile();
	std::cout << "written to file " << std::endl;
}


/////// CODE FOR SHOWING BMP ON SCREEN
//#include <windows.h>
//#include "Image.h"
//
//#define BMP_IMAGEPATH "bmp_24.bmp"
//#define BMP_BITCOUNT 24
//
//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//
//int main()
//{
//    // 1. Define and Register Window Class
//    const wchar_t CLASS_NAME[] = L"MyWindowClass";
//
//    WNDCLASSEX wc = {};
//    wc.cbSize = sizeof(WNDCLASSEX);
//    wc.lpfnWndProc = WindowProc; // Pointer to the window procedure
//    wc.hInstance = GetModuleHandle(nullptr);
//    wc.lpszClassName = CLASS_NAME;
//    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//
//    if (!RegisterClassEx(&wc))
//    {
//        MessageBox(NULL, L"Window Registration Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
//        return 0;
//    }
//
//    // 2. Create the Window
//    HWND hwnd = CreateWindowEx(
//        0,                      // Optional window styles
//        CLASS_NAME,             // Window class name
//        L"Window",     // Window title
//        WS_OVERLAPPEDWINDOW,    // Window style
//        CW_USEDEFAULT, CW_USEDEFAULT, // Position
//        400, 300,               // Size
//        NULL,                   // Parent window
//        NULL,                   // Menu
//        wc.hInstance,              // Instance handle
//        NULL                    // Additional application data
//    );
//
//    if (hwnd == NULL)
//    {
//        MessageBox(NULL, L"Window Creation Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
//        return 0;
//    }
//
//    // 3. Show and Update the Window
//    ShowWindow(hwnd, 1);
//    UpdateWindow(hwnd);
//
//    BMPImage img(BMP_IMAGEPATH);
//    auto pixels = img.GetPixels();
//
//    BITMAPINFO bmi = {};
//    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
//    bmi.bmiHeader.biWidth = img._width;
//    bmi.bmiHeader.biHeight = img._height; // top-down
//    bmi.bmiHeader.biPlanes = 1;
//    bmi.bmiHeader.biBitCount = BMP_BITCOUNT;
//    bmi.bmiHeader.biCompression = BI_RGB;
//
//
//    // Main message loop
//    MSG msg = {};
//    HDC hdc = GetDC(hwnd);
//
//    // Draw once
//    StretchDIBits(hdc,
//        0, 0, img._width, img._height,
//        0, 0, img._width, img._height,
//        pixels.data(), &bmi, DIB_RGB_COLORS, SRCCOPY
//    );
//
//    while (GetMessage(&msg, NULL, 0, 0)) {
//        TranslateMessage(&msg);
//        DispatchMessage(&msg);
//    }
//
//    ReleaseDC(hwnd, hdc);
//    return 0;
//}
//
//// Window Procedure function
//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    switch (uMsg)
//    {
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        return 0;
//
//    case WM_PAINT:
//    {
//        PAINTSTRUCT ps;
//        HDC hdc = BeginPaint(hwnd, &ps);
//        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
//        EndPaint(hwnd, &ps);
//    }
//    return 0;
//
//    default:
//        return DefWindowProc(hwnd, uMsg, wParam, lParam);
//    }
//}
