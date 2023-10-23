//
//  WindowEx.cpp
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#include "WindowEx.h"

#include <ctime>
#include <thread>
using namespace std;
using namespace std::chrono;

#include <dwrite.h>

#pragma comment(lib, "D2d1.lib")
#pragma comment(lib, "DWrite.lib")
#pragma comment(lib, "Windowscodecs.lib")

/***********************WindowEx******************************/
using namespace WindowEx;

template <class Interface>
inline void SafeRelease(Interface** ppInterfaceToRelease);

#define BAD_HR(hr) FAILED(hr)

////////////////////////////////////////////////////////////////////////////////////////////////////////

bool DrawFactory::init(HWND hwnd, float dpiScale) {
    this->dpiScale = dpiScale;
    RECT ClientRect = {0};
    GetClientRect(hwnd, &ClientRect);
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
                                   &this->pD2DFactory);
    if (BAD_HR(hr)) {
        return false;
    }

    hr = this->pD2DFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(
            hwnd,
            D2D1::SizeU(ClientRect.right - ClientRect.left,
                        ClientRect.bottom - ClientRect.top),
            D2D1_PRESENT_OPTIONS_RETAIN_CONTENTS),
        &this->pRT);
    if (BAD_HR(hr)) {
        return false;
    }

    hr = DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED, __uuidof(this->pWriteFactory),
        reinterpret_cast<IUnknown**>(&this->pWriteFactory));
    if (BAD_HR(hr)) {
        return false;
    }

    hr = CoInitialize(nullptr);
    if (BAD_HR(hr)) {
        return false;
    }

    hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
                          IID_PPV_ARGS(&pImageFactory));
    if (BAD_HR(hr)) {
        return false;
    }

    return true;
}

void DrawFactory::release() {
    SafeRelease(&pD2DFactory);
    SafeRelease(&pRT);
    SafeRelease(&pBrush);
    SafeRelease(&pWriteFactory);
    SafeRelease(&pTextFormat);
    SafeRelease(&pImageFactory);
}

void DrawFactory::beginPaint() { pRT->BeginDraw(); }

bool DrawFactory::endPaint() {
    HRESULT hr = pRT->EndDraw();
    if (BAD_HR(hr)) {
        return false;
    }
    return true;
}

void DrawFactory::clear(const Color4B& color) {
    Color4F colorf(color);
    pRT->Clear(D2D1::ColorF(colorf.red, colorf.green, colorf.blue));
}

bool DrawFactory::setStringStyle(float fontSize, FontWeight weight,
                                 FontStyle style,
                                 const std::wstring& fontName) {
    SafeRelease(&this->pTextFormat);
    DWRITE_FONT_WEIGHT fontWeight;
    DWRITE_FONT_STYLE fontStyle;
    switch (weight) {
        case FontWeight::light:
            fontWeight = DWRITE_FONT_WEIGHT_LIGHT;
            break;
        case FontWeight::medium:
            fontWeight = DWRITE_FONT_WEIGHT_MEDIUM;
            break;
        case FontWeight::black:
            fontWeight = DWRITE_FONT_WEIGHT_BLACK;
            break;
        default:
            fontWeight = DWRITE_FONT_WEIGHT_LIGHT;
            break;
    }
    switch (style) {
        case FontStyle::normal:
            fontStyle = DWRITE_FONT_STYLE_NORMAL;
            break;
        case FontStyle::oblique:
            fontStyle = DWRITE_FONT_STYLE_OBLIQUE;
            break;
        case FontStyle::italic:
            fontStyle = DWRITE_FONT_STYLE_ITALIC;
            break;
        default:
            fontStyle = DWRITE_FONT_STYLE_NORMAL;
            break;
    }
    HRESULT hr = this->pWriteFactory->CreateTextFormat(
        fontName.c_str(), NULL, fontWeight, fontStyle,
        DWRITE_FONT_STRETCH_NORMAL, fontSize, L"", &pTextFormat);
    if (BAD_HR(hr)) {
        return false;
    }
    return true;
}

void DrawFactory::drawLine(const Vec2& start, const Vec2& end, LineStyle style,
                           const Color4B& color, float width) {
    D2D1_POINT_2F p1 = {start.x, start.y};
    D2D1_POINT_2F p2 = {end.x, end.y};
    ID2D1SolidColorBrush* brush = nullptr;
    colorToBrush(color, &brush);

    ID2D1StrokeStyle* _style = nullptr;
    D2D1_CAP_STYLE cap;
    switch (style) {
        case LineStyle::flat:
            cap = D2D1_CAP_STYLE_FLAT;
            break;
        case LineStyle::round:
            cap = D2D1_CAP_STYLE_ROUND;
            break;
        case LineStyle::triangle:
            cap = D2D1_CAP_STYLE_TRIANGLE;
            break;
        default:
            cap = D2D1_CAP_STYLE_FLAT;
            break;
    }
    HRESULT hr = pD2DFactory->CreateStrokeStyle(
        D2D1::StrokeStyleProperties(cap, cap, cap, D2D1_LINE_JOIN_MITER, 10.0f,
                                    D2D1_DASH_STYLE_SOLID, 0.0f),
        nullptr, 0, &_style);
    if (BAD_HR(hr)) {
        SafeRelease(&brush);
        SafeRelease(&_style);
    }

    pRT->DrawLine(p1, p2, brush, width, _style);
    SafeRelease(&brush);
    SafeRelease(&_style);
}

void DrawFactory::drawRectangel(const Vec2& leftTop, const Vec2& rightBottom,
                                const Color4B& color, float width) {
    D2D1_RECT_F rect = {leftTop.x, leftTop.y, rightBottom.x, rightBottom.y};

    ID2D1SolidColorBrush* brush = nullptr;
    colorToBrush(color, &brush);
    pRT->DrawRectangle(&rect, brush, width);
    SafeRelease(&brush);
}

void DrawFactory::drawRoundedRectangel(const Vec2& leftTop,
                                       const Vec2& rightBottom, float radius,
                                       const Color4B& color, float width) {
    D2D1_RECT_F rect = {leftTop.x, leftTop.y, rightBottom.x, rightBottom.y};

    D2D1_ROUNDED_RECT rRect = {rect, radius, radius};

    ID2D1SolidColorBrush* brush = nullptr;
    colorToBrush(color, &brush);
    pRT->DrawRoundedRectangle(&rRect, brush, width);
    SafeRelease(&brush);
}

void DrawFactory::drawEllipse(const Vec2& center, float rx, float ry,
                              const Color4B& color, float width) {
    D2D1_POINT_2F point = {center.x, center.y};
    D2D1_ELLIPSE ellipse = {point, rx, ry};

    ID2D1SolidColorBrush* brush = nullptr;
    colorToBrush(color, &brush);
    pRT->DrawEllipse(&ellipse, brush, width);
    SafeRelease(&brush);
}

void DrawFactory::drawDot(const Vec2& center, float radius,
                          const Color4B& color) {
    this->drawFillEllipse(center, radius, radius, color);
}

void DrawFactory::drawString(const Vec2& leftTop, const Vec2& rightBottom,
                             const std::wstring& text, const Color4B& color) {
    D2D1_RECT_F rect = {leftTop.x, leftTop.y, rightBottom.x, rightBottom.y};

    ID2D1SolidColorBrush* brush = nullptr;
    colorToBrush(color, &brush);
    pRT->DrawTextW(text.c_str(), text.length(), this->pTextFormat, rect, brush);
}
void DrawFactory::drawImage(const Vec2& leftTop, Image* img, float alpha) {
    D2D1_SIZE_F size = img->pBitmap->GetSize();
    D2D1_RECT_F rect = {leftTop.x, leftTop.y, leftTop.x + size.width,
                        leftTop.y + size.height};
    pRT->DrawBitmap(img->pBitmap, rect, alpha);
}

void DrawFactory::drawImage(const Vec2& leftTop, const Vec2& size, Image* Img,
                            float alpha) {
    D2D1_RECT_F rect = {leftTop.x, leftTop.y, leftTop.x + size.x,
                        leftTop.y + size.y};
    pRT->DrawBitmap(Img->pBitmap, rect, alpha);
}

void DrawFactory::setScale(const Vec2& center, float x, float y) {
    scaleCenter = center;
    scaleX = x;
    scaleY = y;
}

void DrawFactory::setRotation(const Vec2& center, float angle) {
    rotateCenter = center;
    rotateAngle = angle;
}

void DrawFactory::flushTransform() {
    D2D1::Matrix3x2F transMarix;
    transMarix.SetProduct(
        D2D1::Matrix3x2F::Scale(scaleX, scaleY,
                                D2D1::Point2F(scaleCenter.x, scaleCenter.y)),
        D2D1::Matrix3x2F::Rotation(
            rotateAngle, D2D1::Point2F(rotateCenter.x, rotateCenter.y)));
    pRT->SetTransform(transMarix);
}

void DrawFactory::drawFillRectangel(const Vec2& leftTop,
                                    const Vec2& rightBottom,
                                    const Color4B& color) {
    D2D1_RECT_F rect = {leftTop.x, leftTop.y, rightBottom.x, rightBottom.y};

    ID2D1SolidColorBrush* brush = nullptr;
    colorToBrush(color, &brush);
    pRT->FillRectangle(&rect, brush);
    SafeRelease(&brush);
}

void DrawFactory::drawFillRoundedRectangel(const Vec2& leftTop,
                                           const Vec2& rightBottom,
                                           float radius, const Color4B& color) {
    D2D1_RECT_F rect = {leftTop.x, leftTop.y, rightBottom.x, rightBottom.y};

    D2D1_ROUNDED_RECT rRect = {rect, radius, radius};

    ID2D1SolidColorBrush* brush = nullptr;
    colorToBrush(color, &brush);
    pRT->FillRoundedRectangle(&rRect, brush);
    SafeRelease(&brush);
}

void DrawFactory::drawFillEllipse(const Vec2& center, float rx, float ry,
                                  const Color4B& color) {
    D2D1_POINT_2F point = {center.x, center.y};
    D2D1_ELLIPSE ellipse = {point, rx, ry};

    ID2D1SolidColorBrush* brush = nullptr;
    colorToBrush(color, &brush);
    pRT->FillEllipse(&ellipse, brush);
    SafeRelease(&brush);
}

void DrawFactory::colorToBrush(const Color4B& color,
                               ID2D1SolidColorBrush** pBrush) {
    Color4F colorf(color);
    HRESULT hr = pRT->CreateSolidColorBrush(
        D2D1::ColorF(colorf.red, colorf.green, colorf.blue, colorf.alpha),
        pBrush);
}

void Image::release() { SafeRelease(&pBitmap); }

Size Image::size() {
    auto s = pBitmap->GetSize();
    return Size(s.width, s.height);
}

bool WindowEx::loadIMAGE(Image* img, DrawFactory* drawFactory,
                         const std::wstring& fileName) {
    IWICBitmapDecoder* decoder = nullptr;
    drawFactory->pImageFactory->CreateDecoderFromFilename(
        fileName.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad,
        &decoder);

    IWICBitmapFrameDecode* source = nullptr;
    decoder->GetFrame(0, &source);

    IWICFormatConverter* converter = nullptr;
    drawFactory->pImageFactory->CreateFormatConverter(&converter);

    converter->Initialize(source, GUID_WICPixelFormat32bppPBGRA,
                          WICBitmapDitherTypeNone, 0, 0.0f,
                          WICBitmapPaletteTypeMedianCut);

    drawFactory->pRT->CreateBitmapFromWicBitmap(converter, nullptr,
                                                &img->pBitmap);

    return true;
}

HWND WindowEx::InitGraph(const Size& size, WNDPROC WndProc,
                         const std::wstring& windowName) {
    WNDCLASSEXW wce = {0};

    wce.cbSize = sizeof(WNDCLASSEX);
    wce.cbClsExtra = 0;
    wce.cbWndExtra = 0;
    wce.hbrBackground = HBRUSH(COLOR_WINDOW + 1);
    wce.hCursor = NULL;
    wce.hIcon = NULL;
    wce.hIconSm = NULL;
    wce.hInstance = NULL;
    wce.lpfnWndProc = WndProc;
    wce.lpszClassName = windowName.c_str();
    wce.lpszMenuName = windowName.c_str();
    wce.style = CS_HREDRAW | CS_VREDRAW;

    BOOL nRet = RegisterClassExW(&wce);
    if (!nRet) {
        if (MessageBoxW(NULL, L"×¢²á´°¿Ú´íÎó!", windowName.c_str(),
                        MB_RETRYCANCEL | MB_ICONERROR) != IDRETRY)
            exit(0);
    }

    RECT rect;
    SetRect(&rect, 0, 0, (int)size.width, (int)size.height);
    AdjustWindowRect(
        &rect, WS_OVERLAPPEDWINDOW & (~WS_MAXIMIZEBOX) & (~WS_SIZEBOX), false);
    HWND hwnd =
        CreateWindowExW(0, windowName.c_str(), windowName.c_str(),
                        WS_OVERLAPPEDWINDOW & (~WS_MAXIMIZEBOX) & (~WS_SIZEBOX),
                        CW_USEDEFAULT, CW_USEDEFAULT, (rect.right - rect.left),
                        (rect.bottom - rect.top), NULL, NULL, NULL, NULL);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    return hwnd;
}

template <class Interface>
inline void SafeRelease(Interface** ppInterfaceToRelease) {
    if (*ppInterfaceToRelease != nullptr) {
        (*ppInterfaceToRelease)->Release();
        (*ppInterfaceToRelease) = nullptr;
    }
}

/***************************************************************/
