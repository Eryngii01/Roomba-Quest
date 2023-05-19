#ifndef _GAMEOBJECTFACTORY_H
#define _GAMEOBJECTFACTORY_H

#include <vector>
#include <string>
#include "PhysicsComponent.h"


//*******************************************************************************************
// GameObjectFactory
//*******************************************************************************************
// A class for maintaining the instantiations of GameObject types, containing factory methods to instantiate various
// types of GameObjects that will appear during gameplay.

class GameObjectFactory
{
    // GameObject building will only be exposed to the Level class 
    friend class Level;

private:
    void createPlayer(Level* level, float width, float height, float xPos, float yPos, std::vector<PhysicsComponent*> colliders);
    void createEnemy(Level* level, float width, float height, float xPos, float yPos);
    void createDirtyTerrain(Level* level, float width, float height, float xPos, float yPos);
    void createObstacle(Level* level, float width, float height, float xPos, float yPos);
    void createUI(Level* level, float x, float y, const char* printText = NULL, const char* graphic = NULL);
    void createTimer(Level* level, float x, float y, float speed, float seconds);
};
#endif

