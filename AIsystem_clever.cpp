
#include<iostream>
#include "cocos2d.h"
#include "PlayerBase.h"
#include"AIsystem_clever.h"
#include"Equipment.h"
#include"Runes.h"

USING_NS_CC;


bool AI_clever::init(const std::string& filename) {
	if (!Player::init(filename)) {
		return false;
	}
	else {
		isAI = 1;//��ʼ��Ϊai
		hero_num_bucket.resize(20);
		occupied_number.resize(4);
		return true;
	}
}

AI_clever* AI_clever::create(const std::string& filename) {
	AI_clever* the_ai = new (std::nothrow) AI_clever(); 
	if (the_ai && the_ai->init(filename)) {
		the_ai->autorelease();
		return the_ai;
	}
	else {
		CC_SAFE_DELETE(the_ai);
		return nullptr;
	}
}


void AI_clever::assign_hero() {
	int hero_num = money / 3;
	std::random_device rd;  
	std::mt19937 gen(rd()); 
	std::uniform_int_distribution<int> distribution(0, 19);

	for (int i = 0; i < hero_num; ++i) {
		int randomNumber = distribution(gen);
		//����Ͱ������
		hero_num_bucket[randomNumber]++;
		auto the_scene = Director::getInstance()->getRunningScene();
		Hero* new_hero = Hero::create();//����Ӣ�۱������Ӣ�� �����ڳ��� ע��
		heroList.pushBack(new_hero);//Ӣ�۷Ž�heroList
		money -= new_hero->getCost();
		synthesize();//���úϳɺ���							
	}

	money = money < 0 ? 0 : money;

	quicksort_power();
	//��������ɾ�� ����ɾ�������˼���Ͱ������
	filter_heroList();

	quicksort_field();
	
}

void AI_clever::put_hero_on_field() {
	std::fill(occupied_number.begin(), occupied_number.end(), 0);
	int current_on_field = 0;
	for (int i = 0; i < heroList.size(); i++) {
		Hero* the_hero = heroList.at(i);
		if (the_hero->getIsOnField() == true) {
			//��Ӣ�۴ӳ��ϳ��µĺ���
		}
		if (current_on_field < hero_on_field) {
			int career_number = the_hero->getCareer();
			occupied_number[career_number]++;
			pair<int, int> pair_position = best_position_for_careers[career_number][occupied_number.size() - 1];
			the_hero->put_on_field(pair_position);//����ĳ��λ�� ����ͼ����������ǳߴ� ע������onfield
			current_on_field++;
		}
		
	}

	
}

//����װ��
void AI_clever::assign_equipment(){
	auto equipment_bar = Director::getInstance()->getRunningScene()->getChildByName("EquipmentBarforGame");
	//�ҵ�equipment_bar ���֮��Ӧ����player_base�еĶ���
	if (equipment_bar) {
		const auto& children = equipment_bar->getChildren();
		for (Node* child : children) {
			if (Equipment* equipment = dynamic_cast<Equipment*> (child)) {
				//�������� װ����ʼ
				int next_to_equip = 0;
				if (!(heroList.at(next_to_equip)->equip(equipment))) {
					if (equipment->getEquipNumber() <= 4) {
						next_to_equip++;
					}
				}
				if (next_to_equip >= heroList.size()) {
					return;
				}
				
			}
		}
	}

}

void AI_clever::select_equipment() {
	auto selection_layer = Director::getInstance()->getRunningScene()->getChildByName("selection_layer");
	if (selection_layer) {
		const auto& children = selection_layer->getChildren();
		Vector<Equipment*> selection_equip;
		std::vector<equip_node> selection_equip_node;
		for (Node* child : children) {
			if (Equipment* equipment = dynamic_cast<Equipment*> (child)) {
				//�ŵ������ӳ��
				selection_equip.pushBack(equipment);//ref+1
				equip_node a =equip_node(selection_equip.size()-1,equipment_power[equipment->getEquipNumber()]);
				selection_equip_node.push_back(a);
			}
		}
		std::sort(selection_equip_node.begin(), selection_equip_node.end(), compareEquipNodes);
		int best_choice = selection_equip_node.front().vector_position;
		Equipment* equip = selection_equip.at(best_choice);//ָ��ѡ���equip
		equip->removeFromParent();//ref-1
		_game_bar->equip(equip);//ref+1
		//�����װ��ɾ������
		selection_equip.clear(); //ref - 1;
	}
}


void AI_clever::quicksort_power() {
	int size = heroList.size();
	for (int i = 1; i < size; i++) {
		Hero* current_hero = heroList.at(i);
		int j = i - 1;
		int number_1 = heroList.at(j)->getHeroNumber();
		int number_2 = current_hero->getHeroNumber();
		while (j >= 0 && heroList.at(j)->getPower()+hero_num_bucket[number_1] < current_hero->getPower()+hero_num_bucket[number_2]) {
			heroList.replace(j + 1, heroList.at(j));
			--j;
		}
		heroList.replace(j + 1, current_hero);
	}
};

void AI_clever::quicksort_field() {
	int size = heroList.size();
	for (int i = 1; i < size; i++) {
		Hero* current_hero = heroList.at(i);
		int j = i - 1;
		while (j >= 0 && heroList.at(j)->getPower() < current_hero->getPower()) {
			heroList.replace(j + 1, heroList.at(j));
			--j;
		}
		heroList.replace(j + 1, current_hero);
	}
}

void AI_clever::filter_heroList() {
	if (heroList.size() > hero_capacity) {
		int data = heroList.size() - hero_capacity;
		while (1) {
			int category = heroList.back()->getHeroNumber();
			hero_num_bucket[category]--;
			//���ð�һ��Ӣ�۷����̵�ĺ��� ע��Ǯ������ 
			heroList.popBack();
			data--;
			if (data <= 0 || heroList.size() == 0) {
				return;
			}
		}
	}
}

void Hero::put_on_field(pair<int,int> pair_position) {
	//���㳡��λ��
	Vec2 position = Vec2(square_width/2+square_width*(pair_position.first-1),square_height/2+square_height*(pair_position.second-1));
	this->setPosition(position);
}

bool Hero::init() {
	_power = _star + _level;
	return true;
}

//�ϳɺ�װ��������
bool Hero::equip(Equipment* equip) {
	int number = equip->getEquipNumber();
	_power += equipment_power[number];
}


