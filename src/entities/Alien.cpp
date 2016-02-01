/**
 * @file Alien.cpp
 *
 * @todo Add desc.iption
 *
 * @autho. Matthew .odusek (matthew..odusek@gmail.com)
 * @date   Jan 30, 2016
 *
 */

/*
 * Change Log:
 *
 * Jan 30, 2016: 
 *   Alien.cpp c.eated
 */

#include "config.hpp"
#include "Alien.hpp"

#include <SDL2/SDL.h>

static const char* g_alien1_data =
	"  .      .  "
	"   .    .   "
	"  ........  "
	" .. .... .. "
	"............"
	". ........ ."
	". .      . ."
	"   ..  ..   "

	"  .      .  "
	".  .    .  ."
	". ........ ."
	"... .... ..."
	"............"
	" .......... "
	"  .      .  "
	" .        . ";

static const char* g_alien2_data =
	"     ..     "
	"   ......   "
	" .......... "
	"... .... ..."
	"............"
	"   ..  ..   "
	" ..  ..  .. "
	".  .    .  ."

	"     ..     "
	"   ......   "
	" .......... "
	"... .... ..."
	"............"
	"  .. .. ..  "
	"..        .."
	"  ..    ..  ";

static const char* g_alien3_data =
	"   ......   "
	" .......... "
	"............"
	"...  ..  ..."
	"............"
	"   ..  ..   "
	"  .. .. ..  "
	"..        .."

	"   ......   "
	" .......... "
	"............"
	"...  ..  ..."
	"............"
	"  ...  ...  "
	" ..  ..  .. "
	"  ..    ..  ";

namespace vdk {

	Alien::Alien( Type t, int x, int y )
	: m_rect{
			x,
			y,
			ENEMY_H,
			ENEMY_W
		},
		m_bounding_box{
			ARENA_X + PIXEL_SIZE * x,
			ARENA_Y + PIXEL_SIZE * y,
			PIXEL_SIZE * ENEMY_W,
			PIXEL_SIZE * ENEMY_H
		},
		m_velocity{0,0},
		m_frame(0)
	{
			switch(t){
			case alien1:
				m_frame_data = (ubyte*) g_alien1_data;
				break;
			case alien2:
				m_frame_data = (ubyte*) g_alien2_data;
				break;
			case alien3:
				m_frame_data = (ubyte*) g_alien3_data;
				break;
			}
	}

	void Alien::move(int x, int y){
		m_rect.x += x;
		m_rect.y += y;
		m_bounding_box.x += PIXEL_SIZE * x;
		m_bounding_box.y += PIXEL_SIZE * y;
	}

	void Alien::draw( SDL_Renderer* renderer ) const{

		ubyte* data = m_frame_data + (m_frame * ENEMY_H * ENEMY_W);

		SDL_Rect dest;

		int i;
		for(ubyte* c = data, i = 0; i < (ENEMY_W * ENEMY_H); ++c, ++i){
			SDL_SetRenderDrawColor(
				renderer,
				(*c=='.' ? 255 : 0),
				(*c=='.' ? 255 : 0),
				(*c=='.' ? 255 : 0),
				SDL_ALPHA_OPAQUE
			);

			dest.x = ARENA_X + PIXEL_SIZE * (m_rect.x + (int) i % ENEMY_W);
			dest.y = ARENA_Y + PIXEL_SIZE * (m_rect.y + (int) i / ENEMY_W);
			dest.w = PIXEL_SIZE;
			dest.h = PIXEL_SIZE;
			SDL_RenderFillRect( renderer, &dest );
	  }

//		SDL_SetRenderDrawColor( renderer, 255, 0, 0, SDL_ALPHA_OPAQUE );
//		SDL_RenderDrawRect( renderer, &m_bounding_box );

	}

	void Alien::update_frame(){
		m_frame = m_frame == 1 ? 0 : 1;
	}

	bool Alien::is_alive() const{
		return true;
	}

}  // namespace vdk

