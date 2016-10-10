//
//  Dalibao.h
//  king04
//
//  Created by mac on 14-5-18.
//
//

#ifndef __king04__Dalibao__
#define __king04__Dalibao__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

class Dalibao : public CCLayer
{
public:
    
    static Dalibao* create(int id);
    bool init(int id);
    CCSprite* bg;
    CCMenuItem* xiaocha;
    CCMenuItem* goumai;
    CCMenuItem* duobi;
    CCMenuItem* shoushen;
    CCSprite* touming;
    CCSprite* touming2;
    CCSprite* xuanzekuang;
    void showInfo(int id);
    void buy(CCObject*);
    void resume(CCObject*);
    void duobiMenu(CCObject*);
    void shoushenMenu(CCObject*);
    void jinbi(CCObject* pSender);
    CCScene* scene(int id);
    int id;
    int libaoid;
    CCMenuItem* menu5888;
    CCMenuItem* menu2888;
    CCMenuItem* menu1888;
    
    CCSprite* yihuode;
    CCSprite* yihuode2;
};

#endif /* defined(__king04__Dalibao__) */
