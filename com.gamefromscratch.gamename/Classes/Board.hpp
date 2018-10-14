//
//  Board.hpp
//  com.gamefromscratch.gamename
//
//  Created by Alexis Brunet on 2018-09-12.
//

#ifndef Board_hpp
#define Board_hpp

#include "Card.hpp"

#include "cocos2d.h"

class Board
{
public:
    Board(int rows, int columns, cocos2d::Node *scene);
    Board(const Board &) = delete;

    void addToScene(cocos2d::Node *parent);
    void flipped(const std::string imageFileName);

private:
    void checkWinningCondition() const;

    std::vector<std::unique_ptr<Card>> m_cards;
    int m_columns;
    std::string m_currentlyFlipped;
    cocos2d::Node *m_scene;
};


#endif /* Board_hpp */
