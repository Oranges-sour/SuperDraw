#include "UI.h"

#include <algorithm>

#include "Director.h"
#include "EventDispatcher.h"
#include "ImagePool.h"
#include "Tools.h"
using namespace std;

//*********************************************************************************

void basic_Button::setEnable(bool en) { enable = en; }

bool basic_Button::isEnable() { return enable; }

int basic_Button::getStatus() { return status; }

void basic_Button::setCallBack(const function<void(basic_Button*)>& func)
{
    this->func = func;
}

//*********************************************************************************

const int Button::NORMAL{0};
const int Button::PUSH_DOWN{1};
const int Button::DISABLE{2};

Button* Button::create(const wstring& normal, const wstring& pushDown,
                       const wstring& disable)
{
    auto b = new (std::nothrow) Button{normal, pushDown, disable};
    if (b) {
        b->autorelease();
        return b;
    }
    return nullptr;
}

Button::Button(const wstring& normal, const wstring& pushDown,
               const wstring& disable)
{
    auto imgPool = ImagePool::instance;
    images[NORMAL] = imgPool->loadImage(normal);
    images[PUSH_DOWN] = imgPool->loadImage(pushDown);
    images[DISABLE] = imgPool->loadImage(disable);
    this->status = NORMAL;
}

Button::~Button() {}

void Button::draw(DrawFactory* drawFactory, const Vec2& vecDelta)
{
    if (!isVisible()) return;
    auto size = images[NORMAL]->size();
    auto pos = this->getPosition();
    pos = Director::instance->convertPosition(pos + vecDelta);
    auto scale = this->getScale();
    auto angle = this->getRotation();
    auto opacity = this->getOpacity();

    auto pos1 = pos;
    pos -= Vec2(size.width / 2, size.height / 2);

    //渲染前准备
    drawFactory->setScale(pos1, scale.x, scale.y);
    drawFactory->setRotation(pos1, angle);
    drawFactory->flushTransform();

    Image* drawImage = nullptr;
    if (!enable)
        drawImage = images[DISABLE];
    else if (status == NORMAL)
        drawImage = images[NORMAL];
    else
        drawImage = images[PUSH_DOWN];

    //*****
    drawFactory->drawImage(pos, drawImage, opacity);
    //*****
}

void Button::setEnable(bool en)
{
    if (en && !enable) status = NORMAL;
    basic_Button::setEnable(en);
}

void Button::mouseDown(const Vec2& pos)
{
    auto rect = getButtonRect();
    if (rect.isInRect(pos) && enable) {
        status = PUSH_DOWN;
    }
}

void Button::mouseUp(const Vec2& pos)
{
    if (enable && status == PUSH_DOWN) {
        auto rect = getButtonRect();
        if (rect.isInRect(pos)) {
            func(this);
        }
        status = NORMAL;
    }
}

void Button::mouseMove(const Vec2& pos)
{
    auto rect = getButtonRect();
    if (rect.isInRect(pos) && enable) {
        status = PUSH_DOWN;
    } else {
        status = NORMAL;
    }
}

Rect Button::getButtonRect()
{
    Rect rect;
    auto pos = this->convertPosToParent();
    auto size = images[NORMAL]->size();
    rect.p0 = pos;
    rect.width = size.width;
    rect.height = size.height;
    return rect;
}

Size Button::getContentSize() { return images[NORMAL]->size(); }

//*********************************************************************************

const int ToggleButton::NORMAL_0{0};
const int ToggleButton::PUSH_DOWN_0{1};
const int ToggleButton::NORMAL_1{2};
const int ToggleButton::PUSH_DOWN_1{3};
const int ToggleButton::DISABLE_0{4};
const int ToggleButton::DISABLE_1{5};

ToggleButton* ToggleButton::create(const std::wstring& normal_0,
                                   const std::wstring& pushDown_0,
                                   const std::wstring& normal_1,
                                   const std::wstring& pushDown_1,
                                   const std::wstring& disable_0,
                                   const std::wstring& disable_1)
{
    auto tb = new (std::nothrow) ToggleButton{
        normal_0, pushDown_0, normal_1, pushDown_1, disable_0, disable_1};
    if (tb) {
        tb->autorelease();
        return tb;
    }
    return nullptr;
}

ToggleButton::ToggleButton(const std::wstring& normal_0,
                           const std::wstring& pushDown_0,
                           const std::wstring& normal_1,
                           const std::wstring& pushDown_1,
                           const std::wstring& disable_0,
                           const std::wstring& disable_1)
{
    auto imgPool = ImagePool::instance;
    images[NORMAL_0] = imgPool->loadImage(normal_0);
    images[PUSH_DOWN_0] = imgPool->loadImage(pushDown_0);
    images[NORMAL_1] = imgPool->loadImage(normal_1);
    images[PUSH_DOWN_1] = imgPool->loadImage(pushDown_1);
    images[DISABLE_0] = imgPool->loadImage(disable_0);
    images[DISABLE_1] = imgPool->loadImage(disable_1);
    this->status = NORMAL_0;
}

ToggleButton::~ToggleButton() {}

void ToggleButton::draw(DrawFactory* drawFactory, const Vec2& vecDelta)
{
    if (!isVisible()) {
        return;
    }
    auto size = images[NORMAL_0]->size();
    auto pos = this->getPosition();
    pos = Director::instance->convertPosition(pos + vecDelta);
    auto scale = this->getScale();
    auto angle = this->getRotation();
    auto opacity = this->getOpacity();

    auto pos1 = pos;
    pos -= Vec2(size.width / 2, size.height / 2);

    //渲染前准备
    drawFactory->setScale(pos1, scale.x, scale.y);
    drawFactory->setRotation(pos1, angle);
    drawFactory->flushTransform();

    Image* drawImage = nullptr;
    if (!enable) {
        if (status == NORMAL_0 || status == PUSH_DOWN_0)
            drawImage = images[DISABLE_0];
        else if (status == NORMAL_1 || status == PUSH_DOWN_1)
            drawImage = images[DISABLE_1];
    } else {
        switch (status) {
            case NORMAL_0:
                drawImage = images[NORMAL_0];
                break;
            case NORMAL_1:
                drawImage = images[NORMAL_1];
                break;
            case PUSH_DOWN_0:
                drawImage = images[PUSH_DOWN_0];
                break;
            case PUSH_DOWN_1:
                drawImage = images[PUSH_DOWN_1];
                break;
        }
    }

    //*****
    drawFactory->drawImage(pos, drawImage, opacity);
    //*****
}

void ToggleButton::mouseDown(const Vec2& pos)
{
    auto rect = getButtonRect();
    if (rect.isInRect(pos) && enable) {
        if (status == NORMAL_0) status = PUSH_DOWN_0;
        if (status == NORMAL_1) status = PUSH_DOWN_1;
    }
}

void ToggleButton::mouseUp(const Vec2& pos)
{
    if (enable && (status == PUSH_DOWN_0 || status == PUSH_DOWN_1)) {
        auto rect = getButtonRect();
        bool isInRect = rect.isInRect(pos);
        if (status == PUSH_DOWN_0) {
            status = NORMAL_1;
            if (isInRect) {
                toggle_func(this, 1);
            }
        }
        if (status == PUSH_DOWN_1) {
            status = NORMAL_0;
            if (isInRect) {
                toggle_func(this, 0);
            }
        }
    }
}

void ToggleButton::mouseMove(const Vec2& pos)
{
    auto rect = getButtonRect();
    if (rect.isInRect(pos) && enable) {
        if (status == NORMAL_0) status = PUSH_DOWN_0;
        if (status == NORMAL_1) status = PUSH_DOWN_1;
    } else {
        if (status == PUSH_DOWN_0) status = NORMAL_0;
        if (status == PUSH_DOWN_1) status = NORMAL_1;
    }
}

Rect ToggleButton::getButtonRect()
{
    Rect rect;
    auto pos = this->convertPosToParent();
    auto size = images[NORMAL_0]->size();
    rect.p0 = pos;
    rect.width = size.width;
    rect.height = size.height;
    return rect;
}

Size ToggleButton::getContentSize() { return images[NORMAL_0]->size(); }

void ToggleButton::setEnable(bool en)
{
    if (en && !enable) {
        if (status == PUSH_DOWN_0) status = NORMAL_0;
        if (status == PUSH_DOWN_1) status = NORMAL_1;
    }
    basic_Button::setEnable(en);
}

void ToggleButton::setCallBack(
    const function<void(ToggleButton*, int)>& callBack)
{
    toggle_func = callBack;
}

//*********************************************************************************

Menu* Menu::create()
{
    auto m = new (std::nothrow) Menu();
    if (m) {
        m->autorelease();
        return m;
    }
    return nullptr;
}

Menu::Menu()
{
    eventRec = EventReceiverLMouse::create(this, 1);

    eventRec->mouseDown = [&](const Vec2& pos) -> bool {
        for (auto it = buttons.begin(); it != buttons.end(); ++it)
            (*it)->mouseDown(pos);
        return true;
    };

    eventRec->mouseMove = [&](const Vec2& pos) -> bool {
        for (auto it = buttons.begin(); it != buttons.end(); ++it)
            (*it)->mouseMove(pos);
        return true;
    };

    eventRec->mouseUp = [&](const Vec2& pos) -> bool {
        for (auto it = buttons.begin(); it != buttons.end(); ++it)
            (*it)->mouseUp(pos);
        return true;
    };
}

Menu::~Menu() {}

void Menu::release()
{
    EventDispatcher::instance->unregist(eventRec);
    for (auto it = buttons.begin(); it != buttons.end(); ++it) {
        (*it)->release();
    }
    Node::release();
}

void Menu::draw(DrawFactory* drawFactory, const Vec2& vecDelta)
{
    if (!isVisible()) {
        return;
    }

    //升序排序<由下向上绘制
    auto comp = [&](const Node* ob1, const Node* ob2) -> bool {
        return ob1->getZOrder() < ob2->getZOrder();
    };

    /*使用稳定的排序,保证ZOrder相等的元素的渲染顺序不改变
     */
    stable_sort(buttons.begin(), buttons.end(), comp);

    for (auto it = buttons.begin(); it != buttons.end(); ++it) {
        (*it)->draw(drawFactory, vecDelta);
    }
}

void Menu::update(float dt)
{
    for (auto it = buttons.begin(); it != buttons.end(); ++it) {
        auto& node = *it;
        node->update(dt);
    }
}

void Menu::addButton(basic_Button* button)
{
    button->retain();
    button->setParent(this);
    buttons.push_back(button);
}

void Menu::removeButton(basic_Button* button)
{
    buttons.erase(remove(buttons.begin(), buttons.end(), button),
                  buttons.end());
    button->release();
}
