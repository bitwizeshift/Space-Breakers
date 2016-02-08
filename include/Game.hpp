/**
 * @file Game.hpp
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
 * - Game.hpp created
 */
#ifndef GAME_HPP_
#define GAME_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <list>

#include "types.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include <InvaderGroup.hpp>
#include <Projectile.hpp>

#define SDL_MAX_KEY 1000

// http://wiki.libsdl.org/SDLKeycodeLookup
// 0x40000000 + 0x00000200 = 0x3FFFFE39
#define SDL_KEY_CONVERT(k) (k > 0x40000000 ? k - 0x3FFFFF39 : k)

#define KEY_QUIT 999

#define KEY_LSHIFT   SDL_KEY_CONVERT(SDLK_LSHIFT)
#define KEY_RSHIFT   SDL_KEY_CONVERT(SDLK_RSHIFT)
#define KEY_A        SDL_KEY_CONVERT(SDLK_a)
#define KEY_D        SDL_KEY_CONVERT(SDLK_d)
#define KEY_LCTRL    SDL_KEY_CONVERT(SDLK_LCTRL)
#define KEY_RCTRL    SDL_KEY_CONVERT(SDLK_RCTRL)
#define KEY_ESCAPE   SDL_KEY_CONVERT(SDLK_ESCAPE)
#define KEY_ENTER    SDL_KEY_CONVERT(SDLK_RETURN)
#define KEY_TAB      SDL_KEY_CONVERT(SDLK_TAB)
#define KEY_PAUSE    SDL_KEY_CONVERT(SDLK_p)
#define KEY_UP       SDL_KEY_CONVERT(SDLK_UP)
#define KEY_DOWN     SDL_KEY_CONVERT(SDLK_DOWN)
#define KEY_LEFT     SDL_KEY_CONVERT(SDLK_LEFT)
#define KEY_RIGHT    SDL_KEY_CONVERT(SDLK_RIGHT)
#define KEY_SPACE    SDL_KEY_CONVERT(SDLK_SPACE)

namespace vdk{

	////////////////////////////////////////////////////////////////////////////
	/// @class vdk::Game
	///
	///
	///
	////////////////////////////////////////////////////////////////////////////
	class Game{

		//------------------------------------------------------------------------
		// Public Methods
		//------------------------------------------------------------------------
	public:

		///
		/// Constructs a game object
		///
		Game();

		///
		/// Destructs the game object
		///
		~Game();

		///
		/// Runs the game
		///
		void run();

		//------------------------------------------------------------------------
		// Private Methods
		//------------------------------------------------------------------------
	private:

		///
		/// @brief Resets the game
		///
		///
		void reset();

		///
		/// @brief Updates all entities in the game
		///
		void update_entities();

		///
		/// @brief Handles the keyboard input for the game
		///
		void handle_input();

		// ------------------------------------------------------------------------

		///
		/// @brief Draw the screen
		///
		void draw();

		///
		/// @brief Draw all entities
		///
		void draw_entities();

		///
		/// @brief Draw the score
		///
		void draw_score();


		///
		/// @brief Draws text at the specified coordinates
		///
		/// @param str
		/// @param x
		/// @param y
		///
		void draw_text( const char* str, int x, int y );

		///
		/// @brief Initializes the SDL Video mode
		///
		/// This method calls and constructs the video screen and renderer, along
		/// with enabled SDL to support Video.
		///
		void init_SDL_Video();

		///
		/// @brief Initializes the True-type-font mode of SDL
		///
		/// This method creates the font file that will be used in this game
		///
		void init_SDL_ttf();

		///
		/// @brief Initializes the Sound-mixer for SDL
		///
		/// This method creates all sound objects that is used in this game
		///
		void init_SDL_Mixer();

		//------------------------------------------------------------------------
		// Private Members
		//------------------------------------------------------------------------
	private:

		typedef std::list<Projectile>  projectiles_collections;

		///
		/// @enum Game::States
		///
		/// @brief An enumeration of all possible game states
		///
		enum State{
			state_game_opening,  //!< Opening Menu
			state_game_highscore,//!< Highscore Menu
			state_game_running,  //!< Running (normal gameplay)
			state_game_paused,   //!< Game is paused
			state_game_over      //!< Game Over menu
		};

		//------------------------------------------------------------------------

		SDL_Window*   m_screen;   ///< The SDL window screen
		SDL_Renderer* m_renderer; ///< The SDL Renderer screen
		TTF_Font*     m_font;     ///< The font to display

		//------------------------------------------------------------------------

		Rect  m_dimensions;    ///< The current screen dimensions
		State m_current_state; ///< The current state of this Game

		Player                   m_player;      ///< The player entity
		InvaderGroup             m_invaders;    ///< The group of invaders in the game
		projectiles_collections  m_projectiles; ///< A collection of projectiles

		int m_score;
		int m_highest_score;
		int m_counter;
		int m_level;
		int m_sound_frame;

		Mix_Chunk* m_sound_invader1; ///< The first alien sound
		Mix_Chunk* m_sound_invader2; ///< The second alien sound
		Mix_Chunk* m_sound_invader3; ///< The third alien sound
		Mix_Chunk* m_sound_invader4; ///< The fourht alien sound
		Mix_Chunk* m_sound_shoot;    ///< The projectile shoot sound
		Mix_Chunk* m_sound_death;    ///< The damage sound (destroy wall)
		Mix_Chunk* m_sound_invader_killed; ///< The space-invaders killed sound

		char m_keys[SDL_MAX_KEY];

		bool collides_with_boundary( const Entity* entity ) const;
	};

} // namespace vdk


#endif /* GAME_HPP_ */
