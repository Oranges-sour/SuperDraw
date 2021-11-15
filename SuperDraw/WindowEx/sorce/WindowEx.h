//
//  WindowEx.h
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#ifndef __WINDOWEX_H__
#define __WINDOWEX_H__

#include <D2d1.h>
#include <Windows.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#include <chrono>
#include <string>

#ifdef _WIN64
#error Only on x86!
#endif

#ifndef __cplusplus
#error Only on C++!
#endif

#include "Tools.h"

/*基于Direct2D的绘图扩展**************************************************/

namespace WindowEx {
class Image;
class DrawFactory;

bool loadIMAGE(Image* img, DrawFactory* drawFactory,
               const std::wstring& fileName);

class Image {
public:
    void release();
    Size size();

private:
    friend bool loadIMAGE(Image* img, DrawFactory* drawFactory,
                          const std::wstring& fileName);
    friend class DrawFactory;
    ID2D1Bitmap* pBitmap = nullptr;
};

class DrawFactory {
public:
    DrawFactory(DrawFactory&) = delete;
    DrawFactory(){};
    virtual ~DrawFactory(){};
    void release();
    bool init(HWND hwnd, float dpiScale);

public:
    void beginPaint();
    bool endPaint();
    void clear(const Color4B& color = Color4B::WHITE);

    bool setStringStyle(float fontSize, FontWeight weight, FontStyle style,
                        const std::wstring& fontName);

    /*绘图普通函数****************************/

    void drawLine(const Vec2& start, const Vec2& end,
                  LineStyle style = LineStyle::flat,
                  const Color4B& color = Color4B::WHITE, float width = (1.0f));

    void drawRectangel(const Vec2& leftTop, const Vec2& rightBottom,
                       const Color4B& color = Color4B::WHITE,
                       float width = (1.0f));
    void drawFillRectangel(const Vec2& leftTop, const Vec2& rightBottom,
                           const Color4B& color = Color4B::WHITE);

    void drawRoundedRectangel(const Vec2& leftTop, const Vec2& rightBottom,
                              float radius = (0.0f),
                              const Color4B& color = Color4B::WHITE,
                              float width = (1.0f));
    void drawFillRoundedRectangel(const Vec2& leftTop, const Vec2& rightBottom,
                                  float radius = (0.0f),
                                  const Color4B& color = Color4B::WHITE);

    void drawEllipse(const Vec2& center, float rx, float ry,
                     const Color4B& color = Color4B::WHITE,
                     float width = (1.0f));
    void drawFillEllipse(const Vec2& center, float rx, float ry,
                         const Color4B& color = Color4B::WHITE);

    void drawDot(const Vec2& center, float radius = (1.0f),
                 const Color4B& color = Color4B::WHITE);

    void drawString(const Vec2& leftTop, const Vec2& rightBottom,
                    const std::wstring& text,
                    const Color4B& color = Color4B::WHITE);

    void drawImage(const Vec2& leftTop, Image* img, float alpha = (1.0f));
    void drawImage(const Vec2& leftTop, const Vec2& size, Image* Img,
                   float alpha = (1.0f));

    //设置缩放
    void setScale(const Vec2& center, float x, float y);
    //设置旋转
    void setRotation(const Vec2& center, float angle);
    //应用缩放与旋转
    void flushTransform();

private:
    ID2D1Factory* pD2DFactory = nullptr;
    ID2D1HwndRenderTarget* pRT = nullptr;
    ID2D1SolidColorBrush* pBrush = nullptr;
    IDWriteFactory* pWriteFactory = nullptr;
    IDWriteTextFormat* pTextFormat = nullptr;
    IWICImagingFactory* pImageFactory = nullptr;
    void colorToBrush(const Color4B& color, ID2D1SolidColorBrush** pBrush);

    friend bool loadIMAGE(Image* img, DrawFactory* drawFactory,
                          const std::wstring& fileName);

    Vec2 scaleCenter;
    float scaleX = 0;
    float scaleY = 0;
    float dpiScale = 1.0f;

    Vec2 rotateCenter;
    float rotateAngle = 0;
};

//其他函数
HWND InitGraph(const Size& size, WNDPROC WndProc,
               const std::wstring& windowName);
}  // namespace WindowEx

/************************************************************************/

#endif  //!_WindowEx_H_
