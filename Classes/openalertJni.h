
#ifndef __openalertJni_H__
#define __openalertJni_H__

#include "cocos2d.h"
#include "XXIconv.h"

#define CALL_COUNT  XXIconv::GBK2UTF("客服电话拨打次数").c_str()

using namespace cocos2d;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#endif

extern "C" {
	class	openalertJni{
	public:
		static void payRequest(const std::string& paycode);
		//退出按钮调用
		static void backBtn();
		//检测4个技能的计费点是否已发出支付请求
		static bool isPaying(int payid); 
	};
}

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#ifdef __cplusplus
extern "C" {
#endif
	JNIEXPORT void JNICALL Java_com_ysgame_quanhuang_hwgame_CppHelper_payResultC
		(JNIEnv *, jclass, jboolean, jstring);

	JNIEXPORT void JNICALL Java_com_ysgame_quanhuang_hwgame_CppHelper_exitGame
		(JNIEnv *, jclass);
#ifdef __cplusplus
}
#endif
#endif

#endif // __ANDROID_COCOS2D_JNI_H__
