#pragma once
#include "Event.h"
#include "../../FileSystem/FileSystem.h"

namespace QwerkE {

    class AssetLoadedEvent : public Event
    {
    public:
        AssetLoadedEvent(QImageFile asset);
        virtual ~AssetLoadedEvent() = default;

        QImageFile GetAsset() { return m_Asset; }

        void Process();

    private:
        QImageFile m_Asset;
    };

}
