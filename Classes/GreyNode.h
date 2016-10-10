#ifndef  __GREYNODE_H__
#define  __GREYNODE_H__

#include "cocos2d.h"

class GreyNode :public cocos2d::CCSprite
{
public:
	bool init(const std::string& filename);
	static GreyNode* create(const std::string& filename);
	void onExit();
	void draw();
private:
	cocos2d::CCTexture2D* _texture;
	GLuint   posLoc;
	GLuint   coordLoc;
	GLuint   textureLoc;
};


#endif
