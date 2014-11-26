#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

class Results;

class Options : public cocos2d::Layer
{
private:
    cocos2d::Sprite* _sprite;
    bool _positioned;
    cocos2d::Point _original;
    Results* _result;
    Options();
public:
    
    Options(cocos2d::Sprite* sprite, const std::string& name, cocos2d::Point original){
        _sprite=sprite;
        _positioned=false;
        _original=original;
        _sprite->setPosition(_original);
        _sprite->setName(name);
    };
    
    cocos2d::Sprite* getSprite(){
        return  _sprite;
    };
 
    void setResult(Results* res)
    {
        _result=res;
    };
    
    Results* getResult()
    {
        return _result;
    };
    
    std::string getSpriteName(){
        return _sprite->getName();
    };
    
    void resetPosition()
    {
        auto moveTo = cocos2d::MoveTo::create(0.2f, _original);
        _sprite->runAction(moveTo);
        _positioned = false;
      
    };
    
    bool isPositioned()
    {
        return _positioned;
    };
    
    void setPositioned(bool pos)
    {
        _positioned=pos;
    };
    
    void reset1Position()
    {
        _positioned=false;
    }
    
    cocos2d::Point getOriginalPos(){
        return _original;
    };
};

/* This class holds the structure for class and has enablers to set the questions
 And it's quite normal.Im sleepy and I dono what I'm writing.	
 */

class QuestionSet
{
private:
    std::string* _question;
    std::string* _option1;
    std::string* _option2;
    std::string* _option3;
    std::string* _option4;
    int num=0;
public:
    std::string* getQuestion(){
        return _question;
    }
    std::string* getOption1(){
        return _option1;
    }
    std::string* getOption2(){
        return _option2;
    }
    std::string* getOption3(){
        return _option3;
    }
    std::string* getOption4(){
        return _option4;
    }
    
    void setOption1(std::string* opt){
        _option1 =opt;
    }
    
    void setOption2(std::string* opt){
        _option2 =opt;
    }
    
    void setOption3(std::string* opt){
        _option3 =opt;
    }
    
    void setOption4(std::string* opt){
        _option4 =opt;
    }
    
    QuestionSet(){
        _question = new std::string("A Bird in ________ is worth _______ in the bush");
        _option1 = new std::string("Hand");
        _option2 = new std::string("Band");
        _option3 = new std::string("Two");
        _option4 = new std::string("Three");
    }

    void loadNewSet(){
        
    }
};

class Results : public cocos2d::Layer
{
private:
    Options* _optionSet;
    cocos2d::Point _dest;
    bool _vacant;
public:
    Results(cocos2d::Point point)
    {
        _dest=point;
        _vacant=true;
    };
    
    void resetOption()
    {
        _optionSet=NULL;
    }
    
    cocos2d::Point getDest()
    {
        return _dest;
    };
    
    bool vacant()
    {
        return _vacant;
    };
    
    void setVacant()
    {
        _vacant=true;
    };
    
    void setOption(Options* opt);
    
    Options* getOption()
    {
     return _optionSet;
    };

};

/* This class is called after the puzzle is solved sucessfully
 The method setQuestionSet immediately loads the next question
 */
class Sucess : public cocos2d::Layer
{
private:
    QuestionSet* _questionSet;
public:
    CREATE_FUNC(Sucess);
    
    Sucess();
    
    void setQuestionSet(QuestionSet* quest){
        _questionSet=quest;
        _questionSet->loadNewSet();
    }
    
    void backMenuCallback(Ref *pSender);
    
    void nextMenuCallback(Ref *pSender);
};


class HelloWorld : public cocos2d::Layer
{
private:
    int qnum=1;

    QuestionSet* _questionSet;
    cocos2d::MenuItem*    _ItemToMove;
    cocos2d::Vector<cocos2d::Sprite *> spriteArray;
    cocos2d::Vector<Options *> optArray;
    cocos2d::Vector<Results *> resultArray;
    
    Sucess* _sucessFrame;
    
    cocos2d::Vector<cocos2d::CCString *> sucessData;
    cocos2d::Vector<cocos2d::CCString *> responseData;
    
    Options* _option1;
    Options* _option2;
    Options* _option3;
    Options* _option4;
    
    Results* _result1;
    Results* _result2;
    
    cocos2d::Sprite* _mySprite1;
    cocos2d::Sprite* _mySprite2;
    cocos2d::Sprite* _mySprite3;
    cocos2d::Sprite* _mySprite4;
    
    cocos2d::Sprite* _sucessSprite;
    cocos2d::Sprite* _failSprite;
    bool _completed;
    cocos2d::Menu* _finishMenu;
    
    cocos2d::Sprite* _finishSprite;
    
    cocos2d::EventListenerTouchOneByOne* _touchListener;
    void resetAllSprites();
    
public:
    HelloWorld();
    static cocos2d::Scene* createScene();
    virtual bool init();
    void setSucessPtr(Sucess* sucess){
        _sucessFrame=sucess;
    }
    
    void hello(Ref* sender) ;
    void menuCloseCallback(cocos2d::Ref* pSender);
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event * event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);
    void drawBoundingBox(cocos2d::Sprite* sprite);
    void finishCallback(Ref* sender);
    bool init1();
    void setTouchEnabled(bool enabled);
    void touchEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
   
    CREATE_FUNC(HelloWorld);
    Text* _displayValueLabel;
};

#endif // __HELLOWORLD_SCENE_H__
