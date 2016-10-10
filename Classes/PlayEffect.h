//
//  PlayEffect.h
//  King
//
//  Created by mac on 14-4-1.
//
//

#ifndef __King__PlayEffect__
#define __King__PlayEffect__

#include "cocos2d.h"
USING_NS_CC;

class PlaysEffect : public CCNode
{
public:
    static PlaysEffect* create(CCPoint p);
    
    bool init(CCPoint p);
    
};
#endif /* defined(__King__PlayEffect__) */
