//
//  TouchScene.h
//  com.gamefromscratch.gamename
//
//  Created by Alexis Brunet on 2018-09-12.
//

#ifndef TouchScene_h
#define TouchScene_h

#include "Board.hpp"

#include "cocos2d.h"

class TouchScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene *createScene();
    virtual bool init();

    CREATE_FUNC(TouchScene);

private:
    std::unique_ptr<Board> m_board;
};

#endif /* TouchScene_h */
