#pragma once

namespace QwerkE {

    class Renderer final
    {
    public:
        static int g_WindowWidth, g_WindowHeight; // #TODO No globals

        // TODO: Expose API for changing clear color, culling, etc
        static void Initialize(); // #TODO Review any missing shutdown logic

        static void NewFrame();

        static void DrawFont(const char* text);

    private:
        Renderer() = default;
    };

}

