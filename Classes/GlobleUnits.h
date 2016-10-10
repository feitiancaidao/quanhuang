#ifndef _cocos_globle_units__h__
#define _cocos_globle_units__h__

#include "cocos2d.h"
#include "cocos-ext.h"



USING_NS_CC;
USING_NS_CC_EXT;

struct AnimSp
{
	float voids;
	float nextcalltime;
};


enum RictTextType
{
	SAMPLETEXT = 0, //普通文本
	SAMPLEIMG = 1, //图片
	SAMPLEANIM = 2, //动画表情
	SAMPLEPRITISE = 3,
};


struct CellBeanData
{
	int id;
	int type;
	std::string image1;
	std::string image2;
	std::string tips;
	int data;

};






class SehouldNode : public CCNode
{
	public:
		SehouldNode();
		~SehouldNode();

		bool init();

		void callshowAds(float);

		void callshowTips(float );

		CREATE_FUNC(SehouldNode);
};



class GlobleUnits
{
	public:
		static GlobleUnits* getInstance();

		bool MusicStaet();

		void payitemById( int info);

		void paySuccess(int );

		void callExit();
		
		//每日领奖
		bool canshowEveryDataGif();

		void getAwardData();

		int getAwardTimes();
		
		
		
	private:
			
			GlobleUnits();
			~GlobleUnits();

		
			

			
			std::string _userphonename;

			
};










#endif