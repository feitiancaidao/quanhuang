//
//  XMLData.h
//  King
//
//  Created by mac on 14-4-25.
//
//

#ifndef __King__XMLData__
#define __King__XMLData__

#include "cocos2d.h"
USING_NS_CC;
#include "support/tinyxml2/tinyxml2.h"



using namespace tinyxml2;
class XMLData : public CCObject
{
public:
    static XMLData* sharedXMLData();
    bool init();
    const char* read(int guan);
    int getScore(int guan);
    int getTimes(int guan);
    void update(int guan,int score,int times=1);

private:
	std::string _readInfos;
};

#endif /* defined(__King__XMLData__) */
