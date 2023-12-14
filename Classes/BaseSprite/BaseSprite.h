#pragma once
#ifndef BASESPRITE_H_
#define BASESPRITE_H_

#include"cocos2d.h"
USING_NS_CC;

class BaseSprite :public Sprite
{
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

private:
    EventListenerMouse* _mouseListener;
    EventListenerKeyboard* _keyboardListener;
};

#endif // !BASESPRITE_H_
