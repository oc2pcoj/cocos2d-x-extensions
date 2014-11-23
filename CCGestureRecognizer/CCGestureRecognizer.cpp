/****************************************************************************
Copyright (c) 2013 Artavazd Barseghyan

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

#include "CCGestureRecognizer.h"

USING_NS_CC;

CCGestureRecognizer::CCGestureRecognizer()
{
    isRecognizing = false;
    
    dispatcher = Director::getInstance()->getEventDispatcher();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(CCGestureRecognizer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(CCGestureRecognizer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(CCGestureRecognizer::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    setCancelsTouchesInView(false);
}

CCGestureRecognizer::~CCGestureRecognizer()
{
    
}

void CCGestureRecognizer::setTarget(Ref * tar, SEL_CallFuncGR sel)
{
    target = tar;
    selector = sel;
}

void CCGestureRecognizer::setTarget(const std::function<void(CCGesture *)> &callback)
{
    this->callback = callback;
}

void CCGestureRecognizer::setTargetForBegan(Ref * tar, SEL_CallFuncGR sel)
{
    targetForBegan = tar;
    selectorForBegan = sel;
}

void CCGestureRecognizer::setTargetForBegan(const std::function<void(CCGesture *)> &callback)
{
    this->callbackForBegan = callback;
}

void CCGestureRecognizer::setTargetForEnded(Ref * tar, SEL_CallFuncGR sel)
{
    targetForEnded = tar;
    selectorForEnded = sel;
}

void CCGestureRecognizer::setTargetForEnded(const std::function<void(CCGesture *)> &callback)
{
    this->callbackForEnded = callback;
}

float CCGestureRecognizer::distanceBetweenPoints(Point p1, Point p2)
{
    return p2.getDistance(p1);
}


void CCGestureRecognizer::stopTouchesPropagation(Event * pEvent)
{
    pEvent->stopPropagation();
}

void CCGestureRecognizer::setParent(Node*p)
{
    Layer::setParent(p);
    
    if (p!=NULL) {
        Size size = p->getContentSize();
        setContentSize(size);
        setPosition(p->getPosition());
        frame = Rect(0, 0, size.width, size.height);
        CCLOG("x pos is %f y pos is %f, w %f and h %f", frame.origin.x, frame.origin.y, frame.size.width, frame.size.height);
    }
}

bool CCGestureRecognizer::isPositionBetweenBounds(Point pos)
{
    return frame.containsPoint(pos);
}

void CCGestureRecognizer::gestureRecognized(CCGesture * gesture)
{
    CCLOG ("RECONGNIZED");
    if (callback) callback(gesture);
    else if (target && selector) (target->*selector)(gesture); //call selector
}

void CCGestureRecognizer::gestureBegan(CCGesture * gesture)
{
    if (callbackForBegan) callbackForBegan(gesture);
    else if (targetForBegan && selectorForBegan) (targetForBegan->*selectorForBegan)(gesture); //call selector
}

void CCGestureRecognizer::gestureEnded(CCGesture * gesture)
{
    if (callbackForEnded) callbackForEnded(gesture);
    else if (targetForEnded && selectorForEnded) (targetForEnded->*selectorForEnded)(gesture); //call selector
}