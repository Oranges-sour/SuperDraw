#include "Schedule.h"

#include <string>
#include <vector>
using namespace std;

void Schedule::updateSche(float dt)
{
    vector<wstring> needToErase;
    for (auto it = schedulePool.begin(); it != schedulePool.end(); ++it) {
        auto& ob = it->second;
        ob.realTime += dt;
        if (ob.realTime >= ob.interval) {
            ob.realTime -= ob.interval;
            ob.func();
            if (ob.times != -1) ob.times -= 1;
            if (ob.times == 0) needToErase.push_back(it->first);
        }
    }

    for (auto it = needToErase.begin(); it != needToErase.end(); ++it) {
        schedulePool.erase(*it);
    }
}

void Schedule::schedule(float interval, int times, const function<void()>& func,
                        const std::wstring& key)
{
    if (times == 0) {
        return;
    }
    FuncPack pack;
    pack.func = func;
    pack.interval = interval;
    pack.times = times;
    pack.realTime = pack.interval;
    schedulePool.insert({key, pack});
}

void Schedule::schedule(float interval, const function<void()>& func,
                        const wstring& key)
{
    this->schedule(interval, -1, func, key);
}

void Schedule::scheduleOnce(float delay, const function<void()>& func,
                            const wstring& key)
{
    FuncPack pack;
    pack.func = func;
    pack.interval = delay;
    pack.realTime = 0;
    pack.times = 1;
    schedulePool.insert({key, pack});
}

void Schedule::unschedule(const wstring& key)
{
    auto it = schedulePool.find(key);
    if (it != schedulePool.end()) schedulePool.erase(it);
}
