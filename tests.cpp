#include "intmem.h"
#include <iostream>

using namespace intmem;

#ifdef _MSC_VER
#define ALIGN(n) __declspec(align(n))
#else
#define ALIGN(n) __attribute__((aligned(n)))
#endif

template <class T>
int test_unsigned(const char* Name)
{
  ALIGN(alignof(T)) uint8_t cst_4_le[sizeof(T)] = {0};
  ALIGN(alignof(T)) uint8_t cst_4_be[sizeof(T)] = {0};
  cst_4_le[0] = 4;
  cst_4_be[sizeof(T)-1] = 4;
  if (loadu_le<T>(cst_4_le) != 4) {
    std::cerr << Name << ": error loading LE integer!" << std::endl;
    return 1;
  }
  if (loadu_be<T>(cst_4_be) != 4) {
    std::cerr << Name << ": error loading BE integer!" << std::endl;
    return 1;
  }
  if (load_le<T>((T*) cst_4_le) != 4) {
    std::cerr << Name << ": error loading LE integer!" << std::endl;
    return 1;
  }
  if (load_be<T>((T*) cst_4_be) != 4) {
    std::cerr << Name << ": error loading BE integer!" << std::endl;
    return 1;
  }

  ALIGN(alignof(T)) uint8_t tmp[sizeof(T)];
  storeu_le<T>(tmp, 4);
  if (memcmp(tmp, cst_4_le, sizeof(T)) != 0) {
    std::cerr << Name << ": error storing LE integer!" << std::endl;
    return 1;
  }
  storeu_be<T>(tmp, 4);
  if (memcmp(tmp, cst_4_be, sizeof(T)) != 0) {
    std::cerr << Name << ": error storing BE integer!" << std::endl;
    return 1;
  }

  T tmp2;
  store_le<T>(&tmp2, 4);
  if (memcmp(&tmp2, cst_4_le, sizeof(T)) != 0) {
    std::cerr << Name << ": error storing LE integer!" << std::endl;
    return 1;
  }
  storeu_be<T>(&tmp2, 4);
  if (memcmp(&tmp2, cst_4_be, sizeof(T)) != 0) {
    std::cerr << Name << ": error storing BE integer!" << std::endl;
    return 1;
  }
  return 0;
}

template <class T>
int test_signed(const char* Name)
{
  ALIGN(alignof(T)) uint8_t cst_minus10_le[sizeof(T)];
  ALIGN(alignof(T)) uint8_t cst_minus10_be[sizeof(T)];
  memset(&cst_minus10_le[0], 0xFF, sizeof(T));
  memset(&cst_minus10_be[0], 0xFF, sizeof(T));
  cst_minus10_le[0] = 0xF6;
  cst_minus10_be[sizeof(T)-1] = 0xF6;
  if (loadu_le<T>(cst_minus10_le) != -10) {
    std::cerr << Name << ": error loading LE signed integer!" << std::endl;
    return 1;
  }
  if (loadu_be<T>(cst_minus10_be) != -10) {
    std::cerr << Name << ": error loading BE signed integer!" << std::endl;
    return 1;
  }
  if (load_le<T>((T*) cst_minus10_le) != -10) {
    std::cerr << Name << ": error loading LE signed integer!" << std::endl;
    return 1;
  }
  if (load_be<T>((T*) cst_minus10_be) != -10) {
    std::cerr << Name << ": error loading BE signed integer!" << std::endl;
    return 1;
  }

  uint8_t tmp[sizeof(T)];
  storeu_le<T>(tmp, -10);
  if (memcmp(tmp, cst_minus10_le, sizeof(T)) != 0) {
    std::cerr << Name << ": error storing LE integer!" << std::endl;
    return 1;
  }
  storeu_be<T>((T*) tmp, -10);
  if (memcmp(tmp, cst_minus10_be, sizeof(T)) != 0) {
    std::cerr << Name << ": error storing BE integer!" << std::endl;
    return 1;
  }

  T tmp2;
  store_le<T>(&tmp2, -10);
  if (memcmp(&tmp2, cst_minus10_le, sizeof(T)) != 0) {
    std::cerr << Name << ": error storing LE integer!" << std::endl;
    return 1;
  }
  storeu_be<T>(&tmp2, -10);
  if (memcmp(&tmp2, cst_minus10_be, sizeof(T)) != 0) {
    std::cerr << Name << ": error storing BE integer!" << std::endl;
    return 1;
  }
  return 0;
}

int main()
{
  int Ret = 0;
  Ret |= test_unsigned<uint8_t>("uint8_t");
  Ret |= test_unsigned<uint16_t>("uint16_t");
  Ret |= test_unsigned<uint32_t>("uint32_t");
  Ret |= test_unsigned<uint64_t>("uint64_t");

  Ret |= test_signed<int8_t>("int8_t");
  Ret |= test_signed<int16_t>("int16_t");
  Ret |= test_signed<int32_t>("int32_t");
  Ret |= test_signed<int64_t>("int64_t");

  if (Ret == 0) {
    std::cout << "All tests are OK." << std::endl;
  }

  return Ret;
}
