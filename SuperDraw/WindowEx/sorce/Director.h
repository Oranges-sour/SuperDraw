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
    //鼠标左键按下
    void LMouseDown(const Vec2& pos);
    //抬起
    void LMouseUp(const Vec2& pos);
    //鼠标右键按下
    void RMouseDown(const Vec2& pos);
    //抬起
    void RMouseUp(const Vec2& pos);
    //鼠标移动
    void mouseMove(const Vec2& pos);
    //键盘按下
    void keyDown(const std::wstring& key);
    //键盘抬起
    void keyUp(const std::wstring& key);

private:
    Size winSize;
    Scene* scene = nullptr;
    Scene* lastScene = nullptr;
    DrawFactory* drawFactory = nullptr;
};

#endif
