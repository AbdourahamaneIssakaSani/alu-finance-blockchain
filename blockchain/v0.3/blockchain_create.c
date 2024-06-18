#include "blockchain.h"

/**
 * blockchain_create - creates a genesis blockchain
 * Return: pointer to new blockchain or NULL on error
 */
blockchain_t *blockchain_create(void)
{
	blockchain_t *chain = calloc(1, sizeof(*chain));
	block_t *block = calloc(1, sizeof(*block));
	llist_t *list = llist_create(MT_SUPPORT_TRUE);
	llist_t *unspent = llist_create(MT_SUPPORT_TRUE);

	if (!chain || !block || !list || !unspent)
	{
		free(chain), free(block), llist_destroy(list, 1, NULL);
		llist_destroy(unspent, 1, NULL);
		return (NULL);
	}

	block->info.timestamp = GENESIS_TIMESTAMP;
	memcpy(&(block->data.buffer), GENESIS_DATA, GENESIS_DATA_LEN);
	block->data.len = GENESIS_DATA_LEN;
	memcpy(&(block->hash), GENESIS_HASH, SHA256_DIGEST_LENGTH);

	if (llist_add_node(list, block, ADD_NODE_FRONT))
	{
		free(chain), free(block), llist_destroy(list, 1, NULL);
		return (NULL);
	}
	chain->chain = list;
	chain->unspent = unspent;
	printf("Created genesis block with difficulty %u\n", block->info.difficulty);
	return (chain);
}
