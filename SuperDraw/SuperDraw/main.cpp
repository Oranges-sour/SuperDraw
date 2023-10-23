#include "WindowEx.h"
using namespace WindowEx;

#include <chrono>
#include <mutex>
#include <string>
#include <thread>
using namespace std;
using namespace std::chrono;

#include <WinUser.h>
#pragma comment(lib, "User32.lib")
#include <windowsx.h>
#pragma comment(lib, "winmm.lib")

#include "Director.h"
#include "KeyboardHelper.h"
#include "TMath.h"
#include "sorce/AppDelegate.h"

//��Ϣ����
LRESULT CALLBACK windowCallBack(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

//��ѭ����ʱ��
void WINAPI mainLoopTimer(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1,
                          DWORD dw2);

//��ʼ��
void mainInit();

//�ͷ���Դ
void mainRelease();

//����DPI
void setDPI();

namespace {
//��ʱ��ID
MMRESULT timerID;

//Ӧ����Ϣ
AppInfo appInfo;

//��ʱ�õ�ʱ���
steady_clock::time_point time0, time1;

// DPI����
float dpiScale;

//��Դ���
DrawFactory* drawFactory = nullptr;
AppDelegate* appDelegate = nullptr;

thread* mainThread = nullptr;
mutex mainThreadMutex;

}  // namespace

// windows���ڳ������ڵ�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
                   _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

    mainThreadMutex.lock();
    mainInit();

    MSG msg = {0};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    mainThreadMutex.unlock();
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
        case WM_PAINT: {  //������Ϣ����
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

void mainInit() {
    //����ʱ�侫��
    timeBeginPeriod(1);

    setDPI();

    //�������
    appDelegate = new AppDelegate();

    appDelegate->init();
    appInfo = appDelegate->getWindowInfo();

    //��������
    HWND hwnd = InitGraph(appInfo.windowSize * dpiScale, windowCallBack,
                          appInfo.windowName);

    drawFactory = new DrawFactory();
    drawFactory->init(hwnd, dpiScale);

    Director::createInstance(drawFactory, appInfo.windowSize);
    appDelegate->startApp();

    //��¼��һ�ε�ʱ��
    time0 = steady_clock::now();

    mainThread = new thread([&]() {
        while (true) {
            time1 = steady_clock::now();
            float dt = duration_cast<duration<float>>(time1 - time0).count();
            time0 = time1;
            Director::instance->mainLoop(dt);
            if (mainThreadMutex.try_lock()) {
                mainThreadMutex.unlock();
                break;
            }
        }
    });

    SetCursor(LoadCursorW(NULL, IDC_ARROW));
}

void mainRelease() {
    //�ͷ���Դ
    mainThread->join();
    delete mainThread;

    timeEndPeriod(1);
    Director::destoryInstance();
    delete drawFactory;
    delete appDelegate;
}

void setDPI() {
    //��DPI����
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
    int dpi = GetDpiForSystem();
    dpiScale = float(dpi) / 96.0f;
}
