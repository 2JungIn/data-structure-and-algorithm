/**
 * Reference
 *  [1] https://www.rfc-editor.org/rfc/rfc1321.txt
**/

/* MD5.H - header file for MD5C.C*/
/*
 Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
 rights reserved.
 License to copy and use this software is granted provided that it
 is identified as the "RSA Data Security, Inc. MD5 Message-Digest
 Algorithm" in all material mentioning or referencing this software
 or this function.
 License is also granted to make and use derivative works provided
 that such works are identified as "derived from the RSA Data
 Security, Inc. MD5 Message-Digest Algorithm" in all material
 mentioning or referencing the derived work.
 RSA Data Security, Inc. makes no representations concerning either
 the merchantability of this software or the suitability of this
 software for any particular purpose. It is provided "as is"
 without express or implied warranty of any kind.
 These notices must be retained in any copies of any part of this
 documentation and/or software.
*/
#ifndef _MD5_H_
#define _MD5_H_

#include <stdint.h>

// two byte word is uint16_t

typedef uint8_t   MD5_BYTE;		// one byte word is uint8_t
typedef uint32_t  MD5_WORD;		// four byte word is uint32_t
typedef MD5_BYTE  MD5_BLOCK[64];

/* MD5 context. */
typedef struct {
    MD5_WORD state[4];		/* state (ABCD) */
    MD5_WORD count[2];		/* number of bits, modulo 2^64 (lsb first) */
    MD5_BLOCK buffer;		/* input buffer */
} MD5_CTX;

#ifdef __cplusplus
extern "C" {
#endif
    void MD5Init(MD5_CTX *context);
    void MD5Update(MD5_CTX *context, const MD5_BYTE *input, const unsigned int inputLen);
    void MD5Final(MD5_BYTE digest[16], const MD5_CTX *context);
#ifdef __cplusplus
}
#endif

#endif