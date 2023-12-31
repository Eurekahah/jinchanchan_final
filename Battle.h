
# include "Scene/create_button_and_scene.h"
/*����*/
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

/*����*/
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
    const float spacing = screenSize.width * 0.04f; // ͼƬ���
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
    /*����*/
    void createPlayers(int playerId, int enemyId);

    virtual void addPlayer(int playerId);//�����������
    void addEnemy(int enemyId);//���ó��ϵĵ��ˣ�����λ��

    virtual void addPlayerHero(int playerId);
    void addEnemyHero(int enemyId);

    void updateHero(int id);//����idӢ��״̬

    void checkAllHeroesDead(int playerId);//��鳡��Ӣ���Ƿ�ȫ������
    void roundBegin();//ÿ�غϿ�ʼ
    void roundOver(int winnerId, int loserId, int enemyId);//�غϽ�����Ĳ���
    void GameOver();//��Ϸ����
    void playerGameOver();//����������ǰ���������򲻹��˻����ˣ���ִ�����
    CC_SYNTHESIZE(int, round, Round);//��ǰ�غ���

    void removeEnemy(int enemyId);//�����������ȥ���з���Һ͵з�Ӣ��
    void goToFashionShow();//ѡ�㳡����ʼ��
    void removeHeroPause(Vector<Hero*> heroList);//���Ӣ����ͣ״̬
    void goToInterval(int);//ǰ����Ϣ
    void showRunes();
    void removeAndUpdateSprite(Hero* image);
    void synthesis(Hero* image);//3��1

    void updateHeroTarget(int playerId);//����Ӣ������

    void updateHeroesPosition(); 
    /*����*/
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
    //    // ʹ�����������ȴ�
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

