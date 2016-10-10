//
//  Flower.h
//  King
//
//  Created by mac on 14-3-29.
//
//

#ifndef __King__Flower__
#define __King__Flower__

#include "cocos2d.h"
USING_NS_CC;
class Flower : public CCNode
{
public:
    CREATE_FUNC(Flower);
    CCSprite* pic;
    bool init();
    void onTime(float dt);
    void remove();
};

#endif /* defined(__King__Flower__) */
