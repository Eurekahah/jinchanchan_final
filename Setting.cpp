# include "Setting.h"
# include "create_button_and_scene.h"

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
    auto fullScreenSprite = ui::Button::create("backgrounds/full_screen.png");
    auto smallScreenSprite = ui::Button::create("backgrounds/small_screen.jpg");

    // 设置精灵位置
    create_button(fullScreenSprite, 0.7f, 0.7f, 0.1f, 0.1f);
    create_button(smallScreenSprite, 0.7f, 0.55f, 0.1f, 0.1f);

    // 将精灵添加到场景
    this->addChild(fullScreenSprite);
    this->addChild(smallScreenSprite);

    auto listener = EventListenerTouchOneByOne::create();

    listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto bounds = event->getCurrentTarget()->getBoundingBox();

        // 检查是否触摸到了全屏按钮
        if (fullScreenSprite->getBoundingBox().containsPoint(touch->getLocation())) {
            // 切换到全屏模式
// 获取Director实例
            auto director = Director::getInstance();
            // 获取GLView实例
            auto glview = director->getOpenGLView();

            if (!glview) {
                // 如果glview不存在，则需要先创建它
                glview = GLViewImpl::createWithFullScreen("游戏名称");
                director->setOpenGLView(glview);
            }
            else {
                // 获取屏幕尺寸
                Size screenSize = glview->getFrameSize();
                // 设置为全屏模式
                glview->setFrameSize(screenSize.width, screenSize.height);
            }

        }

        // 检查是否触摸到了小窗按钮
        if (smallScreenSprite->getBoundingBox().containsPoint(touch->getLocation())) {
            // 切换到小窗模式
            auto glview = Director::getInstance()->getOpenGLView();
            glview->setFrameSize(720, 480);
            return true;
        }

        return false;
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, fullScreenSprite);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), smallScreenSprite);


}