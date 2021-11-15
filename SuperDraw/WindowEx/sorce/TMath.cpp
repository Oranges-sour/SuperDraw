//
//  TMath.cpp
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#include "TMath.h"

#include "Random.h"

Vec2 TMath::getPosOnLine(const Vec2& from, const Vec2& to, float distance) {
    auto newTo = to;
    //·ÀÖ¹kÎÞÏÞ´ó
    if (TMath::float_equal(from.x, newTo.x, 0.01f)) newTo.x -= 0.5;
    const float k = (newTo.y - from.y) / (newTo.x - from.x);

    float x = distance / sqrt(POT(k) + 1);
    if (from.x > newTo.x) x = -x;
    const float y = k * x;
    return Vec2(from.x + x, from.y + y);
}

Vec2 TMath::randPos(const Vec2& position, float min, float max) {
    auto result = position;
    rand_float r0(min, max);
    rand_bool r1;

    if (r1())
        result.x += r0();
    else
        result.x -= r0();

    if (r1())
        result.y += r0();
    else
        result.y -= r0();

    return result;
}