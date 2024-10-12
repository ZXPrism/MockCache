#pragma once

#include "CacheBase.h"
#include "CacheEntry.h"

#include <vector>

namespace mockcache {

    class CacheDirect : public CacheBase {
    public:
        CacheDirect(std::shared_ptr<Memory> mem, unsigned blockWidthBit,
                    unsigned cacheSizeBit);
        ~CacheDirect();

        virtual HitStatus Read(unsigned address, unsigned width);
        virtual HitStatus Write(unsigned address, std::uint64_t value,
                                unsigned width);
        virtual void LoadBlock(unsigned address);
        virtual void WriteBlock(unsigned address);

    private:
        std::vector<CacheEntry> _Data;
    };

} // namespace mockcache
