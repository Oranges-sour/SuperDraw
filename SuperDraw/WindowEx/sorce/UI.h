//
//  UI.h
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#ifndef __UI_H__
#define __UI_H__

#include <array>
#include <functional>
#include <string>
#include <vector>

#include "WindowEx.h"

class EventReceiverLMouse;
#include "Node.h"

class Menu;

class basic_Button : public Node {
public:
    virtual void mouseDown(const Vec2& pos) = 0;
    virtual void mouseUp(const Vec2& pos) = 0;
    virtual void mouseMove(const Vec2& pos) = 0;
    virtual Rect getButtonRect() = 0;

    virtual void setEnable(bool en);
    bool isEnable();
    int getStatus();
    void setCallBack(const std::function<void(basic_Button*)>& func);

protected:
    std::function<void(basic_Button*)> func;
    int status = 0;
    bool enable = true;
};

class Button : public basic_Button {
public:
    static Button* create(const std::wstring& normal,
                          const std::wstring& pushDown,
                          const std::wstring& disable);
    Button(const std::wstring& normal, const std::wstring& pushDown,
           const std::wstring& disable);
    virtual ~Button();

    //绘制按钮
    virtual void draw(WindowEx::DrawFactory* drawFactory, const Vec2& vecDelta) override;

    virtual void mouseDown(const Vec2& pos) override;
    virtual void mouseUp(const Vec2& pos) override;
    virtual void mouseMove(const Vec2& pos) override;

    virtual Rect getButtonRect() override;
    virtual Size getContentSize() override;

    virtual void setEnable(bool en) override;

    static const int NORMAL;
    static const int PUSH_DOWN;
    static const int DISABLE;

private:
    //状态  0:抬起  1:按下
    // int status = 0;
    std::array<WindowEx::Image*, 3> images;
};

class ToggleButton : public basic_Button {
public:
    static ToggleButton* create(const std::wstring& normal_0,
                                const std::wstring& pushDown_0,
                                const std::wstring& normal_1,
                                const std::wstring& pushDown_1,
                                const std::wstring& disable_0,
                                const std::wstring& disable_1);
    ToggleButton(const std::wstring& normal_0, const std::wstring& pushDown_0,
                 const std::wstring& normal_1, const std::wstring& pushDown_1,
                 const std::wstring& disable_0, const std::wstring& disable_1);
    virtual ~ToggleButton();

    //绘制按钮
    virtual void draw(WindowEx::DrawFactory* drawFactory, const Vec2& vecDelta) override;

    virtual void mouseDown(const Vec2& pos) override;
    virtual void mouseUp(const Vec2& pos) override;
    virtual void mouseMove(const Vec2& pos) override;

    virtual Rect getButtonRect() override;
    virtual Size getContentSize() override;

    virtual void setEnable(bool en) override;

    virtual void setCallBack(
        const std::function<void(ToggleButton*, int)>& callBack);

    static const int NORMAL_0;
    static const int PUSH_DOWN_0;
    static const int NORMAL_1;
    static const int PUSH_DOWN_1;
    static const int DISABLE_0;
    static const int DISABLE_1;

private:
    /*状态
     0:按钮1抬起, 1:按钮1按下
    2:按钮2抬起, 3:按钮2按下
    */
    // int status = 0;
    std::array<WindowEx::Image*, 6> images;

    std::function<void(ToggleButton*, int)> toggle_func;
};

class Menu : public Node {
public:
    static Menu* create();
    Menu();
    virtual ~Menu();
    virtual void release() override;

    virtual void draw(WindowEx::DrawFactory* drawFactory, const Vec2& vecDelta) override;
    virtual void update(float dt);

    void addButton(basic_Button* button);
    void removeButton(basic_Button* button);

private:
    virtual void addChild(Node*) override {}
    virtual void removeChild(Node*) override {}

    EventReceiverLMouse* eventRec = nullptr;
    std::vector<basic_Button*> buttons;
};

#endif
