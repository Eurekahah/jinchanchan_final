# include "DisplayHero.h"
using namespace cocos2d;
Scene* Display_heroes_page::createScene()
{
    return Display_heroes_page::create();
}
bool Display_heroes_page::init() {

    auto button_clicking_audio = CocosDenshion::SimpleAudioEngine::getInstance();
    button_clicking_audio->getInstance()->preloadEffect("music/button_effect.mp3");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto hall_image = Sprite::create("backgrounds/display_heroes_background.png");
    create_background_page(hall_image);
    this->addChild(hall_image, -1);;

    auto backward_button = ui::Button::create("backgrounds/backwards.png");
    backward_button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            button_clicking_audio->getInstance()->playEffect("music/button_effect.mp3", false);
            Director::getInstance()->popScene();
        }
        });
    create_button(backward_button, 0.1f, 0.48f, 0.08f, 0.08f);
    auto backward_label = Label::createWithTTF("reverse", "fonts/Marker Felt.ttf", 24);
    backward_label->setPosition(Vec2(backward_button->getPositionX(), backward_button->getPositionY() - backward_button->getContentSize().height / 2 - backward_label->getContentSize().height / 2));

    this->addChild(backward_button, 1);
    this->addChild(backward_label, 1);

    float imgWidth = visibleSize.width * 0.20;  // ͼƬ���
    float imgHeight = visibleSize.height * 0.25; // ͼƬ�߶�
    float horizontalSpacing = visibleSize.width * 0.05;  // ˮƽ���
    float verticalSpacing = visibleSize.height * 0.12; // ��ֱ���
    float delayTime = 0.1f; // ÿ��ͼƬ����ʱʱ��

    int imagesPerRow = std::floor((visibleSize.width - visibleSize.width * 0.17) / (imgWidth + horizontalSpacing));
    float startX = visibleSize.width * 0.30;
    float startY = visibleSize.height * 0.88; // ����Ļ����0.12��λ�ÿ�ʼ���У����ܸ߶ȵ�88%����
    auto scrollView = cocos2d::ui::ScrollView::create();
    scrollView->setContentSize(cocos2d::Director::getInstance()->getVisibleSize());
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
    scrollView->setBounceEnabled(true); // ���õ���Ч������ѡ��
    scrollView->setScrollBarEnabled(true); // ��ʾ������
    scrollView->setInertiaScrollEnabled(false);

    this->addChild(scrollView, 0);
    auto container = scrollView->getInnerContainer();


    int totalRows = std::ceil(20.0 / imagesPerRow); // ������
    float totalHeight = totalRows * imgHeight + (totalRows - 1) * verticalSpacing;

    if (totalHeight < scrollView->getContentSize().height) {
        totalHeight = scrollView->getContentSize().height + 1;
    }

    scrollView->setInnerContainerSize(cocos2d::Size(scrollView->getContentSize().width, totalHeight));

    float y = totalHeight - imgHeight / 2; // ���ڲ�����������ָ��λ�ÿ�ʼ

    int count = 0;
    for (int i = 1; i <= 5; i++) {
        int num = 0;

        if (i == 1 || i == 3)
            num = 5;
        else if (i == 2 || i == 4)
            num = 4;
        else
            num = 2;

        for (int j = 1; j <= num; j++) {

            std::string imageName = "heroes/cost_" + std::to_string(i) + "/img" + std::to_string(j) + ".png";
            auto sprite = cocos2d::Sprite::create(imageName);
            sprite->setScale(imgWidth / sprite->getContentSize().width, imgHeight / sprite->getContentSize().height);

            int row = count / imagesPerRow;
            int col = count % imagesPerRow;

            float x = startX + col * (imgWidth + horizontalSpacing);
            y = totalHeight - (row * (imgHeight + verticalSpacing) + imgHeight / 2);
            sprite->setPosition(x, y);
            sprite->setOpacity(0); // ��ʼʱ����Ϊ͸��
            // ������ʱ����ʾ����
            auto delay = cocos2d::DelayTime::create(delayTime * count); // ÿ��ͼƬ��ʱ����
            auto show = cocos2d::CallFunc::create([sprite]() {
                sprite->setOpacity(255); // ����Ϊ��͸������ʾͼƬ
                });
            auto sequence = cocos2d::Sequence::create(delay, show, nullptr);
            sprite->runAction(sequence);
            container->addChild(sprite, 1); // ��ӵ�������ͼ���ڲ�������
            count++;
        }
    }

    return true;
}