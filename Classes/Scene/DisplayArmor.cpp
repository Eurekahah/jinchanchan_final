#include "DisplayArmor.h"
using namespace cocos2d;
Scene* Display_armors_page::createScene() {
    return Display_armors_page::create();
}
bool Display_armors_page::init() {



    auto button_clicking_audio = CocosDenshion::SimpleAudioEngine::getInstance();
    button_clicking_audio->getInstance()->preloadEffect("music/button_effect.mp3");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto display_armors_image = Sprite::create("backgrounds/display_armors.png");
    create_background_page(display_armors_image);
    this->addChild(display_armors_image, -1);

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

    float imgWidth = visibleSize.width * 0.15;  // 图片宽度
    float imgHeight = visibleSize.height * 0.15; // 图片高度
    float horizontalSpacing = visibleSize.width * 0.12;  // 水平间距
    float verticalSpacing = visibleSize.height * 0.08; // 垂直间距
    float delayTime = 0.1f; // 每张图片的延时时间

    int imagesPerRow = std::floor((visibleSize.width - visibleSize.width * 0.17) / (imgWidth + horizontalSpacing));
    float startX = visibleSize.width * 0.30;
    float startY = visibleSize.height * 0.88; // 从屏幕顶部0.12的位置开始排列（即总高度的88%处）
    auto scrollView = cocos2d::ui::ScrollView::create();
    scrollView->setContentSize(cocos2d::Director::getInstance()->getVisibleSize());
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
    scrollView->setBounceEnabled(true); // 启用弹跳效果（可选）
    scrollView->setScrollBarEnabled(true); // 显示滚动条
    scrollView->setInertiaScrollEnabled(false);

    this->addChild(scrollView, 0);
    auto container = scrollView->getInnerContainer();


    int totalRows = std::ceil(20.0 / imagesPerRow); // 总行数
    float totalHeight = totalRows * imgHeight + (totalRows - 1) * verticalSpacing;

    if (totalHeight < scrollView->getContentSize().height) {
        totalHeight = scrollView->getContentSize().height + 1;
    }

    scrollView->setInnerContainerSize(cocos2d::Size(scrollView->getContentSize().width, totalHeight));

    float y = totalHeight - imgHeight / 2; // 从内部容器顶部的指定位置开始

    for (int i = 0; i < 20; ++i) {
        std::string imageName = "armors/image" + std::to_string(i + 1) + ".png";
        auto sprite = cocos2d::Sprite::create(imageName);
        sprite->setScale(imgWidth / sprite->getContentSize().width, imgHeight / sprite->getContentSize().height);

        int row = i / imagesPerRow;
        int col = i % imagesPerRow;

        float x = startX + col * (imgWidth + horizontalSpacing);
        y = totalHeight - (row * (imgHeight + verticalSpacing) + imgHeight / 2);
        sprite->setPosition(x, y);
        sprite->setOpacity(0); // 初始时设置为透明
        // 创建延时和显示动作

        std::string labelText; // 为每个图片生成一个标签文本
        /*
        if (i == 0)
            labelText = "name:Chain mail\nproperty: +20 armor\n";
        else if (i == 1)
            labelText = "name:needlessly large rod\nproperty:+ 10% spell power";
        else if (i == 2)
            labelText = "name:sword of the storm\nproperty: +10% attack";
        else if (i == 3)
            labelText = "name:giant's belt\nproperty: +150 hp limit";
        else if (i == 4)
            labelText = "name:brawlers gloves\nproperty: +20% punch rate";
        else if (i == 5)
            labelText = "name:archmages gloves\nproperty:eqiup 2 random armors\nsynthesis:brawlers gloves+brawlers gloves";
        else if (i == 6)
            labelText = "name:corona\nproperty:gain a shield of 30% hp,maintain 8 sec,+35spell power\nsynthesis:needlessly large rod+chain mail:";
        else if (i == 7)
            labelText = "name:duskblade of draktharr\nproperty:avoid negative effests when hp is lower than 60%,gain 15% attack speed\nsynthesis:sword of the storm+chain mail";
        else if (i == 8)
            labelText = "name:rabadons deathcap\nproperty: 8% extra damage\nsynthesis:needlessly large rod+needlessly large rod";
        else if (i == 9)
            labelText = "name:hextech gunblade\nproperty: 22% all-round bloodsucking\nsynthesis:sword of the storm+needlessly large rod";
        else if (i == 10)
            labelText = "name:infinity edge\nproperty:";
        */

        auto my_label = cocos2d::Label::createWithTTF(labelText, "fonts/arial.ttf", 12);
        my_label->setPosition(x, y - sprite->getContentSize().height * sprite->getScaleY() / 2 - 10); // 标签位于图片下方
        container->addChild(my_label, 2);

        auto delay = cocos2d::DelayTime::create(delayTime * i); // 每张图片延时递增
        auto show = cocos2d::CallFunc::create([sprite]() {
            sprite->setOpacity(255); // 设置为不透明，显示图片
            });
        auto sequence = cocos2d::Sequence::create(delay, show, nullptr);
        sprite->runAction(sequence);
        container->addChild(sprite, 1); // 添加到滚动视图的内部容器中
    }

    return true;

}