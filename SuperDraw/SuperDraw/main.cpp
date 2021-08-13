#include "WindowEx.h"
using namespace SuperDraw;

#include <chrono>
#include <string>
#include <thread>
using namespace std;
using namespace std::chrono;

#include <windowsx.h>
#pragma comment(lib, "winmm.lib")

#include "Director.h"
#include "KeyboardHelper.h"
#include "sorce/AppDelegate.h"

//��Ϣ����
LRESULT CALLBACK windowCallBack(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
//��ѭ����ʱ��
void WINAPI mainLoopTimer(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl,
                          DWORD dw2);
namespace {
MMRESULT timerID;
AppInfo appInfo;
}  // namespace

// windows���ڳ������ڵ�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
                   _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    //��ʼ��
    //����ʱ�侫��
    timeBeginPeriod(1);
    //�������
    DrawFactory* drawFactory = new DrawFactory();
    AppDelegate* appDelegate = new AppDelegate();

    appDelegate->init();
    appInfo = appDelegate->getWindowInfo();

    //��������
    HWND hwnd =
        InitGraph(appInfo.windowSize, windowCallBack, appInfo.windowName);
    drawFactory->init(hwnd);

    Director::createInstance(drawFactory, appInfo.windowSize);
    appDelegate->startApp();
    //������ѭ����ʱ��
    timerID =
        timeSetEvent(static_cast<int>(1000 / min(appInfo.frameRate, 1000)), 1,
                     (LPTIMECALLBACK)mainLoopTimer, DWORD(1), TIME_PERIODIC);

    SetCursor(LoadCursorW(NULL, IDC_ARROW));

    MSG msg = {0};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    //�ͷ���Դ
    timeEndPeriod(1);
    Director::destoryInstance();
    delete drawFactory;
    delete appDelegate;
    return 0;
}

LRESULT CALLBACK windowCallBack(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
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
                Vec2((float)GET_X_LPARAM(lp), (float)GET_Y_LPARAM(lp)));
            break;
        }
        case WM_LBUTTONUP: {
            Director::instance->LMouseUp(
                Vec2((float)GET_X_LPARAM(lp), (float)GET_Y_LPARAM(lp)));
            break;
        }
        case WM_RBUTTONDOWN: {
            Director::instance->RMouseDown(
                Vec2((float)GET_X_LPARAM(lp), (float)GET_Y_LPARAM(lp)));
            break;
        }
        case WM_RBUTTONUP: {
            Director::instance->RMouseUp(
                Vec2((float)GET_X_LPARAM(lp), (float)GET_Y_LPARAM(lp)));
            break;
        }
        case WM_MOUSEMOVE: {
            Director::instance->mouseMove(
                Vec2((float)GET_X_LPARAM(lp), (float)GET_Y_LPARAM(lp)));
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

void WINAPI mainLoopTimer(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl,
                          DWORD dw2)
{
    if (wTimerID == timerID) {
        Director::instance->mainLoop(1.0f / appInfo.frameRate);
    }
    return;
}