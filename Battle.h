
# include "Scene/create_button_and_scene.h"
/*以下*/
#include"Player/PlayerManager.h"
#include"Scene/FashionShow.h"
#include <cstdlib>
#include <ctime>
#include<thread>
#include<condition_variable>
#include<mutex>
#include<future>
#include"Player/AIsystem_clever.h"
#include"Runes/Runes.h"
#include"Hero/HeroNew.h"

/*以上*/
USING_NS_CC;

class StoreLayer : public cocos2d::Layer {
    cocos2d::LayerColor* background;
    
    //Hero* hero;
public:
    static StoreLayer* create();
    static const std::string HERO_SELECTED_EVENT;
    bool init();
    void buttonClicked(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void display_random_heroes();

};
class BattleField :public cocos2d::Scene {
    bool IsEnd = false;
    Size screenSize = Director::getInstance()->getVisibleSize();
    const float imageSize = 100.0f;
    const float spacing = screenSize.width * 0.04f; // 图片间隔
    //cocos2d::Vector<Hero*>& heroList = PlayerManager::getInstance()->getPlayerByID(0)->getHeroList();
public:
    void create_hero_by_number(int key);
    static int total_num;
    float nextHeroPositionX;
    cocos2d::Label* moneyLabel;
    static int money ;
    void Activate_timer();
    virtual void display_bank_and_money();
    virtual void updateMoneyDisplay();
    void BattleBegin(const int playerId,const int enemyId);
    //virtual void Activate_timer();
    virtual void create_store();
    virtual void Display_Heroes_Backup(int num);
    virtual void create_reverse_and_audio();

    static cocos2d::Scene* createScene();
    bool init();
    void menuCloseCallBack(cocos2d::Ref* pSender);
    CREATE_FUNC(BattleField);
    /*以下*/
    void createPlayers(int playerId, int enemyId);

    virtual void addPlayer(int playerId);//放置玩家自身
    void addEnemy(int enemyId);//放置场上的敌人，镜像位置

    virtual void addPlayerHero(int playerId);
    void addEnemyHero(int enemyId);

    void updateHero(int id);//更新id英雄状态

    void checkAllHeroesDead(int playerId);//检查场上英雄是否全部阵亡
    void roundBegin();//每回合开始
    void roundOver(int winnerId, int loserId, int enemyId);//回合结束后的操作
    void GameOver();//游戏结束
    void playerGameOver();//如果是玩家提前死亡，（打不过人机，菜）则执行这个
    CC_SYNTHESIZE(int, round, Round);//当前回合数

    void removeEnemy(int enemyId);//从这个场景中去除敌方玩家和敌方英雄
    void goToFashionShow();//选秀场景初始化
    void removeHeroPause(Vector<Hero*> heroList);//解除英雄暂停状态
    void goToInterval(int);//前往休息
    void showRunes();
    void removeAndUpdateSprite(Hero* image);
    void synthesis(Hero* image);//3合1

    void updateHeroTarget(int playerId);//更新英雄索敌

    void updateHeroesPosition(); 
    /*以上*/
};

class interval :public BattleField
{
public:
    static Scene* createScene();
    bool init();
    void Activate_timer();
    void AIop(int AIID);
    void createPlayer(int playerId);
    void onExit();
    
    //void waitForOthers() {
    //    // 使用条件变量等待
    //    std::unique_lock<std::mutex> lock(*cvMutex);
    //    cv->wait(lock, [] {
    //        //bool allReady=true;
    //    int currentRound = PlayerManager::getInstance()->getPlayerByID(0)->getRound();
    //        for (const auto& player : PlayerManager::getInstance()->getPlayerList())
    //        {
    //            if (player->getRound() != currentRound) {
    //                return false;
    //            }
    //        }
    //        return true;
    //       });
    //}
private:
   /* std::condition_variable* cv;
    std::mutex* cvMutex;*/
};

