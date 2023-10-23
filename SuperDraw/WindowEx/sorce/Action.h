//
//  Action.h
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#ifndef __ACTION_H__
#define __ACTION_H__

#include <functional>
#include <queue>
#include <vector>

class Node;
#include "Ref.h"
#include "Tools.h"

class Action : public Ref {
public:
    virtual void step(float time) = 0;
    virtual void update(float time) = 0;
    virtual void setNode(Node* node);
    bool isRunFinish();

protected:
    bool runFinish = false;
    Node* node = nullptr;
};

class ActionInterval : public Action {
public:
    ActionInterval(float duration);
    virtual ~ActionInterval();

    virtual void firstCall();
    /*time����ʵ��ÿһ֡��ʱ��,step()����update()�������
      ����ֵ:(������ʼ������ʱ�� / ������ʱ��)
    */
    virtual void step(float time) override;
    //��ö�����ʱ��
    float getDuration();

protected:
    float pastTime = 0;
    float duration = 0;
    bool _firstCall = true;
};

//��������
class Sequence : public Action {
public:
    static Sequence* create(const std::vector<Action*>& actions);
    Sequence(const std::vector<Action*>& actions);
    virtual ~Sequence();

    virtual void step(float time) override;
    virtual void update(float time) override;
    virtual void setNode(Node* node) override;

private:
    std::queue<Action*> actions;
};

//ͬ��ִ�еĶ���
class Spawn : public Action {
public:
    static Spawn* create(const std::vector<Action*>& actions);
    Spawn(const std::vector<Action*>& actions);
    virtual ~Spawn();

    virtual void step(float time) override;
    virtual void update(float time) override;
    virtual void setNode(Node* node) override;

private:
    std::vector<Action*> actions;
};

class DelayTime : public Action {
public:
    static DelayTime* create(float duration);
    DelayTime(float duration);
    virtual ~DelayTime();

    virtual void step(float time) override;
    virtual void update(float time) override;

private:
    float pastTime = 0;
    float duration = 0;
};

class CallFunc : public Action {
public:
    static CallFunc* create(const std::function<void()>& func);
    CallFunc(const std::function<void()>& func);
    virtual ~CallFunc();

    virtual void step(float time) override;
    virtual void update(float time) override;

private:
    std::function<void()> func;
};

class CallFuncN : public Action {
public:
    static CallFuncN* create(const std::function<void(Node*)>& func);
    CallFuncN(const std::function<void(Node*)>& func);
    virtual ~CallFuncN();

    virtual void step(float time) override;
    virtual void update(float time) override;

private:
    std::function<void(Node*)> func;
};

struct EaseFunction {
public:
    static const std::function<float(float, float)> easeIn;
    static const std::function<float(float, float)> easeOut;
    static const std::function<float(float, float)> easeInOut;
};

class EaseAction : public ActionInterval {
public:
    /*�����func:
      time�� ����ֵ:(������ʼ������ʱ�� / ������ʱ��)
      rate��һ������
    */
    static EaseAction* create(
        ActionInterval* action, float rate,
        const std::function<float(float /*time*/, float /*rate*/)>& func);
    EaseAction(ActionInterval* action, float rate,
               const std::function<float(float, float)>& func);
    virtual ~EaseAction();

    virtual void firstCall() override;
    virtual void update(float time) override;
    virtual void setNode(Node* node) override;

private:
    std::function<float(float, float)> easeFunc;
    ActionInterval* action = nullptr;
    float rate = 0;
};

class MoveBy : public ActionInterval {
public:
    static MoveBy* create(float time, const Vec2& deltaPos);
    MoveBy(float time, const Vec2& deltaPos);
    virtual ~MoveBy();

    virtual void update(float time) override;

protected:
    Vec2 lastPos{};
    Vec2 deltaPos{};
};

class MoveTo : public MoveBy {
public:
    static MoveTo* create(float time, const Vec2& toPos);
    MoveTo(float time, const Vec2& toPos);
    virtual ~MoveTo();

    virtual void firstCall() override;

private:
    Vec2 toPos{};
};

class FadeIn : public ActionInterval {
public:
    static FadeIn* create(float time);
    FadeIn(float time);
    virtual ~FadeIn();

    virtual void firstCall() override;
    virtual void update(float time) override;

protected:
    float lastOp = 0;
    float deltaOp = 0;
};

class FadeOut : public ActionInterval {
public:
    static FadeOut* create(float time);
    FadeOut(float time);
    virtual ~FadeOut();

    virtual void firstCall() override;
    virtual void update(float time) override;

protected:
    float lastOp = 0;
    float deltaOp = 0;
};

class FadeTo : public ActionInterval {
public:
    static FadeTo* create(float time, float opacity);
    FadeTo(float time, float opacity);
    virtual ~FadeTo();

    virtual void firstCall() override;
    virtual void update(float time) override;

protected:
    float startOp = 0;
    float deltaOp = 0;
    float endOp = 0;
};

class RotateBy : public ActionInterval {
public:
    static RotateBy* create(float time, float rotation);
    RotateBy(float time, float rotation);
    virtual ~RotateBy();

    virtual void update(float time) override;

protected:
    float lastRotation = 0;
    float deltaRotation = 0;
};

class RotateTo : public RotateBy {
public:
    static RotateTo* create(float time, float rotation);
    RotateTo(float time, float rotation);
    virtual ~RotateTo();

    virtual void firstCall() override;
    virtual void update(float time) override;

private:
    float toRotation = 0;
};

class ScaleTo : public ActionInterval {
public:
    static ScaleTo* create(float time, float scale);
    ScaleTo(float time, float scale);
    virtual ~ScaleTo();

    virtual void firstCall() override;
    virtual void update(float time) override;

protected:
    Vec2 startScale{};
    float deltaScale = 0;
    float endScale = 0;
};

#endif
