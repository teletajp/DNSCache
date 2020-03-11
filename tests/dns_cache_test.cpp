#include <gtest/gtest.h>
#include <gtest/internal/gtest-internal.h>
#include <dns_cache.h>
using namespace dns;
class DNSCacheTest : public ::testing::Test
{
public:
protected:

  virtual void SetUp(){
  
  }

  virtual void TearDown(){

  }
  
};

TEST(DnsCacheTest_isValidDns, OK)
{
    DNSCache dns_cache(10);
    ASSERT_TRUE(dns_cache.isValidDnsName("ya.ru"));
    ASSERT_FALSE(dns_cache.isValidDnsName("1ya.ru"));
    ASSERT_FALSE(dns_cache.isValidDnsName("-ya.ru"));
    ASSERT_FALSE(dns_cache.isValidDnsName("ya-.ru"));
    ASSERT_FALSE(dns_cache.isValidDnsName("ya$.ru"));
    ASSERT_TRUE(dns_cache.isValidDnsName("yaru"));
    ASSERT_FALSE(dns_cache.isValidDnsName("yaru-"));
    ASSERT_FALSE(dns_cache.isValidDnsName("yaru."));
    ASSERT_TRUE(dns_cache.isValidDnsName("a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.ru"));
    ASSERT_FALSE(dns_cache.isValidDnsName("a64aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.ru"));
    ASSERT_TRUE(dns_cache.isValidDnsName("a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.\
a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
    ASSERT_FALSE(dns_cache.isValidDnsName("a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.\
a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.a64aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
}

TEST(DnsCacheTest_isValidIp, OK)
{
    DNSCache dns_cache(10);
    ASSERT_TRUE(dns_cache.isValidIp("2001:0db8:85a3:0000:0000:8a2e:0370:7334"));
    ASSERT_FALSE(dns_cache.isValidIp("2001:0db8:85a3:0000:0000:8a2e:0370:7334:0"));
    ASSERT_FALSE(dns_cache.isValidIp("2001:0db8:85a3:0000:0000:8a2e:0370"));
    ASSERT_TRUE(dns_cache.isValidIp("127.0.0.1"));
    ASSERT_FALSE(dns_cache.isValidIp("127.0.0.257"));
    ASSERT_FALSE(dns_cache.isValidIp("127.0.0000.257"));
    ASSERT_FALSE(dns_cache.isValidIp("127.0..257"));
    ASSERT_FALSE(dns_cache.isValidIp("0.0.0.FF"));
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    //getchar();
    return ret;
}