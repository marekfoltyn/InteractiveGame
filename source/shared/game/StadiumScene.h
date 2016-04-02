#ifndef __STADIUM_SCENE_H__
#define __STADIUM_SCENE_H__

#include <string>

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "AbstractHandlers.h"


USING_NS_CC;
USING_NS_CC_EXT;

/**
 * Football pitch representation
 * used in both Game and Controller
 * provides common methods for accessing the pitch
 */
class StadiumScene : public Layer
{
public:
    
    /**
     * tag for accessing the scene layer
     */
    static const int SCENE_TAG = 1;
    
    /**
     * cocos2dx
     * used for scene replacement with director
     */
    static Scene * createScene();

    /**
     * internal cocos2dx method
     */
    virtual bool init();

    /**
     * internal cocos2dx method
     */
    CREATE_FUNC(StadiumScene);
    
    ///////////////////////// custom methods /////////////////////////
    
    /**
     * team sides
     */
    typedef int Side;
    static const Side SIDE_LEFT = 0;
    static const Side SIDE_RIGHT = 1;
    
    /**
     * ball state tags
     */
    enum
    {
        BALL_NORMAL,
        BALL_NON_KICKABLE
    };
    
    /**
     * load graphics and render according to size
     * 
     * Controller pitch size is based on size
     * provided by the Game.
     *
     * initPitch() must be called before any of methods below are used!
     */
    void initPitch( Vec2 origin, cocos2d::Size size );
    
    /**
     * toggle labels opacity (better when playing)
     */
    void setMatchMode(bool match, bool animate=true);
    
    /**
     * when an object has this bitmask, when collided with something
     * the handler will be called. The object with this bitmask will
     * be the first argument and the collided object will be the second
     * argument.
     */
    void addCollisionHandler(int bitmask, CollisionHandler * handler);
    
    /**
     * set admin label text
     */
    void setAdminName(std::string name);
    
    /**
     * set server label text
     */
    void setServerName(std::string name);
    
    /**
     * reset score labels (both sides)
     */
    void resetScore();
    
    /**
     * add a score point
     * @param side LEFT or RIGHT
     */
    void addScore(Side side);
    
    /**
     * set game score
     */
    void setScore(Side side, int score);
    
    /**
     * get score points
     */
    int getScore(Side side);
    
    /**
     * runs Goal! animation
     */
    void goalAnimation();
    
    /**
     * set seconds left to match over
     */
    void setSecondsLeft(int seconds);
    
    /**
     * get seconds left to match over
     */
    int getSecondsLeft();
    
    /**
     * show exit button (for Game)
     * @param exit handler
     */
    void showExitButton(VoidHandler * exitHandler);

    /**
     * toggle if players can kick the ball
     */
    void setBallKickable(bool kickable);
    
    /**
     * toggles the ball in the stadium
     * when added, default position is in the center
     */
    void setBallInGame(bool visible);
    
    /**
     * simple ball getter
     */
    Sprite * getBall(){return sprBall;}
    
private:
    
    /**
     * pitch coordinates origin
     */
    Vec2 origin;
    
    /**
     * pitch size
     */
    cocos2d::Size visibleSize;
    
    /**
     * stadium elements
     */
    Label * leftScore;
    Label * rightScore;
    Label * lblAdmin;
    Label * lblAdminName;
    Label * lblServerName;
    Label * lblTime;
    Label * lblGoal;
    ui::Button * btnExit;
    Sprite * sprBall;
    
    /**
     * seconds left to match over
     */
    int secondsLeft;
    
    /**
     * collision handler map
     */
    std::map<int, CollisionHandler * > collisions;
    
    /**
     * collision processing
     * call the handler if found one
     */
    bool collision( PhysicsContact &contact );
};

#endif // __LOBBY_SCENE_H__
