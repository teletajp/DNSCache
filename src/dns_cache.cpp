#include "dns_cache.h"
#include <algorithm>
#include <cctype>
namespace dns
{
#define MAX_DNS_NAME_LEN (255U)
#define MAX_LABLE_LEN (63U)
class DNSCache::Impl
{
public:
    Impl(size_t max_size);
    ~Impl();
    size_t max_size_;
    void update(const std::string &name, const std::string &ip);
};

DNSCache::Impl::Impl(size_t max_size):
max_size_(max_size)
{
}

DNSCache::Impl::~Impl()
{
}
void DNSCache::Impl::update(const std::string &name, const std::string &ip)
{
    const size_t len = name.length();
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
    if (!isValid(name)) return;
    pimpl_->update(name, ip);
}

std::string DNSCache::resolve(const std::string & name)
{
    if (!isValid(name)) return std::string();

    return std::string();
}
bool DNSCache::isValid(const std::string & name)
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
}