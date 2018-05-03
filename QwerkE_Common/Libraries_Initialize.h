#ifndef _Libraries_Initialize_H_
#define _Libraries_Initialize_H_

//////////////////////////////
// Setup any libraries that have program wide states
// that need to be initialized before used
//////////////////////////////

// TODO: Use _QFail and other error messages?
// TODO: Hide loading/unloading behind load/splash screen?
bool Libs_Setup();

void Libs_TearDown();

#endif // !_Libraries_Initialize_H_
