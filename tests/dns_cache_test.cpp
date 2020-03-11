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

TEST(DnsCacheTest_isValid, OK)
{
    DNSCache dns_cache(10);
    ASSERT_TRUE(dns_cache.isValid("ya.ru"));
    ASSERT_FALSE(dns_cache.isValid("1ya.ru"));
    ASSERT_FALSE(dns_cache.isValid("-ya.ru"));
    ASSERT_FALSE(dns_cache.isValid("ya-.ru"));
    ASSERT_FALSE(dns_cache.isValid("ya$.ru"));
    ASSERT_TRUE(dns_cache.isValid("yaru"));
    ASSERT_FALSE(dns_cache.isValid("yaru-"));
    ASSERT_FALSE(dns_cache.isValid("yaru."));
    ASSERT_TRUE(dns_cache.isValid("a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.ru"));
    ASSERT_FALSE(dns_cache.isValid("a64aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.ru"));
    ASSERT_TRUE(dns_cache.isValid("a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.\
a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
    ASSERT_FALSE(dns_cache.isValid("a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.\
a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.a64aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    //getchar();
    return ret;
}