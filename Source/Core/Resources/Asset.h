#pragma once

#include <string>

#include "../../Headers/QwerkE_Global_Constants.h"

namespace QwerkE {

    class Asset_Tag;

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
