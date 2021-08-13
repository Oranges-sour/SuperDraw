//
//  WindowEx.h
//
//  Created by Oranges.
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

/*����Direct2D�Ļ�ͼ��չ**************************************************/

namespace SuperDraw {
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

enum class FontWeight  //����Ĵ�ϸ
{
    light = 300,   //ϸ--Ĭ��
    normal = 500,  //��ͨ
    black = 900    //��
};

enum class LineStyle  //�ߵ����˵����ʽ
{
    flat,      //ƽ��--Ĭ��
    round,     //Բ��
    triangle,  //����
};

class Color4B;
class Color4F;

class Color4B {
public:
    Color4B(int r, int g, int b, int a);
    Color4B(const Color4B& other);
    Color4B(const Color4F& other);

    int red;
    int green;
    int blue;
    int alpha;

public:
    static const Color4B WHITE;
};

class Color4F {
public:
    Color4F(float r, float g, float b, float a);
    Color4F(const Color4F& other);
    Color4F(const Color4B& other);

    float red;
    float green;
    float blue;
    float alpha;

public:
    static const Color4F WHITE;
};

class DrawFactory {
public:
    DrawFactory(DrawFactory&) = delete;
    DrawFactory(){};
    virtual ~DrawFactory(){};
    void release();
    bool init(HWND hwnd);

public:
    void beginPaint();
    bool endPaint();
    void clear(const Color4B& color = Color4B::WHITE);

    bool setStringStyle(int fontSize, FontWeight weight,
                        const std::wstring& fontName);

    /*��ͼ��ͨ����****************************/

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

    //��������
    void setScale(const Vec2& center, float x, float y);
    //������ת
    void setRotation(const Vec2& center, float angle);
    //Ӧ����������ת
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

    Vec2 rotateCenter;
    float rotateAngle = 0;
};

//��������
HWND InitGraph(const Size& size, WNDPROC WndProc,
               const std::wstring& windowName);
}  // namespace SuperDraw

/************************************************************************/

#endif  //!_WindowEx_H_
