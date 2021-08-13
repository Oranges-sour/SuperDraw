//
//  Director.cpp
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#include "Director.h"
#include "EventDispatcher.h"
#include "Ref.h"

Director* Director::instance{nullptr};

void Director::createInstance(DrawFactory* drawFactory, const Size& winSize)
{
    if (instance) {
        destoryInstance();
    }
    instance = new (std::nothrow) Director();
    if (instance) {
        instance->winSize = winSize;
        instance->drawFactory = drawFactory;
    }
}

void Director::destoryInstance()
{
    if (instance->scene) {
        instance->scene->release();
    }
    if (instance->lastScene) {
        instance->lastScene->release();
    }
    delete instance;
    instance = nullptr;
}

void Director::mainLoop(float dt)
{
    if (!scene) {
        return;
    }
    scene->update(dt);
    if (lastScene) {
        lastScene->release();
        lastScene = nullptr;
    }
    drawFactory->beginPaint();
    drawFactory->clear(Color4B(0, 0, 0, 255));

    scene->draw(drawFactory);

    drawFactory->endPaint();

    //自动释放池更新
    ARP::instance->updatePool();
}

void Director::runWithScene(Scene* scene)
{
    lastScene = this->scene;
    this->scene = scene;
    scene->retain();
}

Vec2 Director::convertPosition(const Vec2& pos)
{
    return Vec2(pos.x, winSize.height - pos.y);
}

Size Director::getVisibleSize()
{
    return winSize;
}

DrawFactory* Director::getDrawFactory() { return drawFactory; }

void Director::LMouseDown(const Vec2& pos)
{
    EventDispatcher::instance->LMouseDown(convertPosition(pos));
}

void Director::LMouseUp(const Vec2& pos)
{
    EventDispatcher::instance->LMouseUp(convertPosition(pos));
}

void Director::RMouseDown(const Vec2& pos)
{
    EventDispatcher::instance->RMouseDown(convertPosition(pos));
}

void Director::RMouseUp(const Vec2& pos)
{
    EventDispatcher::instance->RMouseUp(convertPosition(pos));
}

void Director::mouseMove(const Vec2& pos)
{
    EventDispatcher::instance->mouseMove(convertPosition(pos));
}

void Director::keyDown(const std::wstring& key)
{
    EventDispatcher::instance->keyDown(key);
}

void Director::keyUp(const std::wstring& key)
{
    EventDispatcher::instance->keyUp(key);
}
