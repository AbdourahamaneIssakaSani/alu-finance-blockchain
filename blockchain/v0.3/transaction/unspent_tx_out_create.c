#include "transaction.h"


/**
* unspent_tx_out_create - creates an unspent transaction output structure
*
* @block_hash: hash of the Block containing the transaction @tx_id
* @tx_id: ID of the transaction containing @tx_out_hash
* @tx_out: copy of the referenced transaction output
*
* Return: a new unspent transaction output structure
*/
unspent_tx_out_t *unspent_tx_out_create(
	uint8_t block_hash[SHA256_DIGEST_LENGTH],
	uint8_t tx_id[SHA256_DIGEST_LENGTH], tx_out_t const *tx_out)
{
	unspent_tx_out_t *unspent_tx_out;

	if (!block_hash || !tx_id || !tx_out)
		return (NULL);

	unspent_tx_out = calloc(1, sizeof(*unspent_tx_out));
	if (!unspent_tx_out)
		return (NULL);

	memcpy(unspent_tx_out->block_hash, block_hash,
	sizeof(unspent_tx_out->block_hash));
	memcpy(unspent_tx_out->tx_id, tx_id, sizeof(unspent_tx_out->tx_id));
	memcpy(&unspent_tx_out->out, tx_out, sizeof(unspent_tx_out->out));

	return (unspent_tx_out);
}
