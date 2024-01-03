# include "Scene/create_button_and_scene.h"
using namespace cocos2d;

void create_background_page(cocos2d::Sprite* background_sprite) {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // position the sprite on the center of the screen
    background_sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
    background_sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    auto background_image_size = background_sprite->getContentSize();
    float background_scaleX = visibleSize.width / background_image_size.width;
    float background_scaleY = visibleSize.height / background_image_size.height;
    background_sprite->setScaleX(background_scaleX);
    background_sprite->setScaleY(background_scaleY);

}
void create_button(ui::Button* music_button, float X, float Y, float X_size , float Y_size ) {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto music_origin = Director::getInstance()->getVisibleOrigin();
    float music_button_width = visibleSize.width * X_size;
    float music_button_height = visibleSize.height * Y_size;
    auto buttonSize = music_button->getContentSize();
    float music_button_scaleX = music_button_width / buttonSize.width;
    float music_button_scaleY = music_button_height / buttonSize.height;
    music_button->setScale(music_button_scaleX, music_button_scaleY);
    music_button->setPosition(Vec2((music_origin.x + visibleSize.width) * X - music_button->getContentSize().width * music_button_scaleX / 2,
        (music_origin.y + visibleSize.height) * Y - music_button->getContentSize().height * music_button_scaleY / 2));

}