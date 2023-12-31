//# include "HelloWorldScene.h"


# include "Scene/create_button_and_scene.h"

class Loading_page : public cocos2d::Scene {
public:

    static cocos2d::Scene* createScene();

    bool init();
    void play_music();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Loading_page);
};
