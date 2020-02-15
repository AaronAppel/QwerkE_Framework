#ifndef _Time_H_
#define _Time_H_

namespace QwerkE {

    class Time
    {
    public:
        Time();
        ~Time();
        
        static void NewFrame();

        static double Delta();

        static double Now();

		// TODO: This should be in window or some other engine section
        // static void SetFrameRate(float framesPerSecond);
		// static float GetFrameRate();

        // TODO: Make class static
        // TODO: Add methods: UpdateDeltaTime(), DeltaTime(), GetSystemTime(), GetFixedTimestep()

    private:
        static double m_Delta;
        static double m_LastFrame;
    };

}
#endif // !_Time_H_
