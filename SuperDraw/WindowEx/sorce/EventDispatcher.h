//
//  EventDispatcher.h
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#ifndef __EVENT_DISPATCHER_H__
#define __EVENT_DISPATCHER_H__

#include <functional>
#include <map>
#include <string>

#include "Ref.h"
#include "Node.h"
#include "Tools.h"

enum class MouseType { unknow, left, right };

class EventReceiverMouse;
class EventReceiverKeyboard;

//事件分发器
class EventDispatcher final {
public:
    static EventDispatcher* instance;

public:
    void regist(EventReceiverMouse* receiver, int ZOrder);
    void unregist(EventReceiverMouse* receiver);

    void regist(EventReceiverKeyboard* receiver, int ZOrder);
    void unregist(EventReceiverKeyboard* receiver);

    //鼠标左键按下
    void LMouseDown(const Vec2& pos);
    //抬起
    void LMouseUp(const Vec2& pos);
    //鼠标右键按下
    void RMouseDown(const Vec2& pos);
    //抬起
    void RMouseUp(const Vec2& pos);
    //鼠标移动
    void mouseMove(const Vec2& pos);
    //键盘按下
    void keyDown(const std::wstring& key);
    //键盘抬起
    void keyUp(const std::wstring& key);

private:
    std::multimap<int, EventReceiverMouse*> mouseReceiverPool;
    std::multimap<int, EventReceiverKeyboard*> keyboardReceiverPool;
};

class EventReceiverKeyboard final : public Ref {
public:
    static EventReceiverKeyboard* create(Node* node, int ZOrder);
    EventReceiverKeyboard() {}
    virtual ~EventReceiverKeyboard() {}

    //返回false将截断以后的所有消息
    std::function<bool(const std::wstring&)> keyDown =
        [](const std::wstring&) -> bool { return true; };
    std::function<bool(const std::wstring&)> keyUp =
        [](const std::wstring&) -> bool { return true; };

    int ZOrder = 0;
};

class EventReceiverMouse : public Ref {
public:
    EventReceiverMouse() { mouseType = MouseType::unknow; }
    EventReceiverMouse(EventReceiverMouse&) = delete;
    virtual ~EventReceiverMouse() {}

    //返回false将截断以后的所有消息
    std::function<bool(const Vec2&)> mouseDown = [](const Vec2&) -> bool {
        return true;
    };
    std::function<bool(const Vec2&)> mouseUp = [](const Vec2&) -> bool {
        return true;
    };
    std::function<bool(const Vec2&)> mouseMove = [](const Vec2&) -> bool {
        return true;
    };

    MouseType mouseType;
    int ZOrder = 0;
};

//事件接收器
class EventReceiverLMouse final : public EventReceiverMouse {
public:
    static EventReceiverLMouse* create(Node* node, int ZOrder);
    EventReceiverLMouse() { mouseType = MouseType::left; }
    EventReceiverLMouse(EventReceiverLMouse&) = delete;
    virtual ~EventReceiverLMouse() {}
};

class EventReceiverRMouse final : public EventReceiverMouse {
public:
    static EventReceiverRMouse* create(Node* node, int ZOrder);
    EventReceiverRMouse() { mouseType = MouseType::right; }
    EventReceiverRMouse(EventReceiverRMouse&) = delete;
    virtual ~EventReceiverRMouse() {}
};

#endif