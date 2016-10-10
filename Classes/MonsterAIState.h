//
//  MonsterAIState.h
//  XiYouJi
//
//  Created by mac on 14-3-23.
//
//

#ifndef __XiYouJi__MonsterAIState__
#define __XiYouJi__MonsterAIState__

#include "State.h"

class Monster;
//------------------------------------------------------------------------
//    怪物初始化状态
//------------------------------------------------------------------------
class MonsterInitState : public State<Monster>    //怪物移动状态机
{
private:
    MonsterInitState(){}
    //copy ctor and assignment should be private
    MonsterInitState(const MonsterInitState&);
    MonsterInitState& operator=(const MonsterInitState&);
    
public:
    
    static MonsterInitState* Instance();
    
    virtual void Enter(Monster* monster);
    
    virtual void Execute(Monster* monster);
    
    virtual void Exit(Monster* monster);
};

//------------------------------------------------------------------------
//    怪物激活状态
//------------------------------------------------------------------------
class MonsterActiveState : public State<Monster>    //怪物移动状态机
{
private:
    MonsterActiveState(){}
    //copy ctor and assignment should be private
    MonsterActiveState(const MonsterActiveState&);
    MonsterInitState& operator=(const MonsterActiveState&);
    
public:
    
    static MonsterActiveState* Instance();
    
    virtual void Enter(Monster* monster);
    
    virtual void Execute(Monster* monster);
    
    virtual void Exit(Monster* monster);
};

//------------------------------------------------------------------------
//  怪移动状态
//------------------------------------------------------------------------
class MonsterMoveState : public State<Monster>    //怪物移动状态机
{
private:
    MonsterMoveState(){}
    //copy ctor and assignment should be private
    MonsterMoveState(const MonsterMoveState&);
    MonsterMoveState& operator=(const MonsterMoveState&);
    
public:
    
    static MonsterMoveState* Instance();
    
    virtual void Enter(Monster* monster);
    
    virtual void Execute(Monster* monster);
    
    virtual void Exit(Monster* monster);
};
//------------------------------------------------------------------------
//  怪靠近主角状态
//------------------------------------------------------------------------
class MonsterApproachState : public State<Monster>    //怪物移动状态机
{
private:
    MonsterApproachState(){}
    //copy ctor and assignment should be private
    MonsterApproachState(const MonsterApproachState&);
    MonsterApproachState& operator=(const MonsterApproachState&);
    
public:
    
    static MonsterApproachState* Instance();
    
    virtual void Enter(Monster* monster);
    
    virtual void Execute(Monster* monster);
    
    virtual void Exit(Monster* monster);
};
//------------------------------------------------------------------------
//  怪攻击主角状态
//------------------------------------------------------------------------
class MonsterAttackState : public State<Monster>    //怪物移动状态机
{
private:
    MonsterAttackState(){}
    //copy ctor and assignment should be private
    MonsterAttackState(const MonsterAttackState&);
    MonsterAttackState& operator=(const MonsterAttackState&);
    
public:
    
    static MonsterAttackState* Instance();
    
    virtual void Enter(Monster* monster);
    
    virtual void Execute(Monster* monster);
    
    virtual void Exit(Monster* monster);
};


//------------------------------------------------------------------------
//  怪受到攻击状态
//------------------------------------------------------------------------
class MonsterBeAttackState : public State<Monster>    //怪物移动状态机
{
private:
    MonsterBeAttackState(){}
    //copy ctor and assignment should be private
    MonsterBeAttackState(const MonsterBeAttackState&);
    MonsterBeAttackState& operator=(const MonsterBeAttackState&);
    
public:
    
    static MonsterBeAttackState* Instance();
    
    virtual void Enter(Monster* monster);
    
    virtual void Execute(Monster* monster);
    
    virtual void Exit(Monster* monster);
};


//------------------------------------------------------------------------
//  怪死亡状态
//------------------------------------------------------------------------
class MonsterDeadState : public State<Monster>    //怪物移动状态机
{
private:
    MonsterDeadState(){}
    //copy ctor and assignment should be private
    MonsterDeadState(const MonsterDeadState&);
    MonsterDeadState& operator=(const MonsterDeadState&);
    
public:
    
    static MonsterDeadState* Instance();
    
    virtual void Enter(Monster* monster);
    
    virtual void Execute(Monster* monster);
    
    virtual void Exit(Monster* monster){};
};

//------------------------------------------------------------------------
//  怪倒地起身状态
//------------------------------------------------------------------------
class MonserFallUpState : public State<Monster>    //怪物移动状态机
{
private:
    MonserFallUpState(){}
    //copy ctor and assignment should be private
    MonserFallUpState(const MonserFallUpState&);
    MonserFallUpState& operator=(const MonsterDeadState&);
    
public:
    
    static MonserFallUpState* Instance();
    
    virtual void Enter(Monster* monster);
    
    virtual void Execute(Monster* monster);
    
    virtual void Exit(Monster* monster);
};




#endif /* defined(__XiYouJi__MonsterAIState__) */
