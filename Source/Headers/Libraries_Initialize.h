#ifndef _Libraries_Initialize_H_
#define _Libraries_Initialize_H_

//////////////////////////////
// Setup any libraries that have program wide states
// and need to be initialized before use.
//////////////////////////////

// TODO: Use _QFail and other error messages?
// TODO: Hide loading/unloading behind load/splash screen?

namespace QwerkE {

    bool Libs_Setup();

    void Libs_TearDown();

}
#endif // !_Libraries_Initialize_H_
