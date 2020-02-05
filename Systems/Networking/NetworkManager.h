#ifndef _NetworkManager_H_
#define _NetworkManager_H_

#include <string>

namespace QwerkE {

    class NetworkManager
    {
    public:
        NetworkManager();
        ~NetworkManager();

        int test();

    private:
        std::string m_IP = "127.0.0.1";
    };

}
#endif // !_NetworkManager_H_
