#ifndef MCLIB_COMMON_POSITION_H_
#define MCLIB_COMMON_POSITION_H_

#include <mclib/common/Types.h>
#include <mclib/mclib.h>
#include <iosfwd>
#include <string>

namespace mc {

class DataBuffer;

class Position {
private:
    int64_t m_X;
    int64_t m_Y;
    int64_t m_Z;

public:
    Position() noexcept : m_X(0), m_Y(0), m_Z(0) {}
    MCLIB_API Position(int32_t x, int32_t y, int32_t z) noexcept;
    int64_t MCLIB_API Encode64() const noexcept;

    int64_t GetX() const { return m_X; }
    int64_t GetY() const { return m_Y; }
    int64_t GetZ() const { return m_Z; }

    friend MCLIB_API DataBuffer& operator<<(DataBuffer& out,
                                            const Position& pos);
    friend MCLIB_API DataBuffer& operator>>(DataBuffer& in, Position& pos);
};

MCLIB_API DataBuffer& operator<<(DataBuffer& out, const Position& pos);
MCLIB_API DataBuffer& operator>>(DataBuffer& in, Position& pos);

MCLIB_API std::string to_string(const Position& data);

}  // namespace mc

MCLIB_API std::ostream& operator<<(std::ostream& out, const mc::Position& pos);
MCLIB_API std::wostream& operator<<(std::wostream& out,
                                    const mc::Position& pos);

#endif
