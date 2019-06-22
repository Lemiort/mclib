#ifndef NETWORK_IPADDRESS_H_
#define NETWORK_IPADDRESS_H_

#include <mclib/common/Types.h>
#include <iosfwd>
#include <string>
#include <vector>

namespace mc {
namespace network {

/* IPv4 address */
class IPAddress {
private:
    u32 m_Address;
    bool m_Valid;

public:
    /* Create an invalid address */
    MCLIB_API IPAddress() noexcept;

    /* Initialize by string IP */
    MCLIB_API IPAddress(const std::string& str);

    /* Initialize by string IP */
    MCLIB_API IPAddress(const std::wstring& str);

    /* Initialize by octets */
    MCLIB_API IPAddress(uint8_t octet1, uint8_t octet2, uint8_t octet3, uint8_t octet4) noexcept;

    /* Get the specific octet. 1-4 */
    uint8_t MCLIB_API GetOctet(uint8_t num) const;

    /* Set the specific octet. 1-4 */
    void MCLIB_API SetOctet(uint8_t num, uint8_t value);

    /* Make sure the IP is valid. It will be invalid if the host wasn't found.
     */
    bool IsValid() const noexcept { return m_Valid; }

    std::string MCLIB_API ToString() const;

    static IPAddress MCLIB_API LocalAddress();

    MCLIB_API bool operator==(const IPAddress& right);
    MCLIB_API bool operator!=(const IPAddress& right);
    MCLIB_API bool operator==(bool b);
};

typedef std::vector<IPAddress> IPAddresses;

MCLIB_API std::ostream& operator<<(std::ostream& os, const IPAddress& addr);
MCLIB_API std::wostream& operator<<(std::wostream& os, const IPAddress& addr);

}  // namespace network
}  // namespace mc

#endif
