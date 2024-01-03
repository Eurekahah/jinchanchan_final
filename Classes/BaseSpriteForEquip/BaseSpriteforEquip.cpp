
#include"BaseSpriteForEquip/BaseSpriteforEquip.h"
//#include"BaseSpriteforEuqip.h"

bool BaseSpriteforEquip::init() {
    if (!Sprite::init()) {
        return false;
    }
    // ��������������
    _touchListener = EventListenerTouchOneByOne::create();

    // ���ô����ص�����
    _touchListener->onTouchBegan = CC_CALLBACK_2(BaseSpriteforEquip::onTouchBegan, this);
    _touchListener->onTouchMoved = CC_CALLBACK_2(BaseSpriteforEquip::onTouchMoved, this);
    _touchListener->onTouchEnded = CC_CALLBACK_2(BaseSpriteforEquip::onTouchEnded, this);
    _touchListener->onTouchCancelled = CC_CALLBACK_2(BaseSpriteforEquip::onTouchCancelled, this);

    // ��������������ӵ��¼��ַ���
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);

    _touchListener->setEnabled(false);
    _touchListener->setSwallowTouches(true);

    _is_pressed = 0;
   
    return true;
}



BaseSpriteforEquip::~BaseSpriteforEquip()
{
    _eventDispatcher->removeEventListener(_touchListener);
}
