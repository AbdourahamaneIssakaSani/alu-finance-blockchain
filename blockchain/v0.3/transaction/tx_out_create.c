#include "transaction.h"


/**
* tx_out_create - creates a transaction output structure
*
* @amount:	  amount to store in the transaction output
* @pub:	  public key of the receiver
*
* Return: a new transaction output structure
*/
tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN])
{
	tx_out_t *tx_out;

	if (!amount || !pub)
		return (NULL);

	tx_out = calloc(1, sizeof(*tx_out));
	if (!tx_out)
		return (NULL);

	memcpy(tx_out->pub, pub, sizeof(tx_out->pub));
	tx_out->amount = amount;
	if (!sha256((int8_t const *)tx_out,
	sizeof(tx_out->amount) + sizeof(tx_out->pub), tx_out->hash))
	{
		free(tx_out);
		return (NULL);
	}


	return (tx_out);
}
