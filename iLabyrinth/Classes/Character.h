/*
 * Character.h
 *
 *  Created on: 2013-7-21
 *      Author: a582o_000
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "cocos2d.h"
#include "Config.h"
USING_NS_CC;
class Character :public CCSprite
{
private:
	CCPoint    _lastFramePos;
	u_int      _charFrame;
public:
	Character();
	virtual ~Character();
	bool init();
	void rotateToSide(Config::Side side);

	void rotateNode(CCNode *node ,Config::Side side);

	CCPoint gridPosition();

	u_int rotationSide();

	void walkByPath(u_int path);
	void updata();
	u_int opositeSideOfSide(u_int side);
	CCPoint lookingAtGridPosition();
	bool isBussy();
	void nextFrame();
	void reset();
	void setCharPosition(CCPoint pos);
	CREATE_FUNC(Character);
};

#endif /* CHARACTER_H_ */
