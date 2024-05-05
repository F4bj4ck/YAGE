#pragma once

#define BIT(x) (1 << (x))

#define YAGE_ASSERT(x, ...) { if(!(x)) { YAGE_ERROR("Assertion Failed: {0]", __VA_ARGS__); __debugbreak(); } }