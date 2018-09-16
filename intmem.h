#ifndef INTMEM_H
#define INTMEM_H

#include <cstdint>
#include <cstring>
#include <type_traits>

namespace intmem {

// bswap functions. Uses GCC/clang/MSVC intrinsics.
#ifdef _MSC_VER
#include <stdlib.h>
static uint8_t  bswap(uint8_t V) { return V; }
static uint16_t bswap(unsigned short V) { return _byteswap_ushort(V); }
static_assert(sizeof(uint32_t) == sizeof(unsigned long), "unsigned long isn't 32-bit wide!");
static uint32_t bswap(uint32_t V) { return _byteswap_ulong(V); }
static uint64_t bswap(uint64_t V) { return _byteswap_uint64(V); }
#else
static uint8_t  bswap(uint8_t V) { return V; }
static uint16_t bswap(uint16_t V) { return __builtin_bswap16(V); }
static uint32_t bswap(uint32_t V) { return __builtin_bswap32(V); }
static uint64_t bswap(uint64_t V) { return __builtin_bswap64(V); }
#endif

static int8_t  bswap(int8_t V) { return V; }
static int16_t bswap(int16_t V) { return bswap((uint16_t)V); }
static int32_t bswap(int32_t V) { return bswap((uint32_t)V); }
static int64_t bswap(int64_t V) { return bswap((uint64_t)V); }

template <class T>
static T loadu(const void* Ptr)
{
  static_assert(std::is_integral<T>::value, "T must be an integer!");
  T Ret;
  memcpy(&Ret, Ptr, sizeof(T));
  return Ret;
}

template <class T>
static void storeu(void* Ptr, T const V)
{
  static_assert(std::is_integral<T>::value, "T must be an integer!");
  memcpy(Ptr, &V, sizeof(V));
}

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
template <class T>
static T bswap_le(T const v)
{
  return v;
}

template <class T>
static T bswap_be(T const v)
{
  return bswap(v);
}
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
template <class T>
static T bswap_le(T const v)
{
  return bswap(v);
}

template <class T>
static T bswap_be(T const v)
{
  return v;
}
#else
#error Unsupported endianess!
#endif

template <class T>
static T loadu_le(const void* Ptr)
{
  return bswap_le(loadu<T>(Ptr));
}

template <class T>
static T loadu_be(const void* Ptr)
{
  return bswap_be(loadu<T>(Ptr));
}

template <class T>
static void storeu_le(void* Ptr, T const V)
{
  storeu(Ptr, bswap_le(V));
}

template <class T>
static void storeu_be(void* Ptr, T const V)
{
  storeu(Ptr, bswap_be(V));
}

template <class T>
static T load_le(const T* Ptr)
{
  return bswap_le(*Ptr);
}

template <class T>
static T load_be(const T* Ptr)
{
  return bswap_be(*Ptr);
}

template <class T>
static void store_le(T* Ptr, T const V)
{
  *Ptr = bswap_le(V);
}

template <class T>
static void store_be(T* Ptr, T const V)
{
  *Ptr = bswap_be(V);
}

} // intmem 

#endif
