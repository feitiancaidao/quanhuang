#ifndef  __TEXTINFOS_H__
#define  __TEXTINFOS_H__

#include <string>

const std::string  TEXTINFOS[] = {
	"For the first time to buy for free",
	"HP",
	"ATT",
	"DEF",
	"Rage",
	"MAX"
};

const std::string moshiStr[21] =
{
	"", "Kill 10 enemies", "Kill 15 enemies", "Within 1 minute, kill 10 enemies and Boss",
	"Kill 30 enemies", "Within 1 minute, kill 20 enemies", "Walk 600 meters", "Kill the Boss",
	"Walk 800 meters", "Live for 2 minutes", "Kill 40 enemies", "Kill the Boss",
	"Kill 45 enemies", "Live for 2 minutes", "Walk 1200 meters", "Kill the Boss",
	"Kill 60 enemies", "Walk 1500 meters", "Live for 3 minutes", "Kill the Boss"
};

const std::string title[21] =
{ "1-1.H.k.1", "1-1.H.k.1", "1-2.H.k.2", "1-3.H.k.3", "1-4.H.k.4", "2-1.Franz.1", "2-2.Franz.2", "2-3.Franz.3", "2-4.Franz.4", "3-1.Adventure.1", "3-2.Adventure.2", "3-3.Adventure.3", "3-4.Adventure.4", "4-1.Alhambra.1", "4-2.Alhambra.2", "4-3.Alhambra.3", "4-4.Alhambra.4", "5-1.Factories.1", "5-2.Factories.2", "5-3.Factories.3", "5-4.Factories.4" };

static std::string nenglidescTitle[4] = { "YAOTOME", "YA SAKAZUKI", "Ukemi", "Dodge" };
static std::string nenglidescText[7] = { "Eight young woman, with a powerful claws in enemy mad tear on the body, after locking strength in each other's head with your hands, and make the enemy tearing and spray blood throughout the body. ", "Through the power of the flame itself to the recipient nerve and surface damage, make the recipient feel time to stop. ", "Ground start automatically using protection skills", "Forward dodge,dodge when in a state of invincibility", "Rebuild after death,For the first time to buy for free"};
static std::string shopdescTitle[5] = { "1888Gold", "18888Gold","Resurrection", "Rage", "Super Gift" };
static std::string shopdescText[5] = { "1888Gold", "18888Gold", "Rebuild after death","10 rage", "8888金币! 50个怒气包! 学会全部技能! 额外附赠一次死亡复活!" };


const std::string TIP[] = {
	"Hold the right direction to the screen the location of the aperture",

	"Hold the attack button to attack",

	"Click the button release skills",

	"Click the attack button, can achieve more combo",

	"Teaching is complete, reward 500 gold",

	"Can't use skill without rage",
	"Click the button to buy the rage",

	"Congratulations you get 10 rage",
	"The enemy too much to strengthen the property"
};

const std::string wordss[] =
{
	"Hey boss, that girl is really hot!", "Dame yeah, lets buy her a drink.", "Get away,I have other things to do!",
	"wow, I love that temper . Bring her here.","Beauty,relax, am I ur type?","Stop!What are you guys doing! Leave her alone! ","haha, what do you want ?A fight? Gentlemen, kick his ass!"
};

const std::string descr[21] =
{"第一次进入游戏","这是一片法律无法触及的地方，只有一个流传很久的名字—堕落街。","毫无疑问这是一个极其危险的地方，但是救出小舞是你唯一的目标","无穷无尽的敌人，难道你已经陷入了一个巨大的阴谋之中?","代号“鬣狗”,这是堕落街的幕后黑手么？","堕落街原来只是一个入口，这背后居然隐藏着如此巨大的都市。","残破不堪的废弃都市中隐藏着各种犯罪分子，既然如此就惩奸除恶吧。","这些人都是亡命之徒你必须小心，再小心！","终于安奈不住了? 分部首领出现!","分部首领说小舞被抓到了礼拜堂里，礼拜堂？","这隐藏在黑暗中的礼拜堂如此雄伟，为什么在这种地方还有礼拜堂。","看看你发现了什么？一个邪教组织！","邪恶教主, ”鬣狗“组织的又一条狗","这堕落都市居然是在市中心的下面，华尔街大道才是他们的老巢","再现! 传说中的古武术!都去死吧！"
    ,"觉醒吧！我的终极能力","教主再现?! 打不死的邪恶教主?","最终决战之地! 喋血码头!","死拼! 狂暴下的黯月之血!","让我在疯狂一次吧","既然想伤害我最爱的人，就让你们所有人陪葬"};


const std::string loadingTips[] =
{
"小提示: 怪物太强打不过？还不快快强化属性。",
	"小提示: 怒气不够用快去商店购买怒气包吧。",
	"小提示: 多多使用必杀技虐杀BOSS吧。",
	"小提示: 你知道么？在商店可以购买两个超强的隐藏技能。",
	"小提示: 出现隐藏礼包一定要把握机会，下次就不会再来了。"
};


enum { BUY_Bazhinv=8,BUY_Bajiubei=9,BUY_JinjiDuobi=23,BUY_Shoushen=24, \
BUY_Money1888=25,BUY_Money5888=26,BUY_Money18888=27,BUY_Fuhuo=10,BUY_Nuqi=34, \
BUY_Jihuolayer=19,BUY_Dalibao=16};

enum 
{
	NONE_HELP,SHUXING_HELP
};


#endif


