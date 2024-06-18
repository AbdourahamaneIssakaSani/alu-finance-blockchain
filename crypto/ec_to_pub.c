#include "hblk_crypto.h"


/**
 * ec_to_pub - extracts the public key from an EC_KEY struct
 *
 * @key: pointer to the EC_KEY struct
 * @pub: address at which to store the extracted public key
 *
 * Return: pointer to @pub or NULL upon failure
 */
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	const EC_POINT *point = NULL;
	const EC_GROUP *group = NULL;

	if (!key || !pub)
		return (NULL);
	group = EC_KEY_get0_group(key);
	point = EC_KEY_get0_public_key(key);
	if (!group || !point)
		return (NULL);
	if (!EC_POINT_point2oct(group, point, POINT_CONVERSION_UNCOMPRESSED,
		pub, EC_PUB_LEN, NULL))
		return (NULL);
	return (pub);
}
