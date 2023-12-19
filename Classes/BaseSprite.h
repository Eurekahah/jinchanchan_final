#pragma once
#ifndef BASESPRITE_H_
#define BASESPRITE_H_

#include"cocos2d.h"
USING_NS_CC;

class BaseSprite :public Sprite
{
    CC_SYNTHESIZE(int,_sprite_type,SpriteType);//���п��� ��Ӣ�۲��������ɾ�� �ж�����ڵ���ʲô������
    CC_SYNTHESIZE(bool, _is_pressed, isPressed);//��Ҫ��� ������϶���ʱ�� ��ʹ������ж��Ƿ�ס
public:

    BaseSprite();
    virtual ~BaseSprite();

    // ����¼��ص�����
    virtual void onMouseDown(EventMouse* event) {}
    virtual void onMouseUp(EventMouse* event) {}
    virtual void onMouseMove(EventMouse* event) {}
    virtual void onMouseScroll(EventMouse* event) {}

    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {}
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {}
    // ��ʼ��������
    virtual bool init();
    virtual void onExit();

    void ban_mouse();//����
    void resume_mouse();//�ָ�

private:
    EventListenerMouse* _mouseListener;
    EventListenerKeyboard* _keyboardListener;
};

#endif // !BASESPRITE_H_