#include "HelloWorldScene.h"

#include <sstream>
#include <string>

#include "Action.h"
#include "Director.h"
#include "EventDispatcher.h"
#include "Label.h"
#include "Random.h"
#include "Sprite.h"
#include "TMath.h"
using namespace std;

HelloWorldScene* HelloWorldScene::create() {
    auto s = new (std::nothrow) HelloWorldScene();
    if (s && s->init()) {
        s->autorelease();
        return s;
    }
    return nullptr;
}

bool HelloWorldScene::init() {
    auto l = Layer0::create();
    this->addChild(l, 1);
    return true;
}

void HelloWorldScene::release() { Scene::release(); }

Layer0* Layer0::create() {
    auto l = new (std::nothrow) Layer0();
    if (l && l->init()) {
        l->autorelease();
        return l;
    }
    return nullptr;
}

bool Layer0::init() {
    Director::instance->setDebugDraw(true);
    createBall();

    auto mouse = EventReceiverLMouse::create(this, 1);
    mouse->mouseMove = [&](const Vec2& pos) -> void { ball->setPosition(pos); };
    mouse->mouseDown = [&](const Vec2& pos) -> void {
        auto act0 = ScaleTo::create(0.8f, 1.5f);
        auto eact0 = EaseAction::create(act0, 3, EaseFunction::easeInOut);
        ball->stopAllActions();
        ball->runAction(eact0);
    };
    mouse->mouseUp = [&](const Vec2& pos) -> void {
        auto act1 = ScaleTo::create(0.8f, 1.0f);
        auto eact1 = EaseAction::create(act1, 3, EaseFunction::easeInOut);
        ball->stopAllActions();
        ball->runAction(eact1);
    };
    return true;
}

void Layer0::createBall() {
    auto size = Director::instance->getVisibleSize();
    ball = Sprite::create(L"Image\\circle.png");
    this->addChild(ball);
}