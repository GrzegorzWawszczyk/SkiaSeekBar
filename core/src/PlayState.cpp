#include "PlayState.hpp"

#include <algorithm>

#include <SDL3/SDL.h>

namespace ssb::core
{
	bool PlayState::playing() const
	{
		return m_playing;
	}

	bool PlayState::frozen() const
	{
		return m_frozen;
	}

	void PlayState::play()
	{
		setPlayback(true);
	}

	void PlayState::pause()
	{
		setPlayback(false);
	}

	void PlayState::trigger()
	{
		setPlayback(!m_playing);
	}

	void PlayState::freeze()
	{
		m_frozen = true;
	}

	void PlayState::unfreeze()
	{
		m_frozen = false;
	}

	void PlayState::update()
	{
		static uint64_t lastTime = SDL_GetTicks();

		const auto now = SDL_GetTicks();
		const auto dt = (now - lastTime);
		lastTime = now;


		if (m_duration > 0 && m_playing && !m_frozen)
		{
			m_currentTime += dt;
			m_currentTime = std::min(m_currentTime, m_duration);

			if (m_valueCallback)
			{
				m_valueCallback(m_currentTime, m_duration);
			}

			if (m_currentTime == m_duration)
			{
				setPlayback(false);
				if (m_finishedCallback)
				{
					m_finishedCallback();
				}
			}
		}
	}

	void PlayState::setDuration(unsigned int msecs)
	{
		m_duration = msecs;
		m_currentTime = 0;
		if (m_valueCallback)
		{
			m_valueCallback(m_currentTime, m_duration);
		}
	}

	void PlayState::setPlaybackPosition(unsigned int msecs)
	{
		m_currentTime = std::clamp(msecs, 0u, m_duration);
		if (m_duration > 0 && m_valueCallback)
		{
			m_valueCallback(m_currentTime, m_duration);
		}
	}

	void PlayState::skipBySeconds(int secs)
	{
		auto newTime = static_cast<int>(m_currentTime) + static_cast<int>(secs) * 1000;
		newTime = std::clamp(newTime, 0, static_cast<int>(m_duration));
		setPlaybackPosition(static_cast<unsigned int>(newTime));
	}

	void PlayState::addPlaybackStateChangeCallback(PlaybackStateChangeCallback stateCallback)
	{
		m_stateCallback = stateCallback;
	}

	void PlayState::addPlaybackValueChangeCallback(PlaybackValueChangeCallback valueCallback)
	{
		m_valueCallback = valueCallback;
	}

	void PlayState::addPlaybackFinishedCallback(PlaybackFinishedCallback finishedCallback)
	{
		m_finishedCallback = finishedCallback;
	}

	void PlayState::setPlayback(bool value)
	{
		if (m_duration == 0)
		{
			return;
		}

		m_playing = value;
		if (m_stateCallback)
		{
			m_stateCallback(value);
		}
	}
}
