cocos2d-x-extensions
====================

Here is my repository for cocos2d-x extensions.

Usage samples are here https://github.com/spalx/cocos2d-x-extensions/wiki/CCGestureRecognizer

Here is working example of CCSwipeGestureRecognizer

CCSwipeGestureRecognizer * swipe = CCSwipeGestureRecognizer::create();
swipe->setTarget(this, callfuncGR_selector(MyScene::didSwipe));
swipe->setDirection(kSwipeGestureRecognizerDirectionRight | kSwipeGestureRecognizerDirectionLeft);
swipe->setCancelsTouchesInView(true);
this->addChild(swipe);

void MyScene::didSwipe(CCGesture* swipe) {
}


and for LongPressGestureRecognizer

CCLongPressGestureRecognizer * press = CCLongPressGestureRecognizer::create();
press->setTarget(this, callfuncGR_selector(MyObject::didLongTap));
press->setMinimumPressDuration(0.6);
press->setCancelsTouchesInView(true);
this->addChild(press);


void MyObject::didLongTap(CCGesture* tap) {
}
