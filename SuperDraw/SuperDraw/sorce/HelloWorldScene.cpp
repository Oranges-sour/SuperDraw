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


    auto p = Sprite::create(L"1111.png");


    this->addChild(p, 2);

    rand_int x(100, 1100);
    rand_int y(100, 700);

    p->setPosition(Vec2(500, 350));

    auto a1 = FadeIn::create(1);
    auto e1 = EaseAction::create(a1, 1.1, EaseFunction::easeInOut);

    auto a2 = FadeOut::create(1);
    auto e2 = EaseAction::create(a2, 1.1, EaseFunction::easeInOut);

    auto s1 = Sequence::create({e1, e2});

    auto a11 = ScaleTo::create(0.4, 0.9);
    auto e11 = EaseAction::create(a11, 1.1, EaseFunction::easeInOut);

    auto a22 = ScaleTo::create(0.6, 10 / 9);
    auto e22 = EaseAction::create(a22, 1.1, EaseFunction::easeInOut);

    auto s2 = Sequence::create({e11, e22});

    auto s = Spawn::create({s1, s2});

    p->runAction(s);

    this->schedule(
        [this, p](float) {
            auto a1 = FadeIn::create(1);
            auto e1 = EaseAction::create(a1, 1.1, EaseFunction::easeInOut);

            auto a2 = FadeOut::create(1);
            auto e2 = EaseAction::create(a2, 1.1, EaseFunction::easeInOut);

            auto s1 = Sequence::create({e1, e2});

            auto a11 = ScaleTo::create(0.4, 0.9);
            auto e11 = EaseAction::create(a11, 1.1, EaseFunction::easeInOut);

            auto a22 = ScaleTo::create(0.6, 10 / 9);
            auto e22 = EaseAction::create(a22, 1.1, EaseFunction::easeInOut);

            auto s2 = Sequence::create({e11, e22});

            auto s = Spawn::create({s1, s2});

            p->runAction(s);
        },
        2, L"1");
      

    

   



   



    return true;
}