//
//  Label.cpp
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#include "Label.h"

#include "Director.h"
using namespace std;
using namespace WindowEx;

Label* Label::create(const std::wstring& font, const std::wstring& text,
                     float fontSize, const Rect& rect, FontWeight weight,
                     FontStyle style, const Color4F& color) {
    auto la = new (std::nothrow)
        Label{font, text, fontSize, rect, weight, style, color};
    if (la) {
        la->autorelease();
        return la;
    }
    return nullptr;
}

Label::Label(const std::wstring& font, const std::wstring& text, float fontSize,
             const Rect& rect, FontWeight weight, FontStyle style,
             const Color4F& color)
    : font(font),
      text(text),
      fontSize(fontSize),
      rect(rect),
      weight(weight),
      style(style),
      color(color) {}

Label::~Label() {}

void Label::draw(DrawFactory* drawFactory, const Vec2& vecDelta) {
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
    drawFactory->setStringStyle(fontSize, weight, style, font);
    drawFactory->drawString(pos, pos + Vec2(rect.width, rect.height), text,
                            color);
    //*****
}

void Label::setString(const std::wstring& text) { this->text = text; }

void Label::setFontSize(float size) { fontSize = size; }

float Label::getFontSize() const { return fontSize; }

void Label::setWeight(FontWeight weight) { this->weight = weight; }

void Label::setColor(const Color4F& color) { this->color = color; }

const Color4F& Label::getColor() const { return color; }

void Label::setRect(const Rect& rect) { this->rect = rect; }

const Rect& Label::getRect() const { return rect; }

void Label::setPosition(float x, float y) { rect.p0 = Vec2(x, y); }

void Label::setPosition(const Vec2& pos) { rect.p0 = pos; }

const Vec2& Label::getPosition() const { return rect.p0; }

void Label::setOpacity(float opacity) { color.alpha = opacity; }

float Label::getOpacity() { return color.alpha; }
