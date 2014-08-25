#ifndef GLOBALS_H
#define GLOBALS_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "CTexture.h"
#include "CButton.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>

using namespace std;

// Pi
const float PI = 3.14f;

// Bounds block matrices
const int BLOCK_BOUND_4 = 4;
const int BLOCK_BOUND_3 = 3;
const int BLOCK_BOUND_2 = 2;

// Orientations
const int NUM_DIRECTIONS = 4;

// Board dimensions
const int GRID_HEIGHT = 22;
const int GRID_WIDTH  = 10;

// Number of hidden rows
const int HIDDEN_ROWS = 2;

// Tile sizes
const int TILE_WIDTH  = 32;
const int TILE_HEIGHT = 32;

// Number of tile types
const int TILE_TYPES = 8;

// Number of block shapes
const int BLOCK_SHAPES = 7;

// Start delay
const int START_DELAY  = 800;

// Soft drop delay
const int SOFT_DROP_DELAY = 0;

// Delay decrement
const int DELAY_DECREMENT = 40;

// Particle System
const int TOTAL_PARTICLES = 40;

// SNOW
const int DRIFT = 2;

// Button types
enum ButtonTypes
{
    IMAGE = 1,  // button used the constructor with an image
    TEXT = 2  // button used the constructor with text
};

// Particle systems
enum
{
    NONE      = 0,
    STARFIELD = 1,
    SNOW      = 2,
    MATRIX    = 3
};

// Block types
enum blockTypes
{
    TILE_BLANK   = 0,
    TILE_CYAN    = 1,
    TILE_YELLOW  = 2,
    TILE_PURPLE  = 3,
    TILE_GREEN   = 4,
    TILE_RED     = 5,
    TILE_BLUE    = 6,
    TILE_ORANGE  = 7,
};

enum shapes
{
    BLOCK_TYPE_I = 1,
    BLOCK_TYPE_O = 2,
    BLOCK_TYPE_T = 3,
    BLOCK_TYPE_S = 4,
    BLOCK_TYPE_Z = 5,
    BLOCK_TYPE_J = 6,
    BLOCK_TYPE_L = 7,
};

// Block orientations
enum blockOrientation
{
    // Clockwise order
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
};

// Delay Difficulties

// Axix aligned bounding box collision test
extern bool CollisionTest(SDL_Rect A, SDL_Rect B);

// Mouse and Rectangle collision test
extern bool MARCollisionTest(int mouseX, int mouseY, SDL_Rect B);

// Dynamic 3D integer array
typedef vector<vector<vector<int>>> Array_3D;

#endif