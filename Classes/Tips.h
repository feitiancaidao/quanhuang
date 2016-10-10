//
//  Tips.h
//  King
//
//  Created by mac on 14-4-22.
//
//

#ifndef __King__Tips__
#define __King__Tips__

#include "cocos2d.h"
#include "Hero.h"
#include "Monster.h"
USING_NS_CC;
#include "TipStory.h"
class Tips : public CCLayer
{
public:
    ~Tips();
    static CCScene* scene(int id);
    CREATE_FUNC(TipStory);
    bool init(int id);
    static Tips* create(int id);
    Hero* hero;
    Monster* monster;
    CCSprite* back;
    void addTips(CCObject* pSender);
};

#endif /* defined(__King__Tips__) */
