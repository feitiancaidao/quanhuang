//
//  ShopScene.h
//  king04
//
//  Created by mac on 14-5-15.
//
//

#ifndef __king04__ShopScene__
#define __king04__ShopScene__

#include "BaseLayer.h"
#include "cocos2d.h"
#include "Hero.h"
#include "Define.h"
USING_NS_CC;
#include "cocos-ext.h"
USING_NS_CC_EXT;
#include "Hero.h"

enum dalibaotag
{
    dalibaotag = 5001,
    dalibaozorder = 9999999
};
class ShopScene : public BaseLayer
{
public:
    CCSprite* bg;
    CCSprite* nvrole;
    CCArmature* baoxiang;
    CCArmature* texiao;
    CCArmature* xuanguan;
    CCArmature* duboji;
    CCSprite* jinbi;
    CCSprite* jiantou;
    
    void dalibao();
    
    Hero* hero;
    int goumaiweizhi;
    int oldgoumaiweizhi;
    
    
    void update(float dt);
    void updatePosition(float dt);
    
//	bool ccTouchBegan(CCTouch* touch, CCEvent* event)override;
//	void registerWithTouchDispatcher()override;

    CREATE_FUNC(ShopScene);
    static CCScene* scene();
    bool init();

	void changeSelect(int fangxiang);

	void addTip();
	void addDialog();
private:
	int     _tag;
	CCSprite* tip1;
	CCSprite* jiaoshi;
	UILabel*  label;
};

#endif /* defined(__king04__ShopScene__) */




