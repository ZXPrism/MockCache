#pragma once

#include <cstdint>

namespace mockcache {

    struct HitStatus {
        int _Cost;
        bool _Miss;
        std::uint64_t _Result;
    };

} // namespace mockcache
