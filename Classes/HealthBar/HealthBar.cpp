#include"HealthBar/HealthBar.h"


HealthBar::HealthBar() : background(nullptr), fill(nullptr), maxWidth(0.0f), maxHeight(0.0f) {}

HealthBar::~HealthBar() {}

HealthBar* HealthBar::create(const std::string& backgroundFile, const std::string& fillFile, float maxWidth, float maxHeight) {
    HealthBar* healthBar = new HealthBar();

    if (healthBar) {
        healthBar->autorelease();

        healthBar->background = Sprite::createWithSpriteFrameName(backgroundFile);//创建血条背景
        healthBar->background->setAnchorPoint(Vec2(0, 0));
        healthBar->addChild(healthBar->background);

        healthBar->fill = Sprite::createWithSpriteFrameName(fillFile);//创建血条填充（绿色）
        healthBar->fill->setAnchorPoint(Vec2(0, 0));
        healthBar->fill->setPosition(Vec2(0, 0));
        healthBar->addChild(healthBar->fill);

        healthBar->maxWidth = maxWidth;
        healthBar->maxHeight = maxHeight;

        return healthBar;
    }

    CC_SAFE_DELETE(healthBar);

    return nullptr;
}

void HealthBar::setPercentage(int percentage) {//传入要设置的百分比：0-100的整数
    if (percentage < 0) {
        percentage = 0;
    }
    else if (percentage > 100) {
        percentage = 100;
    }

    
    float initialWidth = fill->getScaleX();
    CCLOG("%f", initialWidth);// 记录初始血条的宽度

    float newWidth = (static_cast<float>(percentage) / 100.0f);
    float scale = newWidth ;

    fill->setScaleX(scale);
}
