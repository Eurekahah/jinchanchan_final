#pragma once
#ifndef HEALTHBAR_H_
#define HEALTHBAR_H_

#include "cocos2d.h"

USING_NS_CC;

class HealthBar : public Sprite {
public:
    HealthBar();
    virtual ~HealthBar();

    static HealthBar* create(const std::string& backgroundFile, const std::string& fillFile, float maxWidth, float maxHeight);

    void setPercentage(int percentage);

private:
    Sprite* background;
    Sprite* fill;
    float maxWidth;
    float maxHeight;
};


#endif // !HEALTHBAR_H_
