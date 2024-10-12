#pragma once

#include <cstdint>

namespace mockcache {

    struct CacheEntry {
        bool _Valid;
        bool _Dirty;
        unsigned _Tag;
        std::uint8_t *_Block;
    };

} // namespace mockcache
