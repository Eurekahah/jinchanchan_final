# include "Setting.h"
# include "create_button_and_scene.h"

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
    auto fullScreenSprite = ui::Button::create("backgrounds/full_screen.png");
    auto smallScreenSprite = ui::Button::create("backgrounds/small_screen.jpg");

    // ���þ���λ��
    create_button(fullScreenSprite, 0.7f, 0.7f, 0.1f, 0.1f);
    create_button(smallScreenSprite, 0.7f, 0.55f, 0.1f, 0.1f);

    // ��������ӵ�����
    this->addChild(fullScreenSprite);
    this->addChild(smallScreenSprite);

    auto listener = EventListenerTouchOneByOne::create();

    listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto bounds = event->getCurrentTarget()->getBoundingBox();

        // ����Ƿ�������ȫ����ť
        if (fullScreenSprite->getBoundingBox().containsPoint(touch->getLocation())) {
            // �л���ȫ��ģʽ
// ��ȡDirectorʵ��
            auto director = Director::getInstance();
            // ��ȡGLViewʵ��
            auto glview = director->getOpenGLView();

            if (!glview) {
                // ���glview�����ڣ�����Ҫ�ȴ�����
                glview = GLViewImpl::createWithFullScreen("��Ϸ����");
                director->setOpenGLView(glview);
            }
            else {
                // ��ȡ��Ļ�ߴ�
                Size screenSize = glview->getFrameSize();
                // ����Ϊȫ��ģʽ
                glview->setFrameSize(screenSize.width, screenSize.height);
            }

        }

        // ����Ƿ�������С����ť
        if (smallScreenSprite->getBoundingBox().containsPoint(touch->getLocation())) {
            // �л���С��ģʽ
            auto glview = Director::getInstance()->getOpenGLView();
            glview->setFrameSize(720, 480);
            return true;
        }

        return false;
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, fullScreenSprite);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), smallScreenSprite);


}