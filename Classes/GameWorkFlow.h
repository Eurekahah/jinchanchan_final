#pragma once
#ifndef GAMEWORKFLOW_H_
#define GAMEWORKFLOW_H_
#include"cocos2d.h"
USING_NS_CC;

class GameWorkFlow :public Scene
{
public:
	GameWorkFlow();
	~GameWorkFlow();
	void Menu();//开始游戏
	void gameInit();//游戏初始化
	void interval();//游戏回合间隙
	void match();//游戏匹配
	void battle();//回合战斗
	void roundEnd();//回合结束的结算
	void draft();//选秀
	void GameEnd();//整局游戏结束的结算
	void total();//整体流程
};


#endif // !GAMEWORKFLOW_H_
