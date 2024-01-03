#pragma once


#include<map>
#include<vector>
#include "cocos2d.h"
#include"BaseSpriteForEquip/BaseSpriteforEquip.h"
#include "ui/CocosGUI.h"

const int E_NUM = 20;
const int B_E_NUM = 5;
const int Z_order = 2;

const cocos2d::Vec2 EquipmentBarStart = cocos2d::Vec2(96*0.6-10,700);
const cocos2d::Vec2 RelativeStart = cocos2d::Vec2(1,1);
const int Interval = 10;
const int max_equip_number = 3;
const int max_capacity = 50;




enum EQUIPMENT{
    SWORD_OF_THE_STORM,           // 暴风之剑--0
    NEEDLESSLY_LARGE_ROD,         // 无用大棒--1
    LOCKET_OF_THE_IRON_SOLARI,    // 锁子甲--2
    GIANTS_BELT,                  // 巨人腰带--3
    BRAWLERS_GLOVES,              // 拳套--4
    INFINITY_EDGE,                // 无尽之刃--5
    ZEAL,                         // 珠光护手--6
    WARMONGS_ARMOR,               // 坚定之心--7
    BREAKER,                      // 破防者--8
    ARCHMAGES_GLOVES,             // 秘法手套--9
    STRAIGHT_CHALLENGERS_BRACER,  // 斯特拉克的挑战护手--10
    MORELLONOMICON,               // 莫雷洛秘典--11
    SUNFIRE_CAPE,                 // 日炎斗篷--12
    RANDUINS_OMEN,                // 狂徒铠甲--13
    DUSKBLADE_OF_DRAKTHARR,       // 夜之锋刃--14
    CROWN_GUARD,                  // 冕卫--15
    THORNMAIL,                    // 棘刺背心--16
    HEXTECH_GUNBLADE,             // 海克斯科技刃--17
    RABADONS_DEATHCAP,            // 班克斯的魔法帽--18
    KEEN_BLADE                    // 锐利之刃--19
};




enum TYPE {
    ARMOR,
    CHARACTER,
    OTHER
};


class TestButton : public cocos2d::ui::Button {
public:

    static TestButton* create();
    virtual bool init();
    
    // 按钮点击事件回调函数
    void onTestButtonClick(cocos2d::Ref* sender);


};

class Actor;
class EquipmentBarforGame;

class Buff :public BaseSpriteforEquip {
    
public:
    CC_SYNTHESIZE(int, _health_point, HealthPoint);//生命值 （应该是最大生命值）
    CC_SYNTHESIZE(int, _critical_rate, CriticalRate);//暴击率 整数表示百分比
    CC_SYNTHESIZE(int, _physical_defense, PhysicalDefense);//物理防御 
    CC_SYNTHESIZE(int, _magical_defense, MagicalDefense);//魔法防御
    CC_SYNTHESIZE(int, _physical_attack, PhysicalAttack);//物理攻击
    CC_SYNTHESIZE(int, _mana_attack, ManaAttack);//魔法攻击
    CC_SYNTHESIZE(int, _initial_mana, InitialMana);//初始法力值
    CC_SYNTHESIZE(float, _attack_speed, AttackSpeed);//攻击时间间隔
    CC_SYNTHESIZE(int, _critical_damage, CriticalDamage);//攻击暴击伤害 百分比 用int 储存

    static Buff* create(cocos2d::ValueMap& container);

    virtual bool init(cocos2d::ValueMap& container);
    
    virtual bool init(int healthPoint, int criticalRate, int physicalDefense,
        int magicalDefense, int physicalAttack, int manaAttack,
        int initialMana, float attackSpeed, int criticalDamage);

    static Buff* create(int healthPoint = 0, int criticalRate = 0, int physicalDefense = 0,
        int magicalDefense = 0, int physicalAttack = 0, int manaAttack = 0,
        int initialMana = 0, float attackSpeed = 0.0f, int criticalDamage = 0);

    void add_other(Buff* other);

    void  subtract_other(Buff* other);

    void reset();
};

class Equipment :public Buff {  
public:
    CC_SYNTHESIZE(int, _equip_number, EquipNumber);
    CC_SYNTHESIZE(cocos2d::Vec2, _init_position, InitPosition);
    CC_SYNTHESIZE(int, _init_sequence, InitSequence);
    CC_SYNTHESIZE(bool,_is_picked,isPicked);

    virtual bool init(int& key);

    static Equipment* create(int& key);

    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    //bool main_move_on_up(BaseSpriteforEquip* other_sprite);

    void update();

    virtual void ban_touch();
    virtual void resume_touch();

    Buff* operator+(Equipment* other_equip);
    Buff* operator-(Equipment* other_equip);

    bool pick_up();
};


class EquipmentBar :public Layer {
public:
    static EquipmentBar* create(const int max_num);

    bool init(const int max_num);

    virtual cocos2d::Vec2 getposition(int sequence) { return nullptr; }

    void complete_remove(Equipment* equip);

    void set_information(Equipment* equip, int sequence);

    void  makeVisible(int sequence);

    bool equip(Equipment* add_equipment);

    virtual bool synthesis(Equipment* first_equipment, Equipment* second_equipment);//在装备栏中合成装备

    virtual void node_manager(Equipment* equipment) { ; }

    CC_SYNTHESIZE(cocos2d::Vector<Equipment*>, _equipments, Equipments);
    CC_SYNTHESIZE(int, _capacity, Capacity);
    CC_SYNTHESIZE(cocos2d::Vec2, _start_position, StartPosition);
    CC_SYNTHESIZE(int, _interval, Interval);
    
};

class EquipmentBarforGame :public EquipmentBar {
public:
    virtual cocos2d::Vec2 getposition(int sequence);

    static EquipmentBarforGame* create(const int max_num,const int id);

    bool init(const int max_num,const int id);

    virtual void node_manager(Equipment* equipment);

    void remove_one(Equipment* equipment);

    CC_SYNTHESIZE(int, _player_id, PlayerId);

};

class EquipmentBarforHero :public EquipmentBar {
    CC_SYNTHESIZE(Buff*,_total_buff,TotalBuff);
public:
    static EquipmentBarforHero* create();

    bool init();

    virtual cocos2d::Vec2 getposition(int sequence);

    void unload_all();

    bool auto_equip(Equipment* equipment);

    virtual void node_manager(Equipment* equipment);
};





//以下没用 不必看
/*
class Effect :public Sprite {
    CC_SYNTHESIZE(int,_vampirism,Vampirism);
    CC_SYNTHESIZE(int, _shield, Shield);
    CC_SYNTHESIZE(int,_defense,Defense);
    CC_SYNTHESIZE(int, _max_hp, MaxHp);
    CC_SYNTHESIZE(int,_critical_damage,CriticalDamage);
    CC_SYNTHESIZE(int,_extra_damage,ExtraDamage);
    CC_SYNTHESIZE(int,_extra_physical_damage,ExtraPhysicalDamage);
    CC_SYNTHESIZE(int, _extra_mana_damage, ExtraManaDamage);

    CC_SYNTHESIZE(float, _begin_time, BeginTime);
    CC_SYNTHESIZE(float, _end_time, EndTime);
    CC_SYNTHESIZE(float, _duration, Duration);

public:
    static Effect* create(int key);

    virtual bool init(int key);

};
*/

/*
//把effect放到damage中实现，damage能够提取高级装备上的effect 那Damage上加上效果属性？
class Damage:public cocos2d::Sprite {
    CC_SYNTHESIZE(Actor*, _attack_side, AttackSide);
    CC_SYNTHESIZE(Actor*, _defense_side, DefenseSide);
    CC_SYNTHESIZE(int, _real_physical_damage, RealPhysicalDamage);
    CC_SYNTHESIZE(int, _real_mana_damage, RealManaDamage);
    CC_SYNTHESIZE(std::vector<EFFECT>, _effects, Effects);
public:
    static Damage* create(Actor* attack_side,Actor* defense_side);

    bool init(Actor* attack_side, Actor* defense_side);

    float calculate();
};

class Effect:public Buff {
    CC_SYNTHESIZE(TRIGER, _triger, Triger);
    CC_SYNTHESIZE(END, _end, End);
    CC_SYNTHESIZE(PROPERTY, _property, Property);
    CC_SYNTHESIZE(STATUS, _status, Status);
    CC_SYNTHESIZE(int, _effect_num,EffectNum);
    CC_SYNTHESIZE(float, _begin_time, BeginTime);
    CC_SYNTHESIZE(float, _end_time,EndTime);
    CC_SYNTHESIZE(float,_duration,Duration);
    CC_SYNTHESIZE(int, _condition_num, ConditionNum);
    CC_SYNTHESIZE(Actor*, _target_actor, TargetActor);
public:
    bool init(int& key, Actor* hero, float& begin_time);
    Effect* create(int& key, Actor* hero, float& begin_time);
    bool start_condition();
};

class Actor {
private:
    CC_SYNTHESIZE(std::vector<Effect*> ,_pre_used_effect,PreUsedEffect);

};*/

