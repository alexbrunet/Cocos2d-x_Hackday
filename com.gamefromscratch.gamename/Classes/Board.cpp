//
//  Board.cpp
//  com.gamefromscratch.gamename
//
//  Created by Alexis Brunet on 2018-09-12.
//

#include "Board.hpp"

#include <algorithm>
#include <random>
#include <iostream>

USING_NS_CC;

static const float PADDING = 10.0f;

Board::Board(int columns, int rows, Node *scene)
: m_columns(columns)
, m_scene(scene)
{
    std::vector<std::string> images = { "eggplant.png", "lol.png", "poo.png", "pogchamp.png", "bush.png", "marc.png", "what.png" };

    int cardCount = (columns * rows) / 2;
    for (int i=0; i<cardCount; ++i)
    {
        int imageIdx = i % images.size();

        m_cards.emplace_back(std::move(new Card(images[imageIdx], "HelloWorld.png", this)));
        m_cards.emplace_back(std::move(new Card(images[imageIdx], "HelloWorld.png", this)));
        //m_cards.emplace_back(images[imageIdx], "HelloWorld.png");
    }

    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(m_cards), std::end(m_cards),rng);
}

void Board::addToScene(cocos2d::Node *parent)
{
    auto sprite = Sprite::create("HelloWorld.png");
    auto cardSize = sprite->getContentSize();
    auto screenSize = Director::getInstance()->getVisibleSize();

    const float left = cardSize.width;
    const float top = cardSize.height / 2;

    const float paddingLeft = (screenSize.width - (m_columns * (cardSize.width + PADDING) - PADDING)) / 2;
    const float paddingTop = (screenSize.height - ((m_cards.size() / m_columns) * (cardSize.height + PADDING) - PADDING)) / 2;

    int col = 0;
    int row = 0;

    for (auto &card : m_cards)
    {
        float cardLeft = left + paddingLeft + (col * (cardSize.width + PADDING));
        float cardTop = top + paddingTop + (row * (cardSize.height + PADDING));
        //card->setPosition(Vec2(((col * cardSize.width) + (cardSize.width)), ((row * cardSize.height) + (cardSize.height / 2))));
        card->setPosition(Vec2(cardLeft, cardTop));
        card->addToScene(parent);

        row = row + (++col / m_columns);
        col = col % m_columns;
    }
}

void Board::flipped(const std::string imageFileName)
{
    if (m_currentlyFlipped.empty())
    {
        m_currentlyFlipped = imageFileName;
    }
    else if (m_currentlyFlipped == imageFileName)
    {
        bool won = true;
        for (auto &card : m_cards)
        {
            card->setPaired(true);
            won &= card->isPaired();
        }
        m_currentlyFlipped = "";

        if (won)
        {
            // display winning message
            if (m_scene)
            {
                auto label = Label::createWithSystemFont("YOU WIN!", "Arial", 72);

                label->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2));
                m_scene->addChild(label, 100);
            }
        }
    }
    else
    {
        for (auto &card : m_cards)
        {
            if (!card->isPaired())
            {
                card->flipBack();
            }
        }

        m_currentlyFlipped = "";
    }
}
