/**
 * @file Ball.hpp
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
 * - Ball.hpp created
 */
#ifndef INCLUDE_PROJECTILE_HPP_
#define INCLUDE_PROJECTILE_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include "Entity.hpp"

namespace vdk{

	////////////////////////////////////////////////////////////////////////////
	/// @class vdk::Projectile
	///
	///
	///
	////////////////////////////////////////////////////////////////////////////
	class Projectile : public Entity{

		//------------------------------------------------------------------------
		// Constructor / Destructor
		//------------------------------------------------------------------------
	public:

		///
		/// Constructs a Ball given its starting velocity and position
		///
		/// @param position the starting position of this Ball
		/// @param velocity the starting velocity of this Ball
		///
		Projectile( Point& position, Point& velocity );

		///
		///
		///
		virtual ~Projectile(){}

		//------------------------------------------------------------------------
		// Player API
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

		//------------------------------------------------------------------------
		// Accessors
		//------------------------------------------------------------------------
	public:

		///
		/// @brief Detects whether this current Entity is still alive
		///
		/// @return @c true if Entity is alive
		///
		virtual bool is_alive() const;

		///
		/// @brief Gets the drawing rectangle of this entity
		///
		/// @return The drawing box
		///
		virtual Rect get_rect() const;

		///
		/// @brief Gets the bounding box (collision box) for this Entity
		///
		/// @return the bounding box
		///
		virtual Rect get_bounding_box() const;

		///
		/// @brief Gets the location of this Entity as an (x,y) point
		///
		/// @return the location
		///
		virtual Point get_location() const;

		///
		/// @brief Gets the velocity of this moving ball
		///
		/// @return The velocity of this Ball
		///
		virtual Point get_velocity() const;

		//------------------------------------------------------------------------
		// Mutators
		//------------------------------------------------------------------------
	public:

		///
		/// @brief Sets the velocity
		///
		/// @param velocity the velocity to set
		///
		virtual void set_velocity( int x, int y );

		//------------------------------------------------------------------------
		// Private Members
		//------------------------------------------------------------------------
	private:

		Rect   m_rect;
		Rect   m_bounding_box;
		Point  m_velocity;
	};

	inline Rect Projectile::get_rect() const{
		return m_rect;
	}

	inline Rect Projectile::get_bounding_box() const{
		return m_bounding_box;
	}

	inline Point Projectile::get_velocity() const{
		return m_velocity;
	}

	inline void Projectile::set_velocity( int x, int y ){
		m_velocity.x = x;
		m_velocity.y = y;
	}

}




#endif /* INCLUDE_PROJECTILE_HPP_ */
