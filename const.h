#pragma once
#ifndef __CONST_H__
#define __CONST_H__

#include<map>
#include<vector>
#include<mutex>
#include "cocos2d.h"
#include"BaseSprite.h"
#include "ui/CocosGUI.h"
const int E_NUM = 20;
const int B_E_NUM = 5;
const int Z_order = 2;

const cocos2d::Vec2 EquipmentBarStart = cocos2d::Vec2(96*0.6-10,700);
const cocos2d::Vec2 RelativeStart = cocos2d::Vec2(1,1);
const int Interval = 10;
const int max_equip_number = 3;
const int max_capacity = 50;


const cocos2d::Vec2 RuneStart = cocos2d::Vec2(20,20);
const int rune_height = 170;
const cocos2d::Vec2 rune_button_place = cocos2d::Vec2(50,50);

enum EQUIPMENT{
    SWORD_OF_THE_STORM,           // ����֮��--0
    NEEDLESSLY_LARGE_ROD,         // ���ô��--1
    LOCKET_OF_THE_IRON_SOLARI,    // ���Ӽ�--2
    GIANTS_BELT,                  // ��������--3
    BRAWLERS_GLOVES,              // ȭ��--4
    INFINITY_EDGE,                // �޾�֮��--5
    ZEAL,                         // ��⻤��--6
    WARMONGS_ARMOR,               // �ᶨ֮��--7
    BREAKER,                      // �Ʒ���--8
    ARCHMAGES_GLOVES,             // �ط�����--9
    STRAIGHT_CHALLENGERS_BRACER,  // ˹�����˵���ս����--10
    MORELLONOMICON,               // Ī�����ص�--11
    SUNFIRE_CAPE,                 // ���׶���--12
    RANDUINS_OMEN,                // ��ͽ����--13
    DUSKBLADE_OF_DRAKTHARR,       // ҹ֮����--14
    CROWN_GUARD,                  // ����--15
    THORNMAIL,                    // ���̱���--16
    HEXTECH_GUNBLADE,             // ����˹�Ƽ���--17
    RABADONS_DEATHCAP,            // ���˹��ħ��ñ--18
    KEEN_BLADE                    // ����֮��--19
};

enum RUNES {
    PANDORAS_GEAR,          // �˶�����װ��
    PUMPED_UP1,           // ����1.0
    KICKSTART,              // ����

    TREASURE_TROVE2,      // ��زƱ�2.0
    TONS_OF_ATTRIBUTES,     // �ɶֵ�����
    LOW_RATES,              // ������

    HEDGE_FUND,            // �Գ����+
    BINARY_AIRDROP,         // �����ƿ�Ͷ
    ULTIMATE_ASCENSION,     // �ռ�����
};

enum EFFECT{
    VAMPIRISM,//��Ѫ
    SHIELD,//����
    DEFENSE//���գ�%1�������ֵ����ʵ�˺���
};

enum TYPE {
    ARMOR,
    CHARACTER,
    OTHER
};

class Actor;
class EquipmentBarforGame;

class Buff :public BaseSprite {
    
public:
    CC_SYNTHESIZE(int, _health_point, HealthPoint);//����ֵ ��Ӧ�����������ֵ��
    CC_SYNTHESIZE(int, _critical_rate, CriticalRate);//������ ������ʾ�ٷֱ�
    CC_SYNTHESIZE(int, _physical_defense, PhysicalDefense);//������� 
    CC_SYNTHESIZE(int, _magical_defense, MagicalDefense);//ħ������
    CC_SYNTHESIZE(int, _physical_attack, PhysicalAttack);//������
    CC_SYNTHESIZE(int, _mana_attack, ManaAttack);//ħ������
    CC_SYNTHESIZE(int, _initial_mana, InitialMana);//��ʼ����ֵ
    CC_SYNTHESIZE(float, _attack_speed, AttackSpeed);//����ʱ����
    CC_SYNTHESIZE(int, _critical_damage, CriticalDamage);//���������˺� �ٷֱ� ��int ����

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

    virtual bool init(int& key);

    static Equipment* create(int& key);

    bool check_listener_scale(EventMouse* event);
    virtual void onMouseDown(EventMouse* event);
    virtual void onMouseUp(EventMouse* event);
    virtual void onMouseMove(EventMouse* event);
    bool main_move_on_up(BaseSprite* other_sprite);

    void update();

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

    virtual bool synthesis(Equipment* first_equipment, Equipment* second_equipment);//��װ�����кϳ�װ��

    virtual void node_manager(Equipment* equipment) { ; }

    CC_SYNTHESIZE(cocos2d::Vector<Equipment*>, _equipments, Equipments);
    CC_SYNTHESIZE(int, _capacity, Capacity);
    CC_SYNTHESIZE(cocos2d::Vec2, _start_position, StartPosition);
    CC_SYNTHESIZE(int, _interval, Interval);
    
};

class EquipmentBarforGame :public EquipmentBar {
public:
    virtual cocos2d::Vec2 getposition(int sequence);

    static EquipmentBarforGame* create(const int max_num);

    bool init(const int max_num);

    virtual void node_manager(Equipment* equipment);

    void remove_one(Equipment* equipment);

    

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

class Actor:public BaseSprite {
    CC_SYNTHESIZE(EquipmentBarforHero*,_bar,Bar);
public:
    static Actor* create();
    virtual bool init();
   
    bool take_equip(Equipment* equip);
    bool unload_equip();

    virtual void onMouseDown(EventMouse* event);


};


//�����Ƿ��ĵ� ���ÿ�
class Rune;


class RunesButton:public ui::Button {
public:
    static RunesButton* create();
    virtual bool init();

    virtual void onButtonTouch(Ref* sender, ui::Widget::TouchEventType type);
};


class RuneStore :public Layer{
    CC_SYNTHESIZE(cocos2d::Vector<Rune*>,_store,Store);

    static RuneStore* create();

    virtual bool init();

    void add_rune(Rune* rune);

    cocos2d::Vec2 getposition(int sequence);

    void start_apply();
};

class Rune :public BaseSprite {
public:
    virtual void apply() { ; }

    static Rune* create();

    virtual bool init();

    virtual void onMouseDown(EventMouse* event);
};


class PandorasGear : public Rune {
    CC_SYNTHESIZE(int, _rounds, Rounds);
public:
    static PandorasGear* create(cocos2d::Vec2 position);

    virtual bool init(cocos2d::Vec2 position);

    virtual void apply();

    
};

class PumpedUp1 : public Rune {
public:
    static PumpedUp1* create(cocos2d::Vec2 position);
    virtual bool init(cocos2d::Vec2 position);
};

class Kickstart : public Rune {
public:
    static Kickstart* create(cocos2d::Vec2 position);
    virtual bool init(cocos2d::Vec2 position);
};

class TreasureTrove2 : public Rune {
    CC_SYNTHESIZE(int,_rounds,Rounds);
public:
    static TreasureTrove2* create(cocos2d::Vec2 position);
    virtual bool init(cocos2d::Vec2 position);

    //virtual void apply();
};

class TonsOfAttributes : public Rune {
public:
    static TonsOfAttributes* create(cocos2d::Vec2 position);
    virtual bool init(cocos2d::Vec2 position);
};

class LowRates : public Rune {
public:
    static LowRates* create(cocos2d::Vec2 position);
    virtual bool init(cocos2d::Vec2 position);
};

class HedgeFund : public Rune {
public:
    static HedgeFund* create(cocos2d::Vec2 position);
    virtual bool init(cocos2d::Vec2 position);
};

class BinaryAirdrop : public Rune {
public:
    static BinaryAirdrop* create(cocos2d::Vec2 position);
    virtual bool init(cocos2d::Vec2 position);
};

class UltimateAscension : public Rune {
public:
    static UltimateAscension* create(cocos2d::Vec2 position);
    virtual bool init(cocos2d::Vec2 position);
};

class Runes :public Layer {
    static Runes* create();

    virtual bool init();

    void random_create(int key, cocos2d::Vec2 position);

    CC_SYNTHESIZE(int, _times, Times);
};


#endif

//����û�� ���ؿ�
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
//��effect�ŵ�damage��ʵ�֣�damage�ܹ���ȡ�߼�װ���ϵ�effect ��Damage�ϼ���Ч�����ԣ�
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

