//------------------------------------------------------------------------
#include <string>
#include <vector>
//------------------------------------------------------------------------
#include "stdafx.h"
#include "World.h"
#include "Level.h"
#include "app\app.h"

void World::init()
{
    // Parse all the level files and store their data in Level classes
    for (int i = 0; i < MAX_LEVELS; i++) {
        std::string filename = ".\\Assets\\LevelData\\Level" + std::to_string(i + 1) + ".txt";

        Level level = Level(1);
        if (level.loadLevel(filename.c_str()) == 0)
        {
            levels_.push_back(level);
            maxLevels_++;
        } 
    }

    // Create the last level
    Level lastLevel = Level(2);
    levels_.push_back(lastLevel);
    maxLevels_++;

    // Init the first level
    if (maxLevels_ > 0) {
        state_ = GAME_ACTIVE;
        levels_[currentLevel_].init();
    }
    else 
    {
        state_ = LOAD_FAILED;
        // If no levels correctly load, what to do???
        // Print to screen that it's broken?
    }
}

void World::update(float deltaTime)
{
    if (state_ == GAME_ACTIVE)
    {
        int status = levels_[currentLevel_].update(deltaTime);

        // The level has finished, fetch the next one
        if (status == 1 && currentLevel_ != MAX_LEVELS + 1)
        {
            currentLevel_++;
            levels_[currentLevel_].init();
        }
    }
}

void World::render()
{
    switch (state_)
    {
    case GAME_ACTIVE:
        levels_[currentLevel_].render();
        break;
    case LOAD_FAILED:
        App::Print(400, 400, "Level Load Failed!!!");
        break;
    }
    
}

void World::destroy()
{
    // TODO: COME BACK TO THIS LATER
    // Sadly did not have time :(

    // Destroy all gameObjects and components...
    // Deallocate vector memory using the swap trick
    /*gameObjects_.swap({});
    inputComponents_.swap({});
    physicsComponents_.swap({});
    graphicsComponents_.swap({});*/
}
