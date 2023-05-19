//------------------------------------------------------------------------
#include "stdafx.h"
#include "Level.h"
#include "GameObjectFactory.h"
#include "GameObject.h"

void Level::cleanTerrain(InputComponent* input)
{
    dirtyTerrain_--;

    if (dirtyTerrain_ < 1)
    {
        state_ = LevelState::LEVEL_WON;

        // Set the input controller state machine to know the level is complete
        input->setState(ControllerState::STATE_LEVEL_OVER);

        // Create the level complete UI
        gameObjectFactory_->createUI(this, 200, APP_VIRTUAL_HEIGHT / 2, 
            "LEVEL COMPLETE! You successfully cleaned the floor in time!");
        gameObjectFactory_->createUI(this, 400, APP_VIRTUAL_HEIGHT / 2 - 50,
            "Press A to continue");
    }
}

void Level::loseLevel()
{
    state_ = LevelState::LEVEL_OVER;

    // Set the input controller state machine to know the level is over
    gameObjects_[playerIndex_].getInputComponent()->setState(ControllerState::STATE_LEVEL_OVER);

    // Create the game over UI
    gameObjectFactory_->createUI(this, 220, APP_VIRTUAL_HEIGHT / 2, 
        "GAME OVER! Your owner came home to an unclean floor...");
    gameObjectFactory_->createUI(this, 425, APP_VIRTUAL_HEIGHT / 2 - 50,
        "Press A to retry");
}

void Level::nextLevel()
{
    switch (state_)
    {
    case LevelState::LEVEL_WON:
        state_ = LevelState::LEVEL_DESTROY;
        break;
    case LevelState::LEVEL_OVER:
        // Restart the level

        // TODO: This doesn't work :((
        destroy();
        init();
        break;
    }
}

void Level::init()
{
    state_ = LevelState::LEVEL_ACTIVE;

    if (lastLevel_)
    {
        // Create the game over UI
        gameObjectFactory_->createUI(this, 400, APP_VIRTUAL_HEIGHT / 2, "Thank you for playing!");
        return;
    }

    this->parseLevelData();

    // Create moving obstacles or "enemies"
    /*for (int i = 0; i < enemyData_.size(); i++)
    {
        std::tuple<float, float> position = enemyData_[i];
        gameObjectFactory_->createEnemy(this, 35, 38, get<0>(position), get<1>(position));
    }*/

    // Create the player
    // It's important to create the player last, since the PlayerPhysicsComponent will be handling the
    // collision detection, so this must be done once all the other GameObjects have updated.
    gameObjectFactory_->createPlayer(this, 25, 28, startPosX_, startPosY_, physicsComponents_);
    playerIndex_ = gameObjects_.size() - 1;

    // Create the timer
    gameObjectFactory_->createTimer(this, 425, 700, 1000, 300);
}

int Level::update(float deltaTime)
{
    if (state_ == LevelState::LEVEL_DESTROY)
    {
        // Destroy the created objects (or return them to the object pool if I have time)
        this->destroy();
        return 1;
    }

    if (state_ == LevelState::LEVEL_ACTIVE)
    {
        // Process AI.
        for (int i = 0; i < numInputComponents_; i++)
        {
            inputComponents_[i]->update();
        }

        // Update physics.
        for (int i = 0; i < numPhysicsComponents_; i++)
        {
            physicsComponents_[i]->update(deltaTime);
        }

        // Update animations
        for (int i = 0; i < numGraphicsComponents_; i++)
        {
            graphicsComponents_[i]->update(deltaTime);
        }
    }
    else
    {
        // Process player input
        for (int i = 0; i < numInputComponents_; i++)
        {
            inputComponents_[i]->update();
        }

        // Update graphics
        for (int i = 0; i < numGraphicsComponents_; i++)
        {
            graphicsComponents_[i]->update(deltaTime);
        }
    }

    return 0;
}

void Level::render()
{
    for (int i = 0; i < numGraphicsComponents_; i++)
    {
        graphicsComponents_[i]->render();
    }
}

void Level::destroy()
{
    // TODO: This doesn't guarantee that the objects will be deallocated, so find a better way
    gameObjects_.clear();
    numGameObjects_ = 0;

    inputComponents_.clear();
    numInputComponents_ = 0;

    physicsComponents_.clear();
    numPhysicsComponents_ = 0;

    graphicsComponents_.clear();
    numGraphicsComponents_ = 0;
}

void Level::pushInputComponent(InputComponent* input)
{
    inputComponents_.push_back(input);
    numInputComponents_++;
}

void Level::pushPhysicsComponent(PhysicsComponent* physics)
{
    physicsComponents_.push_back(physics);
    numPhysicsComponents_++;
}

void Level::pushGraphicsComponent(GraphicsComponent* graphics)
{
    graphicsComponents_.push_back(graphics);
    numGraphicsComponents_++;
}

void Level::pushGameObject(GameObject gameObject)
{
    gameObjects_.push_back(gameObject);
    numGameObjects_++;
}

// TODO: Sanitize inputs!!!
int Level::loadLevel(const char* filename)
{
    // load from file
    std::string line;
    unsigned int word;

    std::ifstream fstream(filename);

    if (fstream)
    {
        while (std::getline(fstream, line)) // read each line from level file
        {
            // Temporary vector containing row information
            std::vector<unsigned int> row;

            std::istringstream sstream(line);

            while (sstream >> word)
            {
                row.push_back(word); // Store the parsed value in the temp vector
            }

            // Push the parsed row into the data structure
            terrainData_.emplace_back(row);
        }
    }

    fstream.close();

    if (terrainData_.size() > 0)
    {
        return 0;
    }

    return -1;
}

void Level::parseLevelData()
{
    // calculate dimensions
    unsigned int height = terrainData_.size();
    unsigned int width = terrainData_[0].size();
    int terrain_width = APP_VIRTUAL_WIDTH / width;
    int terrain_height = APP_VIRTUAL_HEIGHT / height;

    // initialize level tiles based on tileData		
    for (unsigned int i = 0; i < height; i++)
    {
        for (unsigned int j = 0; j < width; j++)
        {
            // check block type from level data (2D level array)
            switch (terrainData_[i][j])
            {
            case 0: // Dirty terrain
                gameObjectFactory_->createDirtyTerrain(this, terrain_width, terrain_height, 
                    (terrain_width * (j + 1)), (terrain_height * i));
                dirtyTerrain_++;
                break;
            case 1: // Obstacle
                gameObjectFactory_->createObstacle(this, terrain_width, terrain_height, 
                    (terrain_width * (j + 1)), (terrain_height * i));
                break;
            case 2:
                gameObjectFactory_->createDirtyTerrain(this, terrain_width, terrain_height,
                    (terrain_width * (j + 1)), (terrain_height * i));
                dirtyTerrain_++;

                // Store position data for a moving obstacle
                /*std::tuple<float, float> enemyPosition(terrain_width * (j + 1), terrain_height * i);
                enemyData_.push_back(enemyPosition);*/
                break;
            case 5:
                // Fetch player starting position and create dirty terrain
                startPosX_ = (terrain_width - 15) * (j + 1);
                startPosY_ = (terrain_height) * i;

                gameObjectFactory_->createDirtyTerrain(this, terrain_width, terrain_height, 
                    (terrain_width * (j + 1)), (terrain_height * i));
                dirtyTerrain_++;
                break;
            }
        }
    }
}
