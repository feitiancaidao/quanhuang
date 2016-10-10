//
//  ShopBuy.h
//  King
//
//  Created by mac on 14-3-28.
//
//

#ifndef __King__ShopBuy__
#define __King__ShopBuy__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

class ShopBuy : public CCLayer
{
public:
    ShopBuy();
    CCSprite* xuanzhongkuang;
    CCSprite* xuanzhongkuang2;
    CCSprite* xuanzhongkuang3;
    
public:
    int currToshoW;
    UILabel* nengliDesc;
    UILabel* nengliDescTitle;
    UILabel* shopDesc;
    UILabel* shopDescTitle;
    UILabel* labelnuqi;
    static void isShowFuhuo();
    
    void ShopInit();
    
    CCScale9Sprite* bg;
    
    CCSprite* current_money;
    
    CREATE_FUNC(ShopBuy);
    bool init();
    
    static ShopBuy* create(int currToshoW);
    
    bool init(int currToshoW);
    
    void addGoumai(CCNode* n,CCPoint p);
    
    CCMenu* menu;
    
    void registerWithTouchDispatcher();
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    CCNode* nengliNode;
    
    CCNode* xuetogNode;
    
    CCNode* shangchengNode;
    
    CCArray* nengliArr;
    
    CCArray* shopArr;
    
    CCArray* menus;
    
    CCArray* xuetongAdd;
    
    void nengliCallback(CCObject* pSender);
    
    void shopCallback(CCObject* pSender);
    
    void qiehuanCallback(int index);
    
    void qiehuanCallback(CCObject* pSender);
    
    void addCallback(CCObject* pSender);
    
    CCMenuItem* duobi;
    
    CCMenuItem* shoushen;
	CCMenuItem* yuanbao3;
	CCMenuItem* yuanbao4;
    CCMenuItem* fuhuo;
    
    CCMenuItem* nuqibao;
    
    static CCScene* scene(CCRenderTexture *sqr, bool isFlip );
    
    static CCScene* scene(CCRenderTexture *sqr, bool isFlip ,int currToshoW);
    
    void huodenengli(CCObject* pSender);
    
    void huodeShop(CCObject* pSender);

    int nengliSort;
    
    int shopSort;
    
    void resume(CCObject*);
	void autoBuyFuhuo();

    bool ispop;
    bool ispop2;
    static CCScene* scene();
    CCSpriteBatchNode* shengmingbash;
    CCSpriteBatchNode* gongjibash;
    CCSpriteBatchNode* fangyubash;
    CCSpriteBatchNode* nuqibash;
    void showInfo(int id);
    UILabel* current_money_nuM;
    UILabel* shengmingMoneylabel;
    UILabel* gongjitiaoMoneylabel;
    UILabel* fangyutiaoMoneylabel;
    UILabel* nuqitiaoMoneylabel;
    CCSprite* sprite;
    void update(float dt);
    
    void addTip(std::string text);
    
    void addTip2(std::string text);
    
    void resetTip();
    
    CCSprite* tip1;
    
    CCSprite* jiaoshi;
    
    UILabel* label;
};

#endif /* defined(__King__ShopBuy__) */
