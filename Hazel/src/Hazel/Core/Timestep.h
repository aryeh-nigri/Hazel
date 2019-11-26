#pragma once

namespace Hazel {

	// Timesteps are in seconds by default
	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: m_Time(time) {}

		inline operator float() const { return m_Time; }

		inline float GetSeconds() const { return m_Time; }
		inline float GetMilliseconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};

}