#ifndef MAGMA_H
#define MAGMA_H
#include <stdint.h>
#include <array>

using namespace std;
struct V32xV32 { uint32_t a1, a0; };

array <array <uint8_t, 16>, 8> pi = {
    12, 4, 6, 2, 10, 5, 11, 9, 14, 8, 13, 7, 0, 3, 15, 1,
    6, 8, 2, 3, 9, 10, 5, 12, 1, 14, 4, 7, 11, 13, 0, 15,
    11, 3, 5, 8, 2, 15, 10, 13, 14, 1, 7, 4, 12, 9, 6, 0,
    12, 8, 2, 1, 13, 4, 15, 6, 7, 0, 10, 5, 3, 14, 9, 11,
    7, 15, 5, 10, 8, 1, 6, 13, 0, 9, 3, 14, 11, 4, 2, 12,
    5, 13, 15, 6, 9, 2, 12, 10, 11, 7, 8, 1, 4, 3, 14, 0,
    8, 14, 2, 5, 6, 9, 1, 12, 15, 4, 11, 0, 13, 10, 3, 7,
    1, 7, 14, 13, 0, 5, 8, 3, 4, 15, 10, 6, 9, 12, 11, 2
};

class Magma
{
public:
    array<uint32_t,8> key; // Cipher key 256 bit
    array<uint32_t,32> K; // Array of round keys
    uint32_t rl11 (uint32_t a); //rl11(a)=a<<<11
    uint32_t t(uint32_t a);  //t(a)=t(a7|...|a0)=pi7(a7)...pi0(a0)
    uint32_t g(uint32_t k, uint32_t a); // g[k](a)=t(Vec32(Int32(a)⊞Int32(k)))<<<11
    struct V32xV32 G( uint32_t k, struct V32xV32 a); // G[K](a1,a0)=(a0,g[k](a0)⊕a1)
    uint64_t G_( uint32_t k, struct V32xV32 a); //G_[K](a1,a0)=(g[k](a0)⊕a1)|a0
    uint64_t encrypt(uint64_t plainText);
    size_t encryptECB(uint8_t* input, uint8_t* output, size_t length);
    void setKey (array<uint32_t,8> cipherKey);
    void keyShedule();
};

#endif // MAGMA_H
