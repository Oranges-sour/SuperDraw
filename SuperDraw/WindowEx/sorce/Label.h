//
//  Label.h
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#ifndef __LABEL_H__
#define __LABEL_H__

#include <map>
#include <string>

#include "Node.h"
#include "Tools.h"
#include "WindowEx.h"

class Label : public Node {
public:
    /*
    @param rect: 坐标为左上角点
    */
    static Label* create(const std::wstring& font,
                         const std::wstring& text = std::wstring(L""),
                         float fontSize = 12.0f,
                         const Rect& rect = Rect(0, 0, 0, 0),
                         FontWeight weight = FontWeight::light,
                         FontStyle style = FontStyle::normal,
                         const Color4F& color = Color4F::WHITE);

public:
    Label(const std::wstring& font, const std::wstring& text, float fontSize,
          const Rect& rect, FontWeight weight, FontStyle style,
          const Color4F& color);
    virtual ~Label();
    virtual void draw(WindowEx::DrawFactory* drawFactory,
                      const Vec2& vecDelta) override;

    void setString(const std::wstring& text);
    void setWeight(FontWeight weight);

    void setColor(const Color4F& color);
    const Color4F& getColor() const;

    void setFontSize(float size);
    float getFontSize() const;

    void setRect(const Rect& rect);
    const Rect& getRect() const;

    void setPosition(float x, float y) override;
    void setPosition(const Vec2& pos) override;
    const Vec2& getPosition() const override;

    void setOpacity(float opacity) override;
    float getOpacity() override;

private:
    float fontSize = 0;
    std::wstring text;
    std::wstring font;
    Rect rect;
    FontWeight weight;
    FontStyle style;
    Color4F color;
};

#endif
