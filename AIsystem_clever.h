#pragma once

#include<iostream>
#include"cocos2d.h"
#include"PlayerBase.h"
#include<vector>
#include "Equipment.h"
using namespace std;

enum career {
	Guardian,//���� 0
	Assassin, //�̿� 1
	Archer,//���� 2
	Mage, //��ʦ 3

};

const int hero_on_field=6;//Ӣ�۳�������
const int hero_capacity = 20;//���ϳ���+��������
const int square_width = 74.0f;//�����С
const int square_height = 60.0f;//�����С

//�洢��ְҵ��������
const std::vector<std::vector<std::pair<int, int>>> best_position_for_careers = {
	{{5,4},{4,4},{6,4},{3,4},{7,4},{2,4}},
	{{5,3},{4,3},{6,3},{3,3},{7,3},{2,3}},
	{{5,2},{4,2},{6,2},{3,2},{7,2},{2,2}},
	{{5,1},{4,1},{6,1},{3,1},{7,1},{2,1}}
};

//ÿ��װ����Ӧ��ֵ
const std::vector<int> equipment_power = {
	1,1,1,1,1,
	2,2,2,2,2,
	2,2,2,2,2,
	2,2,2,2,2,
	2,2,2,2,2
};

//����hero��Ȩֵ

struct equip_node {
	int vector_position;
	int power;
	equip_node(int v, int p) :vector_position(v), power(p) { ; }
};

bool compareEquipNodes(const equip_node* a, const equip_node* b) {
	// ����power�Ӵ�С����
	return a->power > b->power;
}

class AI_clever :public Player {
private:
	bool isAI;
	int hero_num;
	std::vector<int> hero_num_bucket;//Ӣ������
	std::vector<int> occupied_number;//ְҵ�ϳ���
	CC_SYNTHESIZE(EquipmentBarforGame*, _game_bar, GameBar);
	//CC_SYNTHESIZE(RuneStore*, _rune_store, RuneStore);
public:
	virtual bool init(const std::string& filename);
	static AI_clever* create(const std::string& filename);


	//int get_power(Hero* the_hero);
	//�޸�Ӣ���б�
	void filter_heroList();
	//���䲢��ѡ���ɫ
	void assign_hero();
	//�ѽ�ɫ���ڳ���
	void put_hero_on_field();
	//����װ��
	void assign_equipment();
	//��ѡ����ѡ��װ��
	void select_equipment();
	//ѡ�����
	void assign_runes();
	//����״̬�µ�������
	void filter_heroList();
	//���ַ�ʽ����heroList
	void quicksort_power();
	void quicksort_field();


	~AI_clever();
};

class Hero:public Sprite {
	CC_SYNTHESIZE(int, _hero_number, HeroNumber);
	CC_SYNTHESIZE(int, _level,Level);
	CC_SYNTHESIZE(int,_star,Star);
	CC_SYNTHESIZE(int, _career, Career);
	CC_SYNTHESIZE(int, _cost, Cost);
	CC_SYNTHESIZE(int, _power, Power);//Ȩֵ
	CC_SYNTHESIZE(bool,is_on_field,IsOnField)
	

	virtual bool init();
	static Hero* create();

	void put_on_field(pair<int, int> pair_position);
	bool equip(Equipment* equip);
};

