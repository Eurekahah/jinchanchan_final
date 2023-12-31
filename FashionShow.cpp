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
	PlayerManager::getInstance()->setIsShowing(true);//����Ϊ����ѡ��

	auto battlefield_image = Sprite::create("backgrounds/BattleImage.jpg");// TO DO:�ƺ����Ի�����ͼ~
	create_background_page(battlefield_image);
	this->addChild(battlefield_image, -1);

	//presentEquipment();//չʾ���װ��

	addAllaLivedPlayers();

	onEnter();//onEnter������ָ���иò��볡���Ľ������ִ�еĺ���

    //onExit();//�˳�ʱ������Դ
	return true;
}

void FashionShow::addAllaLivedPlayers()
{
	playerList = PlayerManager::getInstance()->getPlayerList();
	for (const auto& player : playerList) {
		if (!player->getIsDead()) {// 
			player->setPosition(Vec2(200.0f + player->getPlayerId() * 75.0f, 250.0f));

			//player->pause();//һ��ʼ�ȶ����ܶ�
            player->removeFromParent();
			this->addChild(player);
			
			// TO DO:�����Ƿ�Ҫ��һ���ж��Ƿ���ѡ���bool�أ�����AI�Ļص�����
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
		});// TO DO:������bug

	int currentPlayerIndex = 0;

}

void FashionShow::updatePlayerState(float dt) {
	
	// �����ͣ��һ�����
	playerList.at(currentPlayerIndex)->resume();
    CCLOG("resume the player pause!");
    

	// �ƶ�����һ�����
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
			player->pause();//һ��ʼ�ȶ����ܶ�

		}
	}

	// ��onEnter�����д�����ʱ��������
	schedule(CC_SCHEDULE_SELECTOR(FashionShow::updatePlayerState), 5.0f);//��ʼ����ʱ��
}

void FashionShow::onExit() {	
	// ����������������������ͷ���Դ��
    //this->getChildByName("selection_layer")->removeFromParent();
	PlayerManager::getInstance()->setIsShowing(false);

    this->removeAllChildrenWithCleanup(1);

    

    Director::getInstance()->popScene();

    

	Scene::onExit();
}

const int selection_num = 8;
const Vec2 center_position = Vec2(500, 390);//Բ�����ڵ�λ��


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
    _radius = 200.0f;//�뾶
    _angleIncrement = 0.05f;//�ƶ����ٶ�
    setLocalZOrder(Z_order + 1);//��Ӣ�۲����һ���ĵط�
    _touchListener = cocos2d::EventListenerTouchOneByOne::create();
    // ���ô�����ʼ������
    _touchListener->onTouchBegan = CC_CALLBACK_2(SelectionLayer::onTouchBegan, this);

    // ����������ӵ��¼��ַ���
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
    _touchListener->setEnabled(false);//���ü�������ͣ
    _touchListener->setSwallowTouches(true); // ����Ϊ true��������ɴ����¼�

    return true;
}


void SelectionLayer::random_create() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 19);

    std::set<int> uniqueNumbers;//ʹ�ü��ϱ�֤Ԫ�ػ�����ͬ

    while (uniqueNumbers.size() < selection_num) {
        int randomNumber = distribution(gen);
        uniqueNumbers.insert(randomNumber);
    }
    //���������ڵ�

    int count = 1;
    for (int number : uniqueNumbers) {
        Equipment* equip = Equipment::create(number);
        this->addChild(equip);
        float angle = 2.0f * M_PI * count / selection_num;
        Vec2 position = Vec2(center_position.x + _radius * cos(angle), center_position.y + _radius * sin(angle));
        equip->setPosition(position);
        count++;
    }
    //0.5s����һ�κ���
    _touchListener->setEnabled(true);
    this->schedule(CC_SCHEDULE_SELECTOR(SelectionLayer::circle_move), 0.1f);
}

void SelectionLayer::circle_move(float interval) {
    for (Node* child : getChildren()) {
        Equipment* equip = dynamic_cast<Equipment*>(child);
        if (equip) {
            Vec2 position = equip->getPosition();
            float current_angle = atan2(position.y - center_position.y, position.x - center_position.x);//���㵱ǰ�Ƕ�
            current_angle += _angleIncrement;
            float newx = center_position.x + _radius * cos(current_angle);
            float newy = center_position.y + _radius * sin(current_angle);
            equip->setPosition(Vec2(newx, newy));
        }
    }
}

bool SelectionLayer::onTouchBegan(Touch* touch, cocos2d::Event* event) {
    Vec2 current_position = touch->getLocation();
    auto children = getChildren();//��õĻ��ǵ�ǰ����������ӽڵ�

    for (Node* child : children) {
        Equipment* equipment = dynamic_cast<Equipment*> (child);
        if (equipment) {
            if (equipment->getBoundingBox().containsPoint(current_position)) {
                equipment->pick_up();
                _touchListener->setEnabled(false);//ֹͣ������
                return true;
            }
        }
    }


}
