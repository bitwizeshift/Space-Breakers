/**
 * @file Player.hpp
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
 * - Player.hpp created
 */
#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include "Entity.hpp"

namespace vdk{

	////////////////////////////////////////////////////////////////////////////
	/// @class vdk::Player
	///
	///
	////////////////////////////////////////////////////////////////////////////
	class Player : public Entity{

		//------------------------------------------------------------------------
		// Constructor / Destructor
		//------------------------------------------------------------------------
	public:

		///
		/// Constructs a Player character at the center of the screen
		///
		Player( int health );

		///
		/// Destructs this Player
		///
		virtual ~Player();

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

		///
		///
		/// @param health the health to set
		///
		void set_health( int health );

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
		/// @brief Gets the velocity of this moving Player
		///
		/// @return The velocity of this Player
		///
		virtual Point get_velocity() const;

		int get_health() const;

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

		int m_health;
		Rect m_rect;
		Rect m_bounding_box;
		Point m_velocity;
	};

	//--------------------------------------------------------------------------
	// Inline Definitions
	//--------------------------------------------------------------------------

	inline Rect Player::get_rect() const{
		return m_rect;
	}

	inline Rect Player::get_bounding_box() const{
		return m_bounding_box;
	}

	inline Point Player::get_velocity() const{
		return m_velocity;
	}

	inline void Player::set_velocity( int x, int y ){
		m_velocity.x = x;
		m_velocity.y = y;
	}

	inline int Player::get_health() const{
		return m_health;
	}

} // namespace vdk

#endif /* PLAYER_HPP_ */
