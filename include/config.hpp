/**
 * @file config.hpp
 *
 * @todo Add description
 *
 * @author Matthew Rodusek (matthew.rodusek@gmail.com)
 * @date   Jan 23, 2016
 *
 */

/*
 * Change Log:
 *
 * Jan 23, 2016: 
 * - config.hpp created
 */
#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#define WINDOW_TITLE "Space Breakers"

#define PIXEL_SIZE     3
#define ENTITY_SIZE_H  8
#define ENTITY_SIZE_W  12
#define BASE_SIZE      16

#define ARENA_X         (10)
#define ARENA_Y         (50)
#define ARENA_PADDING   (BASE_SIZE)
#define ARENA_SIZE_H    (BASE_SIZE*15)
#define ARENA_SIZE_W    (BASE_SIZE*15)
#define ARENA_LEFT      (ARENA_X)
#define ARENA_TOP       (ARENA_Y)
#define ARENA_BOTTOM    (PIXEL_SIZE * ARENA_SIZE_H + ARENA_Y)
#define ARENA_RIGHT     (PIXEL_SIZE * ARENA_SIZE_W + ARENA_X)

#define WINDOW_SIZE_H   ((PIXEL_SIZE * ARENA_SIZE_H)+2*ARENA_Y)
#define WINDOW_SIZE_W   ((PIXEL_SIZE * ARENA_SIZE_W)+2*ARENA_X)

//----------------------------------------------------------------------------
// Enemies
//----------------------------------------------------------------------------

#define ENEMY_MARGIN  ((BASE_SIZE - ENEMY_W)/2)

#define ENEMIES_PER_LINE 12
#define ENEMY_H          8
#define ENEMY_W          12
#define ENEMY_MOVE_STEP  3
#define ENEMY_MOVE_LINE  8
#define ENEMY_BASE_SPEED 5
#define ENEMY_SCORE      10

//----------------------------------------------------------------------------
// Ball
//----------------------------------------------------------------------------

#define BALL_SIZE_H      5
#define BALL_SIZE_W      5
#define BALL_MOVE_STEP   3

//----------------------------------------------------------------------------
// Player
//----------------------------------------------------------------------------

#define PLAYER_MOVE_STEP   2
#define PLAYER_H           5
#define PLAYER_W           (24 * PIXEL_SIZE)
#define PLAYER_HEALTH      10

//----------------------------------------------------------------------------
// Assets
//----------------------------------------------------------------------------

#define FONT_SIZE 18
#define FONT_FILE "assets/font.dat"
#define FONT_COLOR (SDL_Color){128,128,128}

#endif /* CONFIG_HPP_ */
