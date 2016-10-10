#include "GreyNode.h"

USING_NS_CC;


const std::string GREY_FSH = "#ifdef GL_ES  \n\
							 precision lowp float;  \n\
							 #endif  \n\
							 varying vec4 v_fragmentColor; \n\
							 varying vec2 v_texCoord; \n\
							 uniform sampler2D my_Texture0; \n\
							 uniform sampler2D my_Texture1;   \n\
							 void main() { \n\
							 	vec4 color = texture2D(my_Texture1, v_texCoord); \n\
									float grey = dot(color.rgb, vec3(0.3, 0.6, 0.1)); \n\
										gl_FragColor = vec4(grey, grey, grey, color.a); \n\
										}";

const std::string GREY_VSH = "attribute vec4 my_position; \n\
							 attribute vec2 my_texCoord; \n\
							 \n\
							 #ifdef GL_ES   \n\
							 varying mediump vec2 v_texCoord; \n\
							 #else  \n\
							 varying vec2 v_texCoord; \n\
							 #endif  \n\
							 void main() { \n\
							 	gl_Position = CC_MVPMatrix * my_position; \n\
									v_texCoord = my_texCoord; \n\
									} ";

bool GreyNode::init(const std::string& filename)
{
	if (!CCSprite::init())
		return false;

	CCGLProgram* gl = new CCGLProgram();
	gl->initWithVertexShaderByteArray(GREY_VSH.c_str(), GREY_FSH.c_str());
	this->setShaderProgram(gl);

	_texture = CCTextureCache::sharedTextureCache()->addImage(filename.c_str());
	_texture->retain();
	setContentSize(_texture->getContentSize());

	gl->addAttribute("my_position", 0);
	gl->addAttribute("my_texCoord", 1);

	CHECK_GL_ERROR_DEBUG();

	gl->link();

	posLoc=glGetAttribLocation(gl->getProgram(), "my_position");
	coordLoc = glGetAttribLocation(gl->getProgram(), "my_texCoord");
	textureLoc = glGetUniformLocation(gl->getProgram(), "my_Texture1");
	getShaderProgram()->updateUniforms();
	
	
	gl->release();

	CHECK_GL_ERROR_DEBUG();

	return true;
}

GreyNode* GreyNode::create(const std::string& filename)
{
	GreyNode* node = new GreyNode();
	if (node&&node->init(filename))
	{
		node->autorelease();
		return node;
	}
	CC_SAFE_DELETE(node);
	return node;
}

void GreyNode::draw()
{
	getShaderProgram()->use();
	
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);

	getShaderProgram()->setUniformsForBuiltins();

	CCSize content = getContentSize();
	float width = content.width;
	float height = content.height;

	GLfloat verts[] = {
		0.0, 0.0,0.0,1.0,
		width, 0.0,0.0,1.0,
		width, height,0.0,1.0,
		0.0, height,0.0,1.0
	};
	GLfloat coord[] = {
		0.0, 1.0,
		1.0, 1.0,
		1.0, 0.0,
		0.0, 0.0
	};

	glVertexAttribPointer(posLoc, 4, GL_FLOAT, false, 0, verts);
	glVertexAttribPointer(coordLoc, 2, GL_FLOAT, false, 0, coord);
	
	glUniform1i(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, _texture->getName());
	
	
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}




void GreyNode::onExit()
{
	_texture->release();
	CCNode::onExit();
}