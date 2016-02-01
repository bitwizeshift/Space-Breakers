/**
 * @file Timer.hpp
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
 * - Timer.hpp created
 */
#ifndef INCLUDE_TIMER_HPP_
#define INCLUDE_TIMER_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

namespace vdk{

	////////////////////////////////////////////////////////////////////////////
	/// @class vdk::Timer
	///
	///
	////////////////////////////////////////////////////////////////////////////
	class Timer{

		//------------------------------------------------------------------------
		// Constructor / Destructor
		//------------------------------------------------------------------------
	public:

		Timer();

		//------------------------------------------------------------------------
		// Timer APi
		//------------------------------------------------------------------------
	public:

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		int get_ticks();

		//Checks the status of the timer
		bool is_started();
		bool is_paused();

		//------------------------------------------------------------------------
		// Private Members
		//------------------------------------------------------------------------
	private:
		//The clock time when the timer started
		int m_start_ticks;

		//The ticks stored when the timer was paused
		int m_paused_ticks;

		//The timer status
		bool m_is_paused;
		bool m_is_started;


	};
}

#endif /* INCLUDE_TIMER_HPP_ */
