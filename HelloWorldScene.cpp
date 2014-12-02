#include "HelloWorldScene.h"

USING_NS_CC;


HelloWorld::HelloWorld()
: _displayValueLabel(nullptr)
{
    _sucessFrame=new Sucess();
}

Sucess::Sucess()
{
    auto next = MenuItemFont::create("Next ->>", CC_CALLBACK_1(Sucess::nextMenuCallback, this));
    
    auto sucessLabel = LabelBMFont::create("Correct", "futura-48.fnt");
    sucessLabel->setAnchorPoint(Vec2(0,0));
    sucessLabel->setPosition(Vec2(0, -6));
    
    auto _sucessSprite = cocos2d::Sprite::create("paddle.png");
    
    _sucessSprite->addChild(sucessLabel);
    _sucessSprite->setScale(0);
    auto s = Director::getInstance()->getWinSize();
    
    _sucessSprite->setPosition(Point(s.width/2, s.height/1.2-260));
    next->setFontSizeObj(49);
    next->setFontName("Marker Felt.ttf");
    
    auto menu = Menu::create(next, nullptr);
    addChild(menu);
    menu->alignItemsVertically();

    menu->setPosition(Vec2(s.width/2, s.height/1.2));
    this->addChild(_sucessSprite);
    
    _sucessSprite->runAction(ScaleTo::create(0.6,1.5));
}


Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer1 = HelloWorld::create();
    auto layer2 = Sucess::create();
    layer1->setSucessPtr(layer2);
    auto layer = LayerMultiplex::create(layer1, layer2, nullptr);
    scene->addChild(layer);
    return scene;
}

void Sucess::backMenuCallback(cocos2d::Ref *pSender)
{
    _questionSet->loadNewSet();
    static_cast<LayerMultiplex*>(_parent)->switchTo(0);
}

void Sucess::nextMenuCallback(cocos2d::Ref *pSender)
{
    _questionSet->loadNewSet();
    static_cast<LayerMultiplex*>(_parent)->switchTo(0);
}

/*
 This method is called when the finish button is pressed
 */
void HelloWorld::finishCallback(Ref* sender)
{
    /*
     Create an array and hold all the response into it. Comapre each of the result with the response
     if each item in the response array match the result, then it is pass else failed
     */
    
    responseData.clear();
    log("Calling from the finish callback");
    
    //going with optimistic flow
    bool complete = true;
    
    //check if two options are filled
    for(int i=0;i<2;i++)
    {
        if(resultArray.at(i)!=NULL)
        {
            if(resultArray.at(i)->getOption()!=NULL)
            {
                if(resultArray.at(i)->getOption()->getSprite()!=NULL){
                    log("%s \n",resultArray.at(i)->getOption()->getSprite()->getName().c_str());
                    CCString* str = CCString::create(resultArray.at(i)->getOption()->getSprite()->getName());
                    responseData.pushBack(str);
                }else{
                    complete=false;
                }
            }else{
                complete=false;
            }
        }else{
            complete=false;
        }
    }
    
    bool sucess = true;
    
    //If all the options are filled check if it all matches
    if(complete)
    {
        for(int i=0;i<2;i++)
        {
            log("resp = %s\n",responseData.at(i)->getCString());
            log("sucss = %s\n",sucessData.at(i)->getCString());
            if((responseData.at(i)->compare(sucessData.at(i)->getCString()))==0)
            {
                //do nothing
            }else
            {
                sucess=false;
            }
        }
    }
    
    // If sucess remove the other unused options and finish button
    // Display the sucess message.
    if(sucess && complete)
    {
        log("*****sucess*****");
        for(int i=0; i<4; i++)
        {
            if(!optArray.at(i)->isPositioned()){
                optArray.at(i)->getSprite()->runAction(ScaleTo::create(0.2,0));
            }else{
                optArray.at(i)->getSprite()->stopAllActions();
            }
                
        }
        _sucessSprite->runAction(ScaleTo::create(0.6,2));
        _finishMenu->runAction(ScaleTo::create(0.2,0));
        _completed=true;
        auto str=new std::string("NEWW");
        resetAllSprites();
        static_cast<LayerMultiplex*>(_parent)->switchTo(1);
    }
    else   //If failed remove the finish button and other unused options
    {
        for(int i=0; i<4; i++)
        {
            if(!optArray.at(i)->isPositioned()){
                optArray.at(i)->getSprite()->runAction(ScaleTo::create(0.2,0));
            }else{
                optArray.at(i)->getSprite()->stopAllActions();
            }
        }
        _failSprite->runAction(ScaleTo::create(0.3,1.5));
        _finishMenu->runAction(ScaleTo::create(0.2,0));
        log("failed");
        _completed=true;
    }
}

void HelloWorld::resetAllSprites()
{
    qnum++;
    char rt[200];
    _completed=false;
    
    _mySprite1->removeChildByName("option1");
    auto label1 = LabelBMFont::create("answer1", "futura-48.fnt");
    
    label1->setAnchorPoint(Vec2(0,0));
    label1->setPosition(Vec2(0, 0));
    
    _mySprite1->addChild(label1,0,"option1");
    _mySprite2->removeChildByName("option2");
    
    auto label2 = LabelBMFont::create("answer2", "futura-48.fnt");
    label2->setAnchorPoint(Vec2(0,0));
    label2->setPosition(Vec2(0, 0));
    
    _mySprite2->addChild(label2,0,"option2");
    
    _mySprite3->removeChildByName("option3");
    auto label3 = LabelBMFont::create("answer3", "futura-48.fnt");
    label3->setAnchorPoint(Vec2(0,0));
    label3->setPosition(Vec2(0, 0));

    _mySprite3->addChild(label3,0,"option3");
    
    _mySprite4->removeChildByName("option4");
    auto label4 = LabelBMFont::create("answer4", "futura-48.fnt");
    label4->setAnchorPoint(Vec2(0,0));
    label4->setPosition(Vec2(0, 0));

    
    _mySprite4->addChild(label4,0,"option4");

    this->removeChildByName("question");
    auto quest = LabelBMFont::create("2. A Bird in ________ is worth _______ in the bush", "futura-48.fnt");

    std::sprintf(rt,"%d A Bird in ________ is worth _______ in the bush",qnum);
    auto qnumStr = LabelBMFont::create(rt,"futura-48.fnt");

    this->addChild(qnumStr,0,"question");
    
    auto s = Director::getInstance()->getWinSize();
    qnumStr->setPosition(Vec2(s.width/2, s.height/1.2));
    _mySprite1->setPosition(Point(s.width/2-160, s.height/1.2-330));
    _mySprite2->setPosition(Point(s.width/2+180, s.height/1.2-330));
    _mySprite3->setPosition(Point(s.width/2-160, s.height/1.2-440));
    _mySprite4->setPosition(Point(s.width/2+180, s.height/1.2-440));
    for(int i=0; i<4; i++)
    {
        optArray.at(i)->setPositioned(false);
    }
    
    for(int j=0;j< 2;j++)
    {
        resultArray.at(j)->setVacant();
        resultArray.at(j)->resetOption();
    }
    _sucessSprite->setScale(0);
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{    log("starting....INITT");
    _questionSet = new QuestionSet();
    _sucessFrame->setQuestionSet(_questionSet);
    return init1();
}

bool HelloWorld::init1()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    std::string question = *_questionSet->getQuestion();
    std::string answer1 = *_questionSet->getOption1();
    std::string answer2 = *_questionSet->getOption2();
    std::string answer3 = *_questionSet->getOption3();
    std::string answer4 = *_questionSet->getOption4();
    
    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->setSwallowTouches(true);
    _touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    _touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    _touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    _touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    _completed=false;
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Puzzler", "Arial", 24);
   
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    /**** Draw Line **/
    CCDrawNode* node = CCDrawNode::create();
   
    
    this->addChild(node);
    
    // Create the button
    cocos2d::ui::Button* button = cocos2d::ui::Button::create("animationbuttonnormal.png",
                                    "animationbuttonpressed.png");
  
    button->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));

    button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::touchEvent, this));
    
    auto fromPoint = cocos2d::Point (500,0);
    auto toPoint = cocos2d::Point (500,200);
    

    
    _mySprite1 = cocos2d::Sprite::create("paddle.png");
    _mySprite2 = cocos2d::Sprite::create("paddle.png");
    _mySprite3 = cocos2d::Sprite::create("paddle.png");
    _mySprite4 = cocos2d::Sprite::create("paddle.png");

    _sucessSprite = cocos2d::Sprite::create("paddle.png");
    _failSprite = cocos2d::Sprite::create("paddle.png");
    
    Rect rect = _mySprite1->boundingBox();
    
    auto s = Director::getInstance()->getWinSize();
    
    auto layer = LayerColor::create(Color4B(128,128,128,255));
    this->addChild(layer, -10);
    
    auto label1 = LabelBMFont::create(question, "futura-48.fnt");
    auto label2 = LabelBMFont::create(answer1, "futura-48.fnt");
    auto label3 = LabelBMFont::create(answer2, "futura-48.fnt");
    auto label4 = LabelBMFont::create(answer3, "futura-48.fnt");
    auto label5 = LabelBMFont::create(answer4, "futura-48.fnt");
    
    label2->setAnchorPoint(Vec2(0,0));
    label2->setPosition(Vec2(0, -6));
    
    label3->setAnchorPoint(Vec2(0,0));
    label3->setPosition(Vec2(0, -6));
    
    label4->setAnchorPoint(Vec2(0,0));
    label4->setPosition(Vec2(0, -6));
    
    label5->setAnchorPoint(Vec2(0,0));
    label5->setPosition(Vec2(0, -6));
    
    _mySprite1->addChild(label2, 1, "option1");
    _mySprite2->addChild(label3, 1, "option2");
    _mySprite3->addChild(label4, 1, "option3");
    _mySprite4->addChild(label5, 1, "option4");
 
    auto sucessLabel = LabelBMFont::create("Correct", "futura-48.fnt");
    auto failLabel = LabelBMFont::create("Wrong", "futura-48.fnt");

    
    sucessLabel->setAnchorPoint(Vec2(0,0));
    sucessLabel->setPosition(Vec2(0, -6));
    
    
    failLabel->setAnchorPoint(Vec2(0,0));
    failLabel->setPosition(Vec2(0, -6));
    
    
    _sucessSprite->addChild(sucessLabel);
    _failSprite->addChild(failLabel);
    
    _sucessSprite->setPosition(Point(s.width/2, s.height/1.2-260));
    _sucessSprite->setScale(0);
    
    _failSprite->setPosition(Point(s.width/2, s.height/1.2-260));
    _failSprite->setScale(0);
    
    spriteArray.pushBack(_mySprite1);
    spriteArray.pushBack(_mySprite2);
    spriteArray.pushBack(_mySprite3);
    spriteArray.pushBack(_mySprite4);
    
    _option1 = new Options(_mySprite1,"_mySprite1", Point(s.width/2-160, s.height/1.2-330));
    _option2 = new Options(_mySprite2,"_mySprite2", Point(s.width/2+180, s.height/1.2-330));
    _option3 = new Options(_mySprite3,"_mySprite3", Point(s.width/2-160, s.height/1.2-440));
    _option4 = new Options(_mySprite4,"_mySprite4", Point(s.width/2+180, s.height/1.2-440));
    
    optArray.pushBack(_option1);
    optArray.pushBack(_option2);
    optArray.pushBack(_option3);
    optArray.pushBack(_option4);
    
    _result1 = new Results(Point(s.width/3.5+50, s.height/1.1));
    _result2 = new Results(Point(s.width/3.5+450, s.height/1.1));
    
    resultArray.pushBack(_result1);
    resultArray.pushBack(_result2);
    
    CCString* one = CCString::create("_mySprite1");
    CCString* two = CCString::create("_mySprite3");
    
    
    sucessData.pushBack(one);
    sucessData.pushBack(two);
    
    label1->setPosition(Vec2(s.width/2, s.height/1.2));
    
    this->addChild(_mySprite1);
    this->addChild(_mySprite2);
    this->addChild(_mySprite3);
    this->addChild(_mySprite4);
    
    this->addChild(_sucessSprite);
    this->addChild(_failSprite);
    
    this->addChild(label1, 0, "question");
    
    _displayValueLabel = Text::create("", "fonts/Marker Felt.ttf",32);
    
    _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
    _displayValueLabel->setPosition(Vec2(s.width / 3.0f, s.height / 2.0f));
    layer->addChild(_displayValueLabel);

    cocos2d::ui::ImageView* imageView = ImageView::create();
    imageView->setPosition(Vec2(s.width / 2.0f + 50+ button->getContentSize().width/2,
                                s.height / 2.0f));
    this->setTouchEnabled(true);
    
    auto finish = MenuItemFont::create("Finish", CC_CALLBACK_1(HelloWorld::finishCallback, this));
    
    auto item4 = MenuItemFont::create("I toggle enable items", [&](Ref *sender) {
        log("insite the move");
        });
    
    item4->setFontSizeObj(20);
    item4->setFontName("futura-48.fnt");
    _finishMenu = Menu::create( finish,  nullptr);
    
    addChild(_finishMenu);
    
    _finishMenu->alignItemsVertically();
    _finishMenu->setPosition(Vec2(s.width/2, s.height/2));

    return true;
}

void Results::setOption(Options* opt)
{
    _optionSet=opt;
    auto moveTo = cocos2d::MoveTo::create(0.2f, _dest );
    opt->setPositioned(true);
    _vacant=false;
    opt->getSprite()->runAction(moveTo);
    log("inside the opt not set");
}

bool HelloWorld::onTouchBegan(Touch *touch, Event * event)
{
    if(_completed){
        return false;
    }
    auto s = Director::getInstance()->getWinSize();
    
    touch->getLocationInView();
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    for (auto _mySprite: this->spriteArray)
    {
        if(_mySprite->boundingBox().containsPoint(location))
        {
            for(int i=0;i<4;i++)
            {
                if(_mySprite->getName() == optArray.at(i)->getSpriteName()){
                    auto option = optArray.at(i);
                    if(option->isPositioned())
                    {
                        option->resetPosition();
                        option->getResult()->setVacant();
                    }else
                    {
                        for(int i=0;i<2;i++){
                            auto result=resultArray.at(i);
                            if(result->vacant())
                            {
                                result->setOption(option);
                                option->setResult(result);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}

void HelloWorld::drawBoundingBox(cocos2d::Sprite *sprite)
{
    CCRect box = sprite->boundingBox();
    ccDrawRect(ccp(box.origin.x, box.origin.y),ccp(box.origin.x+box.size.width, box.origin.y+box.size.height));
}

void HelloWorld::onTouchEnded(Touch *touch, Event * event)
{
    log("insite the onTouch end");
}

void HelloWorld::onTouchCancelled(Touch *touch, Event * event)
{
    log("insite the onTouch cancelled	");
}

void HelloWorld::onTouchMoved(Touch *touch, Event * event)
{
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    for (auto _mySprite: this->spriteArray)
    {
        if(_mySprite->boundingBox().containsPoint(location))
        {
            // Don't do any thing when moved
        }
    }
}

void HelloWorld::setTouchEnabled(bool enabled)
{
    
    log("insite the onTouch set enabled ");
    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    _touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    _touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    _touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
}

void HelloWorld::hello(Ref* sender) 
{
    log("TOUCHES DISABLED FOR 5 SECONDS");
}

void HelloWorld::touchEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
    switch (type)
    {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:
            break;
            
        case cocos2d::ui::Widget::TouchEventType::MOVED:
            break;
            
        case cocos2d::ui::Widget::TouchEventType::ENDED:
        {
            
            if (_displayValueLabel->getString() == "Hand") {
                _displayValueLabel->setString("Band");
            }
            else{
                _displayValueLabel->setString("Hand");
            }
        }
            break;
            
        case cocos2d::ui::Widget::TouchEventType::CANCELED:
            _displayValueLabel->setString(String::createWithFormat("Touch Cancelled")->getCString());
            break;
            
        default:
            break;
    }
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
