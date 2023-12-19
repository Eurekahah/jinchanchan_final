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
void receive_heroes_status();//�յ�Ӣ�۵�����,����,λ����Ϣ

typedef vector<int> VI;
typedef vector<float> VF;
typedef vector<pair<float, float>> VFF;
typedef vector<pair<int, int>> VII;

class Hero_Status {

protected:
	int num_of_heroes;
	VF X_axis;//������
	VF Y_axis;//������
	VI hp;//Ѫ��
	VI magic;//����
	VI armors;//װ��
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
 




