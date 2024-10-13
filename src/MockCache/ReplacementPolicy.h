#pragma once

namespace mockcache {

    enum class ReplacementPolicy {
        RANDOM,
        LRU,
        LFU,
        FIFO
    };

} // namespace mockcache
