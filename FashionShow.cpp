#include"Scene/FashionShow.h"

Scene* FashionShow::createScene()
{
	return FashionShow::create();
}

bool FashionShow::init()
{
	if (!Scene::init()) {
		return false;
	}
	PlayerManager::getInstance()->setIsShowing(true);//设置为正在选秀

	auto battlefield_image = Sprite::create("backgrounds/BattleImage.jpg");// TO DO:似乎可以换个贴图~
	create_background_page(battlefield_image);
	this->addChild(battlefield_image, -1);

	//presentEquipment();//展示随机装备

	addAllaLivedPlayers();

	onEnter();//onEnter函数是指所有该插入场景的结点插入后执行的函数

    //onExit();//退出时清理资源
	return true;
}

void FashionShow::addAllaLivedPlayers()
{
	playerList = PlayerManager::getInstance()->getPlayerList();
	for (const auto& player : playerList) {
		if (!player->getIsDead()) {// 
			player->setPosition(Vec2(200.0f + player->getPlayerId() * 75.0f, 250.0f));

			//player->pause();//一开始先都不能动
            player->removeFromParent();
			this->addChild(player);
			
			// TO DO:这里是否要加一个判断是否在选秀的bool呢？方便AI的回调函数
			PlayerManager::getInstance()->setIsShowing(true);
		}
	}
}

void FashionShow::presentEquipment()
{
    auto circal = SelectionLayer::create();
    this->addChild(circal);
}

void FashionShow::beginShow()
{
	std::sort(playerList.begin(), playerList.end(), [](const Player* a, const Player* b) {
		return a->getBlood() < b->getBlood();
		});// TO DO:可能有bug

	int currentPlayerIndex = 0;

}

void FashionShow::updatePlayerState(float dt) {
	
	// 解除暂停下一个玩家
	playerList.at(currentPlayerIndex)->resume();
    CCLOG("resume the player pause!");
    

	// 移动到下一个玩家
	currentPlayerIndex = (currentPlayerIndex + 1);
	
	//playerList.at(currentPlayerIndex)->pause();
	CCLOG("%d/%d", currentPlayerIndex, playerList.size());
	

	if (currentPlayerIndex >= playerList.size()) {
		CCLOG("timer close.");
		unschedule(CC_SCHEDULE_SELECTOR(FashionShow::updatePlayerState));
		onExit();
	}
	
}

void FashionShow::onEnter() {
	Node::onEnter();

	for (const auto& player : playerList) {
		if (!player->getIsDead()) {// 
			player->pause();//一开始先都不能动

		}
	}

	// 在onEnter函数中创建计时器并启动
	schedule(CC_SCHEDULE_SELECTOR(FashionShow::updatePlayerState), 5.0f);//初始化计时器
}

void FashionShow::onExit() {	
	// 进行其他清理操作，例如释放资源等
    //this->getChildByName("selection_layer")->removeFromParent();
	PlayerManager::getInstance()->setIsShowing(false);

    this->removeAllChildrenWithCleanup(1);

    

    Director::getInstance()->popScene();

    

	Scene::onExit();
}

const int selection_num = 8;
const Vec2 center_position = Vec2(500, 390);//圆心所在的位置


SelectionLayer* SelectionLayer::create() {
    SelectionLayer* layer = new SelectionLayer();
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    else {
        delete layer;
        return nullptr;
    }
}


bool SelectionLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    setName("selection_layer");
    // Add your initialization code here
    _radius = 200.0f;//半径
    _angleIncrement = 0.05f;//移动的速度
    setLocalZOrder(Z_order + 1);//和英雄层放在一样的地方
    _touchListener = cocos2d::EventListenerTouchOneByOne::create();
    // 设置触摸开始处理函数
    _touchListener->onTouchBegan = CC_CALLBACK_2(SelectionLayer::onTouchBegan, this);

    // 将监听器添加到事件分发器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
    _touchListener->setEnabled(false);//先让监听器暂停
    _touchListener->setSwallowTouches(true); // 设置为 true，层会吞噬触摸事件

    return true;
}


void SelectionLayer::random_create() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 19);

    std::set<int> uniqueNumbers;//使用集合保证元素互不相同

    while (uniqueNumbers.size() < selection_num) {
        int randomNumber = distribution(gen);
        uniqueNumbers.insert(randomNumber);
    }
    //生成六个节点

    int count = 1;
    for (int number : uniqueNumbers) {
        Equipment* equip = Equipment::create(number);
        this->addChild(equip);
        float angle = 2.0f * M_PI * count / selection_num;
        Vec2 position = Vec2(center_position.x + _radius * cos(angle), center_position.y + _radius * sin(angle));
        equip->setPosition(position);
        count++;
    }
    //0.5s调用一次函数
    _touchListener->setEnabled(true);
    this->schedule(CC_SCHEDULE_SELECTOR(SelectionLayer::circle_move), 0.1f);
}

void SelectionLayer::circle_move(float interval) {
    for (Node* child : getChildren()) {
        Equipment* equip = dynamic_cast<Equipment*>(child);
        if (equip) {
            Vec2 position = equip->getPosition();
            float current_angle = atan2(position.y - center_position.y, position.x - center_position.x);//计算当前角度
            current_angle += _angleIncrement;
            float newx = center_position.x + _radius * cos(current_angle);
            float newy = center_position.y + _radius * sin(current_angle);
            equip->setPosition(Vec2(newx, newy));
        }
    }
}

bool SelectionLayer::onTouchBegan(Touch* touch, cocos2d::Event* event) {
    Vec2 current_position = touch->getLocation();
    auto children = getChildren();//获得的还是当前界面的所有子节点

    for (Node* child : children) {
        Equipment* equipment = dynamic_cast<Equipment*> (child);
        if (equipment) {
            if (equipment->getBoundingBox().containsPoint(current_position)) {
                equipment->pick_up();
                _touchListener->setEnabled(false);//停止监听器
                return true;
            }
        }
    }


}
