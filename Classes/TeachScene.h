//
//  TeachScene.h
//  King
//
//  Created by mac on 14-4-21.
//
//

#ifndef __King__TeachScene__
#define __King__TeachScene__

#include "cocos2d.h"
USING_NS_CC;
class TeachScene : public CCLayer
{
public:
    static CCScene* scene(CCRenderTexture* text);
    virtual bool init();
    
    CREATE_FUNC(TeachScene);
    
    void iknow(CCObject* pSender);
    //static cocos2d::CCScene* scene();
};
#endif /* defined(__King__TeachScene__) */
