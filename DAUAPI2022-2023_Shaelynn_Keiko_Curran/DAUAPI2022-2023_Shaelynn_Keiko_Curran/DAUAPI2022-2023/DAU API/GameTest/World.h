#ifndef _WORLD_H
#define _WORLD_H

#include <string>
#include "Level.h"

#define MAX_LEVELS            3     // Max levels that were created for this game


// Represents the current state of the game, noting if a level load failed
enum WorldState {
    GAME_ACTIVE,
    LOAD_FAILED
};

//*******************************************************************************************
// World
//*******************************************************************************************
// The World class oversees the entire game process, storing and managing all the level or "scenes" within the game,
// delegating the application update() and render() functions to the individual levels to manage their gameObject
// data.

class World
{
public:
    World() : currentLevel_(0), maxLevels_(0), levels_{}, state_(GAME_ACTIVE) {};


    //*******************************************************************************************
    // Application delegation methods
    //*******************************************************************************************
    
    // A method to be called from the application initialization function. Initializes all the level classes
    // and stores them as metadata before beginning the game.
    void init();

    // A method to delegate the update functionality for all the gameObjects to the current active level.
    void update(float deltaTime);

    // A method to delegate the render functionality for all the existing gameObjects to the current active
    // level.
    void render();

    // A method to clean up all the level data to avoid memory leaks, also calling the levels to destroy themselves.
    void destroy();

private:
    //*******************************************************************************************
    // Level Bookkeeping
    //*******************************************************************************************
    // The max levels can be defined by the macro MAX_LEVELS, dictating how many levels can be created
    // by parsing the Level<#>.txt files found in the project Assets folder. 
    std::vector<Level> levels_;
    // Metadata to ensure correct traversal of the level vector
    int currentLevel_, maxLevels_;

    //*******************************************************************************************
    // Game State
    //*******************************************************************************************
    // The current state of the World class, indicating if level loads have failed.
    WorldState state_;
};
#endif

