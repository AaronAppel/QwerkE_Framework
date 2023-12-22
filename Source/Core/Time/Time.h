#pragma once

namespace QwerkE {

    class Time
    {
    public:

        static void NewFrame();

        static inline double Delta() { return m_Delta; };

        static double Now();

		// TODO: This should be in window or some other engine section
        // static void SetFrameRate(float framesPerSecond);
		// static float GetFrameRate();

        // TODO: Make class static
        // TODO: Add methods: UpdateDeltaTime(), DeltaTime(), GetSystemTime(), GetFixedTimestep()

    private:
        Time() {}
        ~Time() {}

        static double m_Delta;
        static double m_CurrentFrame;
        static double m_LastFrame;
    };

}

