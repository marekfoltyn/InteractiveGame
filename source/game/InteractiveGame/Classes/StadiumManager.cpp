//
//  StadiumManager
//  InteractiveGame
//
//  Created by Marek Foltýn on 05.02.16.
//
//

#include "StadiumManager.h"

StadiumManager * StadiumManager::create(cocos2d::Scene * scene)
{
    return new StadiumManager(scene);
}



StadiumManager::StadiumManager(cocos2d::Scene * scene)
{
    this->scene = scene;
}



void StadiumManager::setPitch()
{

}