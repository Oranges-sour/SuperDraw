//
//  Scene.cpp
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#include "Scene.h"

#include <algorithm>

#include "Director.h"
#include "EventDispatcher.h"
#include "Node.h"
#include "UI.h"

using namespace std;
using namespace WindowEx;

void Scene::update(float dt)
{
    this->updateSche(dt);

    for (auto it = children.begin(); it != children.end(); ++it) {
        auto& node = *it;
        node->update(dt);
    }

    for (auto it = needToErase.begin(); it != needToErase.end(); ++it) {
        auto& node = *it;
        children.erase(remove(children.begin(), children.end(), node),
                       children.end());
        node->release();
    }
    needToErase.clear();
}

void Scene::draw(DrawFactory* drawFactory)
{
    //升序排序<由下向上绘制
    auto comp = [&](const Node* ob1, const Node* ob2) -> bool {
        return ob1->getZOrder() < ob2->getZOrder();
    };

    /*使用稳定的排序,保证ZOrder相等的元素的渲染顺序不改变
     */
    stable_sort(children.begin(), children.end(), comp);

    for (auto it = children.begin(); it != children.end(); ++it) {
        (*it)->draw(drawFactory, Vec2(0, 0));
    }
}