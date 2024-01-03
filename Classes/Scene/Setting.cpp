# include "Setting.h"
# include "create_button_and_scene.h"
#include <Windows.h> 
using namespace cocos2d;
Scene* settings::createScene() {
    return settings::create();
}
bool settings::init() {

    auto visibleSize = Director::getInstance()->getVisibleSize();//获取初始屏幕设置
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto button_clicking_audio = CocosDenshion::SimpleAudioEngine::getInstance();//音乐
    button_clicking_audio->getInstance()->preloadEffect("music/button_effect.mp3");

    auto setting_background = Sprite::create("backgrounds/settings.png");
    create_background_page(setting_background);//加载背景图片
    this->addChild(setting_background, -1);

    auto backward_button = ui::Button::create("backgrounds/backwards.png");
    backward_button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            button_clicking_audio->getInstance()->playEffect("music/button_effect.mp3", false);
            Director::getInstance()->popScene();
        }
        });
    create_button(backward_button, 0.1f, 0.48f, 0.08f, 0.08f);
    auto backward_label = Label::createWithTTF("reverse", "fonts/Marker Felt.ttf", 24);
    backward_label->setPosition(Vec2(backward_button->getPositionX(), backward_button->getPositionY() - backward_button->getContentSize().height / 2 - backward_label->getContentSize().height / 2));

    this->addChild(backward_button, 1);
    this->addChild(backward_label, 1);
    sound_setting();

    WindowSetting();

    return true;

}
void settings::volumeSliderEvent(Ref* sender, cocos2d::ui::Slider::EventType type) {
    if (type == cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
        auto slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
        float volume = slider->getPercent() / 100.0f; // 将百分比转换为0到1的范围
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
    }
}
void settings::sound_setting() {

    auto visibleSize = Director::getInstance()->getVisibleSize();//获取初始屏幕设置
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto slider = cocos2d::ui::Slider::create();
    slider->loadBarTexture("music/sliderTrack.png"); // 滚动条轨道的图片
    slider->loadSlidBallTextures("music/sliderThumb.png", "music/sliderThumb.png", ""); // 滑块的图片
    slider->loadProgressBarTexture("music/sliderTrack.png"); // 进度条的图片
    slider->setPosition(cocos2d::Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.8f));
    slider->setScale(5.0);
    // 设置滑动条的初始值为当前音量
    float currentVolume = CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume(); // 假设musicId是你的音乐ID
    slider->setPercent(static_cast<int>(currentVolume * 100));

    // 添加事件监听器
    slider->addEventListener(CC_CALLBACK_2(settings::volumeSliderEvent, this));

    auto label = cocos2d::Label::createWithTTF("Volume", "fonts/Arial.ttf", 48);
    if (label != nullptr) {
        // 设置标签位置（位于滚动条下方）
        label->setPosition(cocos2d::Vec2(slider->getPositionX(), slider->getPositionY() - slider->getContentSize().height / 2 - visibleSize.height * 0.13f - 20));

        // 添加标签到层
        this->addChild(label, 2);
    }

    this->addChild(slider, 2);

}


void settings::WindowSetting() {
    auto fullScreenButton = cocos2d::ui::Button::create("backgrounds/full_screen.png");
    auto smallScreenButton = cocos2d::ui::Button::create("backgrounds/small_screen.jpg");

    // 设置按钮位置
    create_button(fullScreenButton, 0.7f, 0.7f, 0.1f, 0.1f);
    create_button(smallScreenButton, 0.7f, 0.55f, 0.1f, 0.1f);

    // 将按钮添加到场景
    this->addChild(fullScreenButton);
    this->addChild(smallScreenButton);

    fullScreenButton->addClickEventListener([this](Ref* sender) {
        // 处理全屏按钮的点击事件
        auto glview = Director::getInstance()->getOpenGLView();
       glview->setFrameSize(1920, 1080);
       //glview->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);
        // 重新设置设计分辨率以适应新的窗口大小


    });

    smallScreenButton->addClickEventListener([this](Ref* sender) {
        // 处理小窗按钮的点击事件
        auto glview = Director::getInstance()->getOpenGLView();
        glview->setFrameSize(720, 480);
        //glview->setDesignResolutionSize(720, 480, ResolutionPolicy::SHOW_ALL);


    });
}



