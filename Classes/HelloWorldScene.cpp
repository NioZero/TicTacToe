/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	if (!Scene::init())
	{
		return false;
	}

	_turn = 1;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_originX = visibleSize.width / 2 - (_spriteSize * 1.5 + _spriteMargin * 3);
	_originY = visibleSize.height / 2 - (_spriteSize * 1.5 + _spriteMargin * 3);

	auto _bgColor = LayerColor::create(Color4B(0xFF, 0xFF, 0xFF, 0xFF));
	this->addChild(_bgColor, -10);

	#ifdef _DEBUG
	auto square = DrawNode::create();
	square->drawRect(Point(_originX, _originY), Point(_originX + _spriteSize * 3 + _spriteMargin * 6, _originY + _spriteSize * 3 + _spriteMargin * 6), Color4F::BLUE);
	this->addChild(square);
	#endif

	auto verticalLine1 = DrawNode::create();
	verticalLine1->drawLine(Point(_originX + _spriteSize + _spriteMargin * 2, _originY), Point(_originX + _spriteSize + _spriteMargin * 2, _originY + _spriteMargin * 6 + _spriteSize * 3), Color4F::RED);
	verticalLine1->setLineWidth(4.0f);
	this->addChild(verticalLine1);

	auto verticalLine2 = DrawNode::create();
	verticalLine2->drawLine(Point(_originX + _spriteSize * 2 + _spriteMargin * 4, _originY), Point(_originX + _spriteSize * 2 + _spriteMargin * 4, _originY + _spriteMargin * 6 + _spriteSize * 3), Color4F::RED);
	verticalLine2->setLineWidth(4.0f);
	this->addChild(verticalLine2);

	auto horizontalLine1 = DrawNode::create();
	horizontalLine1->drawLine(Point(_originX, _originY + _spriteSize + _spriteMargin * 2), Point(_originX + _spriteMargin * 6 + _spriteSize * 3, _originY + _spriteSize + _spriteMargin * 2), Color4F::RED);
	horizontalLine1->setLineWidth(4.0f);
	this->addChild(horizontalLine1);

	auto horizontalLine2 = DrawNode::create();
	horizontalLine2->drawLine(Point(_originX, _originY + _spriteSize * 2 + _spriteMargin * 4), Point(_originX + _spriteMargin * 6 + _spriteSize * 3, _originY + _spriteSize * 2 + _spriteMargin * 4), Color4F::RED);
	horizontalLine2->setLineWidth(4.0f);
	this->addChild(horizontalLine2);

	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	cocos2d::log("touch began");
	return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	_turn++;

	int turn = _turn % 2;

	auto sprite = turn == 1 ? Sprite::create("o_64.png") : Sprite::create("x_64.png");



	sprite->setPosition(touch->getLocation());

	this->addChild(sprite, _turn);

	cocos2d::log("touch ended");
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
	cocos2d::log("touch moved");
}

void HelloWorld::onTouchCancelled(Touch* touch, Event* event)
{
	cocos2d::log("touch cancelled");
}
