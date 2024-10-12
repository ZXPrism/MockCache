#include "CacheBase.h"

#include <format>
#include <iostream>
#include <stdexcept>

namespace mockcache {

    CacheBase::CacheBase(std::shared_ptr<Memory> mem, unsigned blockWidthBit,
                         unsigned cacheSizeBit)
        : _Mem(mem), _BlockWidthBit(blockWidthBit),
          _CacheSizeBit(cacheSizeBit) {
        if (blockWidthBit == 0 || cacheSizeBit == 0 ||
            blockWidthBit + cacheSizeBit > 32) {
            throw std::invalid_argument(
                std::format("Invalid cache settings: blockWidthBit {} and "
                            "cacheSizeBit {}!",
                            blockWidthBit, cacheSizeBit));
        }
        _OffsetMask = (1U << _BlockWidthBit) - 1;
        _CacheIndexMask = (1U << _CacheSizeBit) - 1;
    }

    void CacheBase::_PrintStatus(unsigned status, unsigned cacheIndex,
                                 unsigned address) {
        // 0: hit, 1: miss, 2: replace
        // if (status == 0) {
        //     std::cout << "\033[32m[HIT]";
        // } else if (status == 1) {
        //     std::cout << "\033[31m[MISS]";
        // } else {
        //     std::cout << "\033[35m[REPLACE]";
        // }
        // std::cout << std::format("\033[0m Block {} with Address {}\n",
        //                          cacheIndex, address);
    }

} // namespace mockcache
