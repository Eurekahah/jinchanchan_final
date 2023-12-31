# include "Loading_page.h"
# include "HallPage.h"
using namespace cocos2d;

cocos2d::Scene* Loading_page::createScene()
{
    return Loading_page::create();
}
void Loading_page::play_music() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //建立一个声音选项
    auto music_playing_image_loop = "backgrounds/music_on.png";
    auto music_stop_playing_image_loop = "backgrounds/music_off.png";
    auto music_button = ui::Button::create(music_playing_image_loop, music_stop_playing_image_loop, music_stop_playing_image_loop);
    create_button(music_button, 1.0f, 1.0f,0.08f, 0.08f);
    music_button->addClickEventListener([music_button, music_playing_image_loop, music_stop_playing_image_loop](Ref* sender) {

        auto IsPlaying = CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
        if (IsPlaying) {
            music_button->loadTextures(music_stop_playing_image_loop, music_playing_image_loop);
            CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        }
        else {
            music_button->loadTextures(music_playing_image_loop, music_stop_playing_image_loop);
            CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        }
        });
    this->addChild(music_button, 1);
}
bool Loading_page::init() {
    if (!Scene::init())
    {
        return false;
    }

    //CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("warrior_song.ogg", true);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    play_music();
    auto button_clicking_audio = CocosDenshion::SimpleAudioEngine::getInstance();
    button_clicking_audio->getInstance()->preloadEffect("music/button_effect.mp3");
    auto start_image = ui::Button::create("backgrounds/start_image.png", "backgrounds/start_image.png", "backgrounds/start_image.png");
    auto end_image = ui::Button::create("backgrounds/exit_image.png", "backgrounds/exit_image.png", "backgrounds/exit_image.png");
    //auto start_and_exit_size = Director::getInstance()->getVisibleOrigin();
    start_image->setScale(3);
    end_image->setScale(3);
    start_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));

    end_image->setPosition(Vec2(start_image->getPositionX(),
        start_image->getPositionY() - start_image->getContentSize().height / 2 - end_image->getContentSize().height / 2 - visibleSize.height * 0.15f));

    start_image->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            button_clicking_audio->getInstance()->playEffect("music/button_effect.mp3", false);
            // 处理场景切换
            auto newScene = Hall_page::create(); // 创建新场景
            Director::getInstance()->pushScene(newScene);
        }
        });

    end_image->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {

        if (type == ui::Widget::TouchEventType::ENDED) {
            button_clicking_audio->getInstance()->playEffect("music/button_effect.mp3", false);
            Director::getInstance()->end(); // 结束程序
        }
        });



    this->addChild(start_image, 1);
    this->addChild(end_image, 1);

    auto background_sprite = Sprite::create("backgrounds/loading.png");
    create_background_page(background_sprite);
    this->addChild(background_sprite, -1);


    return true;
}