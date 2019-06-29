#ifndef MCLIB_COMMON_VAR_INT_H_
#define MCLIB_COMMON_VAR_INT_H_

#include <mclib/common/Types.h>
#include <mclib/mclib.h>

#include <iosfwd>

namespace mc {

class DataBuffer;

class VarInt {
private:
    int64_t m_Value;

public:
    MCLIB_API VarInt() noexcept;
    MCLIB_API VarInt(int8_t val) noexcept;
    MCLIB_API VarInt(int16_t val) noexcept;
    MCLIB_API VarInt(int32_t val) noexcept;
    MCLIB_API VarInt(int64_t val) noexcept;

    int8_t GetByte() const noexcept { return (int8_t)m_Value; }
    int16_t GetShort() const noexcept { return (int16_t)m_Value; }
    int32_t GetInt() const noexcept { return (int32_t)m_Value; }
    int64_t GetLong() const noexcept { return m_Value; }

    // Returns how many bytes this will take up in a buffer
    std::size_t MCLIB_API GetSerializedLength() const;

    friend MCLIB_API DataBuffer& operator<<(DataBuffer& out, const VarInt& pos);
    friend MCLIB_API DataBuffer& operator>>(DataBuffer& in, VarInt& pos);
};

using VarLong = VarInt;

MCLIB_API DataBuffer& operator<<(DataBuffer& out, const VarInt& var);
MCLIB_API DataBuffer& operator>>(DataBuffer& in, VarInt& var);

}  // namespace mc

MCLIB_API std::ostream& operator<<(std::ostream& out, const mc::VarInt& v);

#endif
