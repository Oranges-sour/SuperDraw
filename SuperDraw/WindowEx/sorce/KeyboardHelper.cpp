#include "KeyboardHelper.h"

#include <sstream>
using namespace std;

namespace {

const wstring letter[26] = {L"A", L"B", L"C", L"D", L"E", L"F", L"G",
                            L"H", L"I", L"J", L"K", L"L", L"M", L"N",
                            L"O", L"P", L"Q", L"R", L"S", L"T", L"U",
                            L"V", L"W", L"X", L"Y", L"Z"};
const wstring number[10] = {
    L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9",
};

const wstring F[12] = {L"F1", L"F2", L"F3", L"F4",  L"F5",  L"F6",
                       L"F7", L"F8", L"F9", L"F10", L"F11", L"F12"};
}  // namespace

const wstring KeyHelper::keyToString(WPARAM wp)
{
    if (wp == VK_BACK) {
        return L"backspace";
    }
    if (wp == VK_TAB) {
        return L"tab";
    }
    if (wp == VK_CLEAR) {
        return L"clear";
    }
    if (wp == VK_RETURN) {
        return L"enter";
    }
    if (wp == VK_SHIFT) {
        return L"shift";
    }
    if (wp == VK_CONTROL) {
        return L"ctrl";
    }
    if (wp == VK_MENU) {
        return L"alt";
    }
    if (wp == VK_PAUSE) {
        return L"pause";
    }
    if (wp == VK_CAPITAL) {
        return L"capsLock";
    }
    if (wp == VK_ESCAPE) {
        return L"esc";
    }
    if (wp == VK_SPACE) {
        return L"space";
    }
    if (wp == VK_PRIOR) {
        return L"pageUp";
    }
    if (wp == VK_NEXT) {
        return L"pageDown";
    }
    if (wp == VK_END) {
        return L"end";
    }
    if (wp == VK_HOME) {
        return L"home";
    }
    if (wp == VK_LEFT) {
        return L"leftArrow";
    }
    if (wp == VK_UP) {
        return L"upArrow";
    }
    if (wp == VK_RIGHT) {
        return L"rightArrow";
    }
    if (wp == VK_DOWN) {
        return L"downArrow";
    }
    if (wp >= 0x30 && wp <= 0x39) {
        return number[wp - 0x30];
    }
    if (wp >= 0x41 && wp <= 0x5A) {
        return letter[wp - 0x41];
    }
    if (wp >= VK_F1 && wp <= VK_F12) {
        return F[wp - VK_F1];
    }
    if (wp == VK_OEM_1) {
        return L";";
    }
    if (wp == VK_OEM_2) {
        return L"/";
    }
    if (wp == VK_OEM_3) {
        return L"~";
    }
    if (wp == VK_OEM_4) {
        return L"[";
    }
    if (wp == VK_OEM_5) {
        return L"|";
    }
    if (wp == VK_OEM_6) {
        return L"]";
    }
    if (wp == VK_OEM_7) {
        return L"'";
    }
    if (wp == VK_OEM_PLUS) {
        return L"+";
    }
    if (wp == VK_OEM_COMMA) {
        return L",";
    }
    if (wp == VK_OEM_MINUS) {
        return L"-";
    }
    if (wp == VK_OEM_PERIOD) {
        return L".";
    }    
    return L"";
}
