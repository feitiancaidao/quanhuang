
#include "openalertJni.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GlobleUnits.h"
#include "TextInfos.h"

#define JAVA_CPP_HALPER_CLASS "com/ysgame/quanhuang/hwgame/CppHelper"

using namespace cocos2d;


std::map<int, int> PayingIndex;


int StringToInt(const std::string& str)
{
	int result = 0;
	for (std::string::const_iterator itr = str.begin(); itr != str.end(); ++itr)
	{
		int tmp = (*itr) - '0';
		result = result * 10 + tmp;
	}
	return result;
}






void openalertJni::payRequest(const std::string& paycode)
{
	CCLOG("%s", "payRequest");
	if(isPaying(StringToInt(paycode)))
	{
		CCLOG("%s", "is buying skill");
		return;
	}
	else
	{
		PayingIndex[StringToInt(paycode)]=1;
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	jobject jobj;
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, JAVA_CPP_HALPER_CLASS,
		"payRequest",
		"(Ljava/lang/String;)V");
	if (isHave)
	{
		jstring jpc = methodInfo.env->NewStringUTF(paycode.c_str());
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jpc);
	}
	else
	{
		CCLOG("%s","payRequest not find");
	}
#else
	GlobleUnits::getInstance()->paySuccess(StringToInt(paycode));
	CCLog("");
#endif
}

void openalertJni::backBtn()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	jobject jobj;
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, JAVA_CPP_HALPER_CLASS,
		"BackBtn",
		"()V");
	if (isHave)
	{
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
	}
	else
	{
		CCLOG("%s","backBtn not find");
	}
#endif
}

bool openalertJni::isPaying(int payid)
{
	//现在仅仅检测四个技能是否正在购买
	if (payid == BUY_Bajiubei || payid == BUY_Bazhinv || payid == BUY_Shoushen || payid == BUY_JinjiDuobi)
	{
		if (PayingIndex.find(payid) == PayingIndex.end() || PayingIndex[payid] != 1)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	return false;
}



#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C"
{
	JNIEXPORT void JNICALL Java_com_ysgame_quanhuang_hwgame_CppHelper_payResultC(JNIEnv *env, jclass thiz, jboolean isSuccess, jstring payCode)
	{
		char * pcode = (char *)env->GetStringUTFChars(payCode, 0);
		std::string pstr(pcode);
		if((bool)isSuccess)
			GlobleUnits::getInstance()->paySuccess(StringToInt(pstr));


		CCLOG("%s","pay back");
		PayingIndex[StringToInt(pstr)]=0;
	}


	JNIEXPORT void JNICALL Java_com_ysgame_quanhuang_hwgame_CppHelper_exitGame
		(JNIEnv * env, jclass thiz)
	{
		CCDirector::sharedDirector()->end();
	}
}
#endif