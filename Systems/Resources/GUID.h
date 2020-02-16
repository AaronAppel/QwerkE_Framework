#ifndef _GUID_H_
#define _GUID_H_

static int g_UniqueID = 0; // Put in a .cpp?
static int UniqueID() { return g_UniqueID++; };

#endif //_GUID_H_