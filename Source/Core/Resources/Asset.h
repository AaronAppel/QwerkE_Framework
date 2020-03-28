#ifndef _Asset_H_
#define _Asset_H_

#include "../../Headers/QwerkE_Global_Constants.h"

#include <string>

class Asset_Tag;

namespace QwerkE {

    class Asset
    {
    public:
        ~Asset();

        // Getters + Setters //
        // Getters
        std::string GetName() { return m_Name; }
        // Setters

    protected:
        Asset();

        std::string m_Name = gc_DefaultStringValue;
        Asset_Tag* m_Tag;

    };

}
#endif // !_Asset_H_
