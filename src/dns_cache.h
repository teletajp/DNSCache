#pragma once
#include <string>
#include <memory>
namespace dns
{
/*! \brief Check ip correct format
* \param ip ip-address string
* \return true - Valid ip, false invalid ip
*/
bool isValidIp(const std::string& ip);
 /*! \brief Check dns name correct format
* \param name Dns name
* \return true - Valid name, false invalid name
*/
bool isValidDnsName(const std::string& name);
/*! \brief Class stores mapping between the name and IP address.
*/
class DNSCache
{
protected:
    /*! \brief Constructor
    * \param max_size The maximum number of records available for storage
    */
    explicit DNSCache(size_t max_size);
public:
    static DNSCache& Instance(size_t max_size); 
    /*! \brief Destructor
    */
    virtual ~DNSCache();
    /*! \brief Update dns record
    * \param name Dns name
    * \param ip ip address string
    */
    void update(const std::string& name, const std::string& ip);
    /*! \brief Returns from cache the IP address for the given name parameter or a string if not found.
    * \param name Dns name
    * \return ip address string
    */
    std::string resolve(const std::string& name);
private:
    DNSCache(const DNSCache&) = delete;
    DNSCache(DNSCache&&) = delete;
    DNSCache& operator= (const DNSCache&) = delete;
    DNSCache& operator= (DNSCache&&) = delete;
    class Impl;
    std::unique_ptr<Impl> pimpl_;
};
}