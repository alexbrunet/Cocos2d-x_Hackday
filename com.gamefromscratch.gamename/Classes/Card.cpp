//
//  Card.cpp
//  com.gamefromscratch.gamename
//
//  Created by Alexis Brunet on 2018-09-12.
//

#include "Card.hpp"

#include "Board.hpp"

USING_NS_CC;

Card::Card(const std::string &front, const std::string &back, Board *board)
: m_isPaired(false)
, m_isFlipped(false)
, m_board(board)
, m_frontImageName(front)
{
    m_back = Sprite::create(back);
    m_back->retain();
    m_front = Sprite::create(front);
    m_front->retain();
//    m_back->setPosition(Vec2(Director::getInstance()->getVisibleSize().width /2,
//                             Director::getInstance()->getVisibleSize().height /2));

    m_front->setContentSize(cocos2d::Size(m_back->getContentSize().width,
                                          m_front->getContentSize().height * (m_back->getContentSize().width / m_front->getContentSize().width                                                                                    )));
    //m_front->setPosition(m_back->getPosition());
    m_front->setRotation3D(Vec3(0, -90, 0));
    m_front->setVisible(false);

    // Add a "touch" event listener to our sprite
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [this](Touch *touch, Event *event) -> bool {
        auto bounds = event->getCurrentTarget()->getBoundingBox();

        auto front = m_front;
        auto self = this;
        if (bounds.containsPoint(touch->getLocation()) && !m_isPaired)
        {
            event->getCurrentTarget()->runAction(Sequence::create(
                                                                  RotateBy::create(0.25, Vec3(0,90,0)),
                                                                  Hide::create(),
                                                                  CallFunc::create([front, self]()
            {
                front->runAction(Sequence::create(Show::create(), RotateBy::create(0.25, Vec3(0,90,0)),
                                                  CallFunc::create([self]() {
                    self->m_board->flipped(self->m_frontImageName);
                }),
                                                  NULL));
            }),
                                                                  NULL));
            m_isFlipped = true;
//            m_board->flipped(m_frontImageName);
        }

        return true;
    };

    auto reverseFlipper = EventListenerTouchOneByOne::create();
    reverseFlipper->onTouchBegan = [this](Touch *touch, Event *event) -> bool {
        auto bounds = event->getCurrentTarget()->getBoundingBox();

        if (bounds.containsPoint(touch->getLocation()) && !m_isPaired)
        {
            auto sprite = m_back;
            event->getCurrentTarget()->runAction(Sequence::create(RotateBy::create(0.25, Vec3(0, -90, 0)),
                                                                  Hide::create(),
                                                                  CallFunc::create([sprite]() {
                sprite->runAction(Sequence::create(Show::create(), RotateBy::create(0.25, Vec3(0, -90, 0)),
                                                   NULL));
            }), NULL));
            m_isFlipped = false;
        }

        return true;
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, m_back);
    //Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(reverseFlipper, m_front);
}

void Card::setPosition(Vec2 position)
{
    m_front->setPosition(position);
    m_back->setPosition(position);
}

void Card::addToScene(Node *parent)
{
    parent->addChild(m_front);
    parent->addChild(m_back);
}

void Card::setPaired(bool paired)
{
    if (!m_isFlipped)
    {
        return;
    }

    if (!m_isPaired)
    {
        m_isPaired = paired;
    }
}

bool Card::isPaired() const
{
    return m_isPaired;
}

void Card::flipBack()
{
    if (!m_isPaired && m_isFlipped)
    {
        auto sprite = m_back;
        m_front->runAction(Sequence::create(RotateBy::create(0.25, Vec3(0, -90, 0)),
                                                              Hide::create(),
                                                              CallFunc::create([sprite]() {
            sprite->runAction(Sequence::create(Show::create(), RotateBy::create(0.25, Vec3(0, -90, 0)), NULL));
        }), NULL));
        m_isFlipped = false;
    }
}
