//
//  Flower.cpp
//  King
//
//  Created by mac on 14-3-29.
//
//

#include "Flower.h"
#include  "Define.h"
bool Flower::init()
{
    
    this->schedule(schedule_selector(Flower::onTime), 1);
    return true;
}

void Flower::onTime(float dt)
{

    int xe = CCRANDOM_MINUS1_1() * SIZE.width/2;     //这个是该图片移动的最后坐标x轴的
    int sp = CCRANDOM_0_1()*10 +5;     //这个是速度
    pic = CCSprite::create("smallUI/huaban.png");
    this->addChild(pic);
    CCMoveTo *move=CCMoveTo::create(sp, ccp(xe,-SIZE.height -10));
    CCFadeOut* fadout=CCFadeOut::create(sp);
    CCCallFunc* call=CCCallFunc::create((Flower*)pic, callfunc_selector(Flower::remove));
    CCSequence* sequence=CCSequence::create(move,fadout,call,NULL);
    pic->runAction(sequence);
}

void Flower::remove()
{
    
}






