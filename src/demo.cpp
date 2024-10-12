#include "MockCache/CacheBase.h"
#include "MockCache/CacheDirect.h"
#include "MockCache/CacheFullAssoc.h"
#include "MockCache/CacheSetAssoc.h"
#include "MockCache/Memory.h"

#include <iostream>
#include <random>

std::mt19937_64 engine;

int main() {
    std::random_device rd;
    engine.seed(rd());

    using namespace mockcache;

    int memSize = 1 << 20;

    int cnt = memSize;

    auto rand = [&]() {
        std::uniform_int_distribution<int> dist(0, memSize - 7);
        return dist(engine);
    };

    // Remove the annotation marks in CacheBase::_PrintStatus..
    // ..if you want to print the status each time when accessing the cache
    // I will add some variables to control it in the future

    std::cout << "[NO CACHE]" << ' ' << "[CACHE 1]" << ' ' << "[CACHE 2]"
              << '\n';
    std::cout << "[Cache 1 Miss Rate]" << ' ' << "[Cache 2 Miss Rate]" << '\n'
              << '\n';

    for (int k = 6; k <= 20; k++) {
        int cost1 = 0, cost2 = 0;
        int miss1 = 0, miss2 = 0;

        auto mem = std::make_shared<Memory>(memSize);
        CacheDirect cache(mem, 6, k);

        auto mem2 = std::make_shared<Memory>(memSize);
        CacheDirect cache2(mem2, 1, 1);

        for (int i = 0; i < cnt; i++) {
            auto width = [&]() { return 1 << (rand() % 3); };
            auto s1 =
                cache.Write(rand() % (memSize - 7), rand() % 0xff, width());
            auto s2 =
                cache2.Write(rand() % (memSize - 7), rand() % 0xff, width());
            auto s11 = cache.Read(rand() % (memSize - 7), width());
            auto s22 = cache2.Read(rand() % (memSize - 7), width());
            cost1 += s1._Cost + s11._Cost;
            cost2 += s2._Cost + s22._Cost;
            if (s1._Miss) {
                ++miss1;
            }
            if (s11._Miss) {
                ++miss1;
            }
            if (s2._Miss) {
                ++miss2;
            }
            if (s22._Miss) {
                ++miss2;
            }
        }

        std::cout << memSize * COST_MISS << ' ' << cost1 << ' ' << cost2
                  << '\n';
        std::cout << 1.0 * miss1 / (2 * cnt) << ' ' << 1.0 * miss2 / (2 * cnt)
                  << '\n'
                  << '\n';
    }

    return 0;
}
