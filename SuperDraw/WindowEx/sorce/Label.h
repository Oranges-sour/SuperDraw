
#ifndef __LABEL_H__
#define __LABEL_H__

#include <map>
#include <string>

#include "Node.h"
#include "Tools.h"
#include "WindowEx.h"

class Label : public Node {
public:
    static Label* create(
        const std::wstring& font, const std::wstring& text = std::wstring(L""),
        int fontSize = 12, const Rect& rect = Rect(0, 0, 0, 0),
        SuperDraw::FontWeight weight = SuperDraw::FontWeight::normal,
        const SuperDraw::Color4F& color = SuperDraw::Color4F::WHITE);

public:
    Label(const std::wstring& font, const std::wstring& text, int fontSize,
          const Rect& rect, SuperDraw::FontWeight weight,
          const SuperDraw::Color4F& color);
    virtual ~Label();
    virtual void draw(DrawFactory* drawFactory, const Vec2& vecDelta) override;

    void setString(const std::wstring& text);
    void setWeight(SuperDraw::FontWeight weight);

    void setColor(const SuperDraw::Color4F& color);
    const SuperDraw::Color4F& getColor() const;

    void setFontSize(int size);
    int getFontSize() const;

    void setRect(const Rect& rect);
    const Rect& getRect() const;

private:
    void setPosition(float, float) override {}
    void setPosition(const Vec2&) override {}
    const Vec2& getPosition() const override { return Vec2::ZERO; }

private:
    int fontSize = 0;
    std::wstring text;
    std::wstring font;
    Rect rect;
    SuperDraw::FontWeight weight;
    SuperDraw::Color4F color;
};

#endif
