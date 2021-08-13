//
//  Director.h
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#ifndef __DIRECTOR_H__
#define __DIRECTOR_H__

#include "WindowEx.h"
using namespace SuperDraw;

#include <string>

#include "Scene.h"
#include "Tools.h"

class Director final {
private:
    Director() {}
    Director(Director&) = delete;
    virtual ~Director() {}

public:
    static void createInstance(DrawFactory* drawFactory, const Size& winSize);
    static void destoryInstance();
    static Director* instance;

public:
    void mainLoop(float dt);
    void runWithScene(Scene* scene);
    Vec2 convertPosition(const Vec2& pos);
    Size getVisibleSize();
    DrawFactory* getDrawFactory();

public:
    //����������
    void LMouseDown(const Vec2& pos);
    //̧��
    void LMouseUp(const Vec2& pos);
    //����Ҽ�����
    void RMouseDown(const Vec2& pos);
    //̧��
    void RMouseUp(const Vec2& pos);
    //����ƶ�
    void mouseMove(const Vec2& pos);
    //���̰���
    void keyDown(const std::wstring& key);
    //����̧��
    void keyUp(const std::wstring& key);

private:
    Size winSize;
    Scene* scene = nullptr;
    Scene* lastScene = nullptr;
    DrawFactory* drawFactory = nullptr;
};

#endif
