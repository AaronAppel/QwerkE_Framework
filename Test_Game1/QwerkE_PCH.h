#ifndef _QwerkE_PCH_
#define _QwerkE_PCH_

/////////////////////////////////////////////////
// include STATIC code that does not change often
/////////////////////////////////////////////////

#include "../QwerkE_Framework/QwerkE_Defines.h"
#include "../QwerkE_Framework/QwerkE_Platform.h"

// TODO: Move pragma warnings and use pop warnings
//#pragma warning(disable : 4996) // old sprintf warnings in RakNet
//#define _CRT_SECURE_NO_WARNINGS // old sprintf warnings in RakNet
//#define _CRT_SECURE_NO_DEPRECATE // old sprintf warnings in RakNet
//#define _WINSOCK_DEPRECATED_NO_WARNINGS // old warnings in RakNet

// standard libraries
// map, vector, string, etc
// TODO: Is including this here a good idea?
// Does it save compile time?
#include <string>
#include <stdio.h>
#include <map>
#include <vector>

// constants, enums
#include "../QwerkE_Framework/Global_Constants.h"
#include "../QwerkE_Framework/QwerkE_Enums.h"

// containers

// libraries
#include "../QwerkE_Common/Libraries_Include.h"

/////////////////////////////////////////////////
// include ENGINE code temporarily for faster build times
/////////////////////////////////////////////////
#include "Additional_Includes.h"


#endif // !_QwerkE_PCH_
