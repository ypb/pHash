
#include "hash.h"
#include <stdio.h>
#include <string.h>

char* strings[] = {
  "a", "ab", "abc",
  "boolba",
  "haharrr",
  ""
};

int main(int argc, char **argv) {
  int len, h8;
  int n = sizeof(strings) / sizeof(char*);
  for(int i = 0; i < n; i++) {
	len = strlen(strings[i]);
	h8 = hash_pFastVLTS_8b(strings[i], len);
	printf("hash8(0x%x), hash16(0x%x), strlen = %d, strings[%d] = \"%s\"\n",
		   h8,
		   hash_pFastVLTS_16b(strings[i], len),
		   len, i, strings[i]);
  }
  return 0;
}

