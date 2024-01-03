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

    // ���ð�ť��λ��
    setPosition(Vec2(240, 160));

    // ��Ӱ�ť����¼��ص�
    addClickEventListener(CC_CALLBACK_1(TestButton::onTestButtonClick, this));
    setLocalZOrder(10);//�Ѳ��԰�ť���õ���߲�  
    
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

//ÿ����Ҫ����ʱ����
void runes_update() {
    Runes* rune_factory = dynamic_cast<Runes*>(Director::getInstance()->getRunningScene()->getChildByName("rune_selection"));//�ҵ����ò�
    rune_factory->getTouchListener()->setEnabled(true);//���ü�����
    //�����������ĵ�λ��
    Vec2 position_1 = RuneStart;
    Vec2 position_2 = Vec2(RuneStart.x, RuneStart.y - rune_height - Interval);
    //���������
    std::random_device rd;
    std::mt19937 gen(rd());
    int runes_stage_min = 3 * (rune_factory->getTimes()) + 1;
    int runes_stage_max = runes_stage_min + 2;
    rune_factory->setTimes(rune_factory->getTimes() + 1);//���������Ľײ�
    std::uniform_int_distribution<int> distribution(runes_stage_min, runes_stage_max);//����ָ����Χ�ķ���
    int randomNumber_1 = distribution(gen);
    int randomNumber_2;
    while (1) {
        randomNumber_2 = distribution(gen);
        if (randomNumber_1 != randomNumber_2) {
            break;
        }
    }
    //��������������������� �Ѿ���Ӳ��һ�������λ��
    rune_factory->random_create(randomNumber_1, position_1);
    rune_factory->random_create(randomNumber_2, position_2);
    //�������ѡ����� Ȼ��ر�layer ɾ�����нڵ�
    //��ѡ��ķ�����ӵ�store�� 
    //���е�һ��apply
}

//����rune�Ĺ��� Ҳ�Ƿ��÷��ĵĲ�
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
    setLocalZOrder(3);//���������в㶼��
    setName("rune_selection");
    //ע�ᵥ�㴥��
    _touchListener = cocos2d::EventListenerTouchOneByOne::create();
    // ���ô�����ʼ������
    _touchListener->onTouchBegan = CC_CALLBACK_2(Runes::onTouchBegan, this);

    // ����������ӵ��¼��ַ���
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
    _touchListener->setEnabled(false);//�ȰѼ���������Ϊ������
    _touchListener->setSwallowTouches(true);
    return true;
}

bool Runes::onTouchBegan(Touch* touch,Event* event) {
    event->stopPropagation();//��ֹ���´���
    Vec2 touchLocation=touch->getLocation();

    for (Node* child : getChildren()) {
        //��ȡ�����ӽڵ�
        Rune* sprite = dynamic_cast<Rune*>(child);
        if (sprite) {
            Rect spriteBoundingBox = sprite->getBoundingBox();
            if (spriteBoundingBox.containsPoint(touchLocation)) {
                sprite->add_to_store();
                getTouchListener()->setEnabled(false);//ֹͣ������

                return true; // ���� true ��ʾ����¼��Ѵ���
            }
        }
    }
}

//����ӵ��ڵ���
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




//����չʾ̨�İ�ť
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
    // ���ð�ť�����
    loadTextures("backgrounds/store.png", "backgrounds/store.png", "backgrounds/store.png");
    this->setPosition(rune_button_place);//����λ��
    // ��Ӱ�ť����¼�������
    this->addTouchEventListener(CC_CALLBACK_2(RunesButton::onButtonTouch, this));
    setLocalZOrder(3);
    return true;
}

void RunesButton::onButtonTouch(Ref* sender, ui::Widget::TouchEventType type) {
    Layer* current=dynamic_cast<Layer*>(Director::getInstance()->getRunningScene()->getChildByName("RuneStore"));

    //������runestore��ɼ� ���򲻿ɼ�
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            current->setVisible(!current->isVisible());
            break;
        default:
            break;
    }
}


//����չʾ̨
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
    setPosition(Vec2(RuneStart));//�Ѳ�ŵ�����λ��
    setVisible(false);
    return true;
}

void RuneStore::add_rune(Rune* rune) {
    _store.pushBack(rune);
    rune->removeFromParent();
    addChild(rune);
    rune->setScale(0.5f);
    rune->setPosition(getposition(_store.size()-1));//����λ��
}

Vec2 RuneStore::getposition(int sequence) {
    Vec2 position = Vec2(10,10-sequence * (Interval + rune_height*0.5f));//�������¼����
    return position;
}

//�ڻغϿ�ʼʱapply���з���
void RuneStore::start_apply() {
    //�غϿ�ʼʱapply
    for (int i = 0; i < _store.size(); i++) {
        _store.at(i)->apply();
    }
}



//���Ļ���
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
    //�ҵ�runestore�� ���Ҽӵ�����
    RuneStore* current = dynamic_cast<RuneStore*>(Director::getInstance()->getRunningScene()->getChildByName("RuneStore"));
    current->add_rune(this);
    //�����Ĳ�������ӽڵ�ɾ�� �ȴ���һ�θ���
    Runes* selection = dynamic_cast<Runes*>(Director::getInstance()->getRunningScene()->getChildByName("rune_selection"));
    selection->removeAllChildren();
    //���е�һ��apply
    selection->getTouchListener()->setEnabled(false);//ֹͣ���Ĳ�ļ�����
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
    //��ȡװ����
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
            //�����ԭ���� �������ڵ�
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
    // ��������� PumpedUp1 ��ĳ�ʼ���߼�
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
    // ��������� Kickstart ��ĳ�ʼ���߼�
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
    // ��������� TonsOfAttributes ��ĳ�ʼ���߼�

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
    // ��������� LowRates ��ĳ�ʼ���߼�

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

    // ��������� HedgeFund ��ĳ�ʼ���߼�
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
    // ��������� BinaryAirdrop ��ĳ�ʼ���߼�

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
    // ��������� UltimateAscension ��ĳ�ʼ���߼�

    return true;
}

