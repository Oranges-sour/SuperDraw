//
//  TMath.h
//
//  Created by Oranges.
//  Copyright 2021 Oranges. All rights reserved.
//

#ifndef __MY_MATH_H__
#define __MY_MATH_H__

#include "Tools.h"
#include <cmath>


#define DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) * 0.01745329252f)
#define RADIANS_TO_DEGREES(__ANGLE__) ((__ANGLE__) * 57.29577951f)

/**
 *ƽ��
 *@param t:Ҫ��ƽ������
 *@return t��ƽ��
 */
inline float POT(float t) { return t * t; }

constexpr float PI = 3.1415926f;

//���Ǻ���,�Ƕ�ģʽ
class DEG {
public:
    static float tan(float d) { return tanf(DEGREES_TO_RADIANS(d)); }
    static float sin(float d) { return sinf(DEGREES_TO_RADIANS(d)); }
    static float cos(float d) { return cosf(DEGREES_TO_RADIANS(d)); }

    static float atan(float d) { return RADIANS_TO_DEGREES(atanf(d)); }
    static float asin(float d) { return RADIANS_TO_DEGREES(asinf(d)); }
    static float acos(float d) { return RADIANS_TO_DEGREES(acosf(d)); }
};

class TMath {
public:

    /**
     *�����ľ���
     *@param p1:��һ����
     *@param p2:�ڶ�����
     *@return ����
     */
    static float distance(const Vec2& p1, const Vec2& p2);

    /**
     *���ֱ���߶���,����ʼ�㿪ʼ����һ�γ��ȵ�����,��from��toΪ����
     *@param from:��ʼ��
     *@param to:����
     *@return ����
     */
    static Vec2 getPosOnLine(const Vec2& from, const Vec2& to, float distance);

    /**
     *�ж������������Ƿ����
     *@param num1:��һ����
     *@param num2:�ڶ�����
     *@param delta:�жϾ���(���������������С��������ֵ����Ϊ�����)
     *@return �Ƿ����
     */
    static bool float_equal(float num1, float num2, float delta = 0.000001f);

    /**
     *���һ������,��positionΪ���ĵ�,x��y��ƫ����������min��max֮��
     *@param position:���ĵ�
     *@param min:��Сƫ����
     *@param max:���ƫ����
     *@return
     */
    static Vec2 randPos(const Vec2& position, float min, float max);

    /**
     *��float��������һλ��int
     *@param num:С��
     *@return ��������������
     */
    static int floatRoundInt(float num);
};

inline float TMath::distance(const Vec2& p1, const Vec2& p2)
{
    return sqrt(POT(p1.x - p2.x) + POT(p1.y - p2.y));
}

inline bool TMath::float_equal(float num1, float num2, float delta)
{
    return (abs(num1 - num2) <= delta);
}

inline int TMath::floatRoundInt(float num)
{
    return static_cast<int>(num + 0.5f);
}

#endif