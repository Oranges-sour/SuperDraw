//
//  Node.h
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#ifndef __NODE_H__
#define __NODE_H__

#include "WindowEx.h"

#include "Action.h"
#include "Ref.h"
#include "Schedule.h"
#include "Tools.h"

class EventReceiverKeyboard;
class EventReceiverMouse;

class Node : public Schedule, public Ref {
public:
    Node();
    virtual ~Node();
    virtual void release() override;
    virtual void update(float dt);

public:
    static Node* create();
    //���ƽڵ�
    virtual void draw(WindowEx::DrawFactory* drawFactory, const Vec2& vecDelta);

    //��ת����ز���(ͼƬ����Ϊԭ��)
    virtual float getRotation() const;
    virtual void setRotation(float rotation);

    //������ز���
    virtual const Vec2& getPosition() const;
    virtual void setPosition(const Vec2& position);
    virtual void setPosition(float x, float y);

    //͸������ز���
    virtual float getOpacity();
    virtual void setOpacity(float opacity);

    //��Ⱦ˳����ز���
    int getZOrder() const;
    void setZOrder(int zOrder);

    //������ز���
    const Vec2& getScale();
    void setScale(float x, float y);
    void setScale(const Vec2& scale);

    //ִ�ж���
    void runAction(Action* action);
    void stopAllActions();

    //�����Ƿ���ʾ
    void setVisible(bool v);
    bool isVisible();

    int getTag();
    void setTag(int tag);

    const std::vector<Node*>& getChildren();
    //���ø��ڵ�
    virtual void setParent(Node* node);
    //�Ӹ��ڵ��Ƴ��˽ڵ�
    virtual void removeFromParent();
    //���,ɾ���ӽڵ�
    virtual void addChild(Node* node);
    virtual void addChild(Node* node, int ZOrder);
    virtual void removeChild(Node* node);
    //�����Ϣ������
    void addEventReceiver(EventReceiverMouse* mouseReceiver);
    void addEventReceiver(EventReceiverKeyboard* keyboardReceiver);

    //��þ������ڵ�ת���������
    Vec2 convertPosToParent();
    //��ô�С
    virtual Size getContentSize() { return Size(); };

protected:
    // tag��ʶ
    int tag = 0;
    //�Ƿ���ʾ
    bool visible = true;
    //�ڵ�ִ�еĶ���
    std::vector<Action*> actions;
    //�ڵ���ӽڵ��
    std::vector<Node*> children;
    //��Ҫ���ӽڵ����ɾ���Ľڵ�
    std::vector<Node*> needToErase;
    //�����ڴ˽ڵ����Ϣ������
    std::vector<EventReceiverMouse*> mouseRecevier;
    std::vector<EventReceiverKeyboard*> keyboardRecevier;
    //�ڵ�����
    Vec2 position;
    //�ڵ�����
    Vec2 scale{1, 1};
    //�ڵ����ת�Ƕ�
    float rotation = 0;
    //�ڵ��͸����
    float opacity = 1;
    //�ڵ����Ⱦ˳��
    int zOrder = 0;
    //���ڵ�ָ��
    Node* parent = nullptr;
};

#endif
