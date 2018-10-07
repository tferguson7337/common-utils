#pragma once

#include <type_traits>

/// Basic Types \\\

// Basic Signed Types
using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;

// Basic Unsigned Types
using uint8 = std::make_unsigned_t<__int8>;
using uint16 = std::make_unsigned_t<__int16>;
using uint32 = std::make_unsigned_t<__int32>;
using uint64 = std::make_unsigned_t<__int64>;

// Basic Address Size Types
#ifndef _WINDOWS_
using byte = int8;
using dbyte = int16;
using qbyte = int32;
using dqbyte = int64;
#endif

// Basic Character Types
using ascii = char;
using utf8 = char;

// Fix for linker errors when using char16_t in place of wchar_t for codecvt (fix your shit M$oft).
// https://stackoverflow.com/questions/32055357/visual-studio-c-2015-stdcodecvt-with-char16-t-or-char32-t
#if _MSC_VER <= 1915
#define _UTF16_IS_WIDE_CHAR
using utf16 = wchar_t;

#define _UTF32_IS_INT32
using utf32 = int32;
#else
using utf16 = char16_t;
using utf32 = char32_t;
#endif

/// Pointer-To-Basic-Types \\\

// Pointer - Basic Signed Types
using int8_ptr = std::add_pointer_t<int8>;
using int16_ptr = std::add_pointer_t<int16>;
using int32_ptr = std::add_pointer_t<int32>;
using int64_ptr = std::add_pointer_t<int64>;

// Pointer - Basic Unsigned Types
using uint8_ptr = std::add_pointer_t<uint8>;
using uint16_ptr = std::add_pointer_t<uint16>;
using uint32_ptr = std::add_pointer_t<uint32>;
using uint64_ptr = std::add_pointer_t<uint64>;

// Pointer - Basic Address Size Types
#ifndef _WINDOWS_ 
using byte_ptr = std::add_pointer_t<byte>;
using dbyte_ptr = std::add_pointer_t<dbyte>;
using qbyte_ptr = std::add_pointer_t<qbyte>;
using dqbyte_ptr = std::add_pointer_t<dqbyte>;
#endif

// Pointer - Basic Character Types
using ascii_ptr = std::add_pointer_t<ascii>;
using utf8_ptr = std::add_pointer_t<utf8>;
using utf16_ptr = std::add_pointer_t<utf16>;
using utf32_ptr = std::add_pointer_t<utf32>;

/// Sanity Checks For Expected Type Sizes \\\

namespace
{
#define TYPE_SASSERT_STR "static assert for types triggered - platform may not be supported."

#ifndef _WINDOWS_
    // Basic Signed Types
    static_assert(sizeof(int8)      == sizeof(byte), TYPE_SASSERT_STR);
    static_assert(sizeof(int16)     == sizeof(dbyte), TYPE_SASSERT_STR);
    static_assert(sizeof(int32)     == sizeof(qbyte), TYPE_SASSERT_STR);
    static_assert(sizeof(int64)     == sizeof(dqbyte), TYPE_SASSERT_STR);

    // Basic Unsigned Types
    static_assert(sizeof(uint8)     == sizeof(byte), TYPE_SASSERT_STR);
    static_assert(sizeof(uint16)    == sizeof(dbyte), TYPE_SASSERT_STR);
    static_assert(sizeof(uint32)    == sizeof(qbyte), TYPE_SASSERT_STR);
    static_assert(sizeof(uint64)    == sizeof(dqbyte), TYPE_SASSERT_STR);

    // Platform-Address Size Type
    static_assert(sizeof(byte)      == 1, TYPE_SASSERT_STR);
    static_assert(sizeof(dbyte)     == sizeof(byte) << 1, TYPE_SASSERT_STR);
    static_assert(sizeof(qbyte)     == sizeof(dbyte) << 1, TYPE_SASSERT_STR);
    static_assert(sizeof(dqbyte)    == sizeof(qbyte) << 1, TYPE_SASSERT_STR);

    // String Types
    static_assert(sizeof(ascii)     == sizeof(byte), TYPE_SASSERT_STR);
    static_assert(sizeof(utf8)      == sizeof(byte), TYPE_SASSERT_STR);
    static_assert(sizeof(utf16)     == sizeof(dbyte), TYPE_SASSERT_STR);
    static_assert(sizeof(utf32)     == sizeof(qbyte), TYPE_SASSERT_STR);
#else
    // Basic Signed Types
    static_assert(sizeof(int8)      == 1, TYPE_SASSERT_STR);
    static_assert(sizeof(int16)     == sizeof(int8) << 1, TYPE_SASSERT_STR);
    static_assert(sizeof(int32)     == sizeof(int16) << 1, TYPE_SASSERT_STR);
    static_assert(sizeof(int64)     == sizeof(int32) << 1, TYPE_SASSERT_STR);

    // Basic Unsigned Types
    static_assert(sizeof(uint8)     == 1, TYPE_SASSERT_STR);
    static_assert(sizeof(uint16)    == sizeof(uint8) << 1, TYPE_SASSERT_STR);
    static_assert(sizeof(uint32)    == sizeof(uint16) << 1, TYPE_SASSERT_STR);
    static_assert(sizeof(uint64)    == sizeof(uint32) << 1, TYPE_SASSERT_STR);

    // String Types
    static_assert(sizeof(ascii)     == 1, TYPE_SASSERT_STR);
    static_assert(sizeof(utf8)      == sizeof(ascii), TYPE_SASSERT_STR);
    static_assert(sizeof(utf16)     == sizeof(utf8) << 1, TYPE_SASSERT_STR);
    static_assert(sizeof(utf32)     == sizeof(utf16) << 1, TYPE_SASSERT_STR);
#endif
}
