//
//  TouchScene.cpp
//  com.gamefromscratch.gamename-mobile
//
//  Created by Alexis Brunet on 2018-09-12.
//

#include "TouchScene.h"

#include "Card.hpp"

#include <memory>

USING_NS_CC;

Scene* TouchScene::createScene()
{
    auto scene = Scene::create();
    auto layer = TouchScene::create();
    scene->addChild(layer);

    return scene;
}

bool TouchScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto sprite = Sprite::create("HelloWorld.png");
    auto front = Sprite::create("eggplant.png");
    sprite->setPosition(Vec2(Director::getInstance()->getVisibleSize().width /2,
                             Director::getInstance()->getVisibleSize().height /2));

    front->setContentSize(cocos2d::Size(sprite->getContentSize().width, front->getContentSize().height * (
                               sprite->getContentSize().width / front->getContentSize().width
                                                                                                          )));
    front->setPosition(sprite->getPosition());
    front->setRotation3D(Vec3(0, -90, 0));
    front->setVisible(false);

    // Add a "touch" event listener to our sprite
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [front](Touch *touch, Event *event) -> bool {
        auto bounds = event->getCurrentTarget()->getBoundingBox();

        if (bounds.containsPoint(touch->getLocation()))
        {
            std::stringstream touchDetails;
            touchDetails << "Touched at OpenGL coordinates: " <<
            touch->getLocation().x << "," << touch->getLocation().y << std::endl <<
            "Touched at UI coordinate: " << touch->getLocationInView().x << "," << touch->getLocationInView().y << std::endl <<
            "Touched at local coordinate: " << event->getCurrentTarget()->convertToNodeSpace(touch->getLocation()).x << "," <<
            event->getCurrentTarget()->convertToNodeSpace(touch->getLocation()).y << std::endl <<
            "Touch moved by: " << touch->getDelta().x << "," << touch->getDelta().y;

//            MessageBox(touchDetails.str().c_str(), "Touched!");
//            auto action = cocos2d::RotateBy::create(1, Vec3(0,180,0));
//            event->getCurrentTarget()->runAction(action);

            event->getCurrentTarget()->runAction(Sequence::create(
                                                                  RotateBy::create(0.25, Vec3(0,90,0)),
                                                                  Hide::create(),
                                                                  CallFunc::create([front](){
                front->runAction(Sequence::create(Show::create(), RotateBy::create(0.25, Vec3(0,90,0)), NULL));
            }),
            NULL));

        }

        return true;
    };

    auto reverseFlipper = EventListenerTouchOneByOne::create();
    reverseFlipper->onTouchBegan = [sprite](Touch *touch, Event *event) -> bool {
        auto bounds = event->getCurrentTarget()->getBoundingBox();

        if (bounds.containsPoint(touch->getLocation()))
        {
            event->getCurrentTarget()->runAction(Sequence::create(RotateBy::create(0.25, Vec3(0, -90, 0)),
                                                                  Hide::create(),
                                                                  CallFunc::create([sprite]() {
                sprite->runAction(Sequence::create(Show::create(), RotateBy::create(0.25, Vec3(0, -90, 0)), NULL));
            }), NULL));
        }

        return true;
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, sprite);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(reverseFlipper, front);
//    this->addChild(sprite, 0);
//    this->addChild(front, 1);

    m_board = std::unique_ptr<Board>(new Board(6, 4, this));
    m_board->addToScene(this);

    return true;
}
