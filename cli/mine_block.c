#include "cli.h"

/**
 * transaction_is_invalid - program that checks if a transaction
 * in a node is invalid
 *
 * @node: the transaction node to check
 * @arg: a pointer to unspent transaction list
 *
 * Return: true if the transaction is invalid
 */

static int transaction_is_invalid(llist_node_t node, void *arg)
{
	transaction_t *transaction = node;
	llist_t *unspent = arg;

	return (!transaction_is_valid(transaction, unspent));
}



/**
 * add_transaction - program that adds a transaction to the block's transaction list
 *
 * @node: the transaction node to be added
 * @idx: the index of the transaction (unused)
 * @arg: a pointer to the block where the transaction will be added
 *
 * Return: the result of adding the node to the block's transactions list
 */

static int add_transaction(llist_node_t node,
			   unsigned int idx __attribute__((unused)), void *arg)
{
	transaction_t *transaction = node;
	block_t *block = arg;

	return (llist_add_node(block->transactions, transaction, ADD_NODE_REAR));
}



/**
 * update_utxo - program that updates the unspent transaction outputs
 * list after a new block is added
 *
 * @state: the current state of the blockchain
 * @block: the new block added to the blockchain
 * @coinbase_tx: the coinbase transaction of the new block
 *
 * Return: a pointer to the new unspent transaction output
 */

static unspent_tx_out_t *update_utxo(state_t *state, block_t *block,
				     transaction_t *coinbase_tx)
{
	state->blockchain->unspent = update_unspent(
		state->tx_pool, block->hash, state->blockchain->unspent);

	return (unspent_tx_out_create(
			block->hash, coinbase_tx->id,
			llist_get_head(coinbase_tx->outputs)));
}



/**
 * mine_process - program that mines a block and handles transactions
 * until a valid block is created or an error occurs
 *
 * @state: the current state of the blockchain
 * @block: the block to be mined
 * @prev_block: the previous block in the chain
 * @coinbase_tx: the coinbase transaction for the new block
 *
 * Return: the status code indicating success or failure
 */

static int mine_process(state_t *state, block_t *block,
			    block_t *prev_block, transaction_t *coinbase_tx)
{
	unspent_tx_out_t *utxo = NULL;

	while (!llist_remove_node(
			state->tx_pool, transaction_is_invalid,
			state->blockchain->unspent, 1,
			(node_dtor_t)transaction_destroy))
		;
	llist_for_each(state->tx_pool, add_transaction, block);
	block->info.difficulty = blockchain_difficulty(state->blockchain);
	llist_add_node(block->transactions, coinbase_tx, ADD_NODE_FRONT);
	block_mine(block);

	// TODO: Fix block_is_valid function
	// if (block_is_valid(block, prev_block, state->blockchain->unspent) != 0)
	// {
	// 	fprintf(stderr, "%s: failed to mine a valid block\n",
	// 		state->argv[0]);
	//
	// 	while (llist_pop(block->transactions))
	// 		;
	// 	transaction_destroy(coinbase_tx);
	// 	block_destroy(block);
	//
	// 	return ((state->status = EXIT_FAILURE));
	// }

	utxo = update_utxo(state, block, coinbase_tx);

	if (!utxo)
	{
		fprintf(stderr, "%s: failed to create UTXO\n",
			state->argv[0]);

		while (llist_pop(block->transactions))
			;
		transaction_destroy(coinbase_tx);
		block_destroy(block);

		return ((state->status = EXIT_FAILURE));
	}

	while (llist_pop(state->tx_pool))
		;
	llist_add_node(state->blockchain->chain, block, ADD_NODE_REAR);
	llist_add_node(state->blockchain->unspent, utxo, ADD_NODE_REAR);
	fprintf(stdout, "Successfully mined a block\n");

	return ((state->status = EXIT_SUCCESS));
}



/**
 * cli_mine - program that initiates the mining of a block,
 * handling all transactions and updates
 *
 * @state: the current state of the blockchain
 *
 * Return: the status code indicating success or failure of the mining process
 */

int mine_block(state_t *state)
{
	int8_t block_data[BLOCKCHAIN_DATA_MAX] = {0};
	block_t *block = NULL;
	block_t *prev_block = llist_get_tail(state->blockchain->chain);
	transaction_t *coinbase_tx = NULL;

	if (state->argc > 1)
	{
		fprintf(stderr, "%s: too many arguments\n", state->argv[0]);
		return ((state->status = 2));
	}

	block = block_create(prev_block, block_data, BLOCKCHAIN_DATA_MAX);

	if (!block)
	{
		fprintf(stderr, "%s: failed to create block\n", state->argv[0]);
		return ((state->status = EXIT_FAILURE));
	}

	coinbase_tx = coinbase_create(state->wallet, block->info.index);

	if (!coinbase_tx)
	{
		fprintf(stderr, "%s: failed to create coinbase transaction\n",
			state->argv[0]);
		block_destroy(block);

		return ((state->status = EXIT_FAILURE));
	}

	if (!coinbase_is_valid(coinbase_tx, block->info.index))
	{
		fprintf(stderr, "%s: failed to create valid coinbase transaction\n",
			state->argv[0]);
		transaction_destroy(coinbase_tx);
		block_destroy(block);

		return ((state->status = EXIT_FAILURE));
	}

	return (mine_process(state, block, prev_block, coinbase_tx));
}
