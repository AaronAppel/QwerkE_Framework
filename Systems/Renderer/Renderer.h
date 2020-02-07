#ifndef _Renderer_H_
#define _Renderer_H_

namespace QwerkE {

    class Renderer
    {
    public:
        static void DrawFont(const char* text);

    private:
        Renderer();
        ~Renderer();
    };

}
#endif // !_Renderer_H_
