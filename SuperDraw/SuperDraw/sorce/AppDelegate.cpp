//
//  AppDelegate.cpp
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#include "AppDelegate.h"

#include "HelloWorldScene.h"
#include "SuperDraw.h"

void AppDelegate::init() {
    appInfo.frameRate = 60;
    appInfo.windowSize = Size(1280, 720);
    appInfo.windowName = L"test";
    Random::init();
}

void AppDelegate::startApp() {
    auto s = HelloWorldScene::create();
    Director::instance->runWithScene(s);
}

const AppInfo& AppDelegate::getWindowInfo() { return appInfo; }
