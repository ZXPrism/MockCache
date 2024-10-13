#pragma once

#include <cstdint>

namespace mockcache {

    enum class Status {
        HIT,
        MISS,
        REPLACE
    };

    struct HitStatus {
        int _Cost = 0;
        bool _Miss = false;
        std::uint64_t _Result = 0;
    };

} // namespace mockcache
