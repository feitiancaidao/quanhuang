//
//  PlayEffect.cpp
//  King
//
//  Created by mac on 14-4-1.
//
//

#include "PlayEffect.h"
PlaysEffect* PlaysEffect::create(CCPoint p)
{
    PlaysEffect* effect = new PlaysEffect();
    effect->init(p);
    effect->autorelease();
    return effect;
}

bool PlaysEffect::init(CCPoint p)
{
    this->setPosition(p);
    return true;
}