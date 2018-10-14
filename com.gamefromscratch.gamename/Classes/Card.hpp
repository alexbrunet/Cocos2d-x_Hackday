//
//  Card.hpp
//  com.gamefromscratch.gamename
//
//  Created by Alexis Brunet on 2018-09-12.
//

#ifndef Card_hpp
#define Card_hpp

#include "cocos2d.h"

class Board;

class Card
{
public:
    Card(const std::string &front, const std::string &back, Board *board);
    Card(const Card &) = delete;

    void setPosition(cocos2d::Vec2 position);
    void setPaired(bool paired);
    bool isPaired() const;
    void flipBack();

    void addToScene(cocos2d::Node *parent);

private:

    cocos2d::Sprite *m_front;
    cocos2d::Sprite *m_back;

    bool m_isPaired;
    bool m_isFlipped;

    Board *m_board;
    std::string m_frontImageName;
};

#endif /* Card_hpp */
