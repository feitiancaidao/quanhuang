//
//  PersonalAudioEngine.cpp
//  FishingJoy
//
//  Created by Ringo_D on 12-9-27.
//
//

#include "PersonalAudioEngine.h"
#include "GameData.h"
#include "Define.h"
static PersonalAudioEngine* _sharedEngine = NULL;
using namespace CocosDenshion;
USING_NS_CC;
void PersonalAudioEngine::setBackgroundMusicVolume(float volume)
{
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
    KingData->setMusicVolume(volume);
}
void PersonalAudioEngine::setEffectsVolume(float volume)
{
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
    KingData->setSoundVolume(volume);
}
PersonalAudioEngine* PersonalAudioEngine::sharedEngine()
{
    if(_sharedEngine==NULL){
        _sharedEngine = new PersonalAudioEngine();
        _sharedEngine->init();
    }
    return _sharedEngine;
}
bool PersonalAudioEngine::init()
{
    this->preloadBackgroundMusic("music/jiemianbgmusic.mp3");
    this->preloadEffect("music/baoqi.mp3");
    this->preloadEffect("music/dajiqie1.mp3");
    this->preloadEffect("music/dajiqie2.wav");
    this->preloadEffect("music/dajiqing.WAV");
    this->preloadEffect("music/dajiqie1.mp3");
    this->preloadEffect("music/dajiz.WAV");
    this->preloadEffect("music/dajizhong.WAV");
    this->preloadEffect("music/dazhao.mp3");
    this->preloadEffect("music/ko.mp3");
    this->preloadEffect("music/shanbi.mp3");
    this->preloadEffect("music/zhugongji1.mp3");
    this->preloadEffect("music/zhugongji2.mp3");
    this->preloadEffect("music/zhushouji.mp3");
    this->preloadEffect("music/prop.WAV");
    this->setBackgroundMusicVolume(100);
    this->setEffectsVolume(20.0);
    return true;
}
void PersonalAudioEngine::purge()
{

}
PersonalAudioEngine::PersonalAudioEngine()
{
    
}
PersonalAudioEngine::~PersonalAudioEngine()
{
    
}
