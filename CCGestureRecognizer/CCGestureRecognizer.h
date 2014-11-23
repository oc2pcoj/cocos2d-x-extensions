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

#ifndef CCGestureRecognizer_h
#define CCGestureRecognizer_h

#include "cocos2d.h"
#include <chrono>

class CCGesture;

typedef void (cocos2d::Object::*SEL_CallFuncGR)(CCGesture*);
#define callfuncGR_selector(_SELECTOR) static_cast<SEL_CallFuncGR>(&_SELECTOR)


class CCGesture : public cocos2d::Ref
{
public:
    bool init() {return true;}
    CREATE_FUNC(CCGesture);
    cocos2d::Point location;
    // cancelPropagation allows the dynamic canceling of event propagation
    // default value is set to the cancelsTouchesInView value
    bool cancelPropagation;
};

class CCGestureRecognizer : public cocos2d::Layer
{
public:
    CCGestureRecognizer();
    ~CCGestureRecognizer();
    void setTarget(cocos2d::Ref * tar, SEL_CallFuncGR sel);
    void setTarget(const std::function<void(CCGesture*)> &callback);
    void setTargetForBegan(cocos2d::Ref * tar, SEL_CallFuncGR sel);
    void setTargetForBegan(const std::function<void(CCGesture*)> &callback);
    void setTargetForEnded(cocos2d::Ref * tar, SEL_CallFuncGR sel);
    void setTargetForEnded(const std::function<void(CCGesture*)> &callback);
    
    //setParent is called after the layer is added as a child
    virtual void setParent(cocos2d::Node*p);
protected:
    cocos2d::Rect frame;
    bool isRecognizing;
    
    void gestureBegan(CCGesture * gesture);
    void gestureRecognized(CCGesture * gesture);
    void gestureEnded(CCGesture * gesture);
    void stopTouchesPropagation(cocos2d::Event * pEvent);
    
    //utility methods
    bool isPositionBetweenBounds(cocos2d::Point pos);
    float distanceBetweenPoints(cocos2d::Point p1, cocos2d::Point p2);
    
    std::chrono::high_resolution_clock::time_point getCurrentTime() { return std::chrono::high_resolution_clock::now(); }
    
    double getTimeDifference(std::chrono::high_resolution_clock::time_point endTime, std::chrono::high_resolution_clock::time_point startTime) {
        std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime);
        return time_span.count();
    }
    //if gesture is correctly recognized, cancel touch over other views (default: false)
    //NOTE: subclasses must check the value and implement it correctly
    CC_SYNTHESIZE(bool, cancelsTouchesInView, CancelsTouchesInView);
private:
    SEL_CallFuncGR selector, selectorForBegan, selectorForEnded;
    cocos2d::Ref * target, * targetForBegan, * targetForEnded;
    std::function<void(CCGesture*)> callback, callbackForBegan, callbackForEnded;
    cocos2d::EventDispatcher * dispatcher;
};

#endif