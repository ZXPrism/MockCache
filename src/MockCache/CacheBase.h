#pragma once

#include "HitStatus.h"
#include "Memory.h"

#include <memory>

namespace mockcache {

    constexpr int COST_HIT = 5;
    constexpr int COST_MISS = 50;

    class CacheBase {
    public:
        CacheBase(std::shared_ptr<Memory> mem, unsigned blockWidthBit,
                  unsigned cacheSizeBit);
        virtual ~CacheBase() = default;

        virtual HitStatus Read(unsigned address, unsigned width) = 0;
        virtual HitStatus Write(unsigned address, std::uint64_t value,
                                unsigned width) = 0;
        virtual void LoadBlock(unsigned address) = 0;
        virtual void WriteBlock(unsigned address) = 0;

    protected:
        void _PrintStatus(unsigned status, unsigned cacheIndex,
                          unsigned address);

    protected:
        std::shared_ptr<Memory> _Mem;
        unsigned _BlockWidthBit;
        unsigned _CacheSizeBit;
        unsigned _OffsetMask;
        unsigned _CacheIndexMask;
    };

} // namespace mockcache
