# include "Setting.h"
# include "create_button_and_scene.h"
#include <Windows.h> 
using namespace cocos2d;
Scene* settings::createScene() {
    return settings::create();
}
bool settings::init() {

    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ʼ��Ļ����
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto button_clicking_audio = CocosDenshion::SimpleAudioEngine::getInstance();//����
    button_clicking_audio->getInstance()->preloadEffect("music/button_effect.mp3");

    auto setting_background = Sprite::create("backgrounds/settings.png");
    create_background_page(setting_background);//���ر���ͼƬ
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
        float volume = slider->getPercent() / 100.0f; // ���ٷֱ�ת��Ϊ0��1�ķ�Χ
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
    }
}
void settings::sound_setting() {

    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ʼ��Ļ����
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto slider = cocos2d::ui::Slider::create();
    slider->loadBarTexture("music/sliderTrack.png"); // �����������ͼƬ
    slider->loadSlidBallTextures("music/sliderThumb.png", "music/sliderThumb.png", ""); // �����ͼƬ
    slider->loadProgressBarTexture("music/sliderTrack.png"); // ��������ͼƬ
    slider->setPosition(cocos2d::Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.8f));
    slider->setScale(5.0);
    // ���û������ĳ�ʼֵΪ��ǰ����
    float currentVolume = CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume(); // ����musicId���������ID
    slider->setPercent(static_cast<int>(currentVolume * 100));

    // ����¼�������
    slider->addEventListener(CC_CALLBACK_2(settings::volumeSliderEvent, this));

    auto label = cocos2d::Label::createWithTTF("Volume", "fonts/Arial.ttf", 48);
    if (label != nullptr) {
        // ���ñ�ǩλ�ã�λ�ڹ������·���
        label->setPosition(cocos2d::Vec2(slider->getPositionX(), slider->getPositionY() - slider->getContentSize().height / 2 - visibleSize.height * 0.13f - 20));

        // ��ӱ�ǩ����
        this->addChild(label, 2);
    }

    this->addChild(slider, 2);

}


void settings::WindowSetting() {
    auto fullScreenButton = cocos2d::ui::Button::create("backgrounds/full_screen.png");
    auto smallScreenButton = cocos2d::ui::Button::create("backgrounds/small_screen.jpg");

    // ���ð�ťλ��
    create_button(fullScreenButton, 0.7f, 0.7f, 0.1f, 0.1f);
    create_button(smallScreenButton, 0.7f, 0.55f, 0.1f, 0.1f);

    // ����ť��ӵ�����
    this->addChild(fullScreenButton);
    this->addChild(smallScreenButton);

    fullScreenButton->addClickEventListener([this](Ref* sender) {
        // ����ȫ����ť�ĵ���¼�
        auto glview = Director::getInstance()->getOpenGLView();
       glview->setFrameSize(1920, 1080);
       //glview->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);
        // ����������Ʒֱ�������Ӧ�µĴ��ڴ�С


    });

    smallScreenButton->addClickEventListener([this](Ref* sender) {
        // ����С����ť�ĵ���¼�
        auto glview = Director::getInstance()->getOpenGLView();
        glview->setFrameSize(720, 480);
        //glview->setDesignResolutionSize(720, 480, ResolutionPolicy::SHOW_ALL);


    });
}



