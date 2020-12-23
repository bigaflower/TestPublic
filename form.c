#include <windows.h>

#define IDB_1 1001

#define IDM_OPT1 40001
#define IDM_OPT2 40002
#define IDM_OPT3 40003

#define IDM_OPT_ABOUT 40010

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); //回调函数

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow)
{
    CHAR ClassName[] = "WinMainClass"; //窗体类名
    WNDCLASS wc;                       //窗体类
    HWND hwnd;                         //窗体句柄

    //窗口类结构
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = MainWndProc; //窗口回调函数指针
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;                   //实例句柄
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //默认图标
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //默认指针
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);  //默认背景颜色
    wc.lpszMenuName = NULL;
    wc.lpszClassName = ClassName; //窗口类名

    //注册窗口类
    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, "Failed to register window class !", "ERROR", MB_ICONERROR);
        return 0;
    }

    //创建窗口
    int style = WS_OVERLAPPEDWINDOW;
    char title[] = "TestForm";
    hwnd = CreateWindow(ClassName, title, style, 400, 200, 800, 600, NULL, NULL, hInstance, NULL);
    if (hwnd == NULL)
    {
        MessageBox(NULL, "Failed to create window !", "ERROR", MB_ICONERROR);
        return 0;
    }

    //创建菜单
    HMENU hMenu = CreateMenu(); //主菜单, 水平

    HMENU hMenuPopFile = CreateMenu();                         //下拉的菜单, 垂直
    AppendMenu(hMenu, MF_POPUP, (UINT64)hMenuPopFile, "File"); //64位版本使用UINT64
    AppendMenu(hMenuPopFile, MF_STRING, IDM_OPT1, "New");
    AppendMenu(hMenuPopFile, MF_STRING, IDM_OPT2, "Open");
    AppendMenu(hMenuPopFile, MF_STRING, IDM_OPT3, "Exit");

    HMENU hMenuPopHelp = CreateMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT64)hMenuPopHelp, "Help");
    AppendMenu(hMenuPopHelp, MF_STRING, IDM_OPT_ABOUT, "About");

    SetMenu(hwnd, hMenu); //设置菜单

    //创建控件
    CreateWindow("static", "Test Text", WS_CHILD | WS_VISIBLE, 300, 200, 120, 40, hwnd, (HMENU)stc1, hInstance, NULL);
    CreateWindow("button", "Hello World", WS_CHILD | WS_VISIBLE | BS_FLAT, 300, 240, 100, 40, hwnd, (HMENU)IDB_1, hInstance, NULL);
    //显示、更新窗口
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    //消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    //控件消息
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDB_1:
            MessageBox(hwnd, "Hello World!", "hello", MB_OK | MB_ICONINFORMATION);
            break;
        case IDM_OPT3:
            DestroyWindow(hwnd);
            break;
        case IDM_OPT_ABOUT:
            MessageBox(hwnd, "This is a Win32 GUI project by MinGW !\nAuthor : Dr.zomboss", "About", MB_OK | MB_ICONINFORMATION);
            break;
        default:
            break;
        }
    //窗体创建（在显示之前）
    case WM_CREATE:
        break;
    //按下关闭按钮
    case WM_CLOSE:
        //if (MessageBox(hwnd, "Are you sure ?", "question", MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
        DestroyWindow(hwnd);
        break;
    //销毁窗口
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
        break;
    //默认操作
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
        break;
    }
}
