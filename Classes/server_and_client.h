# pragma once

# ifndef _TCPSOCKET_H_
# define _TCPSOCKET_H_
# endif 

# include "CCDirector.h"
# include <iostream>
# include <WinSock2.h>
# include <vector>

# pragma comment(lib,"ws2_32.lib")
# pragma warning(disable:4996)
using namespace std;

bool isServerExist();
void startServer();
void startClient();
void receive_heroes_status();//收到英雄的数量,名称,位置信息

typedef vector<int> VI;
typedef vector<float> VF;
typedef vector<pair<float, float>> VFF;
typedef vector<pair<int, int>> VII;

class Hero_Status {

protected:
	int num_of_heroes;
	VF X_axis;//横坐标
	VF Y_axis;//纵坐标
	VI hp;//血量
	VI magic;//蓝量
	VI armors;//装备
public:
	void receive_data(int a, VF x,VF y, VI hp,VI mag, VI arm) {
		this->num_of_heroes = a;
		this->hp = hp;
		this->magic = magic;
		this->armors = arm;
		this->X_axis = x;
		this->Y_axis = y;
	}
	//virtual void display_position();
	//virtual void display_image();
	//virtual void display_armor();
	

};
 




