#include "AccelerationHandler.h"
#include "Game.h"
#include "StadiumScene.h"

void AccelerationHandler::execute(GameNet::Box * box)
{
    game->getScene()->onAccelerationBox(box);
}