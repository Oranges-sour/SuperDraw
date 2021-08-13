#include "HelloWorldScene.h"

#include <string>

#include "Action.h"
#include "Director.h"
#include "EventDispatcher.h"
#include "Label.h"
#include "Random.h"
#include "Sprite.h"
#include "TMath.h"
using namespace std;

HelloWorldScene* HelloWorldScene::create()
{
    auto s = new (std::nothrow) HelloWorldScene();
    if (s && s->init()) {
        s->autorelease();
        return s;
    }
    return nullptr;
}

bool HelloWorldScene::init()
{
    auto l = Layer0::create();
    this->addChild(l, 1);
    return true;
}

void HelloWorldScene::release() { Scene::release(); }

Layer0* Layer0::create()
{
    auto l = new (std::nothrow) Layer0();
    if (l && l->init()) {
        l->autorelease();
        return l;
    }
    return nullptr;
}

bool Layer0::init()
{
    createBall();

    auto l = Label::create(L"Consolas", L"hiiiiiiiiii\niiiiiiii\r\n\r\n", 10,
                           Rect(300, 300, 500, 0));
    this->addChild(l);

    this->schedule(
        0.1f, [&, l]() { l->setFontSize(l->getFontSize() + 1); },
        L"crateBalll");

    auto mouse = EventReceiverLMouse::create(this, 1);
    mouse->mouseMove = [&](const Vec2& pos) -> bool { return true; };
    return true;
}

void Layer0::createBall()
{
    auto size = Director::instance->getVisibleSize();

    auto a1 = Sprite::create(L"Image\\circle.png");
    // a1->setOpacity(0);
    a1->setPosition(Vec2(300, 300));
    this->addChild(a1, 1);

    auto act1 = ScaleTo::create(2, 5);
    auto act2 = ScaleTo::create(2, 2);
    auto act3 = Sequence::create({act1, act2});
    //a1->runAction(act3);
}