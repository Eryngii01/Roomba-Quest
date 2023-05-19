#include "stdafx.h"
#include "GameObjectFactory.h"
#include "GameObject.h"
#include "Level.h"
#include "PlayerInputComponent.h"
#include "PlayerPhysicsComponent.h"
#include "TilePhysicsComponent.h"
#include "ObstaclePhysicsComponent.h"
#include "PlayerGraphicsComponent.h"
#include "TileGraphicsComponent.h"
#include "ObstacleGraphicsComponent.h"
#include "UIGraphicsComponent.h"
#include "TimerGraphicsComponent.h"

void GameObjectFactory::createPlayer(Level* level, float width, float height, float xPos, float yPos, std::vector<PhysicsComponent*> colliders)
{
    PlayerInputComponent* input = new PlayerInputComponent(level);
    level->pushInputComponent(input);

    PlayerPhysicsComponent* physics = new PlayerPhysicsComponent(level, width, height, xPos, yPos, input, colliders);
    level->pushPhysicsComponent(physics);

    PlayerGraphicsComponent* graphics = new PlayerGraphicsComponent(input, physics);
    level->pushGraphicsComponent(graphics);

    level->pushGameObject(GameObject(input, physics, graphics));
}

void createEnemy(Level* level, float width, float height, float xPos, float yPos)
{
    /*EnemyPhysicsComponent* physics = new EnemyPhysicsComponent(width, height, xPos, yPos);
    level->pushPhysicsComponent(physics);

    EnemyGraphicsComponent* graphics = new EnemyGraphicsComponent(nullptr, physics);
    level->pushGraphicsComponent(graphics);

    level->pushGameObject(GameObject(nullptr, physics, graphics));*/
}

// Terrain is a stationary object, so no InputComponent is required
void GameObjectFactory::createDirtyTerrain(Level* level, float width, float height, float xPos, float yPos)
{
    TilePhysicsComponent* physics = new TilePhysicsComponent(width, height, xPos, yPos);
    level->pushPhysicsComponent(physics);

    TileGraphicsComponent* graphics = new TileGraphicsComponent(nullptr, physics);
    level->pushGraphicsComponent(graphics);

    level->pushGameObject(GameObject(nullptr, physics, graphics));
}

// Obstacle is a stationary object, so no InputComponent is required
void GameObjectFactory::createObstacle(Level* level, float width, float height, float xPos, float yPos)
{
    ObstaclePhysicsComponent* physics = new ObstaclePhysicsComponent(width, height, xPos, yPos);
    level->pushPhysicsComponent(physics);

    ObstacleGraphicsComponent* graphics = new ObstacleGraphicsComponent(nullptr, physics);
    level->pushGraphicsComponent(graphics);

    level->pushGameObject(GameObject(nullptr, physics, graphics));
}

void GameObjectFactory::createUI(Level* level, float x, float y, const char* printText, const char* graphicName)
{
    UIGraphicsComponent* graphics = new UIGraphicsComponent(x, y, printText, graphicName);
    level->pushGraphicsComponent(graphics);

    level->pushGameObject(GameObject(nullptr, nullptr, graphics));
}

// Timer is UI
void GameObjectFactory::createTimer(Level* level, float x, float y, float speed, float seconds)
{
    TimerGraphicsComponent* graphics = new TimerGraphicsComponent(level, x, y, speed, seconds, nullptr, nullptr);
    level->pushGraphicsComponent(graphics);

    level->pushGameObject(GameObject(nullptr, nullptr, graphics));
}



