#ifndef _Renderer_H_
#define _Renderer_H_

namespace QwerkE {

    class Renderer
    {
    public:
        static int g_WindowWidth, g_WindowHeight; // #TODO No globals

        // TODO: Expose API for changing clear color, culling, etc
        static void Initialize();

        static void NewFrame();

        static void DrawFont(const char* text);

    private:
        Renderer();
        ~Renderer();
    };

}
#endif // !_Renderer_H_
