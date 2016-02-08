/**
 * @file InvaderGroup.hpp
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
 * - InvaderGroup.hpp created
 */
#ifndef ALIENGROUP_HPP_
#define ALIENGROUP_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <list>

#include "Entity.hpp"
#include <Invader.hpp>
#include <Projectile.hpp>

namespace vdk {

	class InvaderGroup{

		//-----------------------------------------------------------------------------
		// Public Members
		//-----------------------------------------------------------------------------
	public:

		typedef std::list<Invader>        invader_column;
		typedef std::list<invader_column> invader_collection;

		//-----------------------------------------------------------------------------
		// Constructors
		//-----------------------------------------------------------------------------
	public:

		///
		/// @brief Constructs an InvaderGroup with the specified number of ranks
		///
		/// @param ranks
		///
		InvaderGroup( int ranks );

		///
		/// Destructs the InvaderGroup
		///
		virtual ~InvaderGroup(){}

		//------------------------------------------------------------------------
		// InvaderGroup API
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

		///
		/// Check collisions with projectiles. If a collision occurs, the
		/// invader at that position is removed from the InvaderGroup and
		/// the method returns true
		///
		/// @param entity the projectile to check collisions with
		/// @return true if there is a collision
		///
		bool check_collision( const Projectile* entity );

		///
		/// Resets the InvaderGroup with the specified number of ranks
		///
		/// @param ranks the number of ranks to reset the group to
		///
		void reset(int ranks);

		Rect get_bounding_box() const;

		Point get_velocity() const;

		void set_velocity( int x, int y );

		Projectile shoot_projectile( int speed );

		bool is_alive() const;

		size_t size() const;

		size_t max_size() const;

		//-----------------------------------------------------------------------------
		// Private Methods
		//-----------------------------------------------------------------------------
	private:

		///
		/// Updates the size of the bounding box of this InvaderGroup
		///
		void update_size();

		//-----------------------------------------------------------------------------
		// Private Member
		//-----------------------------------------------------------------------------
	private:

		invader_collection m_invaders;
		size_t m_size;
		size_t m_max_size;
		Rect m_bounding_box;
		Point m_velocity;
	};

	inline Point InvaderGroup::get_velocity() const{
		return m_velocity;
	}

	inline Rect InvaderGroup::get_bounding_box() const{
		return m_bounding_box;
	}




}  // namespace vdk



#endif /* ALIENGROUP_HPP_ */
