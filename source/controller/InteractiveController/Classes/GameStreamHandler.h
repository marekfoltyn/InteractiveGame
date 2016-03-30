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

class ControlScene;

/**
 * Processing GameStream rendering
 */
class GameStreamHandler: public BoxHandler{
public:

    GameStreamHandler(ControlScene * scene);
    
    /**
     * render game
     */
    virtual bool execute( GameNet::Box * box );
    
private:
  
    Director * director;
    Controller * controller;
    ControlScene * scene;
    PBGameStream actualStream;
    
    void updateActive(bool isActive);
    
    void setStadiumLayerVisible(bool visible);
};

#endif /* GameStream_h */
