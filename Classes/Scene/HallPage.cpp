# include "HallPage.h"
# define hanjingxiao
#include <thread>
#include <mutex>
#include <condition_variable>

//# define Debug_for_lianji

using namespace cocos2d;

cocos2d::Scene* Hall_page::createScene()
{
    return Hall_page::create();
}
bool  Hall_page::init() {
    
    auto button_clicking_audio = CocosDenshion::SimpleAudioEngine::getInstance();
    button_clicking_audio->getInstance()->preloadEffect("music/button_effect.mp3");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto hall_image = Sprite::create("backgrounds/hall.png");
    create_background_page(hall_image);
    this->addChild(hall_image, -1);

    auto music_playing_image_loop = "backgrounds/music_on.png";
    auto music_stop_playing_image_loop = "backgrounds/music_off.png";
    auto music_button = ui::Button::create(music_playing_image_loop, music_stop_playing_image_loop, music_stop_playing_image_loop);
    create_button(music_button, 1.0f, 1.0f, 0.08f, 0.08f);
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

    auto setting_button = ui::Button::create("backgrounds/setting_button.png");
    create_button(setting_button, 0.88f, 1.0f, 0.08f, 0.08f);
    setting_button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            button_clicking_audio->getInstance()->playEffect("music/button_effect.mp3", false);
            // 处理场景切换
            auto newScene = settings::create(); // 创建新场景
            Director::getInstance()->pushScene(newScene); // 切换到新场景
        }
        });
    this->addChild(setting_button, 1);
    auto setting_label = Label::createWithTTF("Settings", "fonts/Chinese.ttf", 24);
    setting_label->setPosition(Vec2(setting_button->getPositionX(), setting_button->getPositionY() - setting_button->getContentSize().height / 2 - setting_label->getContentSize().height / 2));
    this->addChild(setting_label, 1);

    auto heroes_image = ui::Button::create("backgrounds/heroes.png");
    heroes_image->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            button_clicking_audio->getInstance()->playEffect("music/button_effect.mp3", false);
            // 处理场景切换
            auto to_Display_hero_Scene = Display_heroes_page::create(); // 创建新场景
            Director::getInstance()->pushScene(to_Display_hero_Scene); // 切换到新场景
        }
        });
    auto armors_image = ui::Button::create("backgrounds/armors.png");
    armors_image->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            button_clicking_audio->getInstance()->playEffect("music/button_effect.mp3", false);
            // 处理场景切换
            auto to_Display_armors_Scene = Display_armors_page::create(); // 创建新场景
            Director::getInstance()->pushScene(to_Display_armors_Scene); // 切换到新场景
        }
        });
    auto backward_button = ui::Button::create("backgrounds/backwards.png");
    backward_button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            button_clicking_audio->getInstance()->playEffect("music/button_effect.mp3", false);
            Director::getInstance()->popScene();
        }
        });

    create_button(heroes_image, 0.1f, 0.6f, 0.08f, 0.08f);
    create_button(armors_image, 0.1f, 0.72f, 0.08f, 0.08f);
    create_button(backward_button, 0.1f, 0.48f, 0.08f, 0.08f);
    auto heroes_label = Label::createWithTTF("heroes", "fonts/Marker Felt.ttf", 24);
    auto armors_label = Label::createWithTTF("armors", "fonts/Marker Felt.ttf", 24);
    auto backward_label = Label::createWithTTF("reverse", "fonts/Marker Felt.ttf", 24);
    heroes_label->setPosition(Vec2(heroes_image->getPositionX(), heroes_image->getPositionY() - heroes_image->getContentSize().height / 2 - heroes_label->getContentSize().height / 2));
    armors_label->setPosition(Vec2(armors_image->getPositionX(), armors_image->getPositionY() - armors_image->getContentSize().height / 2 - armors_label->getContentSize().height / 2));
    backward_label->setPosition(Vec2(backward_button->getPositionX(), backward_button->getPositionY() - backward_button->getContentSize().height / 2 - backward_label->getContentSize().height / 2));

    auto BattleBegin = ui::Button::create("backgrounds/BattleStart.jpeg");
    create_button(BattleBegin, 0.85f, 0.2f, 0.15f, 0.13f);
    BattleBegin->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            button_clicking_audio->getInstance()->playEffect("music/button_effect.mp3", false);
            // 处理场景切换

#ifdef Debug_for_lianji

            if (isServerExist()) {
                auto to_BattleField = BattleField::create(); // 创建新场景
                Director::getInstance()->pushScene(to_BattleField); // 切换到新场景
                //startClient();

            }
            else {
                auto to_BattleField = BattleField::create(); // 创建新场景
                Director::getInstance()->pushScene(to_BattleField); // 切换到新场景
                //startServer();
            }
#endif // Debug_for_lianji

#ifdef eightBattle
            auto cv = new std::condition_variable();
            auto cvMutex = new std::mutex();
            // 启动后台线程
            //std::thread back();
            Vector<std::thread> threadList;
            for (const auto& player : PlayerManager::getInstance()->getPlayerList())
            {
                std::thread backgroundThread(&interval::create);
                //threadList.pushBack(std::thread backgroundThread(&interval::create););
                backgroundThread.detach();
            }   
#endif // eightBattle
#define doublebattle
#ifdef doublebattle
            auto intervalScene = interval::createScene();
            Director::getInstance()->pushScene(intervalScene);
#endif // doublebattle

            
            //auto to_BattleField = BattleField::create(); // 创建新场景
            //Director::getInstance()->pushScene(to_BattleField); // 切换到新场景

            

        }
        });

    this->addChild(BattleBegin, 1);
    this->addChild(heroes_image, 1);
    this->addChild(armors_image, 1);
    this->addChild(heroes_label, 1);
    this->addChild(armors_label, 1);
    this->addChild(backward_button, 1);
    this->addChild(backward_label, 1);

    return true;

}