#pragma once

#include <cstdint>

namespace mockcache {

    class Memory {
    public:
        explicit Memory(unsigned nBytes);
        ~Memory();

        std::uint8_t Read8(unsigned address) const;
        std::uint16_t Read16(unsigned address) const;
        std::uint32_t Read32(unsigned address) const;
        std::uint64_t Read64(unsigned address) const;

        void Write8(unsigned address, std::uint8_t value);
        void Write16(unsigned address, std::uint16_t value);
        void Write32(unsigned address, std::uint32_t value);
        void Write64(unsigned address, std::uint64_t value);

        void CopyIn(std::uint8_t *src, unsigned destAddress, int nBytes);
        void CopyOut(unsigned srcAddress, std::uint8_t *dest, int nBytes);

    private:
        void _CheckAddr(unsigned address, unsigned width) const;

    private:
        std::uint8_t *_MemData;
        unsigned _MemSizeBytes;
    };

} // namespace mockcache
