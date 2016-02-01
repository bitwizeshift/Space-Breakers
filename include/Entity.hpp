/**
 * @file Entity.hpp
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
 * - Entity.hpp created
 */
#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include "types.hpp"

#include <SDL2/SDL.h>

namespace vdk{

	///
	/// @interface vdk::Entity
	///
	/// @brief The Entity interface provides an API for all drawable and
	///        interactable resources.
	///
	/// This includes the Player, Enemy, Ball, and Wall
	///
	struct Entity{

		///
		/// @brief Purely virtual destructor to disallow construction
		///
		virtual ~Entity() = 0;

		//------------------------------------------------------------------------

		///
		/// @brief Translates this entity @p x , @p y pixels over
		///
		/// @param x the x position to move
		/// @param y the y position to move
		///
		virtual void move(int x, int y) = 0;

		///
		/// @brief Draws this entity onto the screen
		///
		/// @param renderer the renderer to draw to
		///
		virtual void draw( SDL_Renderer* renderer ) const = 0;

		//------------------------------------------------------------------------

		///
		/// @brief Detects whether this current Entity is still alive
		///
		/// @return @c true if Entity is alive
		///
		virtual bool is_alive() const = 0;

		///
		/// @brief Gets the drawing rectangle of this entity
		///
		/// @return The drawing box
		///
		virtual Rect get_rect() const = 0;

		///
		/// @brief Gets the bounding box (collision box) for this Entity
		///
		/// @return the bounding box
		///
		virtual Rect get_bounding_box() const = 0;

		///
		/// @brief Gets the location of this Entity as an (x,y) point
		///
		/// @return the location
		///
		virtual Point get_location() const = 0;

		///
		/// @brief Gets the velocity of this moving Entity
		///
		/// @return The velocity of this Entity
		///
		virtual Point get_velocity() const = 0;

		//------------------------------------------------------------------------

		///
		/// @brief Sets the velocity
		///
		/// @param velocity the velocity to set
		///
		virtual void set_velocity( int x, int y ) = 0;

	};

	inline Entity::~Entity(){}

	inline bool check_collision_sides( const Rect& lhs, const Rect& rhs ){
		const int lhs_left   = lhs.x;
		const int lhs_right  = lhs.x + lhs.w;
		const int rhs_left   = rhs.x;
		const int rhs_right  = rhs.x + rhs.w;
		if( lhs_right <= rhs_left ) return false;
		if( lhs_left >= rhs_right ) return false;

		return true;
	}

	inline bool check_collision_top_bottom( const Rect& lhs, const Rect& rhs ){
		const int lhs_top    = lhs.y;
		const int lhs_bottom = lhs.y + lhs.h;
		const int rhs_top    = rhs.y;
		const int rhs_bottom = rhs.y + rhs.h;
		if( lhs_bottom <= rhs_top ) return false;
		if( lhs_top >= rhs_bottom ) return false;

		//If none of the sides from A are outside B
		return true;
	}

	inline bool check_collision( const Rect& lhs, const Rect& rhs ){

		// left argument
		const int lhs_left   = lhs.x;
		const int lhs_top    = lhs.y;
		const int lhs_right  = lhs.x + lhs.w;
		const int lhs_bottom = lhs.y + lhs.h;

		// right argument
		const int rhs_left   = rhs.x;
		const int rhs_top    = rhs.y;
		const int rhs_right  = rhs.x + rhs.w;
		const int rhs_bottom = rhs.y + rhs.h;

		// Check collisions
		if( lhs_bottom <= rhs_top ) return false;
		if( lhs_top >= rhs_bottom ) return false;
		if( lhs_right <= rhs_left ) return false;
		if( lhs_left >= rhs_right ) return false;

		//If none of the sides from A are outside B
		return true;
	}

	inline bool check_collision_sides( const Entity* lhs, const Entity* rhs ){
		if( !lhs->is_alive() || !rhs->is_alive() ) return false;

		const Rect lrect = lhs->get_bounding_box();
		const Rect rrect = rhs->get_bounding_box();

		return check_collision_sides( lrect, rrect );
	}

	inline bool check_collision_top_bottom( const Entity* lhs, const Entity* rhs ){
		if( !lhs->is_alive() || !rhs->is_alive() ) return false;

		const Rect lrect = lhs->get_bounding_box();
		const Rect rrect = rhs->get_bounding_box();

		return check_collision_top_bottom( lrect, rrect );
	}


	inline bool check_collision( const Entity* lhs, const Entity* rhs ){
		if( !lhs->is_alive() || !rhs->is_alive() ) return false;

		const Rect lrect = lhs->get_bounding_box();
		const Rect rrect = rhs->get_bounding_box();

		return check_collision( lrect, rrect );
	}

	///
	/// Checks if @p inner is contained within @p outer
	///
	/// @param lhs
	/// @param rhs
	/// @return
	///
	inline bool check_containment( const Rect& outer, const Rect& inner ){
		// Left argument
		const int outer_left   = outer.x;
		const int outer_top    = outer.y;
		const int outer_right  = outer.x + outer.w;
		const int outer_bottom = outer.y + outer.h;

		// right argument
		const int inner_left   = inner.x;
		const int inner_top    = inner.y;
		const int inner_right  = inner.x + inner.w;
		const int inner_bottom = inner.y + inner.h;

		return outer_left   < inner_right  &&
		       outer_right  > inner_left   &&
		       outer_top    < inner_bottom &&
		       outer_bottom > inner_top;
	}

} // vdk



#endif /* ENTITY_HPP_ */
