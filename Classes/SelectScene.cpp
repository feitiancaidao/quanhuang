//
//  SelectScene.cpp
//  King
//
//  Created by mac on 14-3-26.
//
//

#include "SelectScene.h"
#include "Define.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "GameData.h"
#include "PersonalAudioEngine.h"
#include "ShopBuy.h"
#include "XMLData.h"
#include "LoadingLayer.h"
#include "BeginLayer.h"
#include "ShopScene.h"

int SelectScene::xuanguan = 1;




SelectScene::SelectScene()
{
    drag = false;
    biaozhi = 0;
	
}
bool SelectScene::init()
{
    if ( !BaseLayer::init() )
    {
        return false;
    }
    
	//在此处也重置技能
	KingData->reset();
    
    tip1 = CCSprite::create("duihuakuang/UI80.png");
    jiaoshi = CCSprite::create("duihuakuang/jiaoshi.png");
    this->addChild(jiaoshi,9999999);
    this->addChild(tip1,999999);
    jiaoshi->setPosition(ccp(-0.15*SIZE.width,10));
    jiaoshi->setAnchorPoint(ccp(0.5, 0));
    tip1->setPosition(ccp( -150, -120));
    label = UILabel::create();
    tip1->addChild(label);
    label->setFontName("宋体");
    label->setFontSize(20);
    label->setPosition(ccp(120, tip1->getContentSize().height));
    label->setAnchorPoint(ccp(0, 1));
    label->setColor(ccc3(241, 191, 194));
    label->setTextAreaSize(CCSize(200,150));
    tip1->setVisible(false);
    jiaoshi->setVisible(false);
    label->setTextVerticalAlignment(kCCVerticalTextAlignmentCenter);
    
    
    ul = UILayer::create();
    this->addChild(ul);
    ul->addWidget(GUIReader::shareReader()->widgetFromJsonFile("NewProject_1/NewProject_1.ExportJson"));
    this->setTouchEnabled(true);
    
    menu = CCMenu::create();
    this->addChild(menu);
    menu->setPosition(0, 0);
    back = CCMenuItemImage::create("xuanze/huiqu1.png", "xuanze/huiqu2.png", this, menu_selector(SelectScene::backScene ) );
    back->setPosition(ccp(SIZE.width*0.05, SIZE.height*0.05 ) );
    menu->addChild(back);
    
    jiantou1 = CCMenuItemImage::create("xuanze/jiantou.png", "xuanze/jiantou.png", this,menu_selector(SelectScene::fudong));
 
    menu->addChild(jiantou1);
    jiantou1->setPosition(ccp(SIZE.width*0.97, SIZE.height*0.5 ) );
    jiantou1->setVisible(false);
    
    jiantou2 = CCMenuItemImage::create("xuanze/jiantou.png", "xuanze/jiantou.png", this,menu_selector(SelectScene::fudong1));
    menu->addChild(jiantou2);
    jiantou2->setScaleX(-1);
    jiantou2->setPosition(ccp(SIZE.width*0.03, SIZE.height*0.5 ) );
    jiantou2->setVisible(false);
    


    
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("jrjm.plist");
//    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
//    CCArray* framesArray = CCArray::create();
//    CCSpriteFrame* frame = NULL;
//    int index = 1;
//    do
//    {
//        frame = cache->spriteFrameByName(CCString::createWithFormat("%s%d.png","jrjm_tb1_",index++)->getCString());
//        if (frame == NULL)
//        {
//            break;
//        }
//        framesArray->addObject(frame);
//    } while (true);
//    CCAnimation* animation = CCAnimation::createWithSpriteFrames(framesArray);
//    animation->setDelayPerUnit(0.2);
//    animation->setLoops(true);
//    animation->setRestoreOriginalFrame(true);
//    aniSprite = CCSprite::createWithSpriteFrame(dynamic_cast<CCSpriteFrame*>(framesArray->objectAtIndex(0)));
//    this->addChild(aniSprite,1000);
//    aniSprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
//    aniSprite->setScale(0.8);
     xuanguan = KingData->getMapIndex();
     char uiChar[5] = {0};
     if(xuanguan>20)
     {
         xuanguan = 20;
     }
 
     for (int i = 1; i<=xuanguan; i++)
     {
        sprintf(uiChar, "%d",i);
        UIButton* button  = dynamic_cast<UIButton*>(ul->getWidgetByName(uiChar));
        button->setUserObject(CCInteger::create(i));
        button->setTouchEnabled(true);
        button->setOpacity(0);
        button->setScale(2);
        button->addTouchEventListener(this, toucheventselector(SelectScene::clickButtonCallback) );
     }
//    for (int i = 1; i<=20; i++)
//    {
//        int x = (i-1)/4 + 1;
//        int y = (i%4==0)?4:i%4;
//        sprintf(uiChar, "%d-%d",x,y);
//        UIButton* button  = dynamic_cast<UIButton*>(ul->getWidgetByName(uiChar));
//        ImageView* view = ImageView::create();
//        ImageView* view1 = ImageView::create();
//        ImageView* view2 = ImageView::create();
//        char viewName[20] = {0};
//        sprintf(viewName, "jrjm_blue%d.png",x);
//        view->loadTexture("jrjm_blue.png");
//        view1->loadTexture(viewName);
//        sprintf(viewName, "jrjm_blue%d.png",y);
//        view2->loadTexture(viewName);
//        ImageView* blueview = ImageView::create();
//        blueview->addChild(view);
//        blueview->addChild(view1);
//        blueview->addChild(view2);
//        view1->setPositionX(-10);
//        view2->setPositionX(10);
//        button->addChild(blueview,1,1001);
//        blueview->setPositionY(20);
//        
//        view->setScale(0.5);
//        view1->setScale(0.5);
//        view2->setScale(0.5);
//        
//        ImageView* viewR = ImageView::create();
//        viewR->loadTexture("jrjm_tb2.png");
//        blueview->addChild(viewR);
//        viewR->setPositionY(-25);
//        viewR->setScale(0.5);
//        
//        ImageView* gview = ImageView::create();
//        ImageView* gview1 = ImageView::create();
//        ImageView* gview2 = ImageView::create();
//        char gviewName[20] = {0};
//        sprintf(gviewName, "jrjm_lvs%d.png",x);
//        gview->loadTexture("jrjm_lvs.png");
//        gview1->loadTexture(gviewName);
//        sprintf(gviewName, "jrjm_lvs%d.png",y);
//        gview2->loadTexture(gviewName);
//        ImageView* greenview = ImageView::create();
//        greenview->addChild(gview);
//        greenview->addChild(gview1);
//        greenview->addChild(gview2);
//        gview1->setPositionX(-10);
//        gview2->setPositionX(10);
//        button->addChild(greenview,1,1002);
//        greenview->setPositionY(20);
//        greenview->setVisible(false);
//        gview->setPositionX(0);
//        gview2->setScale(0.5);
//        gview1->setScale(0.5);
//        gview->setScale(0.5);
//    }
//    
//    for (int j = xuanguan+1;j<=20;j++)
//    {
//        int x = (j-1)/4 + 1;
//        int y = (j%4==0)?4:j%4;
//        sprintf(uiChar, "%d-%d",x,y);
//        UIButton* button  = dynamic_cast<UIButton*>(ul->getWidgetByName(uiChar));
//        button->setBright(false);
//        button->setVisible(false);
//    }
     current_Select = xuanguan;
//    int x = (current_Select-1)/4 + 1;
//    int y = (current_Select%4==0)?4:current_Select%4;
     sprintf(uiChar, "%d",current_Select);
     curr_button  = dynamic_cast<UIButton*>(ul->getWidgetByName(uiChar));
     curr_button->setScale(1.1f);
     curr_button->setBright(true);
     curr_button->setOpacity(200);
     curr_button->runAction(CCRepeatForever::create(CCSequence::create(CCBlink::create(1.5, 2) , NULL))  );
     curr_button->setColor(ccc3(255, 0, 0));
    
     if(current_Select <= 10)
     {
         ul->setPositionX(0);
         jiantou1->setVisible(true);
         jiantou1->runAction(CCRepeatForever::create(CCBlink::create(0.5, 1)));
     }else if (current_Select>10 && current_Select <= 16)
     {
         ul->setPositionX(-SIZE.width + 20);
         jiantou1->setVisible(true);
         jiantou2->setVisible(true);
         jiantou1->runAction(CCRepeatForever::create(CCBlink::create(0.5, 1)));
         jiantou2->runAction(CCRepeatForever::create(CCBlink::create(0.5, 1)));
     }else
     {
         ul->setPositionX(-2048 + SIZE.width  );
         jiantou2->setVisible(true);
         jiantou2->runAction(CCRepeatForever::create(CCBlink::create(0.5, 1)));
     }
    
    new2 = ImageView::create();
    new2->loadTexture("xuanze/60.png");
    ul->addChild(new2);
    //CCPoint p =  ul->convertToWorldSpace();
    new2->setPosition(curr_button->getPosition());
 //   new2->runAction(CCRepeatForever::create(CCBlink::create(0.5, 1)));

//    aniSprite->setPosition(curr_button->getPosition());
//    curr_button->setBright(false);
//    curr_button->getChildByTag(1002)->setVisible(true);
//    curr_button->getChildByTag(1001)->setVisible(false);
//    UIButton* startGame = dynamic_cast<UIButton*>(ul->getWidgetByName("xg_jinruyouxi"));
//    startGame->setTouchEnabled(true);
//    startGame->addTouchEventListener(this, toucheventselector(SelectScene::start_game) );
//    ImageView* view =dynamic_cast<ImageView*>(ul->getWidgetByName("xg_wenbenkuang"));
//    font1 = UILabel::create();
//    font1->setText(title[current_Select]);
//    view->addChild(font1);
//    font1->setFontSize(25);
//    font1->setFontName("宋体");
//    font1->setTextAreaSize(CCSize(view->getContentSize().width-50,view->getContentSize().height/2));
//    font1->setContentSize(CCSize(0,view->getContentSize().height/2));
//    font1->setPositionY(0.67*view->getContentSize().height);
//    font1->setTextHorizontalAlignment(kCCTextAlignmentCenter);
//    font1->setTextVerticalAlignment(kCCVerticalTextAlignmentCenter);
//    font1->setColor(ccc3(255, 255, 0));
//    font1->setPositionX(30);
//    
//    font2 = UILabel::create();
//    XMLData* data =   XMLData::sharedXMLData();
//    const char* dataScore =  data->read(current_Select);
//    char desc[120] = {0};
//    sprintf(desc, "%s\n\n%s\n\n%s",descr[current_Select].c_str(),dataScore,moshiStr[current_Select].c_str());
//    font2->setText(desc);
//    view->addChild(font2);
//    font2->setFontSize(20);
//    font2->setFontName("宋体");
//    font2->setTextAreaSize(CCSize(view->getContentSize().width-160,200));
//    font2->setContentSize(CCSize(0,view->getContentSize().height/2));
//    font2->setTextVerticalAlignment(kCCVerticalTextAlignmentCenter);
//    font2->setTextVerticalAlignment(kCCVerticalTextAlignmentTop);
//    font2->setPositionY(0.25*view->getContentSize().height);
//    font2->setPositionX(0);
//    
    CCMenuItem* shopbutton  =  CCMenuItemImage::create("res/select/shangcheng1.png","res/select/shangcheng2.png"    , this,menu_selector(SelectScene::shopButtonCallback  ));  // UIButton::create();    //dynamic_cast<UIButton*>(ul->getWidgetByName("xg_shangcheng"

    menu->addChild(shopbutton);
    shopbutton->setPosition(ccp(SIZE.width*0.94, SIZE.height*0.07 ));
    

    if (xuanguan == 2 && (!KingData->getFirstTishiShuxing()))
    {
        KingData->setFirstTishiShuxing(true);
        CCUserDefault::sharedUserDefault()->setBoolForKey("firstTishiShuxing", KingData->getFirstTishiShuxing());
        CCUserDefault::sharedUserDefault()->flush();
        this->addTips();
        canClick = false;
    }else
    {
        canClick = true;
    }
    return true;
}

void SelectScene::fudong(CCObject* pSender)
{
    
    jiantou1->stopAllActions();
    jiantou2->stopAllActions();
    ul->stopAllActions();
    CCPoint pp = CCPoint( MAX(- (2048 - ul->getContentSize().width) , MIN(0,  ul->getPositionX() + -SIZE.width) ) , ul->getPositionY());
    float x = ul->getPositionX() - pp.x;
    
    ul->runAction(CCMoveTo::create(x/SIZE.width, pp ));
    
    if (pp.x > -0.2f) {
        jiantou1->setVisible(true);
        jiantou2->setVisible(false);
        jiantou1->runAction(CCRepeatForever::create(CCBlink::create(0.5, 1)));
        
    }else  if (pp.x < -0.2f && pp.x > -SIZE.width - 0.2f) {
        jiantou1->setVisible(true);
        jiantou2->setVisible(true);
        jiantou1->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)  ));
        jiantou2->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)  ));
    }else{
        jiantou1->setVisible(false);
        jiantou2->setVisible(true);
        jiantou2->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)   ));
    }
    
    drag = true;
}

void SelectScene::fudong1(CCObject* pSender)
{
    jiantou1->stopAllActions();
    jiantou2->stopAllActions();
    ul->stopAllActions();
    CCPoint pp = CCPoint( MAX(- (2048 - ul->getContentSize().width) , MIN(0,  ul->getPositionX() + SIZE.width) ) , ul->getPositionY());
    float x = pp.x - ul->getPositionX();
    ul->runAction(CCMoveTo::create(x/SIZE.width, pp ));
    if (pp.x > -0.2f) {
        jiantou1->setVisible(true);
        jiantou2->setVisible(false);
        jiantou1->runAction(CCRepeatForever::create(CCBlink::create(0.5, 1)));
    }else  if (pp.x < -0.2f && pp.x > -SIZE.width - 0.2f) {
        jiantou1->setVisible(true);
        jiantou2->setVisible(true);
        jiantou1->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)  ));
        jiantou2->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL) ));
    }else{
        jiantou1->setVisible(false);
        jiantou2->setVisible(true);
        jiantou2->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)  ));
    }

    drag = true;
}

void SelectScene::backScene(CCObject* pSender)
{
   // CCDirector::sharedDirector()->replaceScene( ShopScene::scene() );
	CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
}

void SelectScene::addTips()
{
    addTip(TIP[8]);
    sprite = CCSprite::create("help11.png");
    sprite->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.3f, ccp(0, 30)),CCMoveBy::create(0.3f, ccp(0, -30)),NULL)));
    this->addChild(sprite,1,9898);
    sprite->setScale(0.6f);
    sprite->setPosition(ccp(SIZE.width*0.93, SIZE.height*0.12));
}

void SelectScene::shopButtonCallback(CCObject* pSender)
{
    if ( biaozhi == 10)
    {
        return;
    }
    if (canClick == false)
    {
        resetTip();
        sprite->setVisible(false);
      //  biaozhi = 10;
        canClick = true;
        this->removeChildByTag(9900);
        sprite->setScale(0.5f);
        sprite->setPosition(ccp(SIZE.width*0.80, SIZE.height*0.25));
        PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.wav");
        CCRenderTexture* renderTexture = CCRenderTexture::create(SIZE.width, SIZE.height);
        renderTexture->begin();
        this->visit();
        renderTexture->end();
        CCDirector::sharedDirector()->pushScene( ShopBuy::scene(renderTexture,false,20));
    }else
    {
        PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.wav");
        CCRenderTexture* renderTexture = CCRenderTexture::create(SIZE.width, SIZE.height);
        renderTexture->begin();
        this->visit();
        renderTexture->end();
        CCDirector::sharedDirector()->pushScene( ShopBuy::scene(renderTexture,false));
    }
}


void SelectScene::shopButtonCallback(CCObject* pSender,TouchEventType type)
{
  
    if ( biaozhi == 10)
    {
        return;
    }
    switch (type) {
        case  cocos2d::gui::TOUCH_EVENT_BEGAN:
        {
            if (canClick == false)
            {
              //  biaozhi = 10;
                
                canClick = true;
                this->removeChildByTag(9900);
                sprite->setScale(0.5f);
                sprite->setPosition(ccp(SIZE.width*0.80, SIZE.height*0.3));
                PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.wav");
                CCRenderTexture* renderTexture = CCRenderTexture::create(SIZE.width, SIZE.height);
                renderTexture->begin();
                this->visit();
                renderTexture->end();
                CCDirector::sharedDirector()->pushScene( ShopBuy::scene(renderTexture,false,20));
            }else
            {
                PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.wav");
                CCRenderTexture* renderTexture = CCRenderTexture::create(SIZE.width, SIZE.height);
                renderTexture->begin();
                this->visit();
                renderTexture->end();
                CCDirector::sharedDirector()->pushScene( ShopBuy::scene(renderTexture,false));
            }
 
            break;
        }
        case cocos2d::gui::TOUCH_EVENT_ENDED:
        {
        }
        default:
            break;
    }
}

void SelectScene::onEnter()
{
    CCLayer::onEnter();
    PersonalAudioEngine::sharedEngine()->playBackgroundMusic("music/jiemianbgmusic.mp3",true);
}

void SelectScene::clickButtonCallback(CCObject* pSender, TouchEventType type)
{
	if (type == cocos2d::gui::TOUCH_EVENT_ENDED)
	{
		if (canClick == false) {
			return;
		}

		if (drag == true)
		{
			return;
		}

		if (this->getChildByTag(999)) {
			return;
		}

		for (int i = 1; i <= xuanguan; i++)
		{
			char uiChar[5] = { 0 };
			sprintf(uiChar, "%d", i);
			UIButton* button = dynamic_cast<UIButton*>(ul->getWidgetByName(uiChar));
			button->setVisible(true);
			button->setBright(true);
			button->setOpacity(0);
			button->stopAllActions();
		}
		UIButton* button = dynamic_cast<UIButton*>(pSender);
		CCInteger* integer = dynamic_cast<CCInteger*>(button->getUserObject());
		current_Select = integer->getValue();
		button->setScale(1.1f);
		button->setBright(true);
		button->setOpacity(200);
		button->runAction(CCRepeatForever::create(CCSequence::create(CCBlink::create(1.5, 2), NULL)));
		button->setColor(ccc3(255, 0, 0));



		BeginLayer* layer = BeginLayer::create(current_Select);
		this->addChild(layer, 999, 999);
		layer->setPosition(ccp(0, 0));
		layer->setVisible(true);
	}
}

void SelectScene::start_game(CCObject* pSender, TouchEventType type)
{
    if (!canClick)
    {
        return;
    }
    switch (type)
    {
        case  cocos2d::gui::TOUCH_EVENT_BEGAN:
        {
            PersonalAudioEngine::sharedEngine()->playEffect("music/confirm.wav");
            CCDirector::sharedDirector()->replaceScene(LoadingLayer::scene(current_Select, moshiID[current_Select]));
            break;
        }
        case cocos2d::gui::TOUCH_EVENT_ENDED:
        {
            
        }
        default:
            break;
    }
}

void SelectScene::Back(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
}

cocos2d::CCScene* SelectScene::scene()
{
    CCScene *scene = CCScene::create();
    SelectScene *layer = SelectScene::create();
    scene->addChild(layer);
    return scene;
}

void SelectScene::onExit()
{
    PersonalAudioEngine::sharedEngine()->stopAllEffects();
    PersonalAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    CCLayer::onExit();
}

bool SelectScene::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    if (canClick == false) {
        return false;
    }
    beginP = touch->getLocation();
    return true;
}
void SelectScene::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{

}
void SelectScene::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    endP = touch->getLocation();
   
    if ( endP.x - beginP.x > 100)
    {
        jiantou1->stopAllActions();
        jiantou2->stopAllActions();
        ul->stopAllActions();
        CCPoint pp = CCPoint( MAX(- (2048 - ul->getContentSize().width) , MIN(0,  ul->getPositionX() + SIZE.width) ) , ul->getPositionY());
        float x = pp.x - ul->getPositionX();
        
        ul->runAction(CCMoveTo::create(x/SIZE.width, pp ));
  
        if (pp.x > -0.2f) {
            jiantou1->setVisible(true);
            jiantou2->setVisible(false);
            jiantou1->runAction(CCRepeatForever::create(CCBlink::create(0.5, 1)));
         
        }else  if (pp.x < -0.2f && pp.x > -SIZE.width - 0.2f) {
            jiantou1->setVisible(true);
            jiantou2->setVisible(true);
            jiantou1->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)  ));
            jiantou2->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)  ));
        }else{
            jiantou1->setVisible(false);
            jiantou2->setVisible(true);
            jiantou2->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)  ));
        }
        
        drag = true;
    }else if (endP.x - beginP.x < -100)
    {
        jiantou1->stopAllActions();
        jiantou2->stopAllActions();
        ul->stopAllActions();
        CCPoint pp = CCPoint( MAX(- (2048 - ul->getContentSize().width) , MIN(0,  ul->getPositionX() + -SIZE.width) ) , ul->getPositionY());
        float x = ul->getPositionX() - pp.x;
        
        ul->runAction(CCMoveTo::create(x/SIZE.width, pp ));
       
        if (pp.x > -0.2f) {
            jiantou1->setVisible(true);
            jiantou2->setVisible(false);
            jiantou1->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)  ));
            
        }else  if (pp.x < -0.2f && pp.x > -SIZE.width - 0.2f) {
            jiantou1->setVisible(true);
            jiantou2->setVisible(true);
            jiantou1->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)  ));
            jiantou2->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)  ));
        }else{
            jiantou1->setVisible(false);
            jiantou2->setVisible(true);
            jiantou2->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.25),CCFadeOut::create(0.25),NULL)  ));
        }
        
        drag = true;
    }else
    {
        drag = false;
    }
   
  }


void SelectScene::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-126,false);
}

void SelectScene::addTip(std::string text)
{
    jiaoshi->setFlipX(false);
    tip1->runAction(CCMoveTo::create(0.2f, ccp(210,70)));
    jiaoshi->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCMoveTo::create(0.2f, ccp(SIZE.width*0.085, 2))
                                          ,NULL ));
    
    label->setPosition(ccp(220, tip1->getContentSize().height));
    tip1->setVisible(true);
    jiaoshi->setVisible(true);
    label->setText(XXIconv::GBK2UTF(text.c_str()));
}

void SelectScene::addTip2(std::string text)
{
    jiaoshi->setVisible(false);
    tip1->setVisible(false);
    jiaoshi->setPosition(ccp(1.15*SIZE.width,10));
    tip1->setPosition(ccp( SIZE.width+150, -120));
    tip1->setVisible(true);
    jiaoshi->setVisible(true);
    jiaoshi->setFlipX(true);
    label->setPosition(ccp(100, tip1->getContentSize().height));
    tip1->runAction(CCMoveTo::create(0.2f, ccp(SIZE.width-210,70)));
    jiaoshi->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCMoveTo::create(0.2f, ccp(SIZE.width-SIZE.width*0.085, 2))
                                          ,NULL ));
    
    label->setText(XXIconv::GBK2UTF(text.c_str()));
}


void SelectScene::resetTip()
{
    tip1->setVisible(false);
    jiaoshi->setVisible(false);
    label->setText("");
    jiaoshi->setPosition(ccp(-0.15*SIZE.width,10));
    tip1->setPosition(ccp( -150, -120));
}