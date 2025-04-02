#include <windows.h>
#include <iostream>
#include <vector>

struct MonitorInfo 
{
    int index;
    RECT rect;
};

std::vector<MonitorInfo> monitors;

BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) 
{
    MonitorInfo info;
    info.index = monitors.size();
    info.rect = *lprcMonitor;
    monitors.push_back(info);
    return TRUE;
}

void DrawRectangleOnMonitor(int monitorIndex, int x, int y, int width, int height, int thickness, COLORREF color) 
{
    if (monitorIndex < 0 || monitorIndex >= monitors.size()) 
    {
        std::cerr << "Неверный индекс монитора!" << std::endl;
        return;
    }

    RECT monitorRect = monitors[monitorIndex].rect;

    HDC hdc = GetDC(NULL);

    HPEN hPen = CreatePen(PS_SOLID, thickness, color);
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    MoveToEx(hdc, monitorRect.left + x, monitorRect.top + y, NULL);
    LineTo(hdc, monitorRect.left + x + width, monitorRect.top + y);
    LineTo(hdc, monitorRect.left + x + width, monitorRect.top + y + height);
    LineTo(hdc, monitorRect.left + x, monitorRect.top + y + height);
    LineTo(hdc, monitorRect.left + x, monitorRect.top + y);

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);

    ReleaseDC(NULL, hdc);
}

int main() 
{
    EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, 0);

    std::cout << "Найдено мониторов: " << monitors.size() << std::endl;
    for (size_t i = 0; i < monitors.size(); i++) {

        std::cout << "Монитор " << i << ": "
            << "Left = " << monitors[i].rect.left << ", "
            << "Top = " << monitors[i].rect.top << ", "
            << "Right = " << monitors[i].rect.right << ", "
            << "Bottom = " << monitors[i].rect.bottom << std::endl;
    }

    int monitorIndex;
    std::cout << "Введите индекс монитора (0-" << monitors.size() - 1 << "): ";
    std::cin >> monitorIndex;

    int x = 284;
    int y = 337; 
    int width = 270;  
    int height = 146; 
    int thickness = 1;  
    COLORREF color = RGB(0, 255, 0);

    while (true)
        DrawRectangleOnMonitor(monitorIndex, x, y, width, height, thickness, color);

    return 0;
}