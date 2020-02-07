#ifndef _Network_H_
#define _Network_H_

#include <string>

namespace QwerkE {

    class Network
    {
    public:
        static int test();

    private:
        Network() {}
        ~Network() {}
        static std::string m_IP;
    };

}
#endif // _Network_H_
