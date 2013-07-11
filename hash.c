/*
  Pearson Fast Variable-Length Text Strings Hash
  (see)
  "Fast Hashing of Variable-Length Text Strings"
  (by)
  Peter K. Pearson
  (in)
  Communications of the ACM, June 1990, Volume 33, Number 6, pp. 677-680
                             
  http://cs.mwsu.edu/~griffin/courses/2133/downloads/Spring11/p677-pearson.pdf
*/

/*
  TODO: mix with some non-zero prime at the END??? or...
        is hash value of ZERO sensible???
*/

#include "hash.h"

/* TABLE I. Pseudorandom Permutation of the Integers 0 through 255
   This permutation gave a good hashing behavior */
/* TODO: recheck for possible c&p errors */
uint8_t T[256] = {
    1,  87,  49,  12, 176, 178, 102, 166, 121, 193,   6,  84, 249, 230,  44, 163,
   14, 197, 213, 181, 161,  85, 218,  80,  64, 239,  24, 226, 236, 142,  38, 200,
  110, 177, 104, 103, 141, 253, 255,  50,  77, 101,  81,  18,  45,  96,  31, 222,
   25, 107, 190,  70,  86, 237, 240,  34,  72, 242,  20, 214, 244, 227, 149, 235,
   97, 234,  57,  22,  60, 250,  82, 175, 208,   5, 127, 199, 111,  62, 135, 248,
  174, 169, 211,  58,  66, 154, 106, 195, 245, 171,  17, 187, 182, 179,   0, 243,
  132,  56, 148,  75, 128, 133, 158, 100, 130, 126,  91,  13, 153, 246, 216, 219,
  119,  68, 223,  78,  83,  88, 201,  99, 122,  11,  92,  32, 136, 114,  52,  10,
  138,  30,  48, 183, 156,  35,  61,  26, 143,  74, 251,  94, 129, 162,  63, 152,
  170,   7, 115, 167, 241, 206,   3, 150,  55,  59, 151, 220,  90,  53,  23, 131,
  125, 173,  15, 238,  79,  95,  89,  16, 105, 137, 225, 224, 217, 160,  37, 123,
  118,  73,   2, 157,  46, 116,   9, 145, 134, 228, 207, 212, 202, 215,  69, 229,
   27, 188,  67, 124, 168, 252,  42,   4,  29, 108,  21, 247,  19, 205,  39, 203,
  233,  40, 186, 147, 198, 192, 155,  33, 164, 191,  98, 204, 165, 180, 117,  76,
  140,  36, 210, 172,  41,  54, 159,   8, 185, 232, 113, 196, 231,  47, 146, 120,
   51,  65,  28, 144, 254, 221,  93, 189, 194, 139, 112,  43,  71, 109, 184, 209
};
/* hopefully we have not transposed the damn thing :-] */

/* start with original 8-bit version */
uint8_t hash_pFastVLTS_8b(uint8_t * buffer, uint16_t length) {
  uint8_t prev = 0;
  uint8_t next;
  uint16_t len;

  if(length == 1)
	return T[ prev ^ *buffer ];

  len = length >> 1;
  length -= len * 2;
  while(len > 0) {
	next = T[ prev ^ *buffer++ ];
	prev = T[ next ^ *buffer++ ];
	len--;
  }
  /* one last odd time */
  if(length == 1)
	return T[ prev ^ *buffer ];
  else
	return prev;
}

/* suggested "trivial" 16-bit hash length extension */
uint16_t hash_pFastVLTS_16b(uint8_t * buffer, uint16_t length) {
  uint8_t prev = 0;
  uint8_t next;
  uint16_t len;

  uint16_t h1 = (uint16_t)hash_pFastVLTS_8b(buffer, length) << 8;

  if(length == 0)
	return h1;
  if(length == 1)
	return h1 | T[ prev ^ (*buffer + 1) ];

  len = length >> 1;
  length -= len * 2;

  next = T[ prev ^ (*buffer++ + 1) ];
  prev = T[ next ^ *buffer++ ];
  len--;
  /* after adding 1 to first buffer's element; continue... */
  while(len > 0) {
	next = T[ prev ^ *buffer++ ];
	prev = T[ next ^ *buffer++ ];
	len--;
  }
  /* one last odd time */
  if(length == 1)
	return h1 | T[ prev ^ *buffer ];
  else
	return h1 | prev;
}

/* TOFIX: what's with "length" == 0 ??? */
