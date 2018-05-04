#ifndef _NetworkManager_H_
#define _NetworkManager_H_

#include <string>

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

	int test();

private:
	std::string m_IP = "172.18.38.65";
};

#endif // !_NetworkManager_H_
