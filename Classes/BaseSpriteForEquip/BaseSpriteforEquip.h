#pragma once
#ifndef BASESPRITEFOREUIP_H_
#define BASESPRITEFOREUIP_H_

#include"cocos2d.h"
USING_NS_CC;

class BaseSpriteforEquip :public Sprite
{
    CC_SYNTHESIZE(int,_sprite_type,SpriteType);//���п��� ��Ӣ�۲��������ɾ�� �ж�����ڵ���ʲô������
    CC_SYNTHESIZE(bool, _is_pressed, isPressed);//��Ҫ��� ������϶���ʱ�� ��ʹ������ж��Ƿ�ס
    CC_SYNTHESIZE(EventListenerTouchOneByOne*, _touchListener, TouchListener);//���㴥����
public:
    virtual ~BaseSpriteforEquip();

    // ����¼��ص�����
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) { return true; }
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {}
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {}
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event) {}

    virtual void ban_touch() { ; }
    virtual void resume_touch() { ; }

    // ��ʼ��������
    virtual bool init();

   
};

#endif // !BASESPRITEFOREUIP_H_