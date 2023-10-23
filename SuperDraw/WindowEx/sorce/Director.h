//
//  Director.h
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#ifndef __DIRECTOR_H__
#define __DIRECTOR_H__

#include <string>

#include "Label.h"
#include "Scene.h"
#include "Tools.h"
#include "WindowEx.h"

class Director final {
private:
    Director() {}
    Director(Director&) = delete;
    virtual ~Director() {}

public:
    static void createInstance(WindowEx::DrawFactory* drawFactory,
                               const Size& winSize);
    static void destoryInstance();
    static Director* instance;

public:
    void setDebugDraw(bool enableDebugDraw);
    void mainLoop(float dt);
    void runWithScene(Scene* scene);
    Vec2 convertPosition(const Vec2& pos);
    Size getVisibleSize();
    WindowEx::DrawFactory* getDrawFactory();

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
    void debugDraw(float dt);

private:
    bool enableDebugDraw = false;
    Label* debugDrawLabel = nullptr;
    float frameTime = 0;
    int frameCount = 0;

    Size winSize;
    Scene* scene = nullptr;
    Scene* lastScene = nullptr;
    WindowEx::DrawFactory* drawFactory = nullptr;
};

#endif
