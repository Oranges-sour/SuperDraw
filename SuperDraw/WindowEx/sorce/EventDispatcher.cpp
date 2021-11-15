//
//  EventDispatcher.cpp
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#include "EventDispatcher.h"

#include "Node.h"

using namespace std;

EventDispatcher* EventDispatcher::instance = new EventDispatcher{};

void EventDispatcher::regist(EventReceiverMouse* receiver, int ZOrder) {
    if (!receiver) {
        return;
    }
    receiver->retain();
    receiver->ZOrder = ZOrder;
    mouseReceiverPool.insert({ZOrder, receiver});
}

void EventDispatcher::regist(EventReceiverKeyboard* receiver, int ZOrder) {
    if (!receiver) {
        return;
    }
    receiver->retain();
    receiver->ZOrder = ZOrder;
    keyboardReceiverPool.insert({ZOrder, receiver});
}

void EventDispatcher::unregist(EventReceiverMouse* receiver) {
    if (!receiver) {
        return;
    }
    auto low = mouseReceiverPool.lower_bound(receiver->ZOrder);
    auto up = mouseReceiverPool.upper_bound(receiver->ZOrder);
    auto it = low;
    bool find = false;
    for (; it != up; ++it) {
        if (it->second == receiver) {
            find = true;
            break;
        }
    }
    if (find) {
        mouseReceiverPool.erase(it);
    }

    receiver->release();
}

void EventDispatcher::unregist(EventReceiverKeyboard* receiver) {
    if (!receiver) {
        return;
    }
    auto low = keyboardReceiverPool.lower_bound(receiver->ZOrder);
    auto up = keyboardReceiverPool.upper_bound(receiver->ZOrder);
    auto it = low;
    bool find = false;
    for (; it != up; ++it) {
        if (it->second == receiver) {
            find = true;
            break;
        }
    }
    if (find) {
        keyboardReceiverPool.erase(it);
    }

    receiver->release();
}

void EventDispatcher::LMouseDown(const Vec2& pos) {
    for (auto it = mouseReceiverPool.begin(); it != mouseReceiverPool.end();
         ++it) {
        auto& rec = *it;
        if (rec.second->mouseType == MouseType::left) {
            rec.second->mouseDown(pos);
        }
    }
}

void EventDispatcher::LMouseUp(const Vec2& pos) {
    for (auto it = mouseReceiverPool.begin(); it != mouseReceiverPool.end();
         ++it) {
        auto& rec = *it;
        if (rec.second->mouseType == MouseType::left) {
            rec.second->mouseUp(pos);
        }
    }
}

void EventDispatcher::RMouseDown(const Vec2& pos) {
    for (auto it = mouseReceiverPool.begin(); it != mouseReceiverPool.end();
         ++it) {
        auto& rec = *it;
        if (rec.second->mouseType == MouseType::right) {
            rec.second->mouseDown(pos);
        }
    }
}

void EventDispatcher::RMouseUp(const Vec2& pos) {
    for (auto it = mouseReceiverPool.begin(); it != mouseReceiverPool.end();
         ++it) {
        auto& rec = *it;
        if (rec.second->mouseType == MouseType::right) {
            rec.second->mouseUp(pos);
        }
    }
}

void EventDispatcher::mouseMove(const Vec2& pos) {
    for (auto it = mouseReceiverPool.begin(); it != mouseReceiverPool.end();
         ++it) {
        auto& rec = *it;
        rec.second->mouseMove(pos);
    }
}

void EventDispatcher::keyDown(const std::wstring& key) {
    for (auto it = keyboardReceiverPool.begin();
         it != keyboardReceiverPool.end(); ++it) {
        auto& rec = *it;
        rec.second->keyDown(key);
    }
}

void EventDispatcher::keyUp(const std::wstring& key) {
    for (auto it = keyboardReceiverPool.begin();
         it != keyboardReceiverPool.end(); ++it) {
        auto& rec = *it;
        rec.second->keyUp(key);
    }
}

//******************************************************************
//******************************************************************
//******************************************************************

EventReceiverKeyboard* EventReceiverKeyboard::create(Node* node, int ZOrder) {
    auto rec = new (std::nothrow) EventReceiverKeyboard{};
    if (rec) {
        rec->autorelease();
        node->addEventReceiver(rec);
        EventDispatcher::instance->regist(rec, ZOrder);
        return rec;
    }
    return nullptr;
}

EventReceiverLMouse* EventReceiverLMouse::create(Node* node, int ZOrder) {
    auto rec = new (std::nothrow) EventReceiverLMouse{};
    if (rec) {
        rec->autorelease();
        node->addEventReceiver(rec);
        EventDispatcher::instance->regist(rec, ZOrder);
        return rec;
    }
    return nullptr;
}

EventReceiverRMouse* EventReceiverRMouse::create(Node* node, int ZOrder) {
    auto rec = new (std::nothrow) EventReceiverRMouse{};
    if (rec) {
        rec->autorelease();
        node->addEventReceiver(rec);
        EventDispatcher::instance->regist(rec, ZOrder);
        return rec;
    }
    return nullptr;
}