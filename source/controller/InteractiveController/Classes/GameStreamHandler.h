//
//  ConnectedHandler.hpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#ifndef GameStream_hpp
#define GameStream_hpp

#include "AbstractHandlers.h"
#include "Controller.h"
#include "GameStream.pb.h"
#include "HandlerMap.h"
#include "Timer.cpp"
#include "Player.h"

#include <map>

class ControlScene;

#define BONUS_COUNTDOWN "bonusCountdown"
#define SCHEDULE_NETWORKING "receiveBoxesInBonusMode"
#define NODE_FORCE "nodeForce"
#define STADIUM_LOADBAR_OFFSET 150
#define FORCEBAR_OPACITY 123

/**
 * Processing GameStream rendering
 * this class also controls all the networking while
 * the invisibility bonus is active
 */
class GameStreamHandler: public BoxHandler{
public:

    GameStreamHandler(ControlScene * scene);
    
    /**
     * render game - update via information
     * provided in the box
     */
    virtual bool execute( GameNet::Box * box );
    
private:
    
    Director * director;
    Controller * controller;
    StadiumScene * stadium;
    ControlScene * controlScene;
    
    /**
     * pitch size received from server
     */
    cocos2d::Size pitchSize;
    
    /**
     * id of this phone received in initial game stream
     */
    unsigned long myId;
    
    /**
     * "stopwatch" instance
     * used to compute kick force
     */
    Util::Timer timer;
    
    /**
     * map of event handlers interacting with stadium scene
     */
    HandlerMap * handlerMap;
    
    /**
     * active players
     */
    std::map<unsigned long, Player*> playerMap;
    
    /**
     * refresh flags
     * if the player was refreshed during game stream update
     * set to true, otherwise it will remain false and it indicates
     * that the player is already not in the game
     */
    std::map<unsigned long, bool> playerRefreshed;
    
    /**
     * similar as Players
     */
    std::map<int, Sprite*> bonusMap;
    std::map<int, bool> bonusRefreshed;
    
    /**
     * score was at least once set, so we can
     * animate gooooaaal
     */
    bool scoreSet;

    /**
     * toggle if bonus is active
     * true - initialize stadium scene, networking and other stuff
     * false - back to the Control scene
     */
    void updateActive(PBGameStream stream);
    
    /**
     * update game score
     */
    void updateScore( StadiumScene::Side side, int score );
    
    /**
     * update ball parameters
     */
    void updateBall(PBBall ballState);
    
    /**
     * update players sprites
     */
    void updatePlayers( PBGameStream stream );
    
    /**
     * update bonuses
     */
    void updateBonuses( PBGameStream stream );
    
    /**
     * schedules box receiving directly to cocos2d::Director
     * because ControlScene won't be active and StadiumScene
     * does not use handlers (due compatibility with server)
     */
    void startNetworking();
    
    /**
     * unschedule box receiving
     */
    void stopNetworking();
    
    /**
     * load stadium and bind control elements
     */
    void prepareStadium(cocos2d::Size pitchSize);
    
    /**
     * kick touch began
     * start "loading" kick force
     */
    bool onTouchBegan(Touch * touch, Event * event);
    
    /**
     * finger moved during "loading" kick force
     * move the loading sprite
     */
    bool onTouchMoved(Touch * touch, Event * event);
    
    /**
     * touch ended
     * kick the ball! :)
     */
    bool onTouchEnded(Touch * touch, Event * event);
    
    /**
     * animation counting down the last seconds of the bonus
     * effect
     */
    void secondsLeftAnimation(int seconds);
    
};

#endif /* GameStream_h */
