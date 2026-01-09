#pragma once

#include <functional>

namespace ssb::core
{
	using PlaybackStateChangeCallback = std::function<void(bool)>;
	using PlaybackValueChangeCallback = std::function<void(int, int)>;
	using PlaybackFinishedCallback = std::function<void()>;

	class PlayState
	{
	public:
		bool playing() const;
		bool frozen() const;
		void play();
		void pause();
		void trigger();
		void freeze(); // for input
		void unfreeze(); // for input
		void update();

		void setDuration(unsigned int msecs);
		void setPlaybackPosition(unsigned int msecs);
		void skipBySeconds(int secs);

		void addPlaybackStateChangeCallback(PlaybackStateChangeCallback stateCallback);
		void addPlaybackValueChangeCallback(PlaybackValueChangeCallback valueCallback);
		void addPlaybackFinishedCallback(PlaybackFinishedCallback finishedCallback);

	private:
		void setPlayback(bool value);

		unsigned int m_currentTime = 0;
		unsigned int m_duration = 0;
		bool m_playing = false;
		bool m_frozen = false;

		PlaybackStateChangeCallback m_stateCallback;
		PlaybackValueChangeCallback m_valueCallback;
		PlaybackFinishedCallback m_finishedCallback;
	};

}