#include "Memory.h"

#include <format>
#include <iostream>
#include <stdexcept>

namespace mockcache {

    Memory::Memory(unsigned nBytes) : _MemSizeBytes(nBytes) {
        _MemData = new std::uint8_t[nBytes];
    }

    Memory::~Memory() {
        delete[] _MemData;
    }

    void Memory::_CheckAddr(unsigned address, unsigned width) const {
        if (address + width - 1 >= _MemSizeBytes) {
            throw std::out_of_range(std::format(
                "Memory address {} is out of range! [Memory Size: {}]", address,
                _MemSizeBytes));
        }
    }

    std::uint8_t Memory::Read8(unsigned address) const {
        _CheckAddr(address, 1);
        return _MemData[address];
    }

    std::uint16_t Memory::Read16(unsigned address) const {
        _CheckAddr(address, 2);
        return *reinterpret_cast<std::uint16_t *>(&_MemData[address]);
    }

    std::uint32_t Memory::Read32(unsigned address) const {
        _CheckAddr(address, 4);
        return *reinterpret_cast<std::uint32_t *>(&_MemData[address]);
    }

    std::uint64_t Memory::Read64(unsigned address) const {
        _CheckAddr(address, 8);
        return *reinterpret_cast<std::uint64_t *>(&_MemData[address]);
    }

    void Memory::Write8(unsigned address, std::uint8_t value) {
        _CheckAddr(address, 1);
        _MemData[address] = value;
    }

    void Memory::Write16(unsigned address, std::uint16_t value) {
        _CheckAddr(address, 2);
        *reinterpret_cast<std::uint16_t *>(&_MemData[address]) = value;
    }

    void Memory::Write32(unsigned address, std::uint32_t value) {
        _CheckAddr(address, 4);
        *reinterpret_cast<std::uint32_t *>(&_MemData[address]) = value;
    }

    void Memory::Write64(unsigned address, std::uint64_t value) {
        _CheckAddr(address, 8);
        *reinterpret_cast<std::uint64_t *>(&_MemData[address]) = value;
    }

    void Memory::CopyIn(std::uint8_t *src, unsigned destAddress, int nBytes) {
        _CheckAddr(destAddress + nBytes - 1, 1);
        std::memcpy(_MemData + destAddress, src, nBytes);
    }

    void Memory::CopyOut(unsigned srcAddress, std::uint8_t *dest, int nBytes) {
        _CheckAddr(srcAddress + nBytes - 1, 1);
        std::memcpy(dest, _MemData + srcAddress, nBytes);
    }

} // namespace mockcache
