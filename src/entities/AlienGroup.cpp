/**
 * @file AlienGroup.cpp
 *
 * @todo Add description
 *
 * @author Matthew Rodusek (matthew.rodusek@gmail.com)
 * @date   Jan 31, 2016
 *
 */

/*
 * Change Log:
 *
 * Jan 31, 2016: 
 * - AlienGroup.cpp created
 */

#include "config.hpp"
#include "AlienGroup.hpp"

#include <cstdlib>
#include <vector>

namespace vdk {

	AlienGroup::AlienGroup( int ranks )
	{
		m_velocity.x = 3;
		m_velocity.y = 0;
		reset(ranks);
	}

	//--------------------------------------------------------------------------

	void AlienGroup::reset( int ranks ){

		m_aliens.clear();
		ranks = std::min(ranks,5); // Max of 5 ranks

		m_size     = ENEMIES_PER_LINE * ranks;
		m_max_size = m_size;
		for( int i = 0; i < ENEMIES_PER_LINE; ++i ){
			alien_column column;
			for( int rank = 0; rank < ranks; ++rank ){
				Alien::Type t;
				switch(rank % 3){
				case 0:
					t = Alien::alien1;
					break;
				case 1:
					t = Alien::alien2;
					break;
				default:
					t = Alien::alien3;
					break;
				}

				int x = (i    * BASE_SIZE) + ENEMY_MARGIN + ARENA_SIZE_W/2 - (ENEMIES_PER_LINE * BASE_SIZE/2);
				int y = (rank * BASE_SIZE) + ENEMY_MARGIN + ARENA_PADDING;

				Alien alien( t, x, y );
				column.push_back(alien);

			}
			m_aliens.push_back(column);
		}
		update_size();
	}

	void AlienGroup::move( int x, int y ){

		m_bounding_box.x += x * PIXEL_SIZE;
		m_bounding_box.y += y * PIXEL_SIZE;
		for( alien_column& column : m_aliens ){
			for( Alien& alien : column ){
				alien.move( x, y );
				alien.update_frame();
			}
		}
	}

	void AlienGroup::draw( SDL_Renderer* renderer ) const{
		// Draw all aliens
		for( const alien_column& column : m_aliens ){
			for( const Alien& alien : column ){
				alien.draw( renderer );
			}
		}
//		SDL_SetRenderDrawColor( renderer, 255, 0, 0, SDL_ALPHA_OPAQUE );
//		SDL_RenderDrawRect( renderer, &m_bounding_box );
	}

	bool AlienGroup::check_collision( const Ball* entity ){

		bool collided = false;
		alien_collection::iterator col;
		alien_column::iterator it;

		alien_column::iterator to_delete;

		for( col =  m_aliens.begin(); col != m_aliens.end() && !collided; ++col ){
			for( it = col->begin(); it != col->end() && !collided; ++it ){
				if( vdk::check_collision( entity->get_bounding_box(), it->get_bounding_box() ) ){
					collided = true;
					to_delete = it;
				}
			}
		}
		if( collided ){
			col->erase(to_delete);
			--m_size;
			update_size();
		}

		return collided;
	}

	void AlienGroup::update_size(){
		m_bounding_box.x = m_bounding_box.y = 0xfffffff;
		m_bounding_box.w = m_bounding_box.h = 0;
		for( const alien_column& column : m_aliens ){
			for( const Alien& alien : column ){
				Rect b = alien.get_bounding_box();
				if( b.x < m_bounding_box.x ){
					m_bounding_box.x = b.x;
				}
				if( b.y < m_bounding_box.y ){
					m_bounding_box.y = b.y;
				}
				if( (b.x + b.w) > m_bounding_box.w ){
					m_bounding_box.w = b.x + b.w - m_bounding_box.x;
				}
				if( (b.y + b.h) > m_bounding_box.h ){
					m_bounding_box.h = b.y + b.h - m_bounding_box.y;
				}
			}
		}
	}

	Ball AlienGroup::shoot_projectile(){
		int x_speed = rand() % m_velocity.x;
		int y_speed = 3 + rand() % 3;
		std::vector<Rect> locations;

		for( const alien_column& column : m_aliens ){
			if( !column.empty() ){
				locations.push_back( column.back().get_bounding_box() );
			}
		}
		int shooter = rand() % locations.size();
		Point speed = {x_speed, y_speed};
		Point loc   = {locations[shooter].x, locations[shooter].y + PIXEL_SIZE * ENEMY_H};
		Ball result(loc, speed);

		return result;
	}

	bool AlienGroup::is_alive() const{
		return m_size != 0;
	}

	size_t AlienGroup::size() const{
		return m_size;
	}

	size_t AlienGroup::max_size() const{
		return m_max_size;
	}


	void AlienGroup::set_velocity( int x, int y ){
		m_velocity.x = x;
		m_velocity.y = y;
	}


}  // namespace vdk

