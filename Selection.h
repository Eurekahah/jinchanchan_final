#pragma once
#include"cocos2d.h"
#include<iostream>
#include"BaseSprite.h"

USING_NS_CC;


class SelectionLayer :public Layer {

public:

	static SelectionLayer* create();

	virtual bool init();

	void random_create();

	void circle_move(float interval);

	void selection_pick_up();

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	CC_SYNTHESIZE(float, _radius, Radius);
	CC_SYNTHESIZE(float, _angleIncrement, AngleIncrement);
	CC_SYNTHESIZE(EventListenerTouchOneByOne*, _touchListener,TouchListener);  // 使用鼠标事件监听器

};