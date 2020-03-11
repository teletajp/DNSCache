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
    ASSERT_TRUE(isValidDnsName("ya.ru"));
    ASSERT_TRUE(isValidDnsName("y"));
    ASSERT_FALSE(isValidDnsName("1ya.ru"));
    ASSERT_FALSE(isValidDnsName("-ya.ru"));
    ASSERT_FALSE(isValidDnsName("ya-.ru"));
    ASSERT_FALSE(isValidDnsName("ya$.ru"));
    ASSERT_TRUE(isValidDnsName("yaru"));
    ASSERT_FALSE(isValidDnsName("yaru-"));
    ASSERT_FALSE(isValidDnsName("yaru."));
    ASSERT_TRUE(isValidDnsName("a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.ru"));
    ASSERT_FALSE(isValidDnsName("a64aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.ru"));
    ASSERT_TRUE(isValidDnsName("a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.\
a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
    ASSERT_FALSE(isValidDnsName("a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.\
a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.a64aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
}

TEST(DnsCacheTest_isValidIp, OK)
{
    ASSERT_TRUE(isValidIp("2001:0db8:85a3:0000:0000:8a2e:0370:7334"));
    ASSERT_FALSE(isValidIp("2001:0db8:85a3:0000:0000:8a2e:0370:7334:0"));
    ASSERT_FALSE(isValidIp("2001:0db8:85a3:0000:0000:8a2e:0370"));
    ASSERT_TRUE(isValidIp("127.0.0.1"));
    ASSERT_FALSE(isValidIp("127.0.0.257"));
    ASSERT_FALSE(isValidIp("127.0.0000.257"));
    ASSERT_FALSE(isValidIp("127.0..257"));
    ASSERT_FALSE(isValidIp("0.0.0.FF"));
}

TEST(DnsCacheTest_update_resolve, ZeroSize)
{
    DNSCache dns_server(0);
    dns_server.update("localhost", "127.0.0.1");
}

TEST(DnsCacheTest_update_resolve, OK)
{
    DNSCache dns_server(5);
    dns_server.update("localhost", "127.0.0.1");
    dns_server.update("google.com", "8.8.8.8");
    dns_server.update("ya.ru", "1.1.1.1");
    dns_server.update("rambler", "2.2.2.2");
    dns_server.update("mail.ru", "3.3.3.3");
    ASSERT_EQ("127.0.0.1", dns_server.resolve("localhost"));
    ASSERT_EQ("8.8.8.8", dns_server.resolve("google.com"));
    ASSERT_EQ("1.1.1.1", dns_server.resolve("ya.ru"));
    ASSERT_EQ("2.2.2.2", dns_server.resolve("rambler"));
    ASSERT_EQ("3.3.3.3", dns_server.resolve("mail.ru"));
    dns_server.update("habr.ru", "4.4.4.4");
    //oldest localhost deleted
    ASSERT_TRUE(dns_server.resolve("localhost").empty());
    //now oldest is google.com
    ASSERT_EQ("8.8.8.8", dns_server.resolve("google.com"));
    //now oldest is ya.ru
    dns_server.update("localhost", "127.0.0.1");
    //oldest ya.ru deleted
    ASSERT_TRUE(dns_server.resolve("ya.ru").empty());
    dns_server.update("habr.ru", "5.5.5.5");
    ASSERT_EQ("5.5.5.5", dns_server.resolve("habr.ru"));
    dns_server.update("a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.\
a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.ru",
"2001:0db8:85a3:0000:0000:8a2e:0370:7334");
    ASSERT_EQ("2001:0db8:85a3:0000:0000:8a2e:0370:7334", dns_server.resolve("a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.\
a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.a63aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.ru"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    //getchar();
    return ret;
}