#include "CacheDirect.h"

#include <format>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace mockcache {

    CacheDirect::CacheDirect(std::shared_ptr<Memory> mem,
                             unsigned blockWidthBit, unsigned cacheEntrySizeBit)
        : CacheBase(mem, blockWidthBit, cacheEntrySizeBit) {

        int nBlockWidth = 1 << blockWidthBit;
        std::size_t cacheEntrySize = static_cast<std::size_t>(1)
                                     << cacheEntrySizeBit;
        _CacheEntries.resize(cacheEntrySize);
        _CacheBlocks = new std::uint8_t[cacheEntrySize * nBlockWidth];

        for (int i = 0; auto &entry : _CacheEntries) {
            entry._Valid = false;
            entry._Dirty = false;
            entry._Tag = 0;
            entry._Block = _CacheBlocks + i * nBlockWidth;
            ++i;
        }
    }

    CacheDirect::~CacheDirect() {
        delete[] _CacheBlocks;
    }

    HitStatus CacheDirect::Read(unsigned address, unsigned width) {
        HitStatus status;

        unsigned prevByteNo = 0;
        unsigned prevCacheIndex = address >> _BlockWidthBit & _CacheIndexMask;
        unsigned prevTag = address >> (_BlockWidthBit + _CacheSizeBit);

        for (unsigned i = 0; i <= width; i++) {
            unsigned addr = address + i;
            unsigned tag = addr >> (_BlockWidthBit + _CacheSizeBit);
            unsigned cacheIndex = addr >> _BlockWidthBit & _CacheIndexMask;

            if (cacheIndex != prevCacheIndex || i == width) {
                status._Cost += COST_HIT;

                auto &entry = _CacheEntries[prevCacheIndex];
                if (entry._Valid && entry._Tag == prevTag) {
                } else {
                    if (entry._Valid && entry._Dirty) {
                        status._Cost += COST_MISS * _BlockWidthBit;
                        WriteBlock(address + prevByteNo);
                    }

                    status._Miss = true;
                    status._Cost += COST_MISS * _BlockWidthBit;

                    LoadBlock(address + prevByteNo);
                }

                for (unsigned j = prevByteNo; j < i; j++) {
                    unsigned addr = address + j;
                    status._Result |= static_cast<std::uint64_t>(
                                          entry._Block[addr & _OffsetMask])
                                      << (j * 8);
                }

                prevCacheIndex = cacheIndex;
                prevByteNo = i;
                prevTag = tag;
            }
        }

        return status;
    }

    HitStatus CacheDirect::Write(unsigned address, std::uint64_t value,
                                 unsigned width) {
        HitStatus status;

        unsigned prevByteNo = 0;
        unsigned prevCacheIndex = address >> _BlockWidthBit & _CacheIndexMask;
        unsigned prevTag = address >> (_BlockWidthBit + _CacheSizeBit);

        for (unsigned i = 0; i <= width; i++) {
            unsigned addr = address + i;
            unsigned tag = addr >> (_BlockWidthBit + _CacheSizeBit);
            unsigned cacheIndex = addr >> _BlockWidthBit & _CacheIndexMask;

            if (cacheIndex != prevCacheIndex || i == width) {
                status._Cost += COST_HIT;

                auto &entry = _CacheEntries[prevCacheIndex];
                if (entry._Valid && entry._Tag == prevTag) {
                } else {
                    if (entry._Valid && entry._Dirty) {
                        WriteBlock(address + prevByteNo);

                        status._Cost += COST_MISS * _BlockWidthBit;
                    }

                    status._Miss = true;
                }

                entry._Valid = true;
                entry._Dirty = true;
                entry._Tag = prevTag;

                for (unsigned j = prevByteNo; j < i; j++) {
                    unsigned addr = address + j;
                    entry._Block[addr & _OffsetMask] = value >> (j * 8) & 0xff;
                }

                prevCacheIndex = cacheIndex;
                prevByteNo = i;
                prevTag = tag;
            }
        }

        return status;
    }

    void CacheDirect::LoadBlock(unsigned address) {
        address &= ~_OffsetMask; // align the address
        int tag = address >> (_BlockWidthBit + _CacheSizeBit);
        int cacheIndex = address >> _BlockWidthBit & _CacheIndexMask;
        _CacheEntries[cacheIndex]._Tag = tag;
        _CacheEntries[cacheIndex]._Valid = true;
        _CacheEntries[cacheIndex]._Dirty = false;
        _Mem->CopyOut(address, _CacheEntries[cacheIndex]._Block,
                      1 << _BlockWidthBit);
    }

    void CacheDirect::WriteBlock(unsigned address) {
        address &= ~_OffsetMask; // align the address
        int tag = address >> (_BlockWidthBit + _CacheSizeBit);
        int cacheIndex = address >> _BlockWidthBit & _CacheIndexMask;
        _CacheEntries[cacheIndex]._Tag = tag;
        _CacheEntries[cacheIndex]._Valid = true;
        _CacheEntries[cacheIndex]._Dirty = false;
        _Mem->CopyIn(_CacheEntries[cacheIndex]._Block, address,
                     1 << _BlockWidthBit);
    }

} // namespace mockcache
