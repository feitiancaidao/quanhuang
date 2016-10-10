//
//  MenuLayer.h
//  King
//
//  Created by mac on 14-3-30.
//
//

#ifndef __King__MenuLayer__
#define __King__MenuLayer__

#include "cocos2d.h"
USING_NS_CC;
#include "cocos-ext.h"
USING_NS_CC_EXT;

class MenuLayer : public cocos2d::CCLayer
{
public:
 //   CREATE_FUNC(MenuLayer);
    static MenuLayer* create(int id);
    bool init(int id);
    int id;
    //设置音乐和音效按钮的状态
    void setSoundAndMusicVolume(float soundVolume, float musicVolume);
    static CCScene* scene(int id);
    static CCScene* scene(CCRenderTexture* sqr);
protected:
    void congxinCall(CCObject* );
    void fanhuijidiCall(CCObject* );
    void qianghuashuxingCall(CCObject* );
    void resume(CCObject* );
    void sound(CCObject* );
    void music(CCObject*);
    void back(CCObject*);
    void shop();
    void createMenu();
    void createBackground();
    
    cocos2d::CCMenuItemToggle* _sound;
    cocos2d::CCMenuItemToggle* _music;
    
    void registerWithTouchDispatcher();
    
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    CCScale9Sprite* bg;
    
    CCMenuItem* duihao;
    CCMenuItem* cuohao;
    
    CCMenuItem* duihao1;
    CCMenuItem* cuohao1;
    
    CCMenuItemToggle* sound_music;
    CCMenuItemToggle* music_sound;

    CCMenuItem* jixu;
    CCMenuItem* zhucaidan;
    CCMenuItem* shopItem;
   
    CCMenuItem* congxin;
    CCMenuItem* fanhuijidi;
    CCMenuItem* qianghuashuxing;
};
#endif /* defined(__King__MenuLayer__) */






