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

        virtual HitStatus Read(unsigned address, unsigned width) override;
        virtual HitStatus Write(unsigned address, std::uint64_t value,
                                unsigned width) override;
        virtual void LoadBlock(unsigned address) override;
        virtual void WriteBlock(unsigned address) override;

    private:
        std::vector<CacheEntry> _Data;
    };

} // namespace mockcache
