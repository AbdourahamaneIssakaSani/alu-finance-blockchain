#include "hblk_crypto.h"


/**
* sha256 - computes the hash of a sequence of bytes
*
* @s: sequence of bytes to be hashed
* @len: number of bytes to hash in s
* @digest: buffer to store the resulting hash
*
* Return: pointer to digest or NULL if an error occurs
*/
uint8_t *sha256(int8_t const *s, size_t len,
uint8_t digest[SHA256_DIGEST_LENGTH])
{

	if (!s || !digest)
		return (NULL);
	return (SHA256((const unsigned char *)s, len, digest));
}
