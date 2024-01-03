


# include "Scene/create_button_and_scene.h"

class Display_armors_page : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    bool init();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(Display_armors_page);
};
