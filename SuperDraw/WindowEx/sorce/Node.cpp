//
//  Node.cpp
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#include "Node.h"

#include "Action.h"
#include "EventDispatcher.h"
using namespace std;
using namespace WindowEx;

Node* Node::create() {
    auto n = new (std::nothrow) Node{};
    if (n) {
        n->autorelease();
        return n;
    }
    return nullptr;
}

void Node::update(float dt) {
    this->updateSche(dt);

    //����Action
    vector<Action*> actionNeedToErase;
    for (auto it = actions.begin(); it != actions.end(); ++it) {
        auto& act = (*it);
        if (!act->isRunFinish()) {
            act->step(dt);
        } else {
            actionNeedToErase.push_back(act);
        }
    }

    //�Ƴ�ִ�н�����action
    for (auto it = actionNeedToErase.begin(); it != actionNeedToErase.end();
         ++it) {
        auto& act = *it;
        actions.erase(remove(actions.begin(), actions.end(), act),
                      actions.end());
        act->release();
    }

    //���½ڵ�
    for (auto it = children.begin(); it != children.end(); ++it) {
        auto& node = *it;
        node->update(dt);
    }

    //�Ƴ��ڵ�
    for (auto it = needToErase.begin(); it != needToErase.end(); ++it) {
        auto& node = *it;
        children.erase(remove(children.begin(), children.end(), node),
                       children.end());
        node->release();
    }
    needToErase.clear();
}

Node::Node() {}

Node::~Node() {}

void Node::release() {
    for (auto it = actions.begin(); it != actions.end(); ++it) {
        (*it)->release();
    }
    for (auto it = children.begin(); it != children.end(); ++it) {
        auto& node = *it;
        node->release();
    }
    for (auto it = mouseRecevier.begin(); it != mouseRecevier.end(); ++it) {
        auto& receiver = *it;
        EventDispatcher::instance->unregist(receiver);
    }
    for (auto it = keyboardRecevier.begin(); it != keyboardRecevier.end();
         ++it) {
        auto& receiver = *it;
        EventDispatcher::instance->unregist(receiver);
    }
    Ref::release();
}

void Node::draw(DrawFactory* drawFactory, const Vec2& vecDelta) {
    if (!visible) {
        return;
    }

    //��������<�������ϻ���
    auto comp = [&](const Node* ob1, const Node* ob2) -> bool {
        return ob1->getZOrder() < ob2->getZOrder();
    };

    /*ʹ���ȶ�������,��֤ZOrder��ȵ�Ԫ�ص���Ⱦ˳�򲻸ı�
     */
    stable_sort(children.begin(), children.end(), comp);

    for (auto it = children.begin(); it != children.end(); ++it) {
        auto& node = *it;
        node->draw(drawFactory, vecDelta + position);
    }
}

float Node::getRotation() const { return rotation; }

void Node::setRotation(float rotation) { this->rotation = rotation; }

const Vec2& Node::getPosition() const { return position; }

void Node::setPosition(const Vec2& position) { this->position = position; }

void Node::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

float Node::getOpacity() { return this->opacity; }

void Node::setOpacity(float opacity) { this->opacity = opacity; }

int Node::getZOrder() const { return zOrder; }

void Node::setZOrder(int zOrder) { this->zOrder = zOrder; }

const Vec2& Node::getScale() { return scale; }

void Node::setScale(float x, float y) {
    scale.x = x;
    scale.y = y;
}

void Node::setScale(const Vec2& scale) { this->scale = scale; }

void Node::runAction(Action* action) {
    action->setNode(this);
    actions.push_back(action);
    action->retain();
}

void Node::stopAllActions() {
    for (auto& act : actions) {
        act->release();
    }
    actions.clear();
}

void Node::setVisible(bool v) { visible = v; }

bool Node::isVisible() { return visible; }

int Node::getTag() { return tag; }

void Node::setTag(int tag) { this->tag = tag; }

const vector<Node*>& Node::getChildren() { return children; }

void Node::setParent(Node* node) { parent = node; }

void Node::removeFromParent() { parent->removeChild(this); }

Vec2 Node::convertPosToParent() {
    if (parent == nullptr) {
        return position;
    }
    return position + parent->convertPosToParent();
}

void Node::addChild(Node* node) {
    node->retain();
    node->setParent(this);
    children.push_back(node);
}

void Node::addChild(Node* node, int ZOrder) {
    node->setZOrder(ZOrder);
    this->addChild(node);
}

void Node::removeChild(Node* node) { needToErase.push_back(node); }

void Node::addEventReceiver(EventReceiverMouse* mouseReceiver) {
    this->mouseRecevier.push_back(mouseReceiver);
}

void Node::addEventReceiver(EventReceiverKeyboard* keyboardReceiver) {
    this->keyboardRecevier.push_back(keyboardReceiver);
}
