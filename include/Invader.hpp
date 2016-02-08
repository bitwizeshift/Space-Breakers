/**
 * @file Invader.hpp
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
 * - Invader.hpp created
 */
#ifndef INVADER_HPP_
#define INVADER_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include "Entity.hpp"

namespace vdk {

	////////////////////////////////////////////////////////////////////////////
	/// @class vdk::Invader
	///
	///
	////////////////////////////////////////////////////////////////////////////
	class Invader : public Entity{

		//------------------------------------------------------------------------
		// Public Members
		//------------------------------------------------------------------------
	public:

		enum Type{ alien1, alien2, alien3 };

		//------------------------------------------------------------------------
		// Constructor / Destructor
		//------------------------------------------------------------------------
	public:

		///
		/// Constructs a Player character at the center of the screen
		///
		Invader( Type t, int x, int y );

		///
		/// Destructs this Player
		///
		virtual ~Invader(){}

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

		void update_frame();

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

		//------------------------------------------------------------------------
		// Mutators
		//------------------------------------------------------------------------
	public:

		///
		/// @brief Sets this Invader as frantic
		///
		/// @param frantic
		///
		void set_frantic( bool frantic );

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

		bool   m_frantic;
		Rect   m_rect;
		Rect   m_bounding_box;
		Point  m_velocity;
		int    m_frame;
		ubyte* m_frame_data;
	};

	//--------------------------------------------------------------------------
	// Inline Definitions
	//--------------------------------------------------------------------------

	inline Rect Invader::get_rect() const{
		return m_rect;
	}

	inline Rect Invader::get_bounding_box() const{
		return m_bounding_box;
	}

	inline Point Invader::get_velocity() const{
		return m_velocity;
	}

	inline void Invader::set_frantic( bool frantic ){
		m_frantic = frantic;
	}

	inline void Invader::set_velocity( int x, int y ){
		m_velocity.x = x;
		m_velocity.y = y;
	}

	inline Point Invader::get_location() const{
			Point loc;
			loc.x = m_rect.x;
			loc.y = m_rect.y;
			return loc;
		}


}  // namespace vdk


#endif /* INVADER_HPP_ */
