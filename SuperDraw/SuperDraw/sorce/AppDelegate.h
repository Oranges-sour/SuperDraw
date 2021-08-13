//
//  AppDelegate.h
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#ifndef __APP_DELEGATE_H__
#define __APP_DELEGATE_H__

#include <string>

#include "Tools.h"

struct AppInfo {
    float frameRate;
    Size windowSize;
    std::wstring windowName;
};

class AppDelegate final {
public:
    AppDelegate() {}
    AppDelegate(AppDelegate&) = delete;
    virtual ~AppDelegate(){};

    void init();
    void startApp();
    const AppInfo& getWindowInfo();

private:
    AppInfo appInfo;
};

#endif
