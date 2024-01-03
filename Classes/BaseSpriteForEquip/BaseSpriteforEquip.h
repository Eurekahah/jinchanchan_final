#pragma once
#ifndef BASESPRITEFOREUIP_H_
#define BASESPRITEFOREUIP_H_

#include"cocos2d.h"
USING_NS_CC;

class BaseSpriteforEquip :public Sprite
{
    CC_SYNTHESIZE(int,_sprite_type,SpriteType);//可有可无 等英雄层出来可以删除 判断这个节点是什么类型用
    CC_SYNTHESIZE(bool, _is_pressed, isPressed);//需要这个 大家用拖动的时候 请使用这个判断是否按住
    CC_SYNTHESIZE(EventListenerTouchOneByOne*, _touchListener, TouchListener);//单点触摸器
public:
    virtual ~BaseSpriteforEquip();

    // 鼠标事件回调函数
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) { return true; }
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {}
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {}
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event) {}

    virtual void ban_touch() { ; }
    virtual void resume_touch() { ; }

    // 初始化和销毁
    virtual bool init();

   
};

#endif // !BASESPRITEFOREUIP_H_