#include<iostream>
#include"cocos2d.h"
#include"Selection.h"
#include"Equipment.h"
#include<random>
#include "cocos/base/CCScheduler.h"

USING_NS_CC;

const int selection_num = 8;
const Vec2 center_position = Vec2(500,390);//Բ�����ڵ�λ��


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
    setLocalZOrder(Z_order+1);//��Ӣ�۲����һ���ĵط�
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
    std::uniform_int_distribution<int> distribution(0, 4);

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
    this->schedule(CC_SCHEDULE_SELECTOR(SelectionLayer::circle_move),0.1f);
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
            equip->setPosition(Vec2(newx,newy));
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




