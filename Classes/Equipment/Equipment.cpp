#include<iostream>
#include<string>
#include<vector>
#include "cocos2d.h"
#include "Equipment/Equipment.h"
#include"Hero/HeroNew.h"
#include"Player/PlayerManager.h"


USING_NS_CC;

//�洢��װ���ĸ�������
bool Buff::init(cocos2d::ValueMap& container) {
	if (!BaseSpriteforEquip::init()) {
		return false;
	}
	_health_point = container.at("hp").asInt();//int
	_critical_rate = container.at("critical_rate").asInt();//percent
	_physical_defense = container.at("physical_defense").asInt();//int
	_magical_defense = container.at("magical_defense").asInt();//int
	_physical_attack = container.at("physical_attack").asInt();//percent
	_mana_attack = container.at("mana_attack").asInt();//percent
	_initial_mana = container.at("initial_mana").asInt();//int
	_attack_speed = container.at("attack_speed").asFloat();//percent
	_critical_damage = container.at("critical_damage").asInt();//percent
	
	return true;
	//�ҵ�plist�е�·�����г�ʼ��
}

Buff* Buff::create(cocos2d::ValueMap& container) {

	Buff* buff = new Buff;
	if (buff && buff->init(container)) {
		buff->autorelease();
		return buff;
	}
	CC_SAFE_DELETE(buff);
	return nullptr;
}

Buff* Buff::create(int healthPoint, int criticalRate, int physicalDefense,
	int magicalDefense, int physicalAttack, int manaAttack,
	int initialMana, float attackSpeed, int criticalDamage) {
	Buff* buff = new Buff();
	if (buff && buff->init(healthPoint, criticalRate, physicalDefense,
		magicalDefense, physicalAttack, manaAttack,
		initialMana, attackSpeed, criticalDamage)) {
		buff->autorelease();
		return buff;
	}
	CC_SAFE_DELETE(buff);
	return nullptr;
}

bool Buff::init(int healthPoint, int criticalRate, int physicalDefense,
	int magicalDefense, int physicalAttack, int manaAttack,
	int initialMana, float attackSpeed, int criticalDamage) {
	if (!BaseSpriteforEquip::init()) {
		return false;
	}
	setHealthPoint(healthPoint);
	setCriticalRate(criticalRate);
	setPhysicalDefense(physicalDefense);
	setMagicalDefense(magicalDefense);
	setPhysicalAttack(physicalAttack);
	setManaAttack(manaAttack);
	setInitialMana(initialMana);
	setAttackSpeed(attackSpeed);
	setCriticalDamage(criticalDamage);

	return true;
}

//�����������Լӵ�һ��
void Buff::add_other(Buff* other) {
	setHealthPoint(getHealthPoint() + other->getHealthPoint());
	setCriticalRate(getCriticalRate() + other->getCriticalRate());
	setPhysicalDefense(getPhysicalDefense() + other->getPhysicalDefense());
	setMagicalDefense(getMagicalDefense() + other->getMagicalDefense());
	setPhysicalAttack(getPhysicalAttack() + other->getPhysicalAttack());
	setManaAttack(getManaAttack() + other->getManaAttack());
	setInitialMana(getInitialMana() + other->getInitialMana());
	setAttackSpeed(getAttackSpeed() + other->getAttackSpeed());
	setCriticalDamage(getCriticalDamage() + other->getCriticalDamage());
}

//���
void  Buff::subtract_other(Buff* other) {
	setHealthPoint(getHealthPoint() - other->getHealthPoint());
	setCriticalRate(getCriticalRate() - other->getCriticalRate());
	setPhysicalDefense(getPhysicalDefense() - other->getPhysicalDefense());
	setMagicalDefense(getMagicalDefense() - other->getMagicalDefense());
	setPhysicalAttack(getPhysicalAttack() - other->getPhysicalAttack());
	setManaAttack(getManaAttack() - other->getManaAttack());
	setInitialMana(getInitialMana() - other->getInitialMana());
	setAttackSpeed(getAttackSpeed() - other->getAttackSpeed());
	setCriticalDamage(getCriticalDamage() - other->getCriticalDamage());
}

//��0
void Buff::reset() {
	setHealthPoint(0);
	setCriticalRate(0);
	setPhysicalDefense(0);
	setMagicalDefense(0);
	setPhysicalAttack(0);
	setManaAttack(0);
	setInitialMana(0);
	setAttackSpeed(0.0f);
	setCriticalDamage(0);
}



bool Equipment::init(int& key) {
	//��keyת��Ϊ���������
	_sprite_type = 0;//0ִ��װ���߼�
	cocos2d::ValueMap container = FileUtils::getInstance()->getValueVectorFromFile("DataforEquipment/EquipData.plist").at(int(key)).asValueMap();
	if (!Buff::init(container)) {
		return false;
	}
	else {
		_equip_number = key;
		//��ʼ��ΪͼƬ
		std::string png_file_name = "";
		png_file_name += std::to_string(key);
		png_file_name += ".webp";
		setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(png_file_name));//��ʼ��ͼƬ
		setScale(1.0f);//��ʼ�����ű���  �����ʼ���˵Ļ� ע��֮��getcontentsize�Ļ���ԭͼƬ��С ��Ҫ���ź��С*getScale
		_init_sequence = -1;//��װ���е�λ�� ��ʼΪ-1

		//setLocalZOrder(Z_order);
		_is_picked = 0;

		_touchListener->setEnabled(false);
		_touchListener->setSwallowTouches(true);
		setLocalZOrder(1);
		return true;
	}

}

Equipment* Equipment::create(int& key) {

	Equipment* equip = new Equipment;
	if (equip && equip->init(key)) {
		equip->autorelease();
		return equip;
	}
	CC_SAFE_DELETE(equip);

	return nullptr;

}


//�ⲿ�ӿڣ�����װ�� ���ж�����ײ֮�����
bool Equipment::pick_up() {
	auto _the_bar = dynamic_cast<EquipmentBarforGame*>(Director::getInstance()->getRunningScene()->getChildByName("EquipmentBarforGame"));
	_the_bar->equip(this);
	log("pick_up");
	_is_picked = 1;
	return true;
}


bool Equipment::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {

	Vec2 touchposition = touch->getLocation();
	Rect spriteRect = getBoundingBox();
	if (spriteRect.containsPoint(touchposition)&&_is_pressed==0) {
		if (_init_sequence == -1) {
			pick_up();
		}
		else {
			_is_pressed = 1;//��¼��갴��
		}
		return true;
	}
	return false;
	
}

//����ƶ��϶�װ�� ע����֮�е��߼�һ��Ҫ�� ��Ҫ�ж����λ���Ƿ���ͼƬ�� ʹ��is_pressed�ж� ����Ῠ
void Equipment::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (_init_sequence!=-1&&_is_pressed==1) {
		event->stopPropagation();
		//��갴�Ų����ƶ�
		Vec2 mouse_current_position = touch->getLocation();

		setPosition(mouse_current_position);	

		update();
	}
}

//��Ӣ�۲�������������ø�
//�ɿ� ��ײҲ������
void Equipment::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	Vec2 touchposition = touch->getLocation();
	Rect spriteRect = getBoundingBox();

	if (spriteRect.containsPoint(touchposition) && _init_sequence != -1) {
		_is_pressed = 0;
		event->stopPropagation();
		//��ȡ�Լ�����ײ���
		Rect my_bounding_box = getBoundingBox();
		EquipmentBarforGame* game_equip_bar = Director::getInstance()->getRunningScene()->getChildByName<EquipmentBarforGame*>("EquipmentBarforGame");
		const auto& children = game_equip_bar->getChildren();
		bool is_success = 0;

		for (Node* child : children) {
			Equipment* other_sprite = dynamic_cast<Equipment*>(child);
			if (other_sprite && other_sprite != this) {
				Rect otherBoundingBox = other_sprite->getBoundingBox();
				if (my_bounding_box.intersectsRect(otherBoundingBox)) {
					//��ײ���뵽�˽��� ���鲻�Ǿ�����ο�����ξ���ı�boundingbox 
					if (game_equip_bar->synthesis(this, other_sprite)) {
						is_success = 1;
						break;
					}

				}
			}
		}


		//Ѱ���Լ���id Ȼ��getherolist
		auto scene = Director::getInstance()->getRunningScene();
		const auto& children_for_hero = scene->getChildren();
		for (Node* child : children_for_hero) {
			Hero* other_sprite = dynamic_cast<Hero*> (child);

			if (other_sprite) {
				CCLOG(" team %d", other_sprite->getTeam());
			}

			if (other_sprite && other_sprite->getTeam() == 0) {
				
				Rect otherBoundingBox = other_sprite->getBoundingBox();
				if (my_bounding_box.intersectsRect(otherBoundingBox)) {
					//��ײ���뵽�˽��� ���鲻�Ǿ�����ο�����ξ���ı�boundingbox 
					if (other_sprite->take_equip(this)) {
						is_success = 1;
						break;
					}

				}
			}
		}
		/*
		for (int i = 0; i < herolist.size(); ++i) {
			Hero* other_sprite = herolist.at(i);
			if (other_sprite) {
				Rect otherBoundingBox = other_sprite->getBoundingBox();
				if (my_bounding_box.intersectsRect(otherBoundingBox)) {
					// ��ײ���뵽�˽��� ���鲻�Ǿ�����ο�����ξ���ı�boundingbox 
					if (other_sprite->take_equip(this)) {
						is_success = 1;
					}
				}
			}
		}*/
		//���ɹ������
		if (is_success == 0) {
			this->setPosition(_init_position);//û�ɹ�Ҫ�ص�ԭ��λ��
			setLocalZOrder(Z_order);//������Ⱦ˳�� ���û�ȥ��
		}
	}


	
}




//ȷ�����鲻�ɳ��߽� ��chatgpt��ֱ�Ӱǵ� ��ͦ����
void Equipment::update() {
	auto sceneSize = Director::getInstance()->getVisibleSize();
	auto currentPosition = getPosition();

	// ��ȡ�����ê��
	auto anchorPoint = getAnchorPoint();

	// ȷ�����鲻�ɳ���߽�
	if (currentPosition.x - anchorPoint.x * getContentSize().width* getScale() < 0)
	{
		currentPosition.x = anchorPoint.x * getContentSize().width* getScale();
	}

	// ȷ�����鲻�ɳ��ұ߽�
	if (currentPosition.x + (1 - anchorPoint.x) * getContentSize().width*getScale() > sceneSize.width)
	{
		currentPosition.x = sceneSize.width - (1 - anchorPoint.x) * getContentSize().width* getScale();
	}

	// ȷ�����鲻�ɳ��ױ߽�
	if (currentPosition.y - anchorPoint.y *getContentSize().height* getScale() < 0)
	{
		currentPosition.y = anchorPoint.y * getContentSize().height* getScale();
	}

	// ȷ�����鲻�ɳ����߽�
	if (currentPosition.y + (1 - anchorPoint.y) * getContentSize().height* getScale() > sceneSize.height)
	{
		currentPosition.y = sceneSize.height - (1 - anchorPoint.y) * getContentSize().height* getScale();
	}

	// ���¾����λ��
	setPosition(currentPosition);
}

void Equipment::ban_touch() {
	_touchListener->setEnabled(false);
}

void Equipment::resume_touch() {
	_touchListener->setEnabled(true);
}



//װ���� ����layer
EquipmentBar* EquipmentBar:: create(const int max_num) {
	EquipmentBar* bar = new EquipmentBar();
	if (bar && bar->init(max_num)) {
		bar->autorelease();
		return bar;
	}
	CC_SAFE_DELETE(bar);
	return nullptr;

}

//��ʼ��װ��������
bool EquipmentBar:: init(const int max_num) {
	if (!Layer::init()) {
		return false;
	}
	_capacity = max_num;
	return true;
}

//����װ����Ϣ
void EquipmentBar::set_information(Equipment* equip, int sequence) {
	equip->setInitPosition(getposition(sequence));
	equip->setInitSequence(sequence);
}

//װ�� �����λ�ö��޸ĵ�
bool EquipmentBar::equip(Equipment* add_equipment) {
	if (_equipments.size() >= _capacity) {
		return 0;
	}
	int number = add_equipment->getEquipNumber();
	int sequence=0;
	log("_equip_number");
	if (number >= 0 && number <= 4) {
		//�ŵ�װ�����������
		_equipments.pushBack(add_equipment);
		sequence = _equipments.size() - 1;
	}
	else {
		sequence = 0;
		_equipments.insert(sequence, add_equipment);
		
	}
	log("push_back");
	node_manager(add_equipment);
	makeVisible(sequence);
	return 1;

}

//���޸ĺ��������ӻ�
void EquipmentBar::makeVisible(int sequence) {
	for (int i = sequence; i < _equipments.size(); i++) {
		set_information(_equipments.at(i), i);
		log("set_information");
		_equipments.at(i)->setPosition(_equipments.at(i)->getInitPosition());
		log("setposition");
	}
}

//�ϳ� ����ɾ����ԭ����������װ��
bool EquipmentBar::synthesis(Equipment* first_equipment, Equipment* second_equipment) {
	
	int added_equip = first_equipment->getEquipNumber();
	int init_equip = second_equipment->getEquipNumber();
	auto bar = dynamic_cast<EquipmentBarforGame*>(Director::getInstance()->getRunningScene()->getChildByName("EquipmentBarforGame"));
	
	if (added_equip < B_E_NUM && init_equip < B_E_NUM) {

		if (_equipments.contains(first_equipment)) {
			complete_remove(first_equipment);
		}
		else {
			bar->complete_remove(first_equipment);//�����װ�������Ƴ�
		}
		complete_remove(second_equipment);//����һ��װ���Ƴ�
		//���������Ƴ�
		
		Equipment* new_equipment = new Equipment;
		int new_equipment_key = FileUtils::getInstance()->getValueVectorFromFile("DataforEquipment/synthesis_table.plist").at(added_equip).asValueVector().at(init_equip).asInt();
		new_equipment=Equipment::create(new_equipment_key);//�ϳɱ��е�����

		equip(new_equipment);
		return new_equipment;
	}
	return nullptr;
}

//����������к�������Ϸ�ж�ɾ��
void EquipmentBar::complete_remove(Equipment* equip) {
	int index = equip->getInitSequence();
	int count = _equipments.size();

	if (index >= 0 && index < count) {
		_equipments.erase(index);
		equip->removeFromParent();//�ͷŽڵ�
	}

	makeVisible(index);
	return;
}




//������װ��������
EquipmentBarforGame* EquipmentBarforGame::create(const int max_num,const int id) {
	EquipmentBarforGame* bar = new EquipmentBarforGame();
	if (bar && bar->init(max_num,id)) {
		bar->autorelease();
		return bar;
	}
	CC_SAFE_DELETE(bar);
	return nullptr;
}

//д����ο�����
bool EquipmentBarforGame::init(const int max_num,const int id) {
	if (!EquipmentBar::init(max_num)) {
		return false;
	}
	_start_position = EquipmentBarStart;
	_interval = Interval;
	//setLocalZOrder(Z_order+2);//�涨�ò����Ⱦ˳�� �����Ҫ��Ӣ�۲��
	setName("EquipmentBarforGame");//�涨�ò������
	_player_id = id;
	//�����ai
	if (id == 1) {
		setVisible(false);
		//ȡ�����ļ�����
	}

	setLocalZOrder(2);//������Ⱦ���� �Ƚϸ߲�
	
	return true;
}

//����Ӧ���ڵ�λ��
Vec2 EquipmentBarforGame::getposition(int sequence) {
	Vec2 position = Vec2(_start_position.x+(sequence/10)*(_interval + 96 * 0.6), _start_position.y - (sequence % 10) * (_interval + 96 * 0.6));
	return position;
}

void EquipmentBarforGame::node_manager(Equipment* equipment) {

	if (equipment->getParent() != nullptr) {
		equipment->removeFromParent();
	}
	this->addChild(equipment);
	equipment->setScale(1.0f);
	//equipment->setLocalZOrder(Z_order);
	//�˴�����ʹ�ü�����
	equipment->resume_touch();
}

void EquipmentBarforGame::remove_one(Equipment* equipment) {
	int index = _equipments.getIndex(equipment);
	if (index != -1) {
		_equipments.erase(index);
		makeVisible(index);
	}

}



EquipmentBarforHero*  EquipmentBarforHero::create() {
	EquipmentBarforHero* bar = new EquipmentBarforHero();
	if (bar && bar->init()) {
		bar->autorelease();
		return bar;
	}
	CC_SAFE_DELETE(bar);
	return nullptr;
}

bool EquipmentBarforHero::init() {
	if (!EquipmentBar::init(max_equip_number)) {
		return false;
	}
	_capacity = max_equip_number;
	_start_position = RelativeStart;
	_interval = Interval;
	_total_buff = Buff::create();
	this->addChild(_total_buff);
	_total_buff->getTouchListener()->setEnabled(false);
	return true;
}

//����λ��
Vec2 EquipmentBarforHero::getposition(int sequence) {
	Vec2 position = Vec2(RelativeStart.x,RelativeStart.y+sequence*(_interval+48));
	return position;
}

//��Ӣ����������װ��ж�·ŵ�װ������
void EquipmentBarforHero::unload_all() {
	int count = _equipments.size();
	
	for (int i = 0; i < count; i++) {
		Equipment* equipment = _equipments.back();
		auto bar = dynamic_cast<EquipmentBarforGame*>(Director::getInstance()->getRunningScene()->getChildByName("EquipmentBarforGame"));
		bar->equip(equipment);
		_equipments.popBack();

	}
	_total_buff->reset();
	makeVisible(0);
}

//Ӣ������װ���Զ��ϳ� �����ȡ��ο��˴�
bool EquipmentBarforHero::auto_equip(Equipment* equipment) {
	//�յ� ֱ��װ��
	int result = 0;
	//�����ȡ
	auto bar = dynamic_cast<EquipmentBarforGame*>(Director::getInstance()->getRunningScene()->getChildByName("EquipmentBarforGame"));
	if (_equipments.empty()) {
		result=equip(equipment);
		if (result == 1) {
			bar->remove_one(equipment);
		}
	}
	//���� �����Ժϳ�
	else {
		result = synthesis(equipment, _equipments.back());
		//���ܺϳ� ������ֱ��װ��
		if(!result) {
			result=equip(equipment);
			if (result == 1) {
				bar->remove_one(equipment);
			}
		}
	}
	return result;
	
}

void EquipmentBarforHero::node_manager(Equipment* equipment) {
	if (equipment->getParent() != nullptr) {
		equipment->removeFromParent();
	}
	this->addChild(equipment);
	equipment->setScale(1.0f);
	equipment->setLocalZOrder(Z_order);
	equipment->ban_touch();
	_total_buff->add_other(equipment);
}



//������Ӣ������Ҫ��ӵĶ���


// �������ط� ʹ��_bar->getTotalBuff()���ɵõ�װ���������Եļ����� ������ָ�� �������Բο������Buff �ȵ�������ʽ������ʹ�� 
//ע����percent������ ��int��İٷֱ� ��ת��Ϊ��Ӧ��floatʹ��


//�������� ֻ��unload_equip�ǽӿ� ����ɾ��Ӣ��ʱ��ж����װ��
//����ע��û�� ���ÿ�
/*
Effect* Effect::create(int key) {
	Effect* effect = new Effect();
	if (effect && effect->init(key)) {
		effect->autorelease();
		return effect;
	}
	else {
		CC_SAFE_DELETE(effect);
		return nullptr;
	}
}

bool Effect::init(int key) {
	cocos2d::ValueMap container = FileUtils::getInstance()->getValueVectorFromFile("data/EffectData.plist").at(int(key)).asValueMap();
	if (!Buff::init(container)) {
		return false;
	}

	// ��ʼ���Լ��ĳ�Ա����
	_vampirism = container.at("vampirism").asInt();
	_shield = container.at("shield").asInt();
	_burn = container.at("burn").asInt();

	return true;
}

*/

/*void Effect::apply() {

}*/

/*
Damage* Damage::create(Actor* attack_side, Actor* defense_side) {
	Damage* damage = new Damage();
	if (damage && damage->init(attack_side, defense_side)) {
		damage->autorelease();
		return damage;
	}
	else {
		CC_SAFE_DELETE( damage);
		return nullptr;
	}
}


bool Damage::init(Actor* attack_side, Actor* defense_side) {
	if (!Sprite::init()) {
		return false;
	}

	_attack_side = attack_side;

	_defense_side=defense_side;


	// ������������������ʼ���߼���������ʾ�˺����ֵľ����

	return true;
}

float Damage::calculate() {

}


bool Effect::init(int& key,Actor* hero,float& begin_time) {
	ValueMap container=//
	if (!Buff::init(container)) {
		return false;
	}

	// ��ʼ�� Effect ��ĳ�Ա����
	this->_triger = ;
	this->_end = ;
	this->_property = ;
	this->_status = ;
	this->_effect_num = ;
	_target_actor = hero;
	_begin_time=//ս����ʼʱ��
	// ������ʼ���߼��������������

	return true;
}

Effect* Effect::create(int& key, Actor* hero,float& begin_time) {
	Effect* effect = new (std::nothrow) Effect();
	if (effect && effect->init(key,hero,begin_time)) {
		effect->autorelease();
		return effect;
	}
	else {
		CC_SAFE_DELETE(effect);
		return nullptr;
	}
}

bool Effect::start_condition() {
	switch (_triger) {
		case 0:
			_begin_time =//ս����ʼʱ��
				_end_time = _begin_time + duration;
			return 1;
		case 1:
			if()//���Ӣ��current����ֵΪ60% ��return 1
	}
}

bool Effect::end_condition() {

}
*/



