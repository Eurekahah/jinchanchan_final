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
	void Menu();//��ʼ��Ϸ
	void gameInit();//��Ϸ��ʼ��
	void interval();//��Ϸ�غϼ�϶
	void match();//��Ϸƥ��
	void battle();//�غ�ս��
	void roundEnd();//�غϽ����Ľ���
	void draft();//ѡ��
	void GameEnd();//������Ϸ�����Ľ���
	void total();//��������
};


#endif // !GAMEWORKFLOW_H_
