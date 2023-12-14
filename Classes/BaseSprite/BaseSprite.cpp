#include"BaseSprite.h"

bool BaseSprite::init() {

    if (!Sprite::init())
        return false;

    // 初始化鼠标事件监听器和键盘事件监听器
    _mouseListener = EventListenerMouse::create();
    _keyboardListener = EventListenerKeyboard::create();

    _mouseListener->onMouseDown = CC_CALLBACK_1(BaseSprite::onMouseDown, this);
    _mouseListener->onMouseUp = CC_CALLBACK_1(BaseSprite::onMouseUp, this);
    _mouseListener->onMouseMove = CC_CALLBACK_1(BaseSprite::onMouseMove, this);
    _mouseListener->onMouseScroll = CC_CALLBACK_1(BaseSprite::onMouseScroll, this);

    _keyboardListener->onKeyPressed = CC_CALLBACK_2(BaseSprite::onKeyPressed, this);
    _keyboardListener->onKeyReleased = CC_CALLBACK_2(BaseSprite::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
    Sprite::init();
    return true;
}

void BaseSprite::onExit()
{
    _eventDispatcher->removeEventListener(_mouseListener);
    _eventDispatcher->removeEventListener(_keyboardListener);

    Sprite::onExit();
}

BaseSprite::BaseSprite()
{
    BaseSprite::init();
}

BaseSprite::~BaseSprite()
{
    BaseSprite::onExit();
}
