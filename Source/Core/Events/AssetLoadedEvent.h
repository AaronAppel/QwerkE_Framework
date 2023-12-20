#ifndef _AssetLoadedEvent_H_
#define _AssetLoadedEvent_H_

#include "Event.h"
#include "../../FileSystem/FileSystem.h"

namespace QwerkE {

    class AssetLoadedEvent : public Event
    {
    public:
        // TODO: Change from texture to ambiguous asset event
        AssetLoadedEvent(QImageFile asset);
        ~AssetLoadedEvent();

        QImageFile GetAsset() { return m_Asset; }

        void Process();

    private:
        QImageFile m_Asset;
    };

}
#endif // !_AssetLoadedEvent_H_
