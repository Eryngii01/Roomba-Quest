#ifndef _LEVEL_H
#define _LEVEL_H
#define X_TILE_OFFSET            32     // Offset of the tiles to successfully fit in the screen
#define Y_TILE_OFFSET            24     // Offset of the tiles to successfully fit in the screen

//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h> 
#include <string>
#include <sstream>
#include <iostream>
#include <fstream> 
#include <vector>
#include <tuple>
//------------------------------------------------------------------------
#include "GameObjectFactory.h"
#include "GameObject.h"

// Represents the current state of the level
// State management is getting unruly; make a state class to fix this if time permits to delegate to for code readability
enum class LevelState {
    LEVEL_ACTIVE,
    LEVEL_WON,
    LEVEL_OVER,
    LEVEL_RESTART,
    LEVEL_DESTROY
};

//*******************************************************************************************
// Level
//*******************************************************************************************
// A class representing the game world/environment, holding all the GameObjects and their components. The application
// init() and update() functions will delegate to this class to handle the management of GameObjects and their behaviour
// throughout the course of the game, aiming to optimize the sequential execution of update on every GameObject entity.
class Level
{
	// Level building and updates will only be exposed to the World and GameObjectFactory classes
	friend class World;
    friend class GameObjectFactory;

// These operations will be the only ones exposed to the gameObjects and their components
public:
    // A method to decrement the remaining number of dirty tiles left to clean. 
    void cleanTerrain(InputComponent* input);

    // A method to change the level state to lost in response to the timer counting to 0. GameObjects
    // will take a different behaviour once the level state has changed to game over
    void loseLevel();

    // A method to load the next level, either notifying World that this level has been complete, or restarted
    // if the level was lost.
    void nextLevel();

    // A member method to return the current state of the level
    LevelState getState() 
    {
        return state_;
    }

private:
	Level(int code): state_(LevelState::LEVEL_ACTIVE), dirtyTerrain_(0), numGameObjects_(0), numInputComponents_(0), numPhysicsComponents_(0), 
        numGraphicsComponents_(0), playerIndex_(0), gameObjects_{}, startPosX_(0), startPosY_(0), gameObjectFactory_(new GameObjectFactory()) 
    {
        switch (code)
        {
        case 0:
            // First scene?
            break;
        case 2:
            // Generate the end level
            lastLevel_ = true;
            break;
        }
    }

	void init();

    // Return 0 is the level is running, return 1 if the level has finished
	int update(float deltaTime);
	void render();
	void destroy();

    //*******************************************************************************************
    // Level State
    //*******************************************************************************************
    LevelState state_;

    // Bookkeeping of how many dirty areas are left in the level
    int dirtyTerrain_;

    //*******************************************************************************************
    // GameObject & Component Bookkeeping
    //*******************************************************************************************
    // To avoid CPU thrashing, GameObject components that must be updated every frame will be stored
    // contiguously to optimize performance.
    // This was originally meant to be paired with object pooling to maintain where the GameObjects are allocated
    // in memory, but I did not have the time to implement it :(

    std::vector<GameObject> gameObjects_;

    std::vector<InputComponent*> inputComponents_;
    std::vector<PhysicsComponent*> physicsComponents_;
    std::vector<GraphicsComponent*> graphicsComponents_;

    // For now .size() could be used in place, but if I do have time to implement the sorting of active and inactive
    // GameObjects, these would be very useful for indexing
    int numGameObjects_, numInputComponents_, numPhysicsComponents_, numGraphicsComponents_;
    int playerIndex_;

    void pushInputComponent(InputComponent* input);
    void pushPhysicsComponent(PhysicsComponent* physics);
    void pushGraphicsComponent(GraphicsComponent* graphics);
    void pushGameObject(GameObject gameObject);

    //*******************************************************************************************
    // GameObject Building
    //*******************************************************************************************
    GameObjectFactory* gameObjectFactory_;

    //*******************************************************************************************
    // Level Building
    //*******************************************************************************************
	// To maximize the use of object pooling, operations to read file data and parse the contents will
	// be processed separately, aiming to invoke the parsing as lazily as possible once the previous level
	// objects have been returned to their pool.

	// Delegate checking for file read errors to the World class by returning the status code
    // TODO: Only works for 16x16 :(
	int loadLevel(const char* filename);
	void parseLevelData();

    bool lastLevel_ = false;

    // Nested vector to represent the level matrix parsed from a level file
	std::vector<std::vector<unsigned int>> terrainData_;
    std::vector<std::tuple<float, float>> enemyData_;
    float startPosX_, startPosY_;
};
#endif

