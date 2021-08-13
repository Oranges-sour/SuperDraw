//
//  Schedule.h
//
//  Created by Oranges.
//  Copyright 2021 Oranges. All rights reserved.
//

#ifndef __SCHEDULE_H__
#define __SCHEDULE_H__

#include <functional>
#include <map>
#include <string>

class Schedule {
public:
    //����������
    void updateSche(float dt);

    //��������ز���,ʱ�䵥λ:��
    void schedule(float interval, int times,
                  const std::function<void(void)>& func,
                  const std::wstring& key);
    void schedule(float interval, const std::function<void(void)>& func,
                  const std::wstring& key);
    void scheduleOnce(float delay, const std::function<void(void)>& func,
                      const std::wstring& key);

    void unschedule(const std::wstring& key);

private:
    struct FuncPack {
        std::function<void(void)> func;
        float interval = 0;
        int times = 0;
        //������һ�θ����Ѿ�������ʱ��
        float realTime = 0;
    };

    std::map<std::wstring, FuncPack> schedulePool;
};

#endif
