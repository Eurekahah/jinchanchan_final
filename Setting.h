# pragma once
# include "Scene/create_button_and_scene.h"


class settings : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    void volumeSliderEvent(Ref* sender, cocos2d::ui::Slider::EventType type);
    bool init();
    void sound_setting();
    void WindowSetting();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(settings);
};
