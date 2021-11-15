//
//  Sprite.cpp
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#include "Sprite.h"

#include "Director.h"
#include "ImagePool.h"
#include "Tools.h"

using namespace std;
using namespace WindowEx;

Sprite* Sprite::create(const wstring& fileName) {
    auto sp = new (std::nothrow) Sprite{fileName};
    if (sp) {
        sp->autorelease();
        return sp;
    }
    return nullptr;
}

Sprite::Sprite(const wstring& fileName) {
    this->image = ImagePool::instance->loadImage(fileName);
}

Sprite::~Sprite() {}

void Sprite::draw(DrawFactory* drawFactory, const Vec2& vecDelta) {
    if (!isVisible()) {
        return;
    }
    auto size = this->getContentSize();
    auto pos = this->getPosition();
    pos = Director::instance->convertPosition(pos + vecDelta);
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
    drawFactory->drawImage(pos, image, opacity);
    //*****
}

Size Sprite::getContentSize() { return image->size(); }