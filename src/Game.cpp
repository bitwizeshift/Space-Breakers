/**
 * @file Game.cpp
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
 * - Game.cpp created
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_timer.h>

#include "config.hpp"
#include "types.hpp"
#include "Timer.hpp"

#include "Game.hpp"

#include <sstream>

namespace vdk{

	static const int g_max_health = PLAYER_HEALTH;

	static const int g_max_framerate = 60;
	static const int g_max_ticks = 1000 / g_max_framerate;

	//--------------------------------------------------------------------------
	// Constructor / Destructor
	//--------------------------------------------------------------------------

	Game::Game()
		: m_current_state(Game::State::state_game_opening),
			m_player(g_max_health),
			m_invaders(1),
			m_score(0),
			m_highest_score(0),
			m_counter(0),
			m_level(1),
			m_sound_frame(0)
	{

		memset( m_keys, 0 , 1000 );

		// Lazy-load SDL initializers --------------------------------------------

		int    audio_rate     = 22050;
		Uint16 audio_format   = AUDIO_S16SYS;
		int    audio_channels = 2;
		int    audio_buffers  = 4096;

		SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO );
		TTF_Init();
		Mix_OpenAudio( audio_rate, audio_format, audio_channels, audio_buffers );

		// Initialize

		m_dimensions.x = ARENA_X;
		m_dimensions.y = ARENA_Y;
		m_dimensions.w = ARENA_RIGHT;
		m_dimensions.h = ARENA_BOTTOM;

		// Video Elements --------------------------------------------------------

		// Create the window
		m_screen = SDL_CreateWindow(
			WINDOW_TITLE,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WINDOW_SIZE_W,
			WINDOW_SIZE_H,
			SDL_WINDOW_ALLOW_HIGHDPI
		);
		// Create the renderer
		m_renderer = SDL_CreateRenderer(
			m_screen,
			-1,
			0
		);

		// Font Elements ---------------------------------------------------------

		m_font= TTF_OpenFont( FONT_FILE, FONT_SIZE );

		// Sound Elements --------------------------------------------------------

		m_sound_invader1       = Mix_LoadWAV("assets/audio/invader1.wav");
		m_sound_invader2       = Mix_LoadWAV("assets/audio/invader2.wav");
		m_sound_invader3       = Mix_LoadWAV("assets/audio/invader3.wav");
		m_sound_invader4       = Mix_LoadWAV("assets/audio/invader4.wav");
		m_sound_shoot          = Mix_LoadWAV("assets/audio/shoot.wav");
		m_sound_death          = Mix_LoadWAV("assets/audio/death.wav");
		m_sound_invader_killed = Mix_LoadWAV("assets/audio/invaderkilled.wav");
	}

	Game::~Game(){

		TTF_CloseFont( m_font );

		TTF_Quit();
		SDL_Quit();
	}


	//--------------------------------------------------------------------------
	// Game Run
	//--------------------------------------------------------------------------

	void Game::run(){

		bool game_running = true;

		Timer fps;
		SDL_Event event;
		while( game_running ){
			// Start timing fps
			fps.start();

			SDL_PollEvent(&event);
			if(event.key.repeat != 1){

				switch(event.type){
					case SDL_QUIT:
						game_running = false;
						break;
					case SDL_KEYDOWN:
						m_keys[SDL_KEY_CONVERT(event.key.keysym.sym)] = 1;
						break;
					case SDL_KEYUP:
						m_keys[SDL_KEY_CONVERT(event.key.keysym.sym)] = 0;
						break;
				}
				handle_input();
			}

			// Only update if game is running
			if( m_current_state == state_game_running ){
				update_entities();
			}
			draw();

			// Lock framerate
			if( fps.get_ticks() < g_max_ticks ){
				SDL_Delay( ( g_max_ticks ) - fps.get_ticks() );
			}
		}
	}

	void Game::draw(){

		// Clear the screen
		SDL_SetRenderDrawColor(
			this->m_renderer,
		  0, 0, 0,
		  SDL_ALPHA_OPAQUE
		);

		SDL_RenderClear(this->m_renderer);

		SDL_Rect rect;

		u8 red   = (200 * std::max((g_max_health - m_player.get_health()),0)) / g_max_health;
		u8 green = (200 * std::min(m_player.get_health(), g_max_health)) / g_max_health;

		// Draw bottom line
		SDL_SetRenderDrawColor(
			this->m_renderer,
			red, green, 0,
			SDL_ALPHA_OPAQUE
		);
		rect.x = ARENA_X;
		rect.y = ARENA_BOTTOM;
		rect.h = PIXEL_SIZE;
		rect.w = PIXEL_SIZE * ARENA_SIZE_W;
		SDL_RenderFillRect(m_renderer, &rect);

		for( Projectile& ball : m_projectiles ){
			ball.draw( m_renderer );
		}

		m_invaders.draw( m_renderer );

		m_player.draw(m_renderer);

		std::stringstream s;

		// Print the health
		s.str("");
		s << "Health: ";
		s << m_player.get_health();

		draw_text( s.str().c_str(), 10, ARENA_BOTTOM + 10 );

		// Prints the level
		s.str("");
		s << "Level: ";
		s << m_level;

		draw_text( s.str().c_str(), 400, ARENA_BOTTOM + 10 );

		// Print the player score
		s.str("");
		s << "Score: ";
		s << m_score;

		draw_text( s.str().c_str(), 10, 10 );

		// Print the highest score
		s.str("");
		s << "High Score: ";
		s << m_highest_score;

		draw_text( s.str().c_str(), 400, 10 );

		switch(m_current_state){
		case state_game_opening:
			draw_text("Press any [enter] to begin", 130, 300);
			break;
		case state_game_paused:
			draw_text("Paused", 320, 300);
			break;
		case state_game_over:
			draw_text("Game Over", 300,300);
			draw_text("Press [enter] to continue", 130, 330);
			break;
		case state_game_running:

			break;
		}

		SDL_RenderPresent(m_renderer);
	}

	void Game::draw_text( const char* str, int x, int y ){
	   SDL_Surface* surface;
	   SDL_Texture* texture;
	   SDL_Rect     rect;

	   SDL_Color color = {128,128,128};

	   surface = TTF_RenderText_Solid( m_font, str, color );
	   texture = SDL_CreateTextureFromSurface( m_renderer, surface );

	   // display texture
	   rect.x = x;
	   rect.y = y;
	   rect.w = surface->w;
	   rect.h = surface->h;

	   SDL_RenderCopy( m_renderer, texture, NULL, &rect );
	   SDL_FreeSurface( surface );
	   SDL_DestroyTexture( texture );
	}

	//--------------------------------------------------------------------------

	void Game::handle_input(){

		if( m_keys[KEY_ESCAPE] ){
			if( m_current_state == state_game_running ){
				m_current_state = state_game_paused;
			}else if( m_current_state == state_game_paused ){
				m_current_state = state_game_running;
			}
		}else if( m_keys[KEY_ENTER] ){
			if( m_current_state == state_game_opening ){
				m_current_state = state_game_running;
			}else if( m_current_state == state_game_over ){
				m_current_state = state_game_opening;
				reset();
			}
		}
	}

	void Game::reset(){
		m_level = 1;
		m_invaders.reset(m_level);
		m_player.set_health( g_max_health );
		m_projectiles.clear();
		if( m_highest_score < m_score ){
			m_highest_score = m_score;
		}
		m_score = 0;
	}

	void Game::update_entities(){
		Rect player_bound = m_player.get_bounding_box();

		// Only move if one of the two keys is pressed
		if( m_keys[KEY_LEFT] ^ m_keys[KEY_RIGHT] ){
			int speed = (m_keys[KEY_LSHIFT] ^ m_keys[KEY_RSHIFT]) ? 8 : 5;

			int delta = 0;
			if( m_keys[KEY_LEFT] ){
				if( player_bound.x > ARENA_LEFT ){
					int delta = -speed;
					if( (player_bound.x - speed) <= ARENA_LEFT ){
						delta = -abs( player_bound.x - ARENA_LEFT );
					}
					m_player.move( delta, 0 );
					m_player.set_velocity(-speed,0);
				}
			}else if( m_keys[KEY_RIGHT] ){
				if( (player_bound.x + player_bound.w) < ARENA_RIGHT ){
					delta = speed;
					if( (player_bound.x + player_bound.w + speed) <= ARENA_LEFT ){
						delta = abs( (player_bound.x + player_bound.w) - ARENA_RIGHT );
					}
					m_player.move( delta, 0 );
					m_player.set_velocity( speed,0 );
				}
			}
		}else{
			m_player.set_velocity( 0,0 );
		}

		// Check projectile collisions

		projectiles_collections::iterator it = m_projectiles.begin();

		while( it != m_projectiles.end() ){
			bool marked_to_delete = false;
			Projectile& ball = (*it);
			Rect  bound    = ball.get_bounding_box();
			Point velocity = ball.get_velocity();

			// Check arena bounce
			if( ((velocity.x < 0) && (bound.x <= ARENA_LEFT)) ||
					((velocity.x > 0) && ((bound.x + bound.w) >= ARENA_RIGHT))
				 ){
				velocity.x = -velocity.x;
			}

			// Bounce off the player
			if( check_collision( &m_player, &ball ) ){
				Point player_velocity = m_player.get_velocity();
				if( player_velocity.x < 0 ){
					velocity.x -= rand() % (-player_velocity.x/2 + 1);
				}else if( player_velocity.x > 0 ){
					velocity.x += rand() % (player_velocity.x/2 + 1);
				}
				velocity.y = -velocity.y;
				m_score += 10 * m_level;
			}

			// Bounce off the top of the arena
			if( (velocity.y < 0) && (bound.y <= ARENA_TOP ) ){
				marked_to_delete = true;
			}

			// Hurt the player if a ball hits the wall
			if( (velocity.y > 0) && (bound.y + bound.h) >= ARENA_BOTTOM ){
				m_player.set_health( m_player.get_health() - 1 );
				marked_to_delete = true;
				Mix_PlayChannel( -1, m_sound_death, 0 );
			}

			if( m_invaders.check_collision( &ball ) ){
				m_score += 100 * m_level;
				marked_to_delete = true;
				Mix_PlayChannel( -1, m_sound_invader_killed, 0 );
			}

			if( !marked_to_delete ){
				ball.set_velocity( velocity.x, velocity.y );
				ball.move( velocity.x, velocity.y );
				++it;
			}else{
				m_projectiles.erase(it++);
			}
		}

		Rect alien_bound = m_invaders.get_bounding_box();
		Point alien_velocity = m_invaders.get_velocity();

		int speed = 25;
		if( m_invaders.size() == 1 ){
			speed = 5;
		}else if( m_invaders.size() < (m_invaders.max_size() / 4) ){
			speed = 10;
		}else if( m_invaders.size() < (m_invaders.max_size() / 3) ){
			speed = 15;
		}else if( m_invaders.size() < (m_invaders.max_size() / 2) ){
			speed = 20;
		}

		m_counter = ((m_counter + 1) % speed);
		if( m_counter == 0 ){
			if( ((alien_velocity.x < 0) && (alien_bound.x < ARENA_LEFT)) ||
					((alien_velocity.x > 0) && (alien_bound.x + alien_bound.w > ARENA_RIGHT ))
			){
				alien_velocity.x = -alien_velocity.x;
			}
			switch(m_sound_frame){
			case 0: Mix_PlayChannel( -1, m_sound_invader1, 0 ); break;
			case 1: Mix_PlayChannel( -1, m_sound_invader2, 0 ); break;
			case 2: Mix_PlayChannel( -1, m_sound_invader3, 0 ); break;
			case 3: Mix_PlayChannel( -1, m_sound_invader4, 0 ); break;
			}

			m_sound_frame = (m_sound_frame + 1) % 4;

			m_invaders.set_velocity( alien_velocity.x, alien_velocity.y );
			m_invaders.move( alien_velocity.x, 0 );

			// Always fire if the projectile is empty
			// Otherwise have 10% chance of firing, as long as below projectile cap
			if( m_projectiles.empty() || (((rand() % 10) == 0) && (m_projectiles.size() < (size_t)(m_level * 2))) ){
				int speed = std::min(3 + m_level, 8);
				m_projectiles.push_back( m_invaders.shoot_projectile( speed ) );
				Mix_PlayChannel( -1, m_sound_shoot, 0 );
			}
		}

		// Check whether the player is alive
		if( !m_player.is_alive() ){
			m_current_state = state_game_over;
		}else if( !m_invaders.is_alive() ){
			m_player.set_health( m_player.get_health() + m_level*2 ); // regain 'level' health
			m_level++;
			m_invaders.reset(m_level);
			m_projectiles.clear();
		}

	}

	//--------------------------------------------------------------------------
	// Lazy-loaders
	//--------------------------------------------------------------------------

	void Game::init_SDL_Video(){
		static bool enabled = false;
		if(!enabled){
		  SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO );
			enabled = true;
		}
	}

	void Game::init_SDL_ttf(){
		static bool enabled = false;
		if(!enabled){
		   TTF_Init();
		   enabled = true;
		}
	}

	void Game::init_SDL_Mixer(){
		static bool enabled = false;
		if(!enabled){
		  SDL_Init( SDL_INIT_AUDIO );


			enabled = true;
		}
	}
}
