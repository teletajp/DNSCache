#pragma once
#include <string>
namespace dns
{
/*! \brief Class stores mapping between the name and IP address.
*/
class DNSCache
{
public:
    /*! \brief Constructor
    * \param max_size The maximum number of records available for storage
    */
    explicit DNSCache(size_t max_size);
    /*! \brief Destructor
    */
    virtual ~DNSCache();
    /*! \brief Update dns record
    * \param name Dns name
    * \param ip ip address string
    */
    void update(const std::string& name, const std::string& ip);
    /*! \brief Update dns record
    * \param name Dns name
    * \return ip address string
    */
    std::string resolve(const std::string& name);
    /*! \brief Check dns name correct format
    * \param name Dns name
    * \return true - Valid name, false invalid name
    */
    bool isValid(const std::string& name);
private:
    DNSCache(const DNSCache&) = delete;
    DNSCache(DNSCache&&) = delete;
    DNSCache& operator= (const DNSCache&) = delete;
    DNSCache& operator= (DNSCache&&) = delete;
    class Impl;
    std::unique_ptr<Impl> pimpl_;
};
}