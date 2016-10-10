//
//  SkillObject.h
//  king04
//
//  Created by mac on 14-5-26.
//
//

#ifndef __king04__SkillObject__
#define __king04__SkillObject__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
#include "cocos-ext.h"
USING_NS_CC_EXT;

class SkillObject : public CCNode
{
public:
    static SkillObject* create(int id);
    bool init(int id);
    CCArmature* armature;
    void update(float dt);
    CCRect getBondingBox();

    int id;
};



#endif /* defined(__king04__SkillObject__) */
