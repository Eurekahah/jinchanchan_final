#include<iostream>
#include<string>
#include<vector>
#include "cocos2d.h"
#include"Equipment/Equipment.h"
#include "ui/CocosGUI.h"
#include<random>
#include "Scene/FashionShow.h"
#include"Runes.h"


USING_NS_CC;



TestButton* TestButton::create() {
    auto button = new (std::nothrow) TestButton();
    if (button && button->init()) {
        button->autorelease();
        return button;
    }
    else {
        delete button;
        return nullptr;
    }
}

bool TestButton::init() {
    if (!Button::init()) {
        return false;
    }
    loadTextures("store.png", "store.png", "store.png");

    // 设置按钮的位置
    setPosition(Vec2(240, 160));

    // 添加按钮点击事件回调
    addClickEventListener(CC_CALLBACK_1(TestButton::onTestButtonClick, this));
    setLocalZOrder(10);//把测试按钮设置到最高层  
    
    return true;
}

void TestButton::onTestButtonClick(Ref* sender) {
    CCLOG("Test Button Clicked");
    //auto selection_layer = dynamic_cast<SelectionLayer*>(Director::getInstance()->getRunningScene()->getChildByName("selection_layer"));
    //selection_layer->random_create();
    int key = 1;
    Equipment* equip = Equipment::create(key);
    Director::getInstance()->getRunningScene()->addChild(equip);
    equip->setPosition(500,500);
    
    runes_update();
}

//每次需要符文时调用
void runes_update() {
    Runes* rune_factory = dynamic_cast<Runes*>(Director::getInstance()->getRunningScene()->getChildByName("rune_selection"));//找到放置层
    rune_factory->getTouchListener()->setEnabled(true);//启用监听器
    //划定两个符文的位置
    Vec2 position_1 = RuneStart;
    Vec2 position_2 = Vec2(RuneStart.x, RuneStart.y - rune_height - Interval);
    //生成随机数
    std::random_device rd;
    std::mt19937 gen(rd());
    int runes_stage_min = 3 * (rune_factory->getTimes()) + 1;
    int runes_stage_max = runes_stage_min + 2;
    rune_factory->setTimes(rune_factory->getTimes() + 1);//更新所处的阶层
    std::uniform_int_distribution<int> distribution(runes_stage_min, runes_stage_max);//生成指定范围的符文
    int randomNumber_1 = distribution(gen);
    int randomNumber_2;
    while (1) {
        randomNumber_2 = distribution(gen);
        if (randomNumber_1 != randomNumber_2) {
            break;
        }
    }
    //根据随机数生成两个符文 已经添加并且划定好了位置
    rune_factory->random_create(randomNumber_1, position_1);
    rune_factory->random_create(randomNumber_2, position_2);
    //按下鼠标选择符文 然后关闭layer 删除所有节点
    //把选择的符文添加到store中 
    //进行第一次apply
}

//生产rune的工厂 也是放置符文的层
Runes* Runes::create() {
    Runes* rune = new Runes();
    if (rune && rune->init()) {
        rune->autorelease();
        return rune;
    }
    else {
        CC_SAFE_DELETE(rune);
        return nullptr;
    }
}

bool Runes::init() {
    if (!Layer::init()) {
        return false;
    }
    _times = 0;
    setLocalZOrder(3);//比其他所有层都高
    setName("rune_selection");
    //注册单点触摸
    _touchListener = cocos2d::EventListenerTouchOneByOne::create();
    // 设置触摸开始处理函数
    _touchListener->onTouchBegan = CC_CALLBACK_2(Runes::onTouchBegan, this);

    // 将监听器添加到事件分发器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
    _touchListener->setEnabled(false);//先把监听器设置为不工作
    _touchListener->setSwallowTouches(true);
    return true;
}

bool Runes::onTouchBegan(Touch* touch,Event* event) {
    event->stopPropagation();//防止向下传递
    Vec2 touchLocation=touch->getLocation();

    for (Node* child : getChildren()) {
        //获取符文子节点
        Rune* sprite = dynamic_cast<Rune*>(child);
        if (sprite) {
            Rect spriteBoundingBox = sprite->getBoundingBox();
            if (spriteBoundingBox.containsPoint(touchLocation)) {
                sprite->add_to_store();
                getTouchListener()->setEnabled(false);//停止监听器

                return true; // 返回 true 表示鼠标事件已处理
            }
        }
    }
}

//先添加到节点中
void Runes::random_create(int key,Vec2 position) {
    switch (key) {
        case 1:
            this->addChild(PandorasGear::create(position));
            break;
        case 2:
            this->addChild(PumpedUp1::create(position));
            break;
        case 3:
            this->addChild(Kickstart::create(position));
            break;
        case 4:
            this->addChild(TreasureTrove2::create(position));
            break;
        case 5:
            this->addChild(TonsOfAttributes::create(position));
            break;
        case 6:
            this->addChild(LowRates::create(position));
            break;
        case 7:
            this->addChild(HedgeFund::create(position));
            break;
        case 8:
            this->addChild(BinaryAirdrop::create(position));
            break;
        case 9:
            this->addChild(UltimateAscension::create(position));
            break;
        default:
            break;
    }
}




//符文展示台的按钮
RunesButton* RunesButton::create() {
    RunesButton* ret = new (std::nothrow) RunesButton();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool RunesButton::init() {
    if (!ui::Button::init()) {
        return false;
    }
    // 设置按钮的外观
    loadTextures("backgrounds/store.png", "backgrounds/store.png", "backgrounds/store.png");
    this->setPosition(rune_button_place);//设置位置
    // 添加按钮点击事件监听器
    this->addTouchEventListener(CC_CALLBACK_2(RunesButton::onButtonTouch, this));
    setLocalZOrder(3);
    return true;
}

void RunesButton::onButtonTouch(Ref* sender, ui::Widget::TouchEventType type) {
    Layer* current=dynamic_cast<Layer*>(Director::getInstance()->getRunningScene()->getChildByName("RuneStore"));

    //按下让runestore层可见 否则不可见
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            current->setVisible(!current->isVisible());
            break;
        default:
            break;
    }
}


//符文展示台
RuneStore* RuneStore::create() {
    RuneStore* ret = new (std::nothrow) RuneStore();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool RuneStore::init() {
    if (!Layer::init()) {
        return false;
    }
    setLocalZOrder(Z_order+2);
    setName("RuneStore");
    setPosition(Vec2(RuneStart));//把层放到合适位置
    setVisible(false);
    return true;
}

void RuneStore::add_rune(Rune* rune) {
    _store.pushBack(rune);
    rune->removeFromParent();
    addChild(rune);
    rune->setScale(0.5f);
    rune->setPosition(getposition(_store.size()-1));//计算位置
}

Vec2 RuneStore::getposition(int sequence) {
    Vec2 position = Vec2(10,10-sequence * (Interval + rune_height*0.5f));//从上向下计算的
    return position;
}

//在回合开始时apply所有符文
void RuneStore::start_apply() {
    //回合开始时apply
    for (int i = 0; i < _store.size(); i++) {
        _store.at(i)->apply();
    }
}



//符文基类
Rune* Rune::create() {
    Rune* rune = new Rune();
    if (rune && rune->init()) {
        rune->autorelease();
        return rune;
    }
    else {
        delete rune;
        return nullptr;
    }
}

bool Rune::init() {
    if (!Sprite::init()) {
        return false;
    }
    _rounds = 0;
    setLocalZOrder(1);
    return true;
}

bool Rune::add_to_store() {
    //找到runestore层 并且加到其中
    RuneStore* current = dynamic_cast<RuneStore*>(Director::getInstance()->getRunningScene()->getChildByName("RuneStore"));
    current->add_rune(this);
    //将符文层的所有子节点删除 等待下一次更新
    Runes* selection = dynamic_cast<Runes*>(Director::getInstance()->getRunningScene()->getChildByName("rune_selection"));
    selection->removeAllChildren();
    //进行第一次apply
    selection->getTouchListener()->setEnabled(false);//停止符文层的监听器
    //apply();
    return true;
}

void Rune::apply() {
    _rounds++;
}



PandorasGear* PandorasGear::create(Vec2 position) {

    PandorasGear* rune = new PandorasGear();
    if (rune && rune->init(position)) {
        rune->autorelease();
        return rune;
    }
    else {
        delete rune;
        return nullptr;
    }
}

bool PandorasGear::init(Vec2 position) {
    if (!Rune::init()) {
        return false;
    }
    setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("0.png"));
    setPosition(position);
    return true;
}

void PandorasGear::apply() {
    /*Rune::apply();
    //获取装备栏
    EquipmentBarforGame* _the_bar = dynamic_cast<EquipmentBarforGame*> (Director::getInstance()->getRunningScene()->getChildByName("EquipmentBarforGame"));
    if (_rounds == 0) {
        int randomInt = RandomHelper::random_int(0, E_NUM - 1);
        Equipment* equipment = Equipment::create(randomInt);
        _the_bar->addChild(equipment);
    }
    else {
        int count = _the_bar->getEquipments().size();
        Vector<Equipment*> the_equipments = _the_bar->getEquipments();
        for (int i = 0; i < count; i++) {
            //处理掉原来的 生成现在的
            _the_bar->complete_remove(the_equipments.at(i));
            int randomInt = RandomHelper::random_int(0, E_NUM - 1);
            _the_bar->equip(Equipment::create(randomInt));
        }
    }
    */
}



PumpedUp1* PumpedUp1::create(Vec2 position) {
    PumpedUp1* rune = new PumpedUp1();
    if (rune && rune->init(position)) {
        rune->autorelease();
        return rune;
    }
    else {
        delete rune;
        return nullptr;
    }
}

bool PumpedUp1::init(Vec2 position) {
    if (!Rune::init()) {
        return false;
    }
    setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("2.png"));
    // 在这里进行 PumpedUp1 类的初始化逻辑
    setPosition(position);
    return true;
}




Kickstart* Kickstart::create(Vec2 position) {
    Kickstart* rune = new Kickstart();
    if (rune && rune->init(position)) {
        rune->autorelease();
        return rune;
    }
    else {
        delete rune;
        return nullptr;
    }
}

bool Kickstart::init(Vec2 position) {
    if (!Rune::init()) {
        return false;
    }
    setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("1.png"));
    // 在这里进行 Kickstart 类的初始化逻辑
    setPosition(position);
    return true;
}



TreasureTrove2* TreasureTrove2::create(Vec2 position) {
    TreasureTrove2* rune = new TreasureTrove2();
    if (rune && rune->init(position)) {
        rune->autorelease();
        return rune;
    }
    else {
        delete rune;
        return nullptr;
    }
}

bool TreasureTrove2::init(Vec2 position) {
    if (!Rune::init()) {
        return false;
    }
    setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("4.png"));
    setPosition(position);
    return true;
}

void TreasureTrove2::apply() {
    Rune::apply();
    EquipmentBarforGame* _the_bar = dynamic_cast<EquipmentBarforGame*> (Director::getInstance()->getRunningScene()->getChildByName("EquipmentBarforGame"));
    if (_rounds >= 4) {
        return;
    }
    else {
        int randomInt = RandomHelper::random_int(0, B_E_NUM - 1);
        _the_bar->equip(Equipment::create(randomInt));
    }
}




TonsOfAttributes* TonsOfAttributes::create(Vec2 position) {
    TonsOfAttributes* rune = new TonsOfAttributes();
    if (rune && rune->init(position)) {
        rune->autorelease();
        return rune;
    }
    else {
        delete rune;
        return nullptr;
    }
}

bool TonsOfAttributes::init(Vec2 position) {
    if (!Rune::init()) {
        return false;
    }
    setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("5.png"));
    setPosition(position);
    // 在这里进行 TonsOfAttributes 类的初始化逻辑

    return true;
}



LowRates* LowRates::create(Vec2 position) {
    LowRates* rune = new LowRates();
    if (rune && rune->init(position)) {
        rune->autorelease();
        return rune;
    }
    else {
        delete rune;
        return nullptr;
    }
}

bool LowRates::init(Vec2 position) {
    if (!Rune::init()) {
        return false;
    }
    setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("3.png"));
    setPosition(position);
    // 在这里进行 LowRates 类的初始化逻辑

    return true;
}



HedgeFund* HedgeFund::create(Vec2 position) {
    HedgeFund* rune = new HedgeFund();
    if (rune && rune->init(position)) {
        rune->autorelease();
        return rune;
    }
    else {
        delete rune;
        return nullptr;
    }
}

bool HedgeFund::init(Vec2 position) {
    if (!Rune::init()) {
        return false;
    }

    // 在这里进行 HedgeFund 类的初始化逻辑
    setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("6.png"));
    setPosition(position);
    return true;
}



BinaryAirdrop* BinaryAirdrop::create(Vec2 position) {
    BinaryAirdrop* rune = new BinaryAirdrop();
    if (rune && rune->init(position)) {
        rune->autorelease();
        return rune;
    }
    else {
        delete rune;
        return nullptr;
    }
}

bool BinaryAirdrop::init(Vec2 position) {
    if (!Rune::init()) {
        return false;
    }
    setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("7.png"));
    setPosition(position);
    // 在这里进行 BinaryAirdrop 类的初始化逻辑

    return true;
}



UltimateAscension* UltimateAscension::create(Vec2 position) {
    UltimateAscension* rune = new UltimateAscension();
    if (rune && rune->init(position)) {
        rune->autorelease();
        return rune;
    }
    else {
        delete rune;
        return nullptr;
    }
}

bool UltimateAscension::init(Vec2 position) {
    if (!Rune::init()) {
        return false;
    }
    setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("8.png"));
    setPosition(position);
    // 在这里进行 UltimateAscension 类的初始化逻辑

    return true;
}

