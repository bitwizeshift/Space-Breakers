/**
 * @file Timer.cpp
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
 * - Timer.cpp created
 */

#include "Timer.hpp"
#include <SDL2/SDL_timer.h>

namespace vdk{

	Timer::Timer(){
		//Initialize the variables
		m_start_ticks = 0;
		m_paused_ticks = 0;
		m_is_paused = false;
		m_is_started = false;
	}

	void Timer::start(){
		//Start the timer
		m_is_started = true;

		//Unpause the timer
		m_is_paused = false;

		//Get the current clock time
		m_start_ticks = SDL_GetTicks();
	}

	void Timer::stop(){
		//Stop the timer
		m_is_started = false;

		//Unpause the timer
		m_is_paused = false;
	}

	void Timer::pause(){
		//If the timer is running and isn't already paused
		if( ( m_is_started == true ) && ( m_is_paused == false ) ){
				//Pause the timer
				m_is_paused = true;

				//Calculate the paused ticks
				m_paused_ticks = SDL_GetTicks() - m_start_ticks;
		}
	}

	void Timer::unpause(){
		//If the timer is paused
		if( m_is_paused == true ){
			//Unpause the timer
			m_is_paused = false;

			//Reset the starting ticks
			m_start_ticks = SDL_GetTicks() - m_paused_ticks;

			//Reset the paused ticks
			m_paused_ticks = 0;
		}
	}

	int Timer::get_ticks(){
		//If the timer is running
		if( m_is_started == true ){
			//If the timer is paused
			if( m_is_paused == true ){
				//Return the number of ticks when the timer was paused
				return m_paused_ticks;
			}else{
				//Return the current time minus the start time
				return SDL_GetTicks() - m_start_ticks;
			}
		}

		//If the timer isn't running
		return 0;
	}

	bool Timer::is_started(){
		return m_is_started;
	}

	bool Timer::is_paused(){
		return m_is_paused;
	}

} // namespace vdk
