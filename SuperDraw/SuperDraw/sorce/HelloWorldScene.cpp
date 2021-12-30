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

    auto l =
        Label::create(L"Î¢ÈíÑÅºÚ", L"Ôªµ©¿ìÀÖ", 48, Rect(500, 500, 1000, 20),
                      FontWeight::light, FontStyle::normal);
    this->addChild(l);

    auto a0 = MoveTo::create(10, Vec2(20, 20));
    l->runAction(a0);

    return true;
}