//
//  Scene.h
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#ifndef __SCENE_H__
#define __SCENE_H__

class Node;
class Menu;
#include <functional>
#include <vector>

#include "WindowEx.h"

#include "Node.h"
#include "Schedule.h"
#include "Tools.h"

class Scene : public Node {
public:
    Scene() {}
    virtual ~Scene() {}

    virtual void update(float dt);

    virtual void draw(WindowEx::DrawFactory* drawFactory);
    virtual bool init() { return true; }

private:
    virtual void setParent(Node*) override final {}
    virtual void removeFromParent() override final {}

    //触摸位置
    Vec2 touchPos;
    //是否按下
    bool touchPressed = false;
};

#endif