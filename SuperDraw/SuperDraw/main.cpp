#include "WindowEx.h"
using namespace WindowEx;

#include <chrono>
#include <string>
#include <thread>
using namespace std;
using namespace std::chrono;

#include <ShellScalingApi.h>
#pragma comment(lib, "Shcore.lib")
#include <windowsx.h>
#pragma comment(lib, "winmm.lib")

#include "Director.h"
#include "KeyboardHelper.h"
#include "TMath.h"
#include "sorce/AppDelegate.h"

//消息函数
LRESULT CALLBACK windowCallBack(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

//主循环定时器
void WINAPI mainLoopTimer(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1,
                          DWORD dw2);

//初始化
void mainInit();

//释放资源
void mainRelease();

//设置DPI
void setDPI();

namespace {
//定时器ID
MMRESULT timerID;

//应用信息
AppInfo appInfo;

//计时用的时间刻
steady_clock::time_point time0, time1;

// DPI缩放
float dpiScale;

//资源句柄
DrawFactory* drawFactory = nullptr;
AppDelegate* appDelegate = nullptr;

}  // namespace

// windows窗口程序的入口点
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
                   _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
    mainInit();

    MSG msg = {0};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    mainRelease();

    return 0;
}

LRESULT CALLBACK windowCallBack(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_KEYDOWN: {
            Director::instance->keyDown(KeyHelper::keyToString(wp));
            break;
        }
        case WM_KEYUP: {
            Director::instance->keyUp(KeyHelper::keyToString(wp));
            break;
        }
        case WM_LBUTTONDOWN: {
            Director::instance->LMouseDown(
                Vec2(float(GET_X_LPARAM(lp)), float(GET_Y_LPARAM(lp))) /
                dpiScale);
            break;
        }
        case WM_LBUTTONUP: {
            Director::instance->LMouseUp(
                Vec2(float(GET_X_LPARAM(lp)), float(GET_Y_LPARAM(lp))) /
                dpiScale);
            break;
        }
        case WM_RBUTTONDOWN: {
            Director::instance->RMouseDown(
                Vec2(float(GET_X_LPARAM(lp)), float(GET_Y_LPARAM(lp))) /
                dpiScale);
            break;
        }
        case WM_RBUTTONUP: {
            Director::instance->RMouseUp(
                Vec2(float(GET_X_LPARAM(lp)), float(GET_Y_LPARAM(lp))) /
                dpiScale);
            break;
        }
        case WM_MOUSEMOVE: {
            Director::instance->mouseMove(
                Vec2(float(GET_X_LPARAM(lp)), float(GET_Y_LPARAM(lp))) /
                dpiScale);
            break;
        }
        case WM_ERASEBKGND: {
            return TRUE;
            break;
        }
        case WM_PAINT: {  //绘制消息处理
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
            break;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

void WINAPI mainLoopTimer(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1,
                          DWORD dw2) {
    if (wTimerID == timerID) {
        time1 = steady_clock::now();
        float dt = duration_cast<duration<float>>(time1 - time0).count();
        time0 = time1;
        Director::instance->mainLoop(dt);
    }
    return;
}

void mainInit() {
    //设置时间精度
    timeBeginPeriod(1);

    setDPI();

    //创建组件
    appDelegate = new AppDelegate();

    appDelegate->init();
    appInfo = appDelegate->getWindowInfo();

    //创建窗口
    HWND hwnd = InitGraph(appInfo.windowSize * dpiScale, windowCallBack,
                          appInfo.windowName);

    drawFactory = new DrawFactory();
    drawFactory->init(hwnd, dpiScale);

    Director::createInstance(drawFactory, appInfo.windowSize);
    appDelegate->startApp();

    //记录第一次的时间
    time0 = steady_clock::now();
    //启动主循环定时器
    timerID =
        timeSetEvent(TMath::floatRoundInt(1000 / min(appInfo.frameRate, 1000)),
                     1, LPTIMECALLBACK(mainLoopTimer), DWORD(1), TIME_PERIODIC);

    SetCursor(LoadCursorW(NULL, IDC_ARROW));
}

void mainRelease() {
    //释放资源
    timeEndPeriod(1);
    Director::destoryInstance();
    delete drawFactory;
    delete appDelegate;
}

void setDPI() {
    //高DPI适配
    SetProcessDpiAwareness(PROCESS_SYSTEM_DPI_AWARE);
    auto monitor = MonitorFromPoint(POINT{1, 1}, MONITOR_DEFAULTTONULL);
    UINT dpiX, dpiY;
    GetDpiForMonitor(monitor, MDT_EFFECTIVE_DPI, &dpiX, &dpiY);
    dpiScale = float(dpiX) / 96.0f;
}
