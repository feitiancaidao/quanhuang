//
//  AboutScene.h
//  King
//
//  Created by mac on 14-3-26.
//
//

#ifndef __King__AboutScene__
#define __King__AboutScene__

#include "BaseLayer.h"

class AboutScene : public BaseLayer
{
public:
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(AboutScene);
    
    void Return(CCObject* pSender);
};
#endif /* defined(__King__AboutScene__) */
