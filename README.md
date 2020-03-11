# DNSCache
The implementation of class for the DNS cache with the following interface:
```
class DNSCache
{
public:
explicit DNSCache(size_t max_size);
void update(const std::string& name, const std::string& ip);
std::string resolve(const std::string& name);
};
```
This class stores mapping between the name and IP address. The maximum number of records available for storage is initialize in the constructor with the max_size parameter.

Method **update()** either updates the existing record or adds a new one. If the limit set by max_size is exceeded, the oldest unused records will be deleted from cache. The oldest pair (name and IP-address) that does not involved in update() or resolve() procedures longer than other.

Method **resolve()** returns from cache the IP address for the given name parameter or a empty string if not found.
The class supports correct operation in a multithreaded application, when update() and resolve() are called from different threads at the same time.

## Build DNSCache library
1. ol git clone https://github.com/teletajp/DNSCache.git
2. ol cd DNSCache
3. ol mkdir build
4. ol cd build
5. ol make

If you want build tests, you need install **googletest framework**.
### Install googletest framework
1. ol git clone https://github.com/google/googletest.git
2. ol cd googletest
3. ol mkdir build
4. ol cd build
5. ol cmake -DCMAKE_CXX_COMPILER="c++" -DCMAKE_CXX_FLAGS="-std=c++11 -stdlib=libc++" ../
6. ol make
7. ol sudo make install

## Features

*   Verifying that the name and ip address are correct
*   Optimazed searching/insertion/updating algorithm (O < LOG N)
*   Optimazed deleting old records algorithm (O = constant time) 