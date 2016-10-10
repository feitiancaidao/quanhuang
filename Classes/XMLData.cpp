//
//  XMLData.cpp
//  King
//
//  Created by mac on 14-4-25.
//
//

#include "XMLData.h"
#include "GameData.h"
#include "Define.h"
#include"XXIconv.h"


static XMLData* xmldata = NULL;


XMLData* XMLData::sharedXMLData()
{
	CCLOG("%s", "getXML");
    if (xmldata == NULL)
    {
        xmldata = new XMLData();
        xmldata->init();
    }
    return xmldata;
}

bool XMLData::init()
{
    std::string filepath =  CCFileUtils::sharedFileUtils()->getWritablePath() + "kingdata2.xml";
	CCLog("init filepath %s", filepath.c_str());
    bool isFIleExist =  CCFileUtils::sharedFileUtils()->isFileExist(filepath.c_str());
    if (isFIleExist)
    {
        return true;
    }
    tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();     //xml文档
    if (NULL==pDoc)
    {
        return false;
    }
    XMLDeclaration *pDel = pDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");   //xml声明
    if (NULL==pDel)
    {
        return false;
    }
    pDoc->LinkEndChild(pDel);
    XMLElement *plistElement = pDoc->NewElement("plist");     //节点plist
    plistElement->SetAttribute("version", "1.0");//给节点设置属性
    pDoc->LinkEndChild(plistElement);
    XMLElement *dictElement = pDoc->NewElement("dict");   //节点dict
    plistElement->LinkEndChild(dictElement);
 
    for (int i = 0; i<=20; i++) {
        char guan[20] = {0};
        sprintf(guan, "guan%d",i+1);
        XMLElement *strEle = pDoc->NewElement(guan);
        strEle->LinkEndChild(pDoc->NewText("No score record"));
        dictElement->LinkEndChild(strEle);
        strEle->SetAttribute("score", 0);
        strEle->SetAttribute("times", 0);
    }
    pDoc->SaveFile(filepath.c_str());//保存文件 参数：路径
    pDoc->Print();//打印
    delete pDoc;

	_readInfos.resize(20);
    return true;
}

const char* XMLData::read(int guan)
{
    std::string filePath = CCFileUtils::sharedFileUtils()->getWritablePath() + "kingdata2.xml";   //xml文件路径
	CCLog("read filePath %s", filePath.c_str());
    tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();     //xmlDoc
    pDoc->LoadFile(filePath.c_str());
	CCLog("pDoc Loc %d", (int)pDoc);
    XMLElement *rootEle = pDoc->RootElement();      //得到跟节点
    XMLElement *dictEle = rootEle->FirstChildElement();
    XMLElement *keyEle = dictEle->FirstChildElement(); //dict下面的子节点 key
    guan = min(guan,20);
    for (int i=1;  i<=guan-1;i++)
    {
        keyEle = keyEle->NextSiblingElement();
    }
    const char* str = keyEle->GetText();
	_readInfos = str;

    pDoc->SaveFile(filePath.c_str());

    delete pDoc;
	return  _readInfos.c_str();
}

int XMLData::getScore(int guan)
{
    std::string filePath = CCFileUtils::sharedFileUtils()->getWritablePath() + "kingdata2.xml";   //xml文件路径
    tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();     //xmlDoc
    pDoc->LoadFile(filePath.c_str());
    XMLElement *rootEle = pDoc->RootElement();      //得到跟节点
    XMLElement *dictEle = rootEle->FirstChildElement();
    XMLElement *keyEle = dictEle->FirstChildElement(); //dict下面的子节点 key
    guan = min(guan,20);
    for (int i=1;  i<=guan-1;i++)
    {
        keyEle = keyEle->NextSiblingElement();
    }
    int str = keyEle->IntAttribute("score");
    pDoc->SaveFile(filePath.c_str());
    delete pDoc;
    return str;
}

int XMLData::getTimes(int guan)
{
    std::string filePath = CCFileUtils::sharedFileUtils()->getWritablePath() + "kingdata2.xml";   //xml文件路径
    tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();     //xmlDoc
    pDoc->LoadFile(filePath.c_str());
    XMLElement *rootEle = pDoc->RootElement();      //得到跟节点
    XMLElement *dictEle = rootEle->FirstChildElement();
    XMLElement *keyEle = dictEle->FirstChildElement(); //dict下面的子节点 key
    guan = min(guan,20);
    for (int i=1;  i<=guan-1;i++)
    {
        keyEle = keyEle->NextSiblingElement();
    }
    int str = keyEle->IntAttribute("times");
    pDoc->SaveFile(filePath.c_str());
    delete pDoc;
    return str;
}


void XMLData::update(int guan,int score,int times)
{
    std::string filePath = CCFileUtils::sharedFileUtils()->getWritablePath() + "kingdata2.xml";   //xml文件路径
    tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();     //xmlDoc
    pDoc->LoadFile(filePath.c_str());
    XMLElement *rootEle = pDoc->RootElement();      //得到跟节点
    XMLElement *dictEle = rootEle->FirstChildElement();
    XMLElement *keyEle = dictEle->FirstChildElement(); //dict下面的子节点 key

    for (int i=1;  i<=guan-1;i++)
    {
        keyEle = keyEle->NextSiblingElement();
    }
    keyEle->DeleteChildren();
    keyEle->SetAttribute("score", score);
    keyEle->SetAttribute("times", times);
    char newScore[50] = {0};
    sprintf(newScore, "%d",score);
    keyEle->LinkEndChild(pDoc->NewText(newScore));//给节点设置值
    pDoc->SaveFile(filePath.c_str());
}


