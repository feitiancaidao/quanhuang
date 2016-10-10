//
//  SkillObject.cpp
//  king04
//
//  Created by mac on 14-5-26.
//
//

#include "SkillObject.h"
#include "Hero.h"
#include "Define.h"
#include "GameScene.h"
SkillObject* SkillObject::create(int id)
{
    SkillObject* skillObject = new SkillObject();
    skillObject->init(id);
    skillObject->autorelease();
    return skillObject;
}
bool SkillObject::init(int id)
{
    this->id = id;
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("quanqiande/quanqiande.ExportJson");
    armature = CCArmature::create("quanqiande");
    armature->getAnimation()->playWithIndex(id);
    this->addChild(armature);
    armature->setAnchorPoint(ccp(0,0));
    this->setAnchorPoint(ccp(0, 0));
    this->scheduleUpdate();
    return true;
}

void SkillObject::update(float dt)
{
    if (this->getBondingBox().intersectsRect(Role->getBondingBox()))
    {
        CCLOG("技能%d",id);
        this->removeFromParent();
        gameLayer->addCard(id);
    }
}

CCRect SkillObject::getBondingBox()
{
    CCRect rect;
    rect.size = armature->getContentSize();
    rect.origin = this->getPosition();
    return rect;
}
