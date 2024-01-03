#pragma once 
#ifndef __FASHION_SHOW_H_
#define __FASHION_SHOW_H_

#include"cocos2d.h"
#include"Scene/create_button_and_scene.h"
#include"Player/PlayerManager.h"
#include"Equipment/Equipment.h"
#include<algorithm>
USING_NS_CC;

//class FashionShow :public Scene
//{
//public:
//	static Scene* createScene();
//
//	bool init();
//
//	virtual void onEnter();
//
//	virtual void onExit();
//
//	void addAllaLivedPlayers();//������л��ŵ����
//
//	void presentEquipment();//�������װ��
//
//	void beginShow();//��ʼѡ��װ��
//
//	void updatePlayerState(float dt);
//
//	CREATE_FUNC(FashionShow);
//
//	Vector<Player*> playerList; // �������
//
//	int currentPlayerIndex;//�������
//};

class SelectionLayer :public Layer {

public:

	static SelectionLayer* create();

	virtual bool init();

	void random_create();

	void circle_move(float interval);

	void selection_pick_up();

	~SelectionLayer();

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	CC_SYNTHESIZE(float, _radius, Radius);
	CC_SYNTHESIZE(float, _angleIncrement, AngleIncrement);
	CC_SYNTHESIZE(EventListenerTouchOneByOne*, _touchListener, TouchListener);  // ʹ������¼�������

};


#endif // !__FASHION_SHOW_H_
