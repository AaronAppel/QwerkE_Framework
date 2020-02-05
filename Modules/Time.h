#ifndef _Time_H_
#define _Time_H_

namespace QwerkE {

    class Time
    {
    public:
        Time();
        ~Time();

        static void SetDeltatime(double* deltaTime);
        static double GetDeltaTime();

		// TODO: This should be in window or some other engine section
        static void SetFrameRate(float* framesPerSecond);
		static float GetFrameRate();

        // TODO: Make class static
        // TODO: Add methods: UpdateDeltaTime(), DeltaTime(), GetSystemTime(), GetFixedTimestep()

    private:
        static const double* m_DeltaTime;
		static const float* m_FPS;
    };

}
#endif // !_Time_H_
