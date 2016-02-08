/**
 * @file Ball.cpp
 *
 * @todo Add description
 *
 * @author Matthew Rodusek (matthew.rodusek@gmail.com)
 * @date   Jan 30, 2016
 *
 */

/*
 * Change Log:
 *
 * Jan 30, 2016: 
 * - Ball.cpp created
 */

#include <Projectile.hpp>
#include "config.hpp"


namespace vdk {

	Projectile::Projectile( Point& position, Point& velocity )
	 : m_velocity(velocity){
		m_rect.x = position.x;
		m_rect.y = position.y;
		m_rect.w = BALL_SIZE_W;
		m_rect.h = BALL_SIZE_H;
		m_bounding_box = m_rect;
	}

	void Projectile::move( int x, int y ){
		m_rect.x += x;
		m_rect.y += y;
		m_bounding_box = m_rect;
	}

	void Projectile::draw( SDL_Renderer* renderer ) const{
		SDL_Surface* s = SDL_CreateRGBSurface(0, m_rect.w, m_rect.h, 32, 0, 0, 0, 0);

		SDL_FillRect( s, &m_rect, SDL_MapRGB( s->format, 0, 0, 255) );

		SDL_SetRenderDrawColor( renderer, 0,255,0,255 );
		SDL_RenderFillRect( renderer, &m_rect );
	}

	Point Projectile::get_location() const{
		Point vel;
		vel.x = m_rect.x;
		vel.y = m_rect.y;
		return vel;
	}

	bool Projectile::is_alive() const{
		return true;
	}

}  // namespace vdk
