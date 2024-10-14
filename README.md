# MockCache / 模拟缓存
MockCache is a project mainly intended for **a basic assessment of my architecture knowledge**. 

Some parts of my implementation or terminologies used may have confict with your cognition, since I've only done a quite shallow study (~3 weeks' self-learning of CS61C) on the relative subjects. Therefore, please read my codes **with caution** 🧐.

If you encounter any problem or want to correct my mistakes, just feel free to post in [Issues](https://github.com/ZXPrism/MockCache/issues) 😊!


## Getting Started
I wrote a demo in [demo.cpp](src/demo.cpp).

### Build
- Please make sure you have at least one C++ compiler **supporting C++20** and **set related environment variables correctly**.

- Install [xmake](https://github.com/xmake-io/xmake/releases).

- Run command `xmake` under **the project root folder**(i.e. the folder of `xmake.lua`)

  - xmake will automatically install necessary dependencies and build the project
  - Since most dependencies are maintained on GitHub, you may encounter network issues during this step. I believe that you can solve them by yourself.

- You will find the demo binary under folder `bin` (which will be created during building)

### Test
For simplicity, I didn't introduce command arguments in the program. In case you want to modify the settings:

- [CacheBase.h](src/MockCache/CacheBase.h): defines the costs of each operation (currently, only `COST_HIT` and `COST_MISS`)
- [demo.cpp](src/demo.cpp): test settings. I've written many annotations which may help.

..and rebuild the project, of course.


## Project Structure
- `Memory`: simulates a simple flat memory
- `CacheBase`: the base class of a cache, defines basic operations and their costs
- `CacheDirect`: a direct mapped cache implementation
- `CacheFullAssoc`: a fully-associative cache implementation
- `CacheSetAssoc`: a set-associative cache implementation
- `CacheArray`: our test harness, can be loaded with different types of caches for each layer
- `CacheEntry`: namely the cache line, comprises attributes(valid, dirty) and a pointer to the block
- `HitStatus`: stores the result of a cache operation (read / write) and costs
- `ReplacementPolicy`: literally. Used in associative caches.


## Progess
- `2024/10/12`: Basic Architecture + Direct Mapped Cache
- `2024/10/13`: Miscs & ..


## Design Notes (WIP, the content is incomplete!)
 
This project is merely a "behavioral simulation", so its basic mechansim differs from real caches. For example, associative caches use comparators which work in parallel to find the right cache line with provided tag, but I simply used a hash map.

### Direct Mapped Cache
Easy to implement. There is only one tricky part: since one access request may cover **multiple blocks**, we need to divide the address into several segments which belongs to each block, and combine the final result.

My solution is to use a simple two pointers approach for segmentation, then process each segments separately.


### Cache Array
Modern cache often have multiple layers, it's not enough to realize 3 types of caches only, so I introduced the concept named `CacheArray`.

The problem is **interaction**. I need to figure out an efficient and elegant way to organize each layer and let them interact with each other.

Suppose we have 3 layers, denoted by L1, L2 and L3. These caches are intrinsically 3 pointers of type `CacheBase*`.

Now the user requests a read operation. Firstly we will look up in L1 cache with its `Read` function. Note that one operation may consists of multiple blocks, **for each missed block**, L1 should issue a message to `CacheArray`, telling it to search the next layer (L2). If we find the data, we will send it back to L1. If not, search L3... No matter where we find the data, **only blocks from L1 will be replaced**.

You may ask, what about L2 and L3? **My strategy is, push data to L2, L3 when evicting dirty data.**

Such action also requires a report from the layer to `CacheArray`, which then ...fixmemmmmmmmm 

This is a recursive pattern but the recursion is contolled by `CacheArray` because it has the only access to all layers, while "there exists other layers" are transparent for each cache layer.

Hence, I introduced a callback parameter in `Read` (see [CacheBase.h](src/MockCache/CacheBase.h)). The function should return the data if encountering a cache miss during `Read`.

A more detailed encapsulation:
