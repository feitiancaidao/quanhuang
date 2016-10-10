//
//  HubLayer.h
//  King
//
//  Created by mac on 14-3-26.
//
//

#ifndef __King__HubLayer__
#define __King__HubLayer__
#include "cocos2d.h"
#include "SneakyButtonSkinnedBase.h"
#include "SneakyButton.h"
#include "PlayerHeadUI.h"
enum
{
    lianjiTag = 100,
    lianjiTagNum = 101,
    herohpTag = 102,
    moneyTag = 104,
    skill1TimerTag =105,
    skill2TimerTag =106,
    skill3TimerTag =107,
    skill4TimerTag =108,
    shengyuMonsterDescTag = 109,
    shengyuTimeTag = 1009,
    
    nowNPCnumberTag = 100003,
    nowShengyuTimeTag = 100004,
    timeTips = 100005
};
USING_NS_CC;
using namespace gui;
class HubLayer : public CCLayer
{
public:
    int type;
    
    HubLayer();
    long lastzuoTime;
    long lastyouTime;
    
    void TouchEnded();
    
    CREATE_FUNC(HubLayer);
    
    virtual bool init();
    
    void setDirectionKeyboardDelegate(void* delegate);//设置方向键盘的事件
    
    void setCommonAttackDelegate(void* delegate);   //设置普通攻击代理
    
    void addJoy();
    
    void addButton();

    std::vector<std::vector<int> > attackNumList;  //连击数
    
    void updateSkill(float dt);
    
    void tishiNuqi();
    
    void tishiNuqi2(float dt);
    
    CCSprite* zuo;
    
    CCSprite* you;

    CCMenuItemSprite* zuoItem;
    
    CCMenuItemSprite* youItem;
    
    PlayerHeadUI* headUI;
    
    CCSprite* goSprite1;
    
    CCSprite* goSprite2;
   
    CCSprite* tishiNuqiSprite;
    
    void HeromoveLeft(CCObject* pSender);
    
    void HeromoveRight(CCObject* pSender);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    
    void ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    
    virtual void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    
    
    bool LeftisTouched;
    
    bool RightisTouched;
    
    void update(float dt);
    
    void registerWithTouchDispatcher();

    SneakyButton* commonAttackButton;
    
    SneakyButton* skillButton1;
    
    SneakyButton* skillButton2;
    
    SneakyButton* skillButton3;
    
    void AddLianJi();
    
    void LianJiCallBack(CCObject* pSender);
    
    void setNumber(int number);
    
    void showGoMessage();
    
    void showHP();
    
    void showHP(float maxHp ,float hp);
    
    void addShowNumNpc();
    
    void showNpcNum(int npcnum);
    
    void jinengban();
    
    void showHeroAnger();       //显示主角怒气
    
    void shop(CCObject* pSender);
    
    void addSkillButton(const char* skilltubiao,const char* skilltubiao2,CCPoint skillpostion,SneakyButton* skillButton1 );
    
    void showTime();

    void showKillMonster();
    
    void showKiloMeter();
    
    void updateKiloMeter(float);
#pragma ///mark -技能痛苦火海
    void zhuangtai();
    
    void showMoney();     //显示金币
    
    void addGoInfo();
    
    void showGoInfo(int goDirection);
    
    void addTip(std::string text);
    
    void addTip2(std::string text);
    
    void resetTip();
    
    void readygo(float dt);
    
    int teachID;
    
    bool isTeach;
    
    CCSprite* sprite;
    
    UILabel* juqingTishiLabel;
    
    bool zhishi;
    
    int zhishiWaitTime;
    
    void juqingTishi();
    
    void updateTime(float dt);
    
    UILabel* labelnuqi;
    
    bool canTouch;
    
    void removetishiNuqi(float dt);
    
    void removetishiNuqi1();
    
    void jihuo();
    
    bool isTishinuqi1;
    
    void addDamageNum(int num,CCPoint p,int dir);
    
	void removeDamage(CCNode* pSender);
    
    CCSprite* tip1;
    
    CCSprite* jiaoshi;
    
    UILabel* label;
    
    void runSkill(int id);
    
    CCMenuItemImage* button4;
    CCMenuItemImage* button2;
    CCMenuItemImage* button3;
};

#endif /* defined(__King__HubLayer__) */
