



# include "Scene/create_button_and_scene.h"
# include "Setting.h"
# include "DisplayHero.h"
# include "DisplayArmor.h"
//# include "server_and_client.h"
# include "Battle.h"

using namespace cocos2d;

class Hall_page :public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    bool init();
    void play_music();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(Hall_page);
};

