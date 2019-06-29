#ifndef MCLIB_COMMON_TYPES_H_
#define MCLIB_COMMON_TYPES_H_

#include <cstddef>
#include <cstdint>

#ifdef _MSC_VER
#define NOEXCEPT
#else
#define NOEXCEPT noexcept
#endif

namespace mc {

using EntityId = int32_t;

enum class Hand { Main, Off };
enum class MainHand { Left, Right };

enum class ChatMode { Enabled, Commands, Hidden };

enum class SkinPart {
    Cape = 0x1,
    Jacket = 0x2,
    LeftSleeve = 0x4,
    RightSleeve = 0x8,
    LeftPants = 0x10,
    RightPants = 0x20,
    Hat = 0x40
};

enum class Face { Bottom = 0, Top, North, South, West, East };

}  // namespace mc

#include <mclib/common/Vector.h>
#include <mclib/mclib.h>

#endif
