//
//  Jihuo.h
//  king04
//
//  Created by mac on 14-5-13.
//
//

#ifndef __king04__Jihuo__
#define __king04__Jihuo__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

class Jihuo : public CCLayer
{
public:
    Jihuo();
    CREATE_FUNC(Jihuo);
    bool init();
    static CCScene* scene(CCRenderTexture *sqr, bool isFlip );
    void resume(CCObject* );
    void buy(CCObject* );
    void showInfo(int id);
    void update(float dt);
    void jihuo();
    CCSprite* bg;
    CCMenuItem* xiaocha;
    CCMenuItem* goumai;
    
    bool ispop;
};

#endif /* defined(__king04__Jihuo__) */
