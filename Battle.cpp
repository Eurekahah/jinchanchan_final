# include "Battle.h"
/*以下*/
const float Player_init_pos = 150.f;
/*以上*/
using namespace cocos2d;
int BattleField::money = 20;
const std::string StoreLayer::HERO_SELECTED_EVENT = "hero_selected_event";
const float imageSize = 100.0f;// 图片大小

//#define DEBUG

StoreLayer* StoreLayer::create() {
    StoreLayer* pRet = new(std::nothrow) StoreLayer();
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}
bool StoreLayer::init() {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建背景框（作为商店界面的背景）
    background = LayerColor::create(Color4B(0, 0, 0, 180), visibleSize.width * 0.5, visibleSize.height * 0.5);
    background->setPosition(origin.x + visibleSize.width * 0.25, origin.y + visibleSize.height * 0.25);
    this->addChild(background);

    // 添加图片和文字
    // 
    // 
    // ...
    this->display_random_heroes();
    // 创建退出按钮
    auto exitButton = cocos2d::ui::Button::create("backgrounds/exit_image.png", "backgrounds/exit_image.png");
    exitButton->setPosition(Vec2(background->getContentSize().width - exitButton->getContentSize().width / 2,
        background->getContentSize().height - exitButton->getContentSize().height / 2));
    exitButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            this->removeFromParentAndCleanup(true);
        }
        });
    background->addChild(exitButton);
    

    return true;
}
void StoreLayer::buttonClicked(Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    CCLOG("totoal num=%d", BattleField::total_num);
    
    //auto money = PlayerManager::getInstance()->getPlayerByID(0)->getMoney();
    //CCLOG("money=%d", money);
    if (BattleField::total_num < 5 && BattleField::money>1) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            int tag = button->getTag();
            BattleField::money -= 2;
            PlayerManager::getInstance()->getPlayerByID(0)->setMoney(BattleField::money);
            //CCLOG("money==%d", money);
            //std::string imageName = StringUtils::format("heroes/%d.png", tag);

            //auto image = cocos2d::Sprite::create(imageName);
            //image->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, 50));
            //this->addChild(image);
            button->setVisible(false);
            EventCustom event(HERO_SELECTED_EVENT);
            event.setUserData(&tag);
            // 分发事件
            _eventDispatcher->dispatchEvent(&event);
            /*
            auto image = cocos2d::Sprite::create(imageName);
            // 获取当前Scene的引用
            auto currentScene = Director::getInstance()->getRunningScene();
            // 计算图片应该放置的位置，这里我们放在屏幕底部中间
            Vec2 position = Vec2(Director::getInstance()->getVisibleSize().width / 2, 50);
            // 将图片的世界坐标转换为当前Scene的局部坐标
            Vec2 localPos = currentScene->convertToNodeSpace(position);
            // 设置图片在当前Scene中的位置
            image->setPosition(localPos);
            // 将图片添加到Scene中而不是Layer中
            currentScene->addChild(image);
            // 隐藏按钮
            button->setVisible(false);
            */

        }
    }
}


void StoreLayer::display_random_heroes() {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // 获取background的尺寸和位置
    Size backgroundSize = background->getContentSize();
    Vec2 backgroundOrigin = background->getPosition();

    // 以background为参照来定位按钮
    float startX = backgroundOrigin.x + backgroundSize.width * 0.20f - (backgroundSize.width / 2);
    float startY = backgroundOrigin.y + backgroundSize.height * 0.72f - (backgroundSize.height / 2);

    const int numButtons = 12;  // 总按钮数
    const int maxButtonsPerRow = 4;  // 每行的最大按钮数
    const float buttonWidth = 100.0f;  // 按钮宽度
    const float buttonHeight = 100.0f;  // 按钮高度
    const float spacing = 10.0f;  // 按钮之间的间距

    for (int i = 0; i < numButtons; ++i) {
        int randomNum = std::rand() % 10 + 1; // 生成随机数以获取随机图片
        std::string buttonImage = StringUtils::format("heroes/%d.png", randomNum);

        // 计算每个图片的位置
        int row = i / maxButtonsPerRow;
        int col = i % maxButtonsPerRow;
        Vec2 buttonPosition = Vec2(startX + col * (buttonWidth + spacing),
            startY - row * (buttonHeight + spacing)); // 更新Y坐标计算

        // 创建图片按钮
        auto button = cocos2d::ui::Button::create(buttonImage);
        button->setPosition(buttonPosition);
        button->setScale(buttonWidth / button->getContentSize().width, buttonHeight / button->getContentSize().height);
        button->setTag(randomNum);  // 设置按钮标签
        button->addTouchEventListener(CC_CALLBACK_2(StoreLayer::buttonClicked, this));
        background->addChild(button); // 确保添加到background中
    }

}

int BattleField::total_num = 0;

Scene* BattleField::createScene() {
    return BattleField::create();
}
//shanle
void BattleField::create_hero_by_number(int key) {
    auto heroList = PlayerManager::getInstance()->getPlayerByID(0)->getHeroList();
    switch (key) {
    case 1:
        heroList.pushBack(AkaliHero::create());//英雄放进heroList
    case 2:
        heroList.pushBack(AnnieHero::create());
    case 3:
        heroList.pushBack(AriHero::create());
    case 4:
        heroList.pushBack(CatalinaHero::create());
    case 5:
        heroList.pushBack(EvelynnHero::create());
    case 6:
        heroList.pushBack(EzrealHero::create());
    case 7:
        heroList.pushBack(GalenHero::create());
    case 8:
        heroList.pushBack(GiggsHero::create());
    case 9:
        heroList.pushBack(JinxHero::create());
    case 10:
        heroList.pushBack(KaiSaHero::create());
    case 11:
        heroList.pushBack(KennenHero::create());
    case 12:
        heroList.pushBack(KSanteHero::create());
    case 13:
        heroList.pushBack(LucianHero::create());
    }
}
Vec2 calculateNearestGridPosition(const Vec2& currentPos) {
    // 格子的尺寸
    const float gridWidth = 74.0f;
    const float gridHeight = 60.0f;

    // 计算当前位置相对于原点的偏移格子数
    int gridX = static_cast<int>((currentPos.x - (gridWidth / 2)) / gridWidth);
    int gridY = static_cast<int>((currentPos.y - (gridHeight / 2)) / gridHeight);

    // 计算最近格子中心的位置
    Vec2 nearestGridPosition = Vec2(
        (gridX * gridWidth) + (gridWidth / 2),
        (gridY * gridHeight) + (gridHeight / 2)
    );
    nearestGridPosition.x += 30.0f;
    nearestGridPosition.y += 30.0f;
    return nearestGridPosition;
}
void BattleField::create_reverse_and_audio() {
    auto button_clicking_audio = CocosDenshion::SimpleAudioEngine::getInstance();
    button_clicking_audio->getInstance()->preloadEffect("music/button_effect.mp3");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

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

    auto backward_button = ui::Button::create("backgrounds/backwards.png");
    backward_button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            button_clicking_audio->getInstance()->playEffect("music/button_effect.mp3", false);
            Director::getInstance()->popScene();
        }
        });
    create_button(backward_button, 0.1f, 0.68f, 0.08f, 0.08f);
    this->addChild(backward_button, 1);
}
void BattleField::create_store() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto store_button = cocos2d::ui::Button::create("backgrounds/store.png", "backgrounds/store.png");
    create_button(store_button, 0.95f, 0.5f, 0.08f, 0.08f);
    //int money = PlayerManager::getInstance()->getPlayerByID(0)->getMoney();
    CCLOG("Money=%d", money);
    store_button->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (money >= 3) {
            if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
                money -= 3;
                PlayerManager::getInstance()->getPlayerByID(0)->setMoney(money);
                updateMoneyDisplay();
                auto storeLayer = StoreLayer::create();
                this->addChild(storeLayer, 1);
            }
        }
        });
    this->addChild(store_button);
    auto store_Label = cocos2d::Label::createWithTTF("store", "fonts/Arial.ttf", 40);
    store_Label->setPosition(visibleSize.width * 0.95f, visibleSize.height * 0.36f);
    this->addChild(store_Label, 1);
}
void BattleField::Activate_timer() {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建倒计时标签
    auto countdownLabel = cocos2d::Label::createWithTTF("10", "fonts/Marker Felt.ttf", 24);///
    countdownLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - countdownLabel->getContentSize().height / 2));
    this->addChild(countdownLabel, 1);

    // 创建进度条背景
    auto progressBar = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("backgrounds/progress_bar.png"));
    progressBar->setType(cocos2d::ProgressTimer::Type::BAR);
    progressBar->setScale(7.0, 1.0);
    // 设置进度条的起始位置为左边（可以根据需要修改）
    progressBar->setMidpoint(Vec2(0, 0));
    progressBar->setBarChangeRate(Vec2(1, 0));  // 水平减少

    // 设置进度条的位置和初始百分比
    progressBar->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 50));
    progressBar->setPercentage(100);  // 初始为100%
    this->addChild(progressBar);



    addPlayer(0);
    addPlayerHero(0);
    AI_clever* AIPlayer = dynamic_cast<AI_clever*>(PlayerManager::getInstance()->getPlayerByID(1));
    if (AIPlayer && AIPlayer->getIsAI())
    {
        AIPlayer->assign_hero();
        AIPlayer->put_hero_on_field();
    }

    int totalTime = 10;  // 总时间，比如50秒
    auto updateTimer = [progressBar, countdownLabel, totalTime,this](float dt) mutable {
        totalTime--;
        float percentage = static_cast<float>(totalTime) / 10.0f * 100.0f;///
        progressBar->setPercentage(percentage);
        countdownLabel->setString(std::to_string(totalTime));
        if (totalTime <= 0) {
            Director::getInstance()->getScheduler()->unschedule("update_progress_bar", progressBar);
            // 倒计时结束的逻辑
            //Director::getInstance()->popScene();
            //auto battlefield = BattleField::createScene();
            //waitForOthers();
            //Director::getInstance()->pushScene(battlefield);
            //BattleBegin(0, 1);
            
            roundBegin();
        }
    };

    // 每秒调用更新函数
    Director::getInstance()->getScheduler()->schedule(updateTimer, progressBar, 1.0f, false, "update_progress_bar");



}
void BattleField::display_bank_and_money() {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bank_button = ui::Button::create("backgrounds/bank.png");
    create_button(bank_button, 0.1f, 0.5f, 0.08f, 0.08f);
    this->addChild(bank_button, 1);
    //auto money = PlayerManager::getInstance()->getPlayerByID(0)->getMoney();
    moneyLabel = cocos2d::Label::createWithTTF(std::to_string(money), "fonts/Marker Felt.ttf", 40);
    moneyLabel->setPosition(visibleSize.width * 0.1f, visibleSize.height * 0.4f);
    this->addChild(moneyLabel, 1);

}
void BattleField::updateMoneyDisplay() {
    // 更新金钱显示
        // 更新金钱显示
    //auto money = PlayerManager::getInstance()->getPlayerByID(0)->getMoney();
    CCLOG("money===%d", money);
    if (moneyLabel)
        moneyLabel->setString(StringUtils::format("money:%d", money));
    auto listener = EventListenerCustom::create(StoreLayer::HERO_SELECTED_EVENT, [this](EventCustom* event) {
        if (moneyLabel)
        moneyLabel->setString(StringUtils::format("money:%d", money));
        });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}
void BattleField::Display_Heroes_Backup(int num) {
    const Rect sellZone = Rect(0, 270, 150, 120);
    const Rect targetRect = Rect(180, 150, 664, 464);


    // 检查是否有足够的空间添加下一张图片，如果没有，则不添加
    if (nextHeroPositionX + imageSize > screenSize.width) {
        // 超出屏幕范围，可以选择不添加图片或者重置位置到新的一行
        return; // 这里选择不添加图片
    }
    //auto image = Sprite::create(imageName);
    //hero = Hero::create();
    //Hero::path.push_back(std::make_pair(image, imageName));
    
    PlayerManager::getInstance()->getPlayerByID(0)->player_push_back_herolist(num);

    auto heroList = PlayerManager::getInstance()->getPlayerByID(0)->getHeroList();
    //Hero* hero;
    CCLOG("%d!!!!!!!!", num);
    
    //heroList.pushBack(hero);
    Hero* hero = heroList.back();
    Player* Player = PlayerManager::getInstance()->getPlayerByID(0);
    synthesis(hero);
    //Hero::displayedHeroes.push_back(image);
    // 设置图片大小
    auto originX = imageSize / hero->getContentSize().width;
    auto originY = imageSize / hero->getContentSize().height;
    hero->setScale(originX, originY);
    // 设置图片位置
    Vec2 position;
    position.x = nextHeroPositionX;
    position.y = screenSize.height * 0.1f;
    hero->setTeam(0);
    hero->setenemyTeam(1);
    hero->setPosition(position);
    hero->setOriginalPos(position);
    hero->setIsOnTheField(false);
    //match_hero[imageName]->original_position = position;
    //match_hero[imageName]->ToBattle = false;
    //match_hero[imageName]->ScaleX = originX;
    //match_hero[imageName]->ScaleY = originY;
    //Hero::backup_heroes[image] = position;
    //Hero::store_backup_pos[image] = position;
    // 添加图片到层

    //drag_heroes();
    this->addChild(hero);
    // 更新下一张图片的x坐标位置
    nextHeroPositionX += imageSize + spacing;

    CCLOG("Initial target rect: %f, %f, %f, %f", targetRect.origin.x, targetRect.origin.y, targetRect.size.width, targetRect.size.height);

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [this, hero](Touch* touch, Event* event) -> bool {
        auto bounds = hero->getBoundingBox();
        if (bounds.containsPoint(touch->getLocation())) {
            //Hero::backup_heroes[image] = image->getPosition();
            //hero->getPosition();//不确定有什么影响
            return true; // 处理触摸事件
        }
        return false;
    };

    listener->onTouchMoved = [this, hero](Touch* touch, Event* event) {
        // 移动英雄图像
        hero->setPosition(hero->getPosition() + touch->getDelta());
    };

    listener->onTouchEnded = [=](Touch* touch, Event* event) {
        // 释放英雄图像时，计算最近的格子并放置英雄

        CCLOG("Image position: %f, %f", hero->getPosition().x, hero->getPosition().y);
        CCLOG("Target rect: %f, %f, %f, %f", targetRect.origin.x, targetRect.origin.y, targetRect.size.width, targetRect.size.height);

        if (!targetRect.containsPoint(hero->getPosition()) && !sellZone.containsPoint(hero->getPosition())) {
            // 如果不在目标区域内，恢复到初始位置和大小
            hero->setIsOnTheField(false);
            CCLOG("Out of target rect, resetting position.");
            //Hero::backup_heroes[image] = Hero::store_backup_pos[image];
            hero->setPosition(hero->getOriginalPos());
            hero->setScale(originX, originY);
            //image->setPosition(Hero::backup_heroes[image].x, Hero::backup_heroes[image].y);
            //image->setScale(originX, originY);
            //match_hero[imageName]->setScale(originX, originY);
            //match_hero[imageName]->ScaleX = originX;
            //match_hero[imageName]->ScaleY = originY;
            //SetHeroesPosition(hero, Vec2(Hero::backup_heroes[image].x, Hero::backup_heroes[image].y), false);
        }
        else if (targetRect.containsPoint(hero->getPosition())) {
            // 如果在目标区域内，可以执行其他操作，例如放置在最近的格子
            CCLOG("Inside target rect, placing in grid.");
            //match_hero[imageName]->ToBattle = true;
            hero->setIsOnTheField(true);           
            Vec2 nearestGridPosition = calculateNearestGridPosition(hero->getPosition());
            const float gridWidth = 74.0f;
            const float gridHeight = 60.0f;
            float scaleX = gridWidth / hero->getContentSize().width;
            float scaleY = gridHeight / hero->getContentSize().height;
            hero->setScale(scaleX, scaleY);
            hero->setBattlePosition(nearestGridPosition);
            //hero->setBattlePos(nearestGridPosition);
            //hero->battle_position = nearestGridPosition;
            hero->setPosition(nearestGridPosition);
            //match_hero[imageName]->setScale(scaleX, scaleY);
            //match_hero[imageName]->ScaleX = scaleX;
            //match_hero[imageName]->ScaleY = scaleY;
            //Hero::used_heroes[image] = nearestGridPosition;
            //Hero::backup_heroes.erase(image);
            total_num--;
            float xPosition = spacing; // 从第一个位置开始
            for (auto& h : PlayerManager::getInstance()->getPlayerByID(0)->getHeroList()) {
                if (!h->getIsOnTheField()) {
                    h->setPosition(xPosition + imageSize * 2, screenSize.height * 0.1f);
                    h->setScale(imageSize / h->getContentSize().width, imageSize / h->getContentSize().height);
                    xPosition += imageSize + spacing;
                    h->setOriginalPos(Vec2(xPosition + imageSize, screenSize.height * 0.1f));
                    
                }

                //auto* hero = my_pair.first;
                //hero->setPosition(xPosition + imageSize * 2, screenSize.height * 0.1f);
                //hero->setScale(imageSize / hero->getContentSize().width, imageSize / hero->getContentSize().height);
                //xPosition += imageSize + spacing;
                //Hero::backup_heroes[hero] = (Vec2(xPosition + imageSize, screenSize.height * 0.1f));
                //Hero::store_backup_pos[hero] = (Vec2(xPosition + imageSize, screenSize.height * 0.1f));
                //SetHeroesPosition(hero, Vec2(xPosition + imageSize, screenSize.height * 0.1f), true);
            }
            nextHeroPositionX -= (imageSize + spacing);
        }
        else {

            removeAndUpdateSprite(hero);
            
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, hero);
}
void BattleField::removeAndUpdateSprite(Hero* image) {
    if (image == nullptr) {
        return;
    }
    int i = 0;
    auto heroList = PlayerManager::getInstance()->getPlayerByID(0)->getHeroList();
    for (Hero* h : heroList) {

        if (h->getHeroNumber() == image->getHeroNumber()) {
            h->removeFromParent();
            heroList.erase(i);
            //heroList.erase(h);
            total_num--;
        }
        i++;
    }
    image->removeFromParentAndCleanup(true);
    float xPosition = spacing; // 从第一个位置开始
    for (Hero* my_hero : heroList) {
        //CCLOG("image=%s", my_pair.first);
        //auto* hero = my_pair.first;
        my_hero->setPosition(xPosition + imageSize * 2, screenSize.height * 0.1f);
        my_hero->setScale(imageSize / my_hero->getContentSize().width, imageSize / my_hero->getContentSize().height);
        //hero->setPosition(xPosition + imageSize * 2, screenSize.height * 0.1f);
        my_hero->setScale(imageSize / my_hero->getContentSize().width, imageSize / my_hero->getContentSize().height);
        my_hero->setOriginalPos(Vec2(xPosition + imageSize, screenSize.height * 0.1f));
        xPosition += imageSize + spacing;
        //my_hero->setOriginalPos(Vec2(xPosition + imageSize, screenSize.height * 0.1f));

        //Hero::backup_heroes[hero] = (Vec2(xPosition + imageSize, screenSize.height * 0.1f));
        //Hero::store_backup_pos[hero] = (Vec2(xPosition + imageSize, screenSize.height * 0.1f));
    }
    nextHeroPositionX -= (imageSize + spacing);
    //auto money = PlayerManager::getInstance()->getPlayerByID(0)->getMoney();
    money += 2;
    PlayerManager::getInstance()->getPlayerByID(0)->setMoney(money);
    updateMoneyDisplay();
}
void BattleField::synthesis(Hero* image) {

    int num = 0;
    auto Player = PlayerManager::getInstance()->getPlayerByID(0);
    auto heroList = Player->getHeroList();
    for (const auto& heroInfo : heroList) {
        //heroInfo->getHeroNumber();
        if (image->getHeroNumber() == heroInfo->getHeroNumber()) {
            num++;
        }
    }
    CCLOG("num=%d", num);
    if (num >= 3) {
        int time = 0;
        for (const auto& heroInfo : heroList) {
            //std::string imagePath = heroInfo.second;
            if (image->getHeroNumber() == heroInfo->getHeroNumber() && time < 2) {
                removeAndUpdateSprite(heroInfo);
                time++;
            }
        }
    }

}
bool BattleField::init() {

    //initializeMatch(match);
    auto money = PlayerManager::getInstance()->getPlayerByID(0)->getMoney();
    CCLOG("money=%d", money);
    nextHeroPositionX = Director::getInstance()->getVisibleSize().width * 0.3f;
    auto battlefield_image = Sprite::create("backgrounds/BattleImage.jpg");
    create_background_page(battlefield_image);
    this->addChild(battlefield_image, -1);
    Activate_timer();
    create_reverse_and_audio();
    display_bank_and_money();
    create_store();
    //roundBegin();
    
    /*
    auto listener = EventListenerCustom::create(StoreLayer::HERO_SELECTED_EVENT, [this](EventCustom* event) {
        //std::string* imageName = static_cast<std::string*>(event->getUserData());
        int my_tag = (event->getUserData());
        this->Display_Heroes_Backup(match[my_tag]);
        // 在场景中放置图片
        });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    */
    auto listener = EventListenerCustom::create(StoreLayer::HERO_SELECTED_EVENT, [this](EventCustom* event) {
        int* my_tag_ptr = static_cast<int*>(event->getUserData());
    if (my_tag_ptr) {
        int my_tag = *my_tag_ptr;
        this->Display_Heroes_Backup(my_tag);
        // 在场景中放置图片
    }
        });

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    return true;

}

/*以下*/
void BattleField::createPlayers(int playerId, int enemyId)
{
    //addPlayer(playerId);
    //addPlayerHero(playerId);
    addEnemy(enemyId);
    addEnemyHero(enemyId);
}

void BattleField::addPlayer(int playerId)
{
    auto player = PlayerManager::getInstance()->getPlayerByID(playerId);
    if (player) {
        player->setPosition(Vec2(Player_init_pos, Player_init_pos));
        this->addChild(player);
    }
    else {
        CCLOG("player is nullptr!");
    }
}

void BattleField::addEnemy(int enemyId)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 center = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    auto enemy = PlayerManager::getInstance()->getPlayerByID(enemyId);
    if (enemy) {
        enemy->setIsEnemy(true);
        enemy->setPosition(Vec2(2 * center.x - Player_init_pos, 2 * center.y - Player_init_pos));
        this->addChild(enemy);
    }
    else {
        CCLOG("enemy is nullptr!");
    }

}

void BattleField::addPlayerHero(int playerId)
{
    auto player = PlayerManager::getInstance()->getPlayerByID(playerId);
    if (!player->getHeroList().empty()) {

        for (const auto& hero : player->getHeroList())
        {
            this->addChild(hero);
        }
    }
    else {
        CCLOG("player heroes is empty!");
    }
}

void BattleField::addEnemyHero(int enemyId)
{
    
    auto enemy = PlayerManager::getInstance()->getPlayerByID(enemyId);
    
    if (!enemy->getHeroList().empty()) {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        Vec2 center = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
        for (const auto& hero : enemy->getHeroList())
        {
            auto originPos = hero->getOriginalPos();
            hero->setPosition(Vec2(2 * center.x - originPos.x, 2 * center.y - originPos.y));
            CCLOG("pos:(%f,%f)", 2 * center.x - originPos.x, 2 * center.y - originPos.y);

            //this->removeFromParent();
            this->addChild(hero);
        }
    }
    else {
        CCLOG("enemy heroes is empty!");
    }
}

void BattleField::roundBegin()
{
#ifdef eightbattle
    std::srand(std::time(0));

    auto getRandNum = [](int min, int max) {return std::rand() % (max - min + 1) + min; };

    auto getOtherRandNum = [&](int min, int max, int num) {
        while (true) {
            int newNum = getRandNum(min, max);
            if (newNum == num) continue;
            return newNum;
        }
        return 0; };
    //获取随机不重复的两玩家ID
    int randID1;
    int randID2;
    while (true) {
        randID1 = getRandNum(0, 7);

        auto Player1 = PlayerManager::getInstance()->getPlayerByID(randID1);

        if (Player1->getIsDead() == true) { continue; }

        if (Player1->getIsInaRound() == true) { continue; }

        Player1->setIsInaRound(true);
    }

    while (true) {
        randID2 = getOtherRandNum(0, 7, randID1);

        auto Player2 = PlayerManager::getInstance()->getPlayerByID(randID2);

        if (Player2->getIsDead() == true) { continue; }

        if (Player2->getIsInaRound() == true) { continue; }

        Player2->setIsInaRound(true);

    }
    auto Player1 = PlayerManager::getInstance()->getPlayerByID(randID1);
    auto Player2 = PlayerManager::getInstance()->getPlayerByID(randID2);
    if (true/*TO DO: 改成是主机的判断，我们双人默认ID为0的玩家是主机，ID为1的玩家是客户端*/)
    {
        if (randID2 == 0) {
            BattleBegin(randID2, randID1);
        }
    }
    else if (false/*TO DO:改成是客户端的判断，*/)
    {
        if (randID2 == 1) {
            BattleBegin(randID2, randID1);
        }
    }
    else {
        BattleBegin(randID1, randID2);
    }
#endif // eightbattle
#define doublebattle
#ifdef doublebattle
    
    BattleBegin(0, 1);
#endif // doublebattle

    
}

void BattleField::BattleBegin(const int playerId,const int enemyId)
{
#define DEBUG
#ifdef DEBUG
    createPlayers(playerId, enemyId);

    CCLOG("%d", playerId);

    auto player1 = PlayerManager::getInstance()->getPlayerByID(playerId);
    
    removeHeroPause(player1->getHeroList());//场上英雄解禁
    auto player2 = PlayerManager::getInstance()->getPlayerByID(enemyId);
    
    removeHeroPause(player2->getHeroList());
    // TO DO:禁用玩家移动场上英雄
    player1->setIsInBattle(true);
    player2->setIsInBattle(true);
    // TO DO:所有场上hero的暂停状态解除


    //每隔一秒检查场上hero状态
    schedule([=](float dt) {
        updateHeroTarget(playerId);
        updateHeroTarget(enemyId);

        this->checkAllHeroesDead(enemyId);//检查敌方英雄是否全体阵亡
        this->checkAllHeroesDead(playerId);//检查玩家方是否英雄全体阵亡
        
        //this->removeChild(PlayerManager::getInstance()->getPlayerByID(1));
        if (player2->getIsRoundLose())
        {
            roundOver(playerId, enemyId, enemyId);

        }
        if (player1->getIsRoundLose())
        {
            //player1败
            roundOver(enemyId,playerId, enemyId);
        
        }
        
        }, 1.0f, "check_hero_key");
#endif // DEBUG

}
void BattleField::updateHeroTarget(int playerId)
{
    auto Player = PlayerManager::getInstance()->getPlayerByID(playerId);
    for (Hero* hero : Player->getHeroList())
    {
        hero->update(2);
        
    }


}

void BattleField::updateHeroesPosition() {

    auto screenSize = Director::getInstance()->getVisibleSize();
    const float spacing = screenSize.width * 0.04f; // 图片间隔
    float xPosition = spacing; // 从第一个位置开始
    for (auto& hero : PlayerManager::getInstance()->getPlayerByID(0)->getHeroList()) {
        hero->setPosition(hero->getOriginalPos());
        hero->setScale(imageSize / hero->getContentSize().width, imageSize / hero->getContentSize().height);
        xPosition += imageSize + spacing;
    }
}

void BattleField::removeHeroPause(Vector<Hero*> heroList)
{
    for (const auto& hero : heroList) {
        if (hero->getIsOnTheField() == true) {
            CCLOG("resume pause!");
            hero->resume();
        }

            
    }
}


void BattleField::checkAllHeroesDead(const int playerId) {
#ifdef DEBUG
    bool allDead = true;
    auto player = PlayerManager::getInstance()->getPlayerByID(playerId);
    //auto enemy= PlayerManager::getInstance()->getPlayerByID(enemyId);
    // 遍历所有英雄，检查是否有英雄存活
    CCLOG("player%d checking...", playerId);
    for (Hero* hero : player->getHeroList()) {
        if (hero->getIsOnTheField() && !hero->getIsDead()) {// TO DO:英雄类放入后要补充
            allDead = false;
            break;
        }
    }
    // 如果所有英雄都死亡，执行相应逻辑
    CCLOG("%d", allDead);
    if (allDead) {
        player->setIsRoundLose(true);//如果全体阵亡则置该玩家的isRoundLose属性为true，表示回合失败
        unschedule("check_hero_key");
        CCLOG("Player%d\'s heroes are all dead!",playerId);               
                
    }
#endif // DEBUG
}
void BattleField::updateHero(int id)
{
#ifdef DEBUG
    auto player = PlayerManager::getInstance()->getPlayerByID(id);
    //所有hero的血量回满
    for (Hero*& hero : player->getHeroList())// TO DO:
    {
        hero->updateAttributes();
        
    }
#endif // DEBUG
}
void BattleField::roundOver(int winnerId, int loserId,int enemyId)
{
#ifdef DEBUG
    setRound(getRound()+1);//回合数自增

    //获取胜者和败者
    auto winner = PlayerManager::getInstance()->getPlayerByID(winnerId);
    auto loser = PlayerManager::getInstance()->getPlayerByID(loserId);
    winner->setRound(getRound() + 1);
    loser->setRound(getRound() + 1);
    //败者扣血
    loser->decreaseBlood(20);
    if (loser->getBlood() <= 0)
    {
        loser->setIsDead(true);//将其设置为死亡状态
#ifdef doublebattle
        GameOver();
#endif // doublebattle
#ifdef eightbattle
        if (loserId == 0) {
            playerGameOver();
    }
#endif // eightbattle

        
        
    }

    // TO DO:胜者和败者金币数改变
    winner->moneychange();
    loser->moneychange();


    //回合结束后对方需要离开battleField，
    winner->setIsEnemy(false);
    loser->setIsEnemy(false);

    winner->setIsInaRound(false);
    loser->setIsInaRound(false);

    winner->setIsInBattle(false);
    loser->setIsInBattle(false);

    loser->setIsRoundLose(false);

    updateHero(winnerId);
    updateHero(loserId);
    
    //回合为偶数时进入选秀
    bool allReadyToFashionShow = true;
    for (const auto& player : PlayerManager::getInstance()->getPlayerList()) {
        if (player->getRound() % 2 != 0) {
            allReadyToFashionShow = false;
            break;
        }
    }
    //this->removeAllChildren();
    //removeEnemy(enemyId);

    if (allReadyToFashionShow)
    {
        goToFashionShow();
    }
    
    this->removeEnemy(enemyId);


    //goToInterval(loserId);
    //goToInterval(winnerId);
    

    
#endif // DEBUG
}

void BattleField::showRunes()
{
    Runes* rune_factory = Runes::create();
    runes_update();
}

void BattleField::removeEnemy(int enemyId)
{
    auto enemy = PlayerManager::getInstance()->getPlayerByID(enemyId);
    for (const auto& hero : enemy->getHeroList())
    {
        this->removeChild(hero);// TO DO:这个目前暂定是从battlefield场景中去除，加入英雄层
    }
    this->removeChild(enemy);
}

/*游戏结束结算*/
void BattleField::GameOver()// TO DO:
{
    // TO DO：
    //展示结算信息界面：
    //可以显示基本的如玩家排名：英雄图片之类的？
    

    //创建退出按钮:按钮作用退出结算界面
    auto exitButton = cocos2d::ui::Button::create("backgrounds/exit_image.png", "backgrounds/exit_image.png");
    exitButton->setPosition(Vec2(this->getContentSize().width - exitButton->getContentSize().width / 2,
        this->getContentSize().height - exitButton->getContentSize().height / 2));
    exitButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            this->removeFromParentAndCleanup(true);
            //this->removeAllChildren();
            //Director::getInstance()->popScene();           
        }
        });
    exitButton->setScale(3.0f);
    this->addChild(exitButton);

}

/*玩家提前死亡*/
void BattleField::playerGameOver()// TO DO:
{
    CCLOG("You are killed!");
    // TO DO:弹出是否结束游戏的按钮或界面
    //是：退出游戏
    // 创建退出按钮
    auto exitButton = cocos2d::ui::Button::create("backgrounds/exit_image.png", "backgrounds/exit_image.png");
    exitButton->setPosition(Vec2(this->getContentSize().width - exitButton->getContentSize().width / 2,
        this->getContentSize().height - exitButton->getContentSize().height / 2));
    exitButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            this->removeFromParentAndCleanup(true);
            //Director::getInstance()->popScene();
            GameOver();
        }
        });
    exitButton->setScale(3.0f);
    this->addChild(exitButton);
    // TO DO:否：可以进入观战（如果观战没做就只能选是了）
    //如果观战做了就再创建一个按钮~

    
}

//选秀
void BattleField::goToFashionShow()//选秀场景初始化
{
    auto FashionShowScene = FashionShow::createScene();
    Director::getInstance()->pushScene(FashionShowScene);
}

void BattleField::goToInterval(int playerId)//进入备战
{
    auto intervalScene = interval::createScene();

    //intervalScene->init();
    Director::getInstance()->pushScene(intervalScene);
#ifdef doublebattle
    /*可能有bug*/
    if (playerId == 1) {
        intervalScene->setVisible(false);
    }
#endif // doublebattle   
    Director::getInstance()->replaceScene(intervalScene);
}
/*以上*/

Scene* interval::createScene() 
{
    return interval::create();
}

bool interval::init()
{
    
    nextHeroPositionX = Director::getInstance()->getVisibleSize().width * 0.3f;
    auto battlefield_image = Sprite::create("backgrounds/BattleImage.jpg");
    create_background_page(battlefield_image);
    this->addChild(battlefield_image, -1);
    Activate_timer();
    create_reverse_and_audio();
    display_bank_and_money();
    create_store();
    createPlayer(0);
    //BattleBegin(0, 1);
    AIop(1);
    auto listener = EventListenerCustom::create(StoreLayer::HERO_SELECTED_EVENT, [this](EventCustom* event) {
        int* my_tag_ptr = static_cast<int*>(event->getUserData());
    if (my_tag_ptr) {
        int my_tag = *my_tag_ptr;
        this->Display_Heroes_Backup(my_tag);
        // 在场景中放置图片
    }
        });

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    

    return true;
}

void interval::createPlayer(int playerId)
{
    addPlayer(playerId);
    addPlayerHero(playerId);
}

void interval::Activate_timer() {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建倒计时标签
    auto countdownLabel = cocos2d::Label::createWithTTF("50", "fonts/Marker Felt.ttf", 24);
    countdownLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - countdownLabel->getContentSize().height / 2));
    this->addChild(countdownLabel, 1);

    // 创建进度条背景
    auto progressBar = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("backgrounds/progress_bar.png"));
    progressBar->setType(cocos2d::ProgressTimer::Type::BAR);
    progressBar->setScale(7.0, 1.0);
    // 设置进度条的起始位置为左边（可以根据需要修改）
    progressBar->setMidpoint(Vec2(0, 0));
    progressBar->setBarChangeRate(Vec2(1, 0));  // 水平减少

    // 设置进度条的位置和初始百分比
    progressBar->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 50));
    progressBar->setPercentage(100);  // 初始为100%
    this->addChild(progressBar);

    
    
    int totalTime = 20;  // 总时间，比如50秒
    auto updateTimer = [progressBar, countdownLabel, totalTime](float dt) mutable {
        totalTime--;
        float percentage = static_cast<float>(totalTime) / 20.0f * 100.0f;
        progressBar->setPercentage(percentage);
        countdownLabel->setString(std::to_string(totalTime));
        if (totalTime <= 0) {
            Director::getInstance()->getScheduler()->unschedule("update_progress_bar", progressBar);
            // 倒计时结束的逻辑
            Director::getInstance()->popScene();
            auto battlefield = BattleField::createScene();
            //waitForOthers();
            Director::getInstance()->pushScene(battlefield);
        }
    };

    // 每秒调用更新函数
    Director::getInstance()->getScheduler()->schedule(updateTimer, progressBar, 1.0f, false, "update_progress_bar");



}

void interval::AIop(int AIID)
{
    AI_clever* player = dynamic_cast<AI_clever*>( PlayerManager::getInstance()->getPlayerByID(AIID));
    if (player&&player->getIsAI())
    {
        player->assign_hero();
        player->put_hero_on_field();
        //player->assign_equipment();
    }
}

void interval::onExit()
{
    this->removeAllChildren();
    Scene::onExit();
}