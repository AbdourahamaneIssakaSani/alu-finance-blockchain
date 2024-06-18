#include "cli.h"

/**
 * handle_transaction_send - program that attempts to create
 * and send a transaction based on provided receiver's public key,
 * amount to transfer, and state information
 *
 * @state: the current state containing wallet, blockchain,
 *         and transaction pool information
 * @amount: the amount of cryptocurrency to send
 * @pub: the public key of the receiver, in bytes,
 *       used to identify the recipient
 *
 * Return: - EXIT_SUCCESS if the transaction is successfully
 *           added to the local transaction pool,
 *         - otherwise, returns EXIT_FAILURE
 */

static int handle_transaction_send(state_t *state, uint32_t amount,
uint8_t pub[EC_PUB_LEN], const char *payment_id,
			   const char *student_id,
			   const char *session_id)
{
	EC_KEY *receiver = NULL;
	transaction_t *tx = NULL;

	receiver = ec_from_pub(pub);

	if (!receiver)
	{
		fprintf(stderr, "%s: %s: invalid receiver public key\n",
			state->argv[0], state->argv[1]);
		return ((state->status = EXIT_FAILURE));
	}

	tx = transaction_create(
		state->wallet, receiver, amount, state->blockchain->unspent);

	if (!tx)
	{
		fprintf(stderr, "%s: failed to create transaction\n",
			state->argv[0]);
		EC_KEY_free(receiver);
		return ((state->status = EXIT_FAILURE));
	}
	tx->payment_id = strdup(payment_id);
	tx->student_id = strdup(student_id);
	tx->session_id = strdup(session_id);

	if (!transaction_is_valid(tx, state->blockchain->unspent))
	{
		fprintf(stderr, "%s: invalid transaction\n",
			state->argv[0]);
		EC_KEY_free(receiver);
		transaction_destroy(tx);
		return ((state->status = EXIT_FAILURE));
	}
	if (llist_add_node(state->tx_pool, tx, ADD_NODE_REAR) == -1)
	{
		fprintf(stdout, "Failed to add transaction to local transaction pool\n");
		EC_KEY_free(receiver);
		transaction_destroy(tx);
		return ((state->status = EXIT_FAILURE));
	}

	fprintf(stdout, "Transaction added to local transaction pool\n");
	EC_KEY_free(receiver);

	return ((state->status = EXIT_SUCCESS));
}



/**
 * cli_send - program that processes the input parameters
 * to extract a public key and a transfer amount, then calls
 * 'handle_transaction_send' to attempt the transaction
 *
 * @state: the current CLI state including arguments from the command line
 *
 * Return: 2 on argument errors, EXIT_FAILURE on processing errors,
 *         or the result of 'handle_transaction_send'
 */

int transaction_add(state_t *state)
{
	uint8_t pub[EC_PUB_LEN] = {0};
	size_t pub_index = 0;
	unsigned long int amount = 0;
	int nmatched = 0;
	char *endptr = NULL;

	if (state->argc > 6)
	{
		fprintf(stderr, "%s: too many arguments\n", state->argv[0]);
		return ((state->status = 2));
	}
	if (state->argc < 6)
	{
		fprintf(stderr, "%s: too few arguments\n", state->argv[0]);
		return ((state->status = 2));
	}

	errno = 0;
	amount = strtoul(state->argv[1], &endptr, 0);

	if ((errno != 0 && (amount == 0 || amount == ULONG_MAX)) ||
		(*state->argv[1] == '\0' || *endptr != '\0') ||
		(amount > UINT32_MAX))
	{
		fprintf(stderr, "%s: %s: invalid amount\n",
			state->argv[0], state->argv[1]);

		return ((state->status = EXIT_FAILURE));
	}
	while (pub_index < EC_PUB_LEN)
	{
		nmatched = sscanf(
			(state->argv[2] + (2 * pub_index)), "%02x",
			(unsigned int *)(pub + pub_index));

		if (nmatched == 0)
			break;
		pub_index += 1;
	}

	return (handle_transaction_send(state, (uint32_t)amount, pub, state->argv[3], state->argv[4], state->argv[5]));
}
