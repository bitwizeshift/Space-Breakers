/**
 * @file Player.cpp
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
 * - Player.cpp created
 */

#include "config.hpp"

#include "Player.hpp"

namespace vdk{

	//--------------------------------------------------------------------------
	// Constructor
	//--------------------------------------------------------------------------

	Player::Player( int health )
		: m_health( health ),
			m_rect{
				ARENA_SIZE_W/2-BASE_SIZE/2,
				ARENA_BOTTOM-BASE_SIZE*2,
				PLAYER_W,
				PLAYER_H
			},
			m_bounding_box(m_rect),
			m_velocity{0,0}
	{

	}

	Player::~Player(){

	}

	//--------------------------------------------------------------------------
	// Player API
	//--------------------------------------------------------------------------

	void Player::move(int x, int y){
		m_rect.x += x;
		m_rect.y += y;
		m_bounding_box.x += x;
		m_bounding_box.y += y;
	}

	void Player::draw( SDL_Renderer* renderer ) const{
		SDL_Surface* s = SDL_CreateRGBSurface(0, m_rect.w, m_rect.h, 32, 0, 0, 0, 0);

		SDL_FillRect( s, &m_rect, SDL_MapRGB( s->format, 0, 0, 255) );

		SDL_SetRenderDrawColor( renderer, 255,0,0,255 );
		SDL_RenderFillRect( renderer, &m_rect );
	}

	void Player::set_health( int health ){
		m_health = health;
	}

	bool Player::is_alive() const{
		return m_health > 0;
	}

	Point Player::get_location() const{
		Point loc;
		loc.x = m_rect.x;
		loc.y = m_rect.y;
		return loc;
	}


} // namespace vdk


