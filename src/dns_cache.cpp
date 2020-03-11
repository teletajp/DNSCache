#include "dns_cache.h"
#include <algorithm>
#include <cctype>
#include <map>
#include <list>
#ifdef _WIN32
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#elif __linux__
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif


namespace dns
{
#define MAX_DNS_NAME_LEN (255U)
#define MAX_LABLE_LEN (63U)
#define MAX_IPV6_LEN (16U)
struct AuxIp;
using record_dict_t = std::map<std::string, AuxIp>;
using record_dict_iterator_t = std::map<std::string, AuxIp>::iterator;
using age_list_t = std::list<record_dict_iterator_t>;
using age_list_iterator_t = std::list<record_dict_iterator_t>::iterator;

struct AuxIp
{
    size_t dns_name_len;
    std::string ip;
    age_list_iterator_t age_it;
    AuxIp(const size_t dns_name_len, const std::string &ip) :dns_name_len(dns_name_len), ip(ip) {}
};

class DNSCache::Impl
{
public:
    Impl(size_t max_size);
    ~Impl();
    size_t max_size_;
    void update(const std::string &name, const std::string &ip);
    std::string resolve(const std::string & name);
    age_list_t    age_list_;
    record_dict_t storage_[MAX_DNS_NAME_LEN];
    size_t current_size_;
};

DNSCache::Impl::Impl(size_t max_size):
max_size_(max_size),
current_size_(0)
{
}
DNSCache::Impl::~Impl()
{
}
void DNSCache::Impl::update(const std::string &name, const std::string &ip)
{
    const size_t len = name.length();
    auto ret = storage_[len].emplace(name, AuxIp{len, ip});
    auto &it = ret.first;
    bool is_new = ret.second;
    if (is_new)
    {
        if (current_size_ == max_size_)
        {
            auto &del_rec_it = age_list_.front();
            storage_[del_rec_it->second.dns_name_len].erase(del_rec_it);
            age_list_.pop_front();
            --current_size_;
        }
        it->second.age_it = age_list_.insert(age_list_.end(), it);
        ++current_size_;
    }
    else
    {
        it->second.ip = ip;
        age_list_.splice(age_list_.end(), age_list_, it->second.age_it);
    }
}
std::string DNSCache::Impl::resolve(const std::string & name)
{
    if (!isValidDnsName(name)) return std::string();
    const size_t len = name.length();
    auto &find_it = storage_[len].find(name);
    if (find_it == storage_[len].end()) return std::string();


    return std::string();
}

DNSCache::DNSCache(size_t max_size):
pimpl_(std::make_unique<Impl>(max_size))
{
}
DNSCache::~DNSCache()
{
}
void DNSCache::update(const std::string & name, const std::string & ip)
{
    if (!isValidDnsName(name) || !isValidIp(ip)) return;
    pimpl_->update(name, ip);
}
std::string DNSCache::resolve(const std::string & name)
{
    if (!isValidDnsName(name)) return std::string();
    return pimpl_->resolve(name);
}
bool isValidDnsName(const std::string & name)
{
    size_t len = name.length();
    if (len == 0 || len > MAX_DNS_NAME_LEN) return false;
    int lable_len = 0;
    bool is_digit, is_hyphen, is_dot, is_alpha;
    for (size_t i = 0; i < len; ++i)
    {
        char ch = name[i];
        is_digit = is_hyphen = is_dot = false;
        is_alpha = std::isalpha(static_cast<unsigned char>(ch));
        //Available characters 'A'-'Z', 'a'-'z', '0'-'9', '-'
        if (!is_alpha)
        {
            if (!(is_digit = std::isdigit(static_cast<unsigned char>(ch))))
            {
                if (!(is_hyphen = (ch == '-')))
                {
                    if (!(is_dot = (ch == '.'))) return false;
                }
            }
        }

        if (is_dot)
        {
            if (lable_len == 0)             return false;
            if (lable_len > MAX_LABLE_LEN)  return false; // rfc 1035 2.3.1 Labels must be 63 characters or less
            if (name[i - 1] == '-')         return false; // rfc 1035 2.3.1 lable end with a letter or digit
            lable_len = 0;
            continue;
        }

        if (lable_len == 0 && !is_alpha) return false; // rfc 1035 2.3.1 lable must start with a letter, end with a letter or digit
        ++lable_len;
    }
    if (is_hyphen || is_dot)  return false;// last char is not letter and not digit
    return true;
}
bool isValidIp(const std::string & ip)
{

    bool isV4 = true;
    bool isV6 = false;
    std::string::size_type beg, end;
    beg = end = 0;
    end = ip.find('.', beg);
    if (end == std::string::npos)
    {
        end = ip.find(':', beg);
        if (end == std::string::npos) return false;
        isV6 = true;
        isV4 = false;
    }

    if (isV4)
    {
        in_addr buf;
        if (inet_pton(AF_INET, ip.c_str(), (PVOID)&buf) > 0) return true;
    }
    else
    {
        in6_addr buf;
        if (inet_pton(AF_INET6, ip.c_str(), (PVOID)&buf) > 0) return true;
    }
    return false;
}
}