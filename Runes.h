#pragma once
#if 0
#include<iostream>
#include"cocos2d.h"
USING_NS_CC;

const cocos2d::Vec2 RuneStart = cocos2d::Vec2(512, 300);
const int rune_height = 170;
const cocos2d::Vec2 rune_button_place = cocos2d::Vec2(50, 50);

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

//�����Ƿ��ĵ� ���ÿ�
void runes_update();

class Rune;


class RunesButton :public cocos2d::ui::Button {
public:
    static RunesButton* create();
    virtual bool init();

    virtual void onButtonTouch(Ref* sender, ui::Widget::TouchEventType type);
};


class RuneStore :public cocos2d::Layer {
    CC_SYNTHESIZE(cocos2d::Vector<Rune*>, _store, Store);

    static RuneStore* create();

    virtual bool init();

    void add_rune(Rune* rune);

    cocos2d::Vec2 getposition(int sequence);

    void start_apply();
};

class Rune :public Sprite {
    CC_SYNTHESIZE(int, _rounds, Rounds);
public:
    virtual void apply();

    static Rune* create();

    virtual bool init();

    bool add_to_store();
};


class PandorasGear : public Rune {

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
    CC_SYNTHESIZE(int, _rounds, Rounds);
public:
    static TreasureTrove2* create(cocos2d::Vec2 position);
    virtual bool init(cocos2d::Vec2 position);
    virtual void apply();
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


class Runes :public cocos2d::Layer {
public:
    static Runes* create();

    virtual bool init();

    void random_create(int key, cocos2d::Vec2 position);

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

    CC_SYNTHESIZE(int, _times, Times);
    CC_SYNTHESIZE(EventListenerTouchOneByOne*, _touchListener, TouchListener);
};

#endif