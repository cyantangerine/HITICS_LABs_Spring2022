#define _CRT_SECURE_NO_WARNINGS 1

#include <windows.h>
#include<strsafe.h>
//#include"sysmets.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
//主函数
// 四个参数：
//hInstance : 程序当前实例的句柄(handle to current instance)，以后随时可以用GetModuleHandle(0)来获得
//hPrevInstance : 前一个实例的句柄(handle to previous instance)，在Win32中，每一个进程都有一个独立的4G地址空间，从0到2G属于进程私有，对其他进程来说是不可见的。所以，在Win32中，hPrevInstance总是为NULL。
//szCmdLine : 指向以 / 0结尾的命令行，不包括EXE本身的文件名(pointer to command line)，以后随时可以用GetCommandLine()来获取完整的命令行。
//iCmdShow : 指明应该以什么方式显示主窗口(show state of window)。

{
    static TCHAR szAppName[] = TEXT("MyWindows");
    HWND hwnd;//句柄
    MSG msg;//消息
    WNDCLASS wndclass;//定义窗口类结构
    HBRUSH hCulorBrush = CreateSolidBrush(RGB(200, 200, 200));//设定背景颜色

    //结构成员：
    wndclass.style = CS_HREDRAW | CS_VREDRAW; //窗口类型
    wndclass.lpfnWndProc = WndProc;  //窗口过程（必须是回调函数）
    wndclass.cbClsExtra = 0;//预留的额外空间，一般为0
    wndclass.cbWndExtra = 0;//预留的额外空间，一般为0
    wndclass.hInstance = hInstance;//应用程序的实例句柄
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//为所有基于该窗口类的窗口设定一个图标
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);//为所有基于该窗口类的窗口设定一个鼠标指针
    //wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);//指定窗口背景色
    wndclass.hbrBackground = hCulorBrush;//指定窗口背景色
    wndclass.lpszMenuName = NULL; //指定窗口菜单
    wndclass.lpszClassName = szAppName; //指定窗口类名

    //注册窗口类
    if (!RegisterClass(&wndclass))
        /*  RegisterClass：注册在随后调用CreateWindow函数和CreateWindowEx函数中使用的窗口类。
          参数为lpWndClass，指向一个WNDCLASS结构的指针
          返回值：ATOM的宏定义
          typedef WORD ATOM;
          typedef unsigned short WORD;
          关于RegisterClassEx:参数lpwcx指向一个WNDCLASSEX结构的指针如果函数成功，返回这个窗口类型的标识号；
          如果函数失败，返回值为0。若想获得更多错误信息，请调用GetLastError函数。*/
    {
        MessageBox(NULL, TEXT("这个程序需要在Windows系统执行！"), szAppName, MB_ICONERROR);
        return 0;
    }
    //实例化创建窗口
    hwnd = CreateWindow(szAppName,// 窗口类名称
        TEXT("中年人学C语言Windows程序设计"),// 窗口标题
        WS_OVERLAPPEDWINDOW|WS_VSCROLL,// 窗口风格，或称窗口格式
        CW_USEDEFAULT,// 初始 x 坐标
        CW_USEDEFAULT, // 初始 y 坐标
        CW_USEDEFAULT,// 初始 x 方向尺寸
        CW_USEDEFAULT,// 初始 y 方向尺寸
        NULL,// 父窗口句柄
        NULL,// 窗口菜单句柄
        hInstance,// 程序实例句柄
        NULL);// 创建参数

    /*_In_说明该参数是输入的，_opt_说明该参数是可选参数
        函数成功返回窗口句柄，否则返回NULL*/

        //显示窗口
    ShowWindow(hwnd, iCmdShow);
    /* 第一次调用时应使用WinMain的参数nCmdShow作为参数
         如果窗口之前可见，则返回非0否则返回0*/

         //更新窗口
    UpdateWindow(hwnd);
    /* 绕过消息队列直接向窗口过程发送WM_PAINT消息
         函数调用成功返回非0*/

         //消息循环
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    /*作用：从当前线程的消息队列里取出一个消息并放入MSG结构中，不能获得其他线程的消息
        若消息队列为空，函数会一直等待到有消息到来才有返回值
        返回值：
        函数出现错误则返回 - 1，
        获得WM_QUIT消息返回0
        否则返回非0*/

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
/*回调函数
//参数：
hwnd : 窗口句柄
message : 消息ID
wParam和lParam：消息参数*/
    //int i;
    //size_t j;
    HDC hdc;;//定义设备环境句柄  
    static TCHAR  szBuffer[128];
    //TEXTMETRIC tm;
   // SCROLLINFO si;
    PAINTSTRUCT ps;
    RECT rect;
    size_t iStrLength;
    static int cxChar, cyChar, yVscrollPos, cxClient, cyClient, yPage,cxCaps, FirstLine, LastLine;
    switch (message)
    {

        case WM_SIZE://窗体大小改变
            hdc = GetDC(hWnd);
            //GetClientRect(hwnd, &rect);
            cxClient = LOWORD(lParam);//当前x像素
            cyClient = HIWORD(lParam);//当前y像素
            StringCchPrintf(szBuffer, 128, TEXT("当前客户区的分辨率:%d * %d px"), cxClient, cyClient);
            StringCchLength(szBuffer, 128, &iStrLength);
            SetTextAlign(hdc, TA_CENTER | TA_TOP);
            TextOut(hdc, cxClient / 2, 0, szBuffer, iStrLength);
            ReleaseDC(hWnd, hdc);
            return 0;

        case WM_PAINT://窗口绘画：点
        {
            int x,xLast;
            HDC hdc = BeginPaint(hWnd, &ps);//函数为指定窗口进行绘画作准备，并用将和绘画有关的信息填充到一个 PAINTSTRUCT 结构中。
            GetClientRect(hWnd, &rect);//获取客户区信息. 函数用于获取窗口客户区的坐标，客户区坐标指定客户区的左上角和右下角。
            xLast = rect.right;//获得客户区最右侧坐标
            for (x = 0; x < xLast; x++)//循环x轴的坐标
            {
                SetPixel(hdc, x, 100, RGB(255, 0, 0));//在客户区上画点
            }
            EndPaint(hWnd, &ps);
            return 0;
        } 
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    return 0;
}

