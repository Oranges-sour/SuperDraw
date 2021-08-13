
#include "Label.h"

#include "WindowEx.h"
using namespace SuperDraw;
#include "Director.h"
using namespace std;

Label* Label::create(const std::wstring& font, const std::wstring& text,
                     int fontSize, const Rect& rect,
                     SuperDraw::FontWeight weight,
                     const SuperDraw::Color4F& color)
{
    auto la =
        new (std::nothrow) Label{font, text, fontSize, rect, weight, color};
    if (la) {
        la->autorelease();
        return la;
    }
    return nullptr;
}

Label::Label(const std::wstring& font, const std::wstring& text, int fontSize,
             const Rect& rect, SuperDraw::FontWeight weight,
             const SuperDraw::Color4F& color)
    : font(font),
      text(text),
      fontSize(fontSize),
      rect(rect),
      weight(weight),
      color(color)
{
}

Label::~Label() {}

void Label::draw(DrawFactory* drawFactory, const Vec2& vecDelta)
{
    if (!isVisible()) {
        return;
    }
    auto size = this->getContentSize();
    auto pos = this->getPosition();
    pos = Director::instance->convertPosition(rect.p0 + vecDelta);
    auto scale = this->getScale();
    auto angle = this->getRotation();
    auto opacity = this->getOpacity();

    auto pos1 = pos;
    pos -= Vec2(size.width / 2, size.height / 2);

    //äÖÈ¾Ç°×¼±¸
    drawFactory->setScale(pos1, scale.x, scale.x);
    drawFactory->setRotation(pos1, angle);
    drawFactory->flushTransform();

    //*****
    drawFactory->setStringStyle(fontSize, weight, font);
    drawFactory->drawString(pos, pos + Vec2(rect.width, rect.height), text,
                            color);
    //*****
}

void Label::setString(const std::wstring& text) { this->text = text; }

void Label::setFontSize(int size) { fontSize = size; }

int Label::getFontSize() const { return fontSize; }

void Label::setWeight(SuperDraw::FontWeight weight) { this->weight = weight; }

void Label::setColor(const SuperDraw::Color4F& color) { this->color = color; }

const SuperDraw::Color4F& Label::getColor() const { return color; }

void Label::setRect(const Rect& rect) { this->rect = rect; }

const Rect& Label::getRect() const { return rect; }
