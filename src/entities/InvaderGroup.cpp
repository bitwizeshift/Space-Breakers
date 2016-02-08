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

#include <InvaderGroup.hpp>
#include "config.hpp"
#include <cstdlib>
#include <vector>
#include <cmath>

namespace vdk {

	InvaderGroup::InvaderGroup( int ranks )
	{
		m_velocity.x = 3;
		m_velocity.y = 0;
		reset(ranks);
	}

	//--------------------------------------------------------------------------

	void InvaderGroup::reset( int ranks ){

		m_invaders.clear();
		ranks = std::min(ranks,5); // Max of 5 ranks

		m_size     = ENEMIES_PER_LINE * ranks;
		m_max_size = m_size;
		for( int i = 0; i < ENEMIES_PER_LINE; ++i ){
			invader_column column;
			for( int rank = 0; rank < ranks; ++rank ){
				Invader::Type t;
				switch(rank % 3){
				case 0:
					t = Invader::alien1;
					break;
				case 1:
					t = Invader::alien2;
					break;
				default:
					t = Invader::alien3;
					break;
				}

				int x = (i    * BASE_SIZE) + ENEMY_MARGIN + ARENA_SIZE_W/2 - (ENEMIES_PER_LINE * BASE_SIZE/2);
				int y = (rank * BASE_SIZE) + ENEMY_MARGIN + ARENA_PADDING;

				Invader alien( t, x, y );
				column.push_back(alien);

			}
			m_invaders.push_back(column);
		}
		update_size();
	}

	void InvaderGroup::move( int x, int y ){

		m_bounding_box.x += x * PIXEL_SIZE;
		m_bounding_box.y += y * PIXEL_SIZE;
		for( invader_column& column : m_invaders ){
			for( Invader& alien : column ){
				alien.move( x, y );
				alien.update_frame();
			}
		}
	}

	void InvaderGroup::draw( SDL_Renderer* renderer ) const{
		// Draw all aliens
		for( const invader_column& column : m_invaders ){
			for( const Invader& alien : column ){
				alien.draw( renderer );
			}
		}
#ifdef DEBUG
		SDL_SetRenderDrawColor( renderer, 255, 0, 0, SDL_ALPHA_OPAQUE );
		SDL_RenderDrawRect( renderer, &m_bounding_box );
#endif
	}

	bool InvaderGroup::check_collision( const Projectile* entity ){

		bool collided = false;
		invader_collection::iterator col;
		invader_column::iterator it;

		invader_column::iterator to_delete;

		for( col =  m_invaders.begin(); col != m_invaders.end() && !collided; ++col ){
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

		// If down to the last invader, set it to frantic mode.
		if( m_size == 1 ){
			for( invader_column& column : m_invaders ){
				for( Invader& invader : column ){
					invader.set_frantic(true);
				}
			}
		}
		return collided;
	}

	void InvaderGroup::update_size(){
		m_bounding_box.x = m_bounding_box.y = 0xfffffff;
		m_bounding_box.w = m_bounding_box.h = 0;
		for( const invader_column& column : m_invaders ){
			for( const Invader& alien : column ){
				Rect b = alien.get_bounding_box();
				if( b.x < m_bounding_box.x ){
					m_bounding_box.x = b.x;
				}
				if( b.y < m_bounding_box.y ){
					m_bounding_box.y = b.y;
				}
				if( (b.x + b.w - m_bounding_box.x) > m_bounding_box.w ){
					m_bounding_box.w = b.x + b.w - m_bounding_box.x;
				}
				if( (b.y + b.h - m_bounding_box.y) > m_bounding_box.h ){
					m_bounding_box.h = b.y + b.h - m_bounding_box.y;
				}
			}
		}
	}

	Projectile InvaderGroup::shoot_projectile( int speed ){
		// Calculate the x and y components of the velocity.
		// The total must equal x^2 + y^2 = speed^2
		int x_speed = (rand() % (m_velocity.x)) - 0.5*m_velocity.x;
		int y_speed = std::sqrt( (speed*speed) - (x_speed*x_speed) );

		// Gather all locations of valid places to fire from
		std::vector<Rect> locations;
		for( const invader_column& column : m_invaders ){
			if( !column.empty() ){
				Invader invader = column.back();
				locations.push_back( invader.get_bounding_box() );
			}
		}
		int shooter = rand() % locations.size();
		Point velocity = {x_speed, y_speed};
		Point position = {locations[shooter].x, locations[shooter].y + PIXEL_SIZE * ENEMY_H};
		Projectile result(position, velocity);

		return result;
	}

	bool InvaderGroup::is_alive() const{
		return m_size != 0;
	}

	size_t InvaderGroup::size() const{
		return m_size;
	}

	size_t InvaderGroup::max_size() const{
		return m_max_size;
	}


	void InvaderGroup::set_velocity( int x, int y ){
		m_velocity.x = x;
		m_velocity.y = y;
	}


}  // namespace vdk

