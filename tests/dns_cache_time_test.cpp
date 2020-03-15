#include "dns_cache.h"
#include <thread>
#include <chrono>
#include <iostream>
class Clock
{
private:
    std::chrono::system_clock::time_point start_;
    std::chrono::system_clock::time_point stop_;

public:
    Clock(/* args */)=default;
    ~Clock()=default;
    void start() { start_ = std::chrono::system_clock::now(); };
    void stop() { stop_ = std::chrono::system_clock::now(); };
    double seconds() { return std::chrono::duration_cast<std::chrono::milliseconds>(stop_ - start_).count()/1000.00; }
};

uint64_t test_update_fun(dns::DNSCache *dc)
{
    std::string name(255, 'a');
    uint64_t count = 0;
    for (char ch250 = 'a'; ch250 <= 'z'; ++ch250)
    {
        name[250] = ch250;
        for (char ch251 = 'a'; ch251 <= 'z'; ++ch251)
        {
            name[251] = ch251;
            for (char ch252 = 'a'; ch252 <= 'z'; ++ch252)
            {
                name[252] = ch252;
                for (char ch253 = 'a'; ch253 <= 'z'; ++ch253)
                {
                    name[253] = ch253;
                    for (char ch254 = 'a'; ch254 <= 'z'; ++ch254)
                    {
                        name[254] = ch254;
                        dc->update(name, std::string());
                        ++count;
                    }
                }
            }
        }
    }
    return count;
}
uint64_t test_resolve_fun(dns::DNSCache *dc)
{
    std::string name(255, 'a');
    uint64_t count = 0;
    for (char ch250 = 'a'; ch250 <= 'z'; ++ch250)
    {
        name[250] = ch250;
        for (char ch251 = 'a'; ch251 <= 'z'; ++ch251)
        {
            name[251] = ch251;
            for (char ch252 = 'a'; ch252 <= 'z'; ++ch252)
            {
                name[252] = ch252;
                for (char ch253 = 'a'; ch253 <= 'z'; ++ch253)
                {
                    name[253] = ch253;
                    for (char ch254 = 'a'; ch254 <= 'z'; ++ch254)
                    {
                        name[254] = ch254;
                        dc->update(name, std::string());
                        ++count;
                    }
                }
            }
        }
    }
    return count;
}
int main(int, char const **)
{
    Clock timer;
    dns::DNSCache dc(12000000);
    timer.start();
    uint64_t count = test_update_fun(&dc);
    timer.stop();
    std::cout <<"One thread update "<< timer.seconds()<<" sec count="<<count<<std::endl;
    timer.start();
    std::thread th1(&test_update_fun, &dc);
    std::thread th2(&test_update_fun, &dc);
    std::thread th3(&test_update_fun, &dc);
    std::thread th4(&test_update_fun, &dc);
    std::thread th5(&test_update_fun, &dc);
    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();
    timer.stop();
    std::cout <<"Five thread update "<< timer.seconds()<<" sec count="<<count<<std::endl;
    test_resolve_fun(&dc);
    timer.stop();
    std::cout <<"One thread resolve " << timer.seconds()<<" sec count="<<count<<std::endl;
    timer.start();
    std::thread th6(&test_resolve_fun, &dc);
    std::thread th7(&test_resolve_fun, &dc);
    std::thread th8(&test_resolve_fun, &dc);
    std::thread th9(&test_resolve_fun, &dc);
    std::thread th10(&test_resolve_fun, &dc);
    th6.join();
    th7.join();
    th8.join();
    th9.join();
    th10.join();
    timer.stop();
    std::cout <<"Five thread resolve "<< timer.seconds()<<" sec count="<<count<<std::endl;
    return 0;
}
