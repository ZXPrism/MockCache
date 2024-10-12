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

- [CacheBase.h](src/MockCache/CacheBase.h): defines the costs of each operation
- [demo.cpp](src/demo.cpp): test settings. I've written many annotations which may help.

..and rebuild the project, of course.


## Project Structure
- `Memory`: simulates a simple flat memory
- `CacheBase`: the base class of a cache, defines basic operations and their costs
- `CacheDirect`: a directly mapped cache implementation
- `CacheFullAssoc`: a fully-associative cache implementation
- `CacheSetAssoc`: a set-associative cache implementation
- `CacheArray`: our test harness, can be loaded with different types of caches for each layer
- `CacheEntry`: namely the cache line, comprises attributes(valid, dirty) and a pointer to the block
- `HitStatus`: stores the result of a cache operation (read / write) and costs


## Progess
- `2024/10/12`: Basic Architecture + Directly Mapped Cache
