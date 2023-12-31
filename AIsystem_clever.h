#pragma once

#include<iostream>
#include"cocos2d.h"
#include"PlayerBase.h"
#include<vector>
#include "Equipment.h"
using namespace std;

enum career {
	Guardian,//护卫 0
	Assassin, //刺客 1
	Archer,//射手 2
	Mage, //法师 3

};

const int hero_on_field=6;//英雄场上容量
const int hero_capacity = 20;//待上场区+场上容量
const int square_width = 74.0f;//方格大小
const int square_height = 60.0f;//方格大小

//存储各职业最优坐标
const std::vector<std::vector<std::pair<int, int>>> best_position_for_careers = {
	{{5,4},{4,4},{6,4},{3,4},{7,4},{2,4}},
	{{5,3},{4,3},{6,3},{3,3},{7,3},{2,3}},
	{{5,2},{4,2},{6,2},{3,2},{7,2},{2,2}},
	{{5,1},{4,1},{6,1},{3,1},{7,1},{2,1}}
};

//每个装备对应赋值
const std::vector<int> equipment_power = {
	1,1,1,1,1,
	2,2,2,2,2,
	2,2,2,2,2,
	2,2,2,2,2,
	2,2,2,2,2
};

//计算hero的权值

struct equip_node {
	int vector_position;
	int power;
	equip_node(int v, int p) :vector_position(v), power(p) { ; }
};

bool compareEquipNodes(const equip_node* a, const equip_node* b) {
	// 按照power从大到小排序
	return a->power > b->power;
}

class AI_clever :public Player {
private:
	bool isAI;
	int hero_num;
	std::vector<int> hero_num_bucket;//英雄数量
	std::vector<int> occupied_number;//职业上场数
	CC_SYNTHESIZE(EquipmentBarforGame*, _game_bar, GameBar);
	//CC_SYNTHESIZE(RuneStore*, _rune_store, RuneStore);
public:
	virtual bool init(const std::string& filename);
	static AI_clever* create(const std::string& filename);


	//int get_power(Hero* the_hero);
	//修改英雄列表
	void filter_heroList();
	//分配并且选择角色
	void assign_hero();
	//把角色放在场上
	void put_hero_on_field();
	//分配装备
	void assign_equipment();
	//在选秀中选择装备
	void select_equipment();
	//选择符文
	void assign_runes();
	//满溢状态下调整数组
	void filter_heroList();
	//两种方式调整heroList
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
	CC_SYNTHESIZE(int, _power, Power);//权值
	CC_SYNTHESIZE(bool,is_on_field,IsOnField)
	

	virtual bool init();
	static Hero* create();

	void put_on_field(pair<int, int> pair_position);
	bool equip(Equipment* equip);
};

