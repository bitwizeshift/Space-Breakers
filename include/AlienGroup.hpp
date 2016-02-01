/**
 * @file AlienGroup.hpp
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
 * - AlienGroup.hpp created
 */
#ifndef ALIENGROUP_HPP_
#define ALIENGROUP_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <list>

#include "Entity.hpp"
#include "Alien.hpp"
#include "Ball.hpp"

namespace vdk {

	class AlienGroup{

		//-----------------------------------------------------------------------------
		// Public Members
		//-----------------------------------------------------------------------------
	public:

		typedef std::list<Alien>        alien_column;
		typedef std::list<alien_column> alien_collection;

		//-----------------------------------------------------------------------------
		// Constructors
		//-----------------------------------------------------------------------------
	public:

		AlienGroup( int ranks );

		virtual ~AlienGroup(){}

		//------------------------------------------------------------------------
		// AlienGroup API
		//------------------------------------------------------------------------
	public:

		///
		/// @brief Translates this entity @p x , @p y pixels over
		///
		/// @param x the x position to move
		/// @param y the y position to move
		///
		virtual void move(int x, int y);

		///
		/// @brief Draws this entity onto the screen
		///
		/// @param renderer the renderer to draw to
		///
		virtual void draw( SDL_Renderer* renderer ) const;

		bool check_collision( const Ball* entity );

		void reset(int ranks);

		Rect get_bounding_box() const;

		Point get_velocity() const;

		void set_velocity( int x, int y );

		Ball shoot_projectile();

		bool is_alive() const;

		size_t size() const;

		size_t max_size() const;

		//-----------------------------------------------------------------------------
		// Private Methods
		//-----------------------------------------------------------------------------
	private:
		void update_size();

		//-----------------------------------------------------------------------------
		// Private Member
		//-----------------------------------------------------------------------------
	private:

		alien_collection m_aliens;
		size_t m_size;
		size_t m_max_size;
		Rect m_bounding_box;
		Point m_velocity;
	};

	inline Point AlienGroup::get_velocity() const{
		return m_velocity;
	}

	inline Rect AlienGroup::get_bounding_box() const{
		return m_bounding_box;
	}




}  // namespace vdk



#endif /* ALIENGROUP_HPP_ */
