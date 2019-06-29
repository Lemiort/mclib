#ifndef MCLIB_COMMON_UUID_H_
#define MCLIB_COMMON_UUID_H_

#include <mclib/common/Types.h>
#include <mclib/mclib.h>

#include <iosfwd>
#include <string>

namespace mc {

class DataBuffer;

class UUID {
private:
    uint64_t m_MostSigBits;
    uint64_t m_LeastSigBits;

public:
    UUID() noexcept : m_MostSigBits(0), m_LeastSigBits(0) {}
    UUID(uint64_t most, uint64_t least)
    noexcept : m_MostSigBits(most), m_LeastSigBits(least) {}

    std::string MCLIB_API ToString(bool dashes = true) const;

    uint64_t GetUpperBits() const noexcept { return m_MostSigBits; }
    uint64_t GetLowerBits() const noexcept { return m_LeastSigBits; }

    static UUID MCLIB_API FromString(const std::string& str,
                                     bool dashes = true);
    static UUID MCLIB_API FromString(const std::wstring& str,
                                     bool dashes = true);

    bool operator<(const UUID& r) const {
        const UUID& l = *this;
        if (l.GetUpperBits() < r.GetUpperBits()) return true;
        if (l.GetUpperBits() > r.GetUpperBits()) return false;
        if (l.GetLowerBits() < r.GetLowerBits()) return true;
        if (l.GetLowerBits() > r.GetLowerBits()) return false;
        return false;
    }

    friend MCLIB_API DataBuffer& operator<<(DataBuffer& out, const UUID& uuid);
    friend MCLIB_API DataBuffer& operator>>(DataBuffer& in, UUID& uuid);
};

MCLIB_API DataBuffer& operator<<(DataBuffer& out, const UUID& uuid);
MCLIB_API DataBuffer& operator>>(DataBuffer& in, UUID& uuid);

MCLIB_API std::ostream& operator<<(std::ostream& out, const UUID& uuid);
MCLIB_API std::wostream& operator<<(std::wostream& out, const UUID& uuid);

}  // namespace mc

#endif
