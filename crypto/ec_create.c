#include "hblk_crypto.h"
#include "../utils/utils.h"

/**
* ec_create - create a new EC key pair
*
* Return: pointer to the created EC key pair, or NULL upon failure
*/
EC_KEY *ec_create(void)
{
	EC_KEY *key = NULL;
	uint8_t pub[EC_PUB_LEN];

	key = EC_KEY_new_by_curve_name(EC_CURVE);
	if (!key)
		return (NULL);
	if (!EC_KEY_generate_key(key))
	{
		EC_KEY_free(key);
		return (NULL);
	}
	printf("Public key: ");
	_print_hex_buffer(pub, EC_PUB_LEN);
	printf("\n");
	return (key);
}
