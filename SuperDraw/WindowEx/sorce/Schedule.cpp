//
//  Schedule.cpp
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#include "Schedule.h"

#include <string>
#include <vector>
using namespace std;

void Schedule::updateSche(float dt) {
    vector<wstring> needToErase;
    for (auto& it : scheduleMap) {
        auto& pack = it.second;
        //先减少delay的值
        if (pack.delay > 0) {
            pack.delay -= dt;
            if (pack.delay < 0)  //减少最后一次delay多减少了,加到计时
                pack.timeCount = -pack.delay;
        } else {
            //每一帧都运行
            if (pack.interval < 0) {
                --pack.repeat;
                pack.callBack(dt);
            } else {
                for (; pack.timeCount >= pack.interval &&
                       (pack.repeat >= 1 || pack.repeat < 0);
                     pack.timeCount -= pack.interval, --pack.repeat)
                    pack.callBack(pack.interval);
                pack.timeCount += dt;
            }
        }
        if (pack.repeat == 0) {
            needToErase.push_back(it.first);
        }
    }

    for (auto& it : needToErase) {
        scheduleMap.erase(it);
    }
}

void Schedule::schedule(const std::function<void(float)>& callback,
                        const std::wstring& key) {
    this->schedule(callback, -1, -1, -1, key);
}

void Schedule::schedule(const std::function<void(float)>& callback,
                        float interval, const std::wstring& key) {
    this->schedule(callback, interval, -1, -1, key);
}

void Schedule::schedule(const std::function<void(float)>& callback,
                        float interval, int repeat, float delay,
                        const std::wstring& key) {
    SchedulePack pack;
    pack.callBack = callback;
    pack.interval = interval;
    pack.repeat = repeat;
    pack.delay = delay;
    pack.timeCount = 0.0f;
    scheduleMap[key] = pack;
}

void Schedule::scheduleOnce(const std::function<void(float)>& callback,
                            float delay, const std::wstring& key) {
    this->schedule(callback, -1, 1, delay, key);
}

void Schedule::unschedule(const std::wstring& key) { scheduleMap.erase(key); }
