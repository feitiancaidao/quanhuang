#include "GlobleUnits.h"
#include "StringUtil.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "jni/JniHelper.h"
#endif
#include "ShopBuyLayer.h"
#include "HubLayer.h"
#include "Define.h"
#include "cocos-ext.h"
#include "GameData.h"
#include "HubLayer.h"
#include "PlayerHeadUI.h"
#include "PersonalAudioEngine.h"
#include "Define.h"
#include "TextInfos.h"


using namespace tinyxml2;

std::string vipkey = "vipsisis";
std::string getxinshoukey = "xinshousisis";
std::string getplaytimekey = "playtimes";
std::string everydatakeyi = "fgfdgfdgfdg";
std::string everydatatime = "fgfdgffdgfdgfg";
std::string everylasttime = "fgfdgfdgfdsdg";
std::string isendlasttime = "fgfdgfdgfdsdgdgf12";
std::string huafeijuan = "fgfdgfdgfdsdgdgfdghfdg2";

std::string _packagename = "org/cocos2dx/plugins/";






GlobleUnits::GlobleUnits()
	
{
	srand(time(0));

}


GlobleUnits::~GlobleUnits()
{
	


}


void GlobleUnits::callExit()
{
	#if (CC_TARGET_PLATFORM ==  CC_PLATFORM_ANDROID   ) 
	
	JniMethodInfo minfo;




	bool isHave  = JniHelper::getStaticMethodInfo(minfo,(_packagename+"DeviceUnits").c_str(),"openexit", "(Ljava/lang/String;)V");
	if( isHave )
	{
		std::string ids[] = { "" };
		jstring   parmestr  =   minfo.env->NewStringUTF( "sfsf" );

		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,parmestr); 
	}else
	{
		//cocos2d::CCLog("not show info...");
	}


#endif

}

void GlobleUnits::payitemById(int info)
{
	std::string infos = StringUtil::toString(info);



	
//#if (CC_TARGET_PLATFORM ==  CC_PLATFORM_ANDROID   ) 
//	
//	JniMethodInfo minfo;
//
//
//
//
//	bool isHave  = JniHelper::getStaticMethodInfo(minfo,(_packagename+"DeviceUnits").c_str(),"openpayById", "(Ljava/lang/String;)V");
//	if( isHave )
//	{
//		std::string ids[] = { "" };
//		jstring   parmestr  =   minfo.env->NewStringUTF( infos.c_str() );
//
//		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,parmestr); 
//	}else
//	{
//		//cocos2d::CCLog("not show info...");
//	}
//
//
//#else
	//jincall
	paySuccess( info ) ;
//#endif
}




void GlobleUnits::paySuccess(int  aaaa)
{

	//int now = StringUtil::parseString<int>( data  );

	  //int xc =UserInfo::GetInstance()->getMyCoin();
      //UserInfo::GetInstance()->setMyCoin(xc+2500);
		int golds[] = {10,22,48,78,112,150,255,255,360};
		int monys[] = {1,2,4,6,8,10,15,15,20};
	
	

		int aaa = (int)aaaa;
	if (aaa == BUY_Bazhinv)
    {
		KingData->buyBazhinv();
        if (HUB!=NULL)
		{
			CCProgressTimer* timer1 = dynamic_cast<CCProgressTimer*>(HUB->getChildByTag(skill2TimerTag));
			timer1->setPercentage(100);
            HUB->runSkill(2);
        }
        
	}
	else if (aaa == BUY_Bajiubei)
    {
		KingData->buyBajiubei();
        // KingData->setShoushen(true);
        if (HUB!=NULL)
        {
			CCProgressTimer* timer1 = dynamic_cast<CCProgressTimer*>(HUB->getChildByTag(skill3TimerTag));
			timer1->setPercentage(100);
           HUB->runSkill(3);
        }
        
	}
	else if (aaa == BUY_JinjiDuobi)
    {
		KingData->buyJinjiduobi();
        if (HUB!=NULL)
        {
          
		    CCProgressTimer* timer1 = dynamic_cast<CCProgressTimer*>(HUB->getChildByTag(skill4TimerTag));
			 timer1->setPercentage(100);
			  HUB->runSkill(4);
        }
	}
	else if (aaa == BUY_Shoushen)
    {
		KingData->buyShouShen();
        if (Role!=NULL)
        {
           Role->fuhuo();
        }
    }
	else if (aaa == BUY_Money1888)
    {
        KingData->alterMoney(1888);
    }
	else if (aaa == BUY_Money5888)
    {
        KingData->alterMoney(5888);
    }
	else if (aaa == BUY_Money18888)
    {
        KingData->alterMoney(18888);
    }
    
    
	else if (aaa == BUY_Fuhuo)
    {
        if (Role != NULL)
        {
                if (Role->isDie)
                {
                     Game::instance()->getShopLayer()->ispop = true;
                }else
                {
                     KingData->setFuhuo(true);
                }
        }else
        {
            KingData->setFuhuo(true);
        }
		KingData->flush();
	}
	else if (aaa == BUY_Nuqi)
    {
         KingData->setExtraNuqi(KingData->getExtraNuqi()+1000);
		 if (Role != NULL)
		 {
			 Game::instance()->getShopLayer()->ispop2 = true;
		 }      
	}
	else if (aaa == BUY_Jihuolayer)
    {
        if (Role != NULL)
        {
           // Game::instance()->getShopLayer()->ispop = true;
            Game::instance()->getJihuolayer()->ispop = true;
        }
	}
	else if (aaa == BUY_Dalibao)
	{
	  KingData->alterMoney(8888);
	  KingData->setNuqibao(true);
	   GameData::sharedGameData()->buyHeroNuqi(50);
	   CCUserDefault::sharedUserDefault()->setBoolForKey("jinjiduobi",true);
	    CCUserDefault::sharedUserDefault()->setBoolForKey("shoushen",true);
        CCUserDefault::sharedUserDefault()->flush();
		KingData->setJinjiDuobi(true);
		KingData->setShoushen(true);
	}
}




bool  GlobleUnits::MusicStaet()
{
	bool state = true;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	
	JniMethodInfo minfo;
	std::string _packagename = "org/cocos2dx/plugins/";
	bool isHave = JniHelper::getStaticMethodInfo(minfo,(_packagename+"DeviceUnits").c_str(),"getMusicState", "(Ljava/lang/String;)Z");
	if( isHave )
	{
		jstring   packagestr  =   minfo.env->NewStringUTF("v" );

		///minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,packagestr); 
		state = minfo.env->CallStaticBooleanMethod( minfo.classID, minfo.methodID,packagestr );
		//setPlayBackState(state);
	

	}else
	{
		////cocos2d::CCLog("not show info...");
	}
	
#endif




	return state;
	
}


int GlobleUnits::getAwardTimes()
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey(everydatatime.c_str(),0);
}

bool GlobleUnits::canshowEveryDataGif()
{
	bool canshow = false;
	everydatakeyi;
	everydatatime;
	everylasttime;

	time_t tt = time(NULL);
	tm* t= localtime(&tt);
	int year = t->tm_year + 1900;
	int mon = t->tm_mon + 1;
	int data = t->tm_mday;

	int firstyear = 0;
	int firstmon = 0;
	int firstdata = 0;



	std::string nowtime = "";
	nowtime =  CCUserDefault::sharedUserDefault()->getStringForKey(everydatakeyi.c_str(),"");
	int gettimenums = CCUserDefault::sharedUserDefault()->getIntegerForKey(everydatatime.c_str(),0);

	if(  nowtime == "" )
	{
		nowtime =  CCString::createWithFormat("%d",year )->getCString() + std::string("-")+ CCString::createWithFormat("%d",mon )->getCString() + std::string("-") +CCString::createWithFormat("%d",data )->getCString();
		 //UserDefault::sharedUserDefault()->setStringForKey(everydatakeyi.c_str(),nowtime);
		 firstyear = year;
		 firstmon = mon;
		 firstdata = data;
		 return true;
	}else
	{
		std::string yearstr = nowtime;
		std::vector<std::string> spits =  StringUtil::split(yearstr,"-");

		firstyear = StringUtil::parseString<int>( spits[0] );
		firstmon = StringUtil::parseString<int>( spits[1] );
		firstdata = StringUtil::parseString<int>( spits[2] );
	}
	
	nowtime =  StringUtil::toString(year) +"-"+ StringUtil::toString(mon) + "-" + StringUtil::toString(data);

	int subdata = (year*365+mon*30+data ) - (firstyear*365+firstmon*30+firstdata ) ;

	if( subdata >= 1 )
	{
		return true;
	}else
	{
		return false;
	}

	return canshow;
}



void  GlobleUnits::getAwardData()
{
	int datanums[] = { 300,500,800,1000,1200,1400,1600 };
	time_t tt = time(NULL);
	tm* t= localtime(&tt);
	int year = t->tm_year + 1900;
	int mon = t->tm_mon + 1;
	int data = t->tm_mday;

	std::string nowtime =  StringUtil::toString(year) +"-"+ StringUtil::toString(mon) + "-" + StringUtil::toString(data);

	int gettimenums = CCUserDefault::sharedUserDefault()->getIntegerForKey(everydatatime.c_str(),0);
	int nCurDay =getAwardTimes();

	////int curGold =NTGameSave::sharedGameSave()->getDataById(_GS_GOLD);
	if(nCurDay < 0)
		return;
		/*
	NTGameCache *pGC = NTGameCache::shareGameCacheManager();
	int zhuanshi = pGC->getMoney_Diamond();
	int jinbi = pGC->getGameCoins();
	int prop1 = pGC->getSkillNum2WarehouseByID(0);
	int prop2 = pGC->getSkillNum2WarehouseByID(1);
	int prop3 = pGC->getSkillNum2WarehouseByID(2);

	switch(nCurDay)
	{
		case 0:
			{
				pGC->setGameCoins(jinbi+150);
				break;
			}
		case 1:
			{
				pGC->setSkillNum2WarehouseByID(0,prop1+1);
				break;
			}
			case 2:
			{
				pGC->setGameCoins(jinbi+200);
				break;
			}
			case 3:
			{
				pGC->setMoney_Diamond(zhuanshi+10);
				break;
			}
			case 4:
			{
				pGC->setGameCoins(jinbi+250);
				break;
			}
			case 5:
			{
				pGC->setMoney_Diamond(zhuanshi+50);
				break;
			}
			case 6:
			{
				pGC->setGameCoins(jinbi+300);
				break;
			}
			case 7:
			{
				break;
			}

	};
	

	*/

	CCUserDefault::sharedUserDefault()->setStringForKey(everydatakeyi.c_str(),nowtime);
	CCUserDefault::sharedUserDefault()->setIntegerForKey(everydatatime.c_str(),1+gettimenums);
	CCUserDefault::sharedUserDefault()->flush();
}





GlobleUnits* GlobleUnits::getInstance()
{
	static GlobleUnits* _instance = NULL;

	if(  _instance == NULL  )
	{
		_instance = new GlobleUnits();
		
		

	}
	return _instance;
}
