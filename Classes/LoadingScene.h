//
//  LoadingScene.h
//  GedouKing
//
//  Created by mac on 14-3-26.
//
//

#ifndef __GedouKing__LoadingScene__
#define __GedouKing__LoadingScene__

#include "cocos2d.h"
#include "BaseLayer.h"
USING_NS_CC;

class LoadingScene : public BaseLayer
{
public:
    virtual bool init();
    
    static cocos2d::CCScene* scene();

    void loadingBack();
    
    CREATE_FUNC(LoadingScene);
    
    void Loading_Over(float dt);
};

#endif /* defined(__GedouKing__LoadingScene__) */
