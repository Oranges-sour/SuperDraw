//
//  Sprite.h
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <string>

#include "WindowEx.h"

#include "Node.h"

class Sprite : public Node {
public:
    static Sprite* create(const std::wstring& fileName);
    Sprite(const std::wstring& fileName);
    virtual ~Sprite();

public:
    virtual void draw(WindowEx::DrawFactory* drawFactory, const Vec2& vecDelta) override;
    virtual Size getContentSize() override;

private:
    WindowEx::Image* image = nullptr;
};

#endif
