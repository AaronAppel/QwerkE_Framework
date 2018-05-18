#ifndef _Math_H_
#define _Math_H_

// TODO: What is a good way of creating an interface for math
// and other utilty functions? Non engine specific files should
// be accessible but not altered to work with a global namespace.
// I can create #defines or functions that just call other functions
// but there should be a better solution. The indirection layer
// would allow users to replace certain functions with their own
// easily.

// May end up defining every math operation and allowing the definition
// to be modified for whatever function calls the user wants to use.

// divide without division
// https://www.geeksforgeeks.org/divide-two-integers-without-using-multiplication-division-mod-operator/

namespace QwerkE
{
    class Math
    {
    public:
        Math();
        ~Math();

        int AddNums(int a, int b); // test func

    private:
    };
}

#endif // !_Time_H_
