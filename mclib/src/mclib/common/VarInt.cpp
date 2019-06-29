#include <mclib/common/VarInt.h>

#include <mclib/common/DataBuffer.h>

#include <ostream>

namespace mc {

VarInt::VarInt() noexcept : m_Value(0) {}
VarInt::VarInt(int8_t val) noexcept : m_Value(val) {}
VarInt::VarInt(int16_t val) noexcept : m_Value(val) {}
VarInt::VarInt(int32_t val) noexcept : m_Value(val) {}
VarInt::VarInt(int64_t val) noexcept : m_Value(val) {}

std::size_t VarInt::GetSerializedLength() const {
    DataBuffer buffer;
    buffer << *this;
    return buffer.GetSize();
}

DataBuffer& operator<<(DataBuffer& out, const VarInt& var) {
    uint64_t uval = var.m_Value;

    int encoded = 0;
    char data[10];

    do {
        uint8_t nextByte = uval & 0b01111111;
        uval >>= 7;
        if (uval) nextByte |= 0b10000000;
        data[encoded++] = nextByte;
    } while (uval);
    out << std::string(data, encoded);

    return out;
}

DataBuffer& operator>>(DataBuffer& in, VarInt& var) {
    uint64_t value = 0;
    int shift = 0;

    if (in.IsFinished()) {
        var.m_Value = 0;
        return in;
    }

    std::size_t i = in.GetReadOffset();

    do {
        if (i >= in.GetSize())
            throw std::out_of_range("Failed reading VarInt from DataBuffer.");
        value |= static_cast<uint64_t>((in[i] & 0b01111111) << shift);
        shift += 7;
    } while ((in[i++] & 0b10000000) != 0);

    in.SetReadOffset(i);

    var.m_Value = value;

    return in;
}

}  // namespace mc

std::ostream& operator<<(std::ostream& out, const mc::VarInt& v) {
    return out << v.GetLong();
}
