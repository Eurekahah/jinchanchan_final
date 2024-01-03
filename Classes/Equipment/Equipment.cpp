#include<iostream>
#include<string>
#include<vector>
#include "cocos2d.h"
#include "Equipment/Equipment.h"
#include"Hero/HeroNew.h"
#include"Player/PlayerManager.h"


USING_NS_CC;

//存储了装备的各种属性
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
	//找到plist中的路径进行初始化
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

//将两个的属性加到一起
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

//相减
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

//归0
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
	//把key转化为数字序号了
	_sprite_type = 0;//0执行装备逻辑
	cocos2d::ValueMap container = FileUtils::getInstance()->getValueVectorFromFile("DataforEquipment/EquipData.plist").at(int(key)).asValueMap();
	if (!Buff::init(container)) {
		return false;
	}
	else {
		_equip_number = key;
		//初始化为图片
		std::string png_file_name = "";
		png_file_name += std::to_string(key);
		png_file_name += ".webp";
		setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(png_file_name));//初始化图片
		setScale(1.0f);//初始化缩放比例  这里初始化了的话 注意之后getcontentsize的还是原图片大小 想要缩放后大小*getScale
		_init_sequence = -1;//在装备中的位置 初始为-1

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


//外部接口：捡起装备 请判断有碰撞之后调用
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
			_is_pressed = 1;//记录鼠标按下
		}
		return true;
	}
	return false;
	
}

//鼠标移动拖动装备 注意这之中的逻辑一定要简化 不要判断鼠标位置是否在图片内 使用is_pressed判断 否则会卡
void Equipment::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (_init_sequence!=-1&&_is_pressed==1) {
		event->stopPropagation();
		//鼠标按着并且移动
		Vec2 mouse_current_position = touch->getLocation();

		setPosition(mouse_current_position);	

		update();
	}
}

//等英雄层出来这两个都得改
//松开 碰撞也在这里
void Equipment::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	Vec2 touchposition = touch->getLocation();
	Rect spriteRect = getBoundingBox();

	if (spriteRect.containsPoint(touchposition) && _init_sequence != -1) {
		_is_pressed = 0;
		event->stopPropagation();
		//获取自己的碰撞体积
		Rect my_bounding_box = getBoundingBox();
		EquipmentBarforGame* game_equip_bar = Director::getInstance()->getRunningScene()->getChildByName<EquipmentBarforGame*>("EquipmentBarforGame");
		const auto& children = game_equip_bar->getChildren();
		bool is_success = 0;

		for (Node* child : children) {
			Equipment* other_sprite = dynamic_cast<Equipment*>(child);
			if (other_sprite && other_sprite != this) {
				Rect otherBoundingBox = other_sprite->getBoundingBox();
				if (my_bounding_box.intersectsRect(otherBoundingBox)) {
					//碰撞代码到此结束 精灵不是矩形请参考多边形精灵改变boundingbox 
					if (game_equip_bar->synthesis(this, other_sprite)) {
						is_success = 1;
						break;
					}

				}
			}
		}


		//寻找自己的id 然后getherolist
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
					//碰撞代码到此结束 精灵不是矩形请参考多边形精灵改变boundingbox 
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
					// 碰撞代码到此结束 精灵不是矩形请参考多边形精灵改变boundingbox 
					if (other_sprite->take_equip(this)) {
						is_success = 1;
					}
				}
			}
		}*/
		//不成功的情况
		if (is_success == 0) {
			this->setPosition(_init_position);//没成功要回到原来位置
			setLocalZOrder(Z_order);//设置渲染顺序 设置回去了
		}
	}


	
}




//确保精灵不飞出边界 从chatgpt上直接扒的 还挺好用
void Equipment::update() {
	auto sceneSize = Director::getInstance()->getVisibleSize();
	auto currentPosition = getPosition();

	// 获取精灵的锚点
	auto anchorPoint = getAnchorPoint();

	// 确保精灵不飞出左边界
	if (currentPosition.x - anchorPoint.x * getContentSize().width* getScale() < 0)
	{
		currentPosition.x = anchorPoint.x * getContentSize().width* getScale();
	}

	// 确保精灵不飞出右边界
	if (currentPosition.x + (1 - anchorPoint.x) * getContentSize().width*getScale() > sceneSize.width)
	{
		currentPosition.x = sceneSize.width - (1 - anchorPoint.x) * getContentSize().width* getScale();
	}

	// 确保精灵不飞出底边界
	if (currentPosition.y - anchorPoint.y *getContentSize().height* getScale() < 0)
	{
		currentPosition.y = anchorPoint.y * getContentSize().height* getScale();
	}

	// 确保精灵不飞出顶边界
	if (currentPosition.y + (1 - anchorPoint.y) * getContentSize().height* getScale() > sceneSize.height)
	{
		currentPosition.y = sceneSize.height - (1 - anchorPoint.y) * getContentSize().height* getScale();
	}

	// 更新精灵的位置
	setPosition(currentPosition);
}

void Equipment::ban_touch() {
	_touchListener->setEnabled(false);
}

void Equipment::resume_touch() {
	_touchListener->setEnabled(true);
}



//装备栏 做的layer
EquipmentBar* EquipmentBar:: create(const int max_num) {
	EquipmentBar* bar = new EquipmentBar();
	if (bar && bar->init(max_num)) {
		bar->autorelease();
		return bar;
	}
	CC_SAFE_DELETE(bar);
	return nullptr;

}

//初始化装备栏基类
bool EquipmentBar:: init(const int max_num) {
	if (!Layer::init()) {
		return false;
	}
	_capacity = max_num;
	return true;
}

//更新装备信息
void EquipmentBar::set_information(Equipment* equip, int sequence) {
	equip->setInitPosition(getposition(sequence));
	equip->setInitSequence(sequence);
}

//装备 数组和位置都修改掉
bool EquipmentBar::equip(Equipment* add_equipment) {
	if (_equipments.size() >= _capacity) {
		return 0;
	}
	int number = add_equipment->getEquipNumber();
	int sequence=0;
	log("_equip_number");
	if (number >= 0 && number <= 4) {
		//放到装备栏的最后面
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

//让修改后的数组可视化
void EquipmentBar::makeVisible(int sequence) {
	for (int i = sequence; i < _equipments.size(); i++) {
		set_information(_equipments.at(i), i);
		log("set_information");
		_equipments.at(i)->setPosition(_equipments.at(i)->getInitPosition());
		log("setposition");
	}
}

//合成 彻底删除了原来两个基础装备
bool EquipmentBar::synthesis(Equipment* first_equipment, Equipment* second_equipment) {
	
	int added_equip = first_equipment->getEquipNumber();
	int init_equip = second_equipment->getEquipNumber();
	auto bar = dynamic_cast<EquipmentBarforGame*>(Director::getInstance()->getRunningScene()->getChildByName("EquipmentBarforGame"));
	
	if (added_equip < B_E_NUM && init_equip < B_E_NUM) {

		if (_equipments.contains(first_equipment)) {
			complete_remove(first_equipment);
		}
		else {
			bar->complete_remove(first_equipment);//否则从装备区中移除
		}
		complete_remove(second_equipment);//将后一个装备移除
		//从数组中移除
		
		Equipment* new_equipment = new Equipment;
		int new_equipment_key = FileUtils::getInstance()->getValueVectorFromFile("DataforEquipment/synthesis_table.plist").at(added_equip).asValueVector().at(init_equip).asInt();
		new_equipment=Equipment::create(new_equipment_key);//合成表中的索引

		equip(new_equipment);
		return new_equipment;
	}
	return nullptr;
}

//将其从数组中和整个游戏中都删除
void EquipmentBar::complete_remove(Equipment* equip) {
	int index = equip->getInitSequence();
	int count = _equipments.size();

	if (index >= 0 && index < count) {
		_equipments.erase(index);
		equip->removeFromParent();//释放节点
	}

	makeVisible(index);
	return;
}




//以下是装备栏代码
EquipmentBarforGame* EquipmentBarforGame::create(const int max_num,const int id) {
	EquipmentBarforGame* bar = new EquipmentBarforGame();
	if (bar && bar->init(max_num,id)) {
		bar->autorelease();
		return bar;
	}
	CC_SAFE_DELETE(bar);
	return nullptr;
}

//写层请参考这里
bool EquipmentBarforGame::init(const int max_num,const int id) {
	if (!EquipmentBar::init(max_num)) {
		return false;
	}
	_start_position = EquipmentBarStart;
	_interval = Interval;
	//setLocalZOrder(Z_order+2);//规定好层的渲染顺序 这个需要比英雄层高
	setName("EquipmentBarforGame");//规定好层的名称
	_player_id = id;
	//如果是ai
	if (id == 1) {
		setVisible(false);
		//取消它的监听器
	}

	setLocalZOrder(2);//设置渲染层数 比较高层
	
	return true;
}

//计算应该在的位置
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
	//此处重新使用监听器
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

//计算位置
Vec2 EquipmentBarforHero::getposition(int sequence) {
	Vec2 position = Vec2(RelativeStart.x,RelativeStart.y+sequence*(_interval+48));
	return position;
}

//将英雄身上所有装备卸下放到装备栏中
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

//英雄身上装备自动合成 层的提取请参考此处
bool EquipmentBarforHero::auto_equip(Equipment* equipment) {
	//空的 直接装备
	int result = 0;
	//层的提取
	auto bar = dynamic_cast<EquipmentBarforGame*>(Director::getInstance()->getRunningScene()->getChildByName("EquipmentBarforGame"));
	if (_equipments.empty()) {
		result=equip(equipment);
		if (result == 1) {
			bar->remove_one(equipment);
		}
	}
	//不空 先试试合成
	else {
		result = synthesis(equipment, _equipments.back());
		//不能合成 再试试直接装备
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



//以下是英雄类需要添加的东西


// 这两个地方 使用_bar->getTotalBuff()即可得到装备的总属性的集合体 类型是指针 具体属性参考上面的Buff 等到攻击公式出来请使用 
//注意标记percent的属性 是int存的百分比 请转化为相应的float使用


//测试用例 只有unload_equip是接口 用于删除英雄时拆卸所有装备
//以下注释没用 不用看
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

	// 初始化自己的成员变量
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


	// 在这里可以添加其他初始化逻辑，例如显示伤害数字的精灵等

	return true;
}

float Damage::calculate() {

}


bool Effect::init(int& key,Actor* hero,float& begin_time) {
	ValueMap container=//
	if (!Buff::init(container)) {
		return false;
	}

	// 初始化 Effect 类的成员变量
	this->_triger = ;
	this->_end = ;
	this->_property = ;
	this->_status = ;
	this->_effect_num = ;
	_target_actor = hero;
	_begin_time=//战斗开始时间
	// 其他初始化逻辑可以添加在这里

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
			_begin_time =//战斗开始时间
				_end_time = _begin_time + duration;
			return 1;
		case 1:
			if()//如果英雄current生命值为60% 则return 1
	}
}

bool Effect::end_condition() {

}
*/



