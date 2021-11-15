//
//  Ref.cpp
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#include "Ref.h"

#include <algorithm>
using namespace std;

AutoReleasePool* AutoReleasePool::instance = new AutoReleasePool{};

void AutoReleasePool::updatePool()
{
    vector<Ref*> needToErase;
    for (auto it = pool.begin(); it != pool.end(); ++it) {
        auto& r = (*it);
        //只有这个池在掌管这个对象了
        if (r->getCount() - 1 == 0) {
            needToErase.push_back(r);
        }
    }

    for (auto it = needToErase.begin(); it != needToErase.end(); ++it) {
        auto& r = (*it);
        pool.erase(remove(pool.begin(), pool.end(), r), pool.end());
        delete r;
    }
}

void AutoReleasePool::addToPool(Ref* ref) { pool.push_back(ref); }
