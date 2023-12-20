#pragma once
#ifndef BASESPRITE_H_
#define BASESPRITE_H_

#include"cocos2d.h"
USING_NS_CC;

class BaseSprite :public Sprite
{
    CC_SYNTHESIZE(int,_sprite_type,SpriteType);//可有可无 等英雄层出来可以删除 判断这个节点是什么类型用
    CC_SYNTHESIZE(bool, _is_pressed, isPressed);//需要这个 大家用拖动的时候 请使用这个判断是否按住
public:

    BaseSprite();
    virtual ~BaseSprite();

    // 鼠标事件回调函数
    virtual void onMouseDown(EventMouse* event) {}
    virtual void onMouseUp(EventMouse* event) {}
    virtual void onMouseMove(EventMouse* event) {}
    virtual void onMouseScroll(EventMouse* event) {}

    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {}
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {}
    // 初始化和销毁
    virtual bool init();
    virtual void onExit();

    void ban_mouse();//禁用
    void resume_mouse();//恢复

private:
    EventListenerMouse* _mouseListener;
    EventListenerKeyboard* _keyboardListener;
};

#endif // !BASESPRITE_H_
