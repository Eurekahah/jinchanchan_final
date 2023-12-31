# include "Battle.h"
/*����*/
const float Player_init_pos = 150.f;
/*����*/
using namespace cocos2d;
int BattleField::money = 20;
const std::string StoreLayer::HERO_SELECTED_EVENT = "hero_selected_event";
const float imageSize = 100.0f;// ͼƬ��С

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

    // ������������Ϊ�̵����ı�����
    background = LayerColor::create(Color4B(0, 0, 0, 180), visibleSize.width * 0.5, visibleSize.height * 0.5);
    background->setPosition(origin.x + visibleSize.width * 0.25, origin.y + visibleSize.height * 0.25);
    this->addChild(background);

    // ���ͼƬ������
    // 
    // 
    // ...
    this->display_random_heroes();
    // �����˳���ť
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
            // �ַ��¼�
            _eventDispatcher->dispatchEvent(&event);
            /*
            auto image = cocos2d::Sprite::create(imageName);
            // ��ȡ��ǰScene������
            auto currentScene = Director::getInstance()->getRunningScene();
            // ����ͼƬӦ�÷��õ�λ�ã��������Ƿ�����Ļ�ײ��м�
            Vec2 position = Vec2(Director::getInstance()->getVisibleSize().width / 2, 50);
            // ��ͼƬ����������ת��Ϊ��ǰScene�ľֲ�����
            Vec2 localPos = currentScene->convertToNodeSpace(position);
            // ����ͼƬ�ڵ�ǰScene�е�λ��
            image->setPosition(localPos);
            // ��ͼƬ��ӵ�Scene�ж�����Layer��
            currentScene->addChild(image);
            // ���ذ�ť
            button->setVisible(false);
            */

        }
    }
}


void StoreLayer::display_random_heroes() {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // ��ȡbackground�ĳߴ��λ��
    Size backgroundSize = background->getContentSize();
    Vec2 backgroundOrigin = background->getPosition();

    // ��backgroundΪ��������λ��ť
    float startX = backgroundOrigin.x + backgroundSize.width * 0.20f - (backgroundSize.width / 2);
    float startY = backgroundOrigin.y + backgroundSize.height * 0.72f - (backgroundSize.height / 2);

    const int numButtons = 12;  // �ܰ�ť��
    const int maxButtonsPerRow = 4;  // ÿ�е����ť��
    const float buttonWidth = 100.0f;  // ��ť���
    const float buttonHeight = 100.0f;  // ��ť�߶�
    const float spacing = 10.0f;  // ��ť֮��ļ��

    for (int i = 0; i < numButtons; ++i) {
        int randomNum = std::rand() % 10 + 1; // ����������Ի�ȡ���ͼƬ
        std::string buttonImage = StringUtils::format("heroes/%d.png", randomNum);

        // ����ÿ��ͼƬ��λ��
        int row = i / maxButtonsPerRow;
        int col = i % maxButtonsPerRow;
        Vec2 buttonPosition = Vec2(startX + col * (buttonWidth + spacing),
            startY - row * (buttonHeight + spacing)); // ����Y�������

        // ����ͼƬ��ť
        auto button = cocos2d::ui::Button::create(buttonImage);
        button->setPosition(buttonPosition);
        button->setScale(buttonWidth / button->getContentSize().width, buttonHeight / button->getContentSize().height);
        button->setTag(randomNum);  // ���ð�ť��ǩ
        button->addTouchEventListener(CC_CALLBACK_2(StoreLayer::buttonClicked, this));
        background->addChild(button); // ȷ����ӵ�background��
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
        heroList.pushBack(AkaliHero::create());//Ӣ�۷Ž�heroList
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
    // ���ӵĳߴ�
    const float gridWidth = 74.0f;
    const float gridHeight = 60.0f;

    // ���㵱ǰλ�������ԭ���ƫ�Ƹ�����
    int gridX = static_cast<int>((currentPos.x - (gridWidth / 2)) / gridWidth);
    int gridY = static_cast<int>((currentPos.y - (gridHeight / 2)) / gridHeight);

    // ��������������ĵ�λ��
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

    // ��������ʱ��ǩ
    auto countdownLabel = cocos2d::Label::createWithTTF("10", "fonts/Marker Felt.ttf", 24);///
    countdownLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - countdownLabel->getContentSize().height / 2));
    this->addChild(countdownLabel, 1);

    // ��������������
    auto progressBar = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("backgrounds/progress_bar.png"));
    progressBar->setType(cocos2d::ProgressTimer::Type::BAR);
    progressBar->setScale(7.0, 1.0);
    // ���ý���������ʼλ��Ϊ��ߣ����Ը�����Ҫ�޸ģ�
    progressBar->setMidpoint(Vec2(0, 0));
    progressBar->setBarChangeRate(Vec2(1, 0));  // ˮƽ����

    // ���ý�������λ�úͳ�ʼ�ٷֱ�
    progressBar->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 50));
    progressBar->setPercentage(100);  // ��ʼΪ100%
    this->addChild(progressBar);



    addPlayer(0);
    addPlayerHero(0);
    AI_clever* AIPlayer = dynamic_cast<AI_clever*>(PlayerManager::getInstance()->getPlayerByID(1));
    if (AIPlayer && AIPlayer->getIsAI())
    {
        AIPlayer->assign_hero();
        AIPlayer->put_hero_on_field();
    }

    int totalTime = 10;  // ��ʱ�䣬����50��
    auto updateTimer = [progressBar, countdownLabel, totalTime,this](float dt) mutable {
        totalTime--;
        float percentage = static_cast<float>(totalTime) / 10.0f * 100.0f;///
        progressBar->setPercentage(percentage);
        countdownLabel->setString(std::to_string(totalTime));
        if (totalTime <= 0) {
            Director::getInstance()->getScheduler()->unschedule("update_progress_bar", progressBar);
            // ����ʱ�������߼�
            //Director::getInstance()->popScene();
            //auto battlefield = BattleField::createScene();
            //waitForOthers();
            //Director::getInstance()->pushScene(battlefield);
            //BattleBegin(0, 1);
            
            roundBegin();
        }
    };

    // ÿ����ø��º���
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
    // ���½�Ǯ��ʾ
        // ���½�Ǯ��ʾ
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


    // ����Ƿ����㹻�Ŀռ������һ��ͼƬ�����û�У������
    if (nextHeroPositionX + imageSize > screenSize.width) {
        // ������Ļ��Χ������ѡ�����ͼƬ��������λ�õ��µ�һ��
        return; // ����ѡ�����ͼƬ
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
    // ����ͼƬ��С
    auto originX = imageSize / hero->getContentSize().width;
    auto originY = imageSize / hero->getContentSize().height;
    hero->setScale(originX, originY);
    // ����ͼƬλ��
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
    // ���ͼƬ����

    //drag_heroes();
    this->addChild(hero);
    // ������һ��ͼƬ��x����λ��
    nextHeroPositionX += imageSize + spacing;

    CCLOG("Initial target rect: %f, %f, %f, %f", targetRect.origin.x, targetRect.origin.y, targetRect.size.width, targetRect.size.height);

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [this, hero](Touch* touch, Event* event) -> bool {
        auto bounds = hero->getBoundingBox();
        if (bounds.containsPoint(touch->getLocation())) {
            //Hero::backup_heroes[image] = image->getPosition();
            //hero->getPosition();//��ȷ����ʲôӰ��
            return true; // �������¼�
        }
        return false;
    };

    listener->onTouchMoved = [this, hero](Touch* touch, Event* event) {
        // �ƶ�Ӣ��ͼ��
        hero->setPosition(hero->getPosition() + touch->getDelta());
    };

    listener->onTouchEnded = [=](Touch* touch, Event* event) {
        // �ͷ�Ӣ��ͼ��ʱ����������ĸ��Ӳ�����Ӣ��

        CCLOG("Image position: %f, %f", hero->getPosition().x, hero->getPosition().y);
        CCLOG("Target rect: %f, %f, %f, %f", targetRect.origin.x, targetRect.origin.y, targetRect.size.width, targetRect.size.height);

        if (!targetRect.containsPoint(hero->getPosition()) && !sellZone.containsPoint(hero->getPosition())) {
            // �������Ŀ�������ڣ��ָ�����ʼλ�úʹ�С
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
            // �����Ŀ�������ڣ�����ִ�������������������������ĸ���
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
            float xPosition = spacing; // �ӵ�һ��λ�ÿ�ʼ
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
    float xPosition = spacing; // �ӵ�һ��λ�ÿ�ʼ
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
        // �ڳ����з���ͼƬ
        });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    */
    auto listener = EventListenerCustom::create(StoreLayer::HERO_SELECTED_EVENT, [this](EventCustom* event) {
        int* my_tag_ptr = static_cast<int*>(event->getUserData());
    if (my_tag_ptr) {
        int my_tag = *my_tag_ptr;
        this->Display_Heroes_Backup(my_tag);
        // �ڳ����з���ͼƬ
    }
        });

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    return true;

}

/*����*/
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
    //��ȡ������ظ��������ID
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
    if (true/*TO DO: �ĳ����������жϣ�����˫��Ĭ��IDΪ0�������������IDΪ1������ǿͻ���*/)
    {
        if (randID2 == 0) {
            BattleBegin(randID2, randID1);
        }
    }
    else if (false/*TO DO:�ĳ��ǿͻ��˵��жϣ�*/)
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
    
    removeHeroPause(player1->getHeroList());//����Ӣ�۽��
    auto player2 = PlayerManager::getInstance()->getPlayerByID(enemyId);
    
    removeHeroPause(player2->getHeroList());
    // TO DO:��������ƶ�����Ӣ��
    player1->setIsInBattle(true);
    player2->setIsInBattle(true);
    // TO DO:���г���hero����ͣ״̬���


    //ÿ��һ���鳡��hero״̬
    schedule([=](float dt) {
        updateHeroTarget(playerId);
        updateHeroTarget(enemyId);

        this->checkAllHeroesDead(enemyId);//���з�Ӣ���Ƿ�ȫ������
        this->checkAllHeroesDead(playerId);//�����ҷ��Ƿ�Ӣ��ȫ������
        
        //this->removeChild(PlayerManager::getInstance()->getPlayerByID(1));
        if (player2->getIsRoundLose())
        {
            roundOver(playerId, enemyId, enemyId);

        }
        if (player1->getIsRoundLose())
        {
            //player1��
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
    const float spacing = screenSize.width * 0.04f; // ͼƬ���
    float xPosition = spacing; // �ӵ�һ��λ�ÿ�ʼ
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
    // ��������Ӣ�ۣ�����Ƿ���Ӣ�۴��
    CCLOG("player%d checking...", playerId);
    for (Hero* hero : player->getHeroList()) {
        if (hero->getIsOnTheField() && !hero->getIsDead()) {// TO DO:Ӣ��������Ҫ����
            allDead = false;
            break;
        }
    }
    // �������Ӣ�۶�������ִ����Ӧ�߼�
    CCLOG("%d", allDead);
    if (allDead) {
        player->setIsRoundLose(true);//���ȫ���������ø���ҵ�isRoundLose����Ϊtrue����ʾ�غ�ʧ��
        unschedule("check_hero_key");
        CCLOG("Player%d\'s heroes are all dead!",playerId);               
                
    }
#endif // DEBUG
}
void BattleField::updateHero(int id)
{
#ifdef DEBUG
    auto player = PlayerManager::getInstance()->getPlayerByID(id);
    //����hero��Ѫ������
    for (Hero*& hero : player->getHeroList())// TO DO:
    {
        hero->updateAttributes();
        
    }
#endif // DEBUG
}
void BattleField::roundOver(int winnerId, int loserId,int enemyId)
{
#ifdef DEBUG
    setRound(getRound()+1);//�غ�������

    //��ȡʤ�ߺͰ���
    auto winner = PlayerManager::getInstance()->getPlayerByID(winnerId);
    auto loser = PlayerManager::getInstance()->getPlayerByID(loserId);
    winner->setRound(getRound() + 1);
    loser->setRound(getRound() + 1);
    //���߿�Ѫ
    loser->decreaseBlood(20);
    if (loser->getBlood() <= 0)
    {
        loser->setIsDead(true);//��������Ϊ����״̬
#ifdef doublebattle
        GameOver();
#endif // doublebattle
#ifdef eightbattle
        if (loserId == 0) {
            playerGameOver();
    }
#endif // eightbattle

        
        
    }

    // TO DO:ʤ�ߺͰ��߽�����ı�
    winner->moneychange();
    loser->moneychange();


    //�غϽ�����Է���Ҫ�뿪battleField��
    winner->setIsEnemy(false);
    loser->setIsEnemy(false);

    winner->setIsInaRound(false);
    loser->setIsInaRound(false);

    winner->setIsInBattle(false);
    loser->setIsInBattle(false);

    loser->setIsRoundLose(false);

    updateHero(winnerId);
    updateHero(loserId);
    
    //�غ�Ϊż��ʱ����ѡ��
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
        this->removeChild(hero);// TO DO:���Ŀǰ�ݶ��Ǵ�battlefield������ȥ��������Ӣ�۲�
    }
    this->removeChild(enemy);
}

/*��Ϸ��������*/
void BattleField::GameOver()// TO DO:
{
    // TO DO��
    //չʾ������Ϣ���棺
    //������ʾ�����������������Ӣ��ͼƬ֮��ģ�
    

    //�����˳���ť:��ť�����˳��������
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

/*�����ǰ����*/
void BattleField::playerGameOver()// TO DO:
{
    CCLOG("You are killed!");
    // TO DO:�����Ƿ������Ϸ�İ�ť�����
    //�ǣ��˳���Ϸ
    // �����˳���ť
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
    // TO DO:�񣺿��Խ����ս�������սû����ֻ��ѡ���ˣ�
    //�����ս���˾��ٴ���һ����ť~

    
}

//ѡ��
void BattleField::goToFashionShow()//ѡ�㳡����ʼ��
{
    auto FashionShowScene = FashionShow::createScene();
    Director::getInstance()->pushScene(FashionShowScene);
}

void BattleField::goToInterval(int playerId)//���뱸ս
{
    auto intervalScene = interval::createScene();

    //intervalScene->init();
    Director::getInstance()->pushScene(intervalScene);
#ifdef doublebattle
    /*������bug*/
    if (playerId == 1) {
        intervalScene->setVisible(false);
    }
#endif // doublebattle   
    Director::getInstance()->replaceScene(intervalScene);
}
/*����*/

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
        // �ڳ����з���ͼƬ
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

    // ��������ʱ��ǩ
    auto countdownLabel = cocos2d::Label::createWithTTF("50", "fonts/Marker Felt.ttf", 24);
    countdownLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - countdownLabel->getContentSize().height / 2));
    this->addChild(countdownLabel, 1);

    // ��������������
    auto progressBar = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("backgrounds/progress_bar.png"));
    progressBar->setType(cocos2d::ProgressTimer::Type::BAR);
    progressBar->setScale(7.0, 1.0);
    // ���ý���������ʼλ��Ϊ��ߣ����Ը�����Ҫ�޸ģ�
    progressBar->setMidpoint(Vec2(0, 0));
    progressBar->setBarChangeRate(Vec2(1, 0));  // ˮƽ����

    // ���ý�������λ�úͳ�ʼ�ٷֱ�
    progressBar->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 50));
    progressBar->setPercentage(100);  // ��ʼΪ100%
    this->addChild(progressBar);

    
    
    int totalTime = 20;  // ��ʱ�䣬����50��
    auto updateTimer = [progressBar, countdownLabel, totalTime](float dt) mutable {
        totalTime--;
        float percentage = static_cast<float>(totalTime) / 20.0f * 100.0f;
        progressBar->setPercentage(percentage);
        countdownLabel->setString(std::to_string(totalTime));
        if (totalTime <= 0) {
            Director::getInstance()->getScheduler()->unschedule("update_progress_bar", progressBar);
            // ����ʱ�������߼�
            Director::getInstance()->popScene();
            auto battlefield = BattleField::createScene();
            //waitForOthers();
            Director::getInstance()->pushScene(battlefield);
        }
    };

    // ÿ����ø��º���
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