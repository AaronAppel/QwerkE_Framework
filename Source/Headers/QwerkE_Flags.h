#pragma once

// QwerkE flags for things like framework systems, etc

// References : https://www.learncpp.com/cpp-tutorial/bit-manipulation-with-bitwise-operators-and-bit-masks/

/* Framework systems */
constexpr std::uint_fast8_t Flag_Physics{ 1 << 0 }; // 0000 0001
constexpr std::uint_fast8_t Flag_Renderer{ 1 << 1 }; // 0000 0010
constexpr std::uint_fast8_t Flag_Audio{ 1 << 2 }; // 0000 0100
//constexpr std::uint_fast8_t Flag_Physics{ 1 << 3 }; // 0000 1000
//constexpr std::uint_fast8_t Flag_Physics{ 1 << 4 }; // 0001 0000
//constexpr std::uint_fast8_t Flag_Physics{ 1 << 5 }; // 0010 0000
//constexpr std::uint_fast8_t Flag_Physics{ 1 << 6 }; // 0100 0000
//constexpr std::uint_fast8_t Flag_Physics{ 1 << 7 }; // 1000 0000
