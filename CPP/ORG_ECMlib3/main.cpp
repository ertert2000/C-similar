#include <windows.h>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const float PI = 3.14159265358979323846f;
const float MIN_X = PI;
const float MAX_X = 11 * PI;

bool isMousePressed = false;
int prevMouseX = 0;
int prevMouseY = 0;

float minX = MIN_X;
float maxX = MAX_X;
float minY = -5.0f;
float maxY = 5.0f;

float func(float x) 
{
    return pow(sin(x / 4), 2) - sqrt(x);
}

int scaleX(float x, float minX, float maxX, int width) 
{
    return (int)((x - minX) / (maxX - minX) * width);
}

int scaleY(float y, float minY, float maxY, int height) 
{
    return height - (int)((y - minY) / (maxY - minY) * height);
}

float FindMaxValue(float minX, float maxX) 
{
    float maxValue = func(minX);

    for (float x = minX; x <= maxX; x += (maxX - minX) / 100) 
    {
        float y = func(x);
        if (y > maxValue)
            maxValue = y;
    }
    return maxValue;
}

void DrawAxesAndLabels(HDC hdc, RECT rect, float minX, float maxX, float minY, float maxY) 
{
    int zeroX = scaleX(0, minX, maxX, rect.right);
    int zeroY = scaleY(0, minY, maxY, rect.bottom);

    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, hPen);

    MoveToEx(hdc, 0, zeroY, NULL);
    LineTo(hdc, rect.right, zeroY);

    MoveToEx(hdc, zeroX, 0, NULL);
    LineTo(hdc, zeroX, rect.bottom);

    HFONT hFont = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Arial");
    SelectObject(hdc, hFont);
    TextOut(hdc, rect.right - 30, zeroY + 10, L"X", 1);

    TextOut(hdc, zeroX + 10, 10, L"Y", 1);

    for (float x = minX; x <= maxX; x += (maxX - minX) / 10) 
    {
        int px = scaleX(x, minX, maxX, rect.right);

        MoveToEx(hdc, px, zeroY - 5, NULL);
        LineTo(hdc, px, zeroY + 5);

        std::wostringstream ossX;
        ossX << std::fixed << std::setprecision(2) << x;
        std::wstring textX = ossX.str();
        TextOut(hdc, px - 15, zeroY + 10, textX.c_str(), textX.size());
    }

    for (float y = minY; y <= maxY; y += (maxY - minY) / 10) 
    {
        int py = scaleY(y, minY, maxY, rect.bottom);

        MoveToEx(hdc, zeroX - 5, py, NULL);
        LineTo(hdc, zeroX + 5, py);

        std::wostringstream ossY;
        ossY << std::fixed << std::setprecision(2) << y;
        std::wstring textY = ossY.str();
        TextOut(hdc, zeroX + 10, py - 8, textY.c_str(), textY.size());
    }

    DeleteObject(hPen);
    DeleteObject(hFont);
}

void DrawGraph(HDC hdc, RECT rect, float minX, float maxX, float minY, float maxY) 
{
    HPEN hGraphPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    SelectObject(hdc, hGraphPen);

    MoveToEx(hdc, scaleX(minX, minX, maxX, rect.right), scaleY(func(minX), minY, maxY, rect.bottom), NULL);

    for (float x = minX; x <= maxX; x += (maxX - minX) / 100) 
    {
        int px = scaleX(x, minX, maxX, rect.right);
        int py = scaleY(func(x), minY, maxY, rect.bottom);
        LineTo(hdc, px, py);
    }

    DeleteObject(hGraphPen);
}

void HandleMouseMove(LPARAM lParam) 
{
    if (isMousePressed) 
    {
        int mouseX = LOWORD(lParam);
        int mouseY = HIWORD(lParam);

        int deltaX = mouseX - prevMouseX;
        int deltaY = mouseY - prevMouseY;

        float xRange = maxX - minX;
        float yRange = maxY - minY;

        minX -= deltaX * xRange / WINDOW_WIDTH;
        maxX -= deltaX * xRange / WINDOW_WIDTH;
        minY += deltaY * yRange / WINDOW_HEIGHT;
        maxY += deltaY * yRange / WINDOW_HEIGHT;

        prevMouseX = mouseX;
        prevMouseY = mouseY;

    }
}

void HandleMouseButtonDown(LPARAM lParam) 
{
    isMousePressed = true;

    prevMouseX = LOWORD(lParam);
    prevMouseY = HIWORD(lParam);
}

void HandleMouseButtonUp() 
{
    isMousePressed = false;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
    static float maxVal = FindMaxValue(minX, maxX);
    std::string text = "Max value: " + std::to_string(maxVal);
    switch (uMsg) 
    {
    case WM_PAINT:
        HFONT hFont = CreateFont(
            20,
            0,
            0,
            0,
            FW_NORMAL,
            FALSE,
            FALSE,
            FALSE,
            ANSI_CHARSET,
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_DONTCARE,
            TEXT("Arial")
        );
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT rect;
        GetClientRect(hwnd, &rect);
        FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
        SelectObject(hdc, hFont);
        TextOutA(hdc, 50, 50, text.c_str(), text.length());
        DrawAxesAndLabels(hdc, rect, minX, maxX, minY, maxY);
        DrawGraph(hdc, rect, minX, maxX, minY, maxY);
        EndPaint(hwnd, &ps);
        break;

    case WM_LBUTTONDOWN:
        HandleMouseButtonDown(lParam);
        break;

    case WM_LBUTTONUP:
        HandleMouseButtonUp();
        break;

    case WM_MOUSEMOVE:
        HandleMouseMove(lParam);
        InvalidateRect(hwnd, NULL, TRUE);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int main() 
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WindowProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"GraphWindowClass", NULL };
    RegisterClassEx(&wc);

    HWND hwnd = CreateWindow(wc.lpszClassName, L"Graph of a function", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, wc.hInstance, NULL);
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) 
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
