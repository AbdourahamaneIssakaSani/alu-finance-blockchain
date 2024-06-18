#ifndef CLI_H
#define CLI_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

#include <llist.h>

#include "../crypto/hblk_crypto.h"
#include "../blockchain/v0.3/blockchain.h"
#include "../utils/provided.h"
#include "../blockchain/v0.3/transaction/transaction.h"



#define BLANK " \t\n"

#define PROMPT "> "

#define EXIT_NAME "exit"
#define EXIT_HELP "exit"
#define EXIT_DESCRIPTION "Exit."

#define HELP_NAME "help"
#define HELP_HELP "help [COMMAND]"
#define HELP_DESCRIPTION "Display information about available commands."

#define CREATE_BLOCKCHAIN_NAME "create_blockchain"
#define CREATE_BLOCKCHAIN_HELP "create_blockchain"
#define CREATE_BLOCKCHAIN_DESCRIPTION "Creates a new blockchain."

#define PRINT_BLOCKCHAIN_NAME "print_blockchain"
#define PRINT_BLOCKCHAIN_HELP "print_blockchain"
#define PRINT_BLOCKCHAIN_DESCRIPTION "Display information about the local blockchain."

#define INFO_TX_NAME "info_tx"
#define INFO_TX_HELP "info_tx TXID"
#define INFO_TX_DESCRIPTION "Display information about a transaction."

#define LOAD_NAME "load"
#define LOAD_HELP "load PATH"
#define LOAD_DESCRIPTION "Load blockchain from a file."

#define MINE_BLOCK_NAME "mine_block"
#define MINE_BLOCK_HELP "mine_block"
#define MINE_BLOCK_DESCRIPTION "Mine a block."

#define SAVE_NAME "save"
#define SAVE_HELP "save PATH"
#define SAVE_DESCRIPTION "Save blockchain to a file."

#define ADD_TRANSACTION_NAME "add_transaction"
#define ADD_TRANSACTION_HELP "add_transaction AMOUNT ADDRESS [PAYMENT_ID] [STUDENT_ID] [SESSION_ID]"
#define ADD_TRANSACTION_DESCRIPTION "Send coins."

#define WALLET_LOAD_NAME "wallet_load"
#define WALLET_LOAD_HELP "wallet_load PATH"
#define WALLET_LOAD_DESCRIPTION "Load wallet from a file."

#define WALLET_SAVE_NAME "wallet_save"
#define WALLET_SAVE_HELP "wallet_save PATH"
#define WALLET_SAVE_DESCRIPTION "Save wallet to a file."



/**
 * struct state_s - CLI state structure
 *
 * @status: status of the most recently executed command
 * @argc: command argument count
 * @argv: command argument vector
 * @line: command line buffer
 * @linesz: size of @line
 * @wallet: wallet
 * @blockchain: blockchain
 * @tx_pool: transaction pool
 */

typedef struct state_s
{
	int status;
	int argc;
	char **argv;
	char *line;
	size_t linesz;
	EC_KEY *wallet;
	blockchain_t *blockchain;
	llist_t *tx_pool;
} state_t;


typedef int (*command_func_t)(state_t *);


/**
 * struct command_s - CLI command structure
 *
 * @func: function associated with the command
 * @name: name of the command
 * @help: short help for the command
 * @desc: description of the command
 */

typedef struct command_s
{
	command_func_t func;
	char const *name;
	char const *help;
	char const *desc;
} command_t;



/* cli_exit.c */
int exit_program(state_t *state);

/* cli_help.c */
int help(state_t *state);

/* cli_info.c */
static int sum_unspent_amounts(void *node,
			       unsigned int idx __attribute__((unused)), void *arg);

void create_blockchain(state_t *state);
int print_blockchain(state_t *state);

int info_tx(state_t *state);

/* cli_load.c */
int load(state_t *state);

/* cli_mine.c */
static int transaction_is_invalid(llist_node_t node, void *arg);
static int add_transaction(llist_node_t node,
			   unsigned int idx __attribute__((unused)), void *arg);
static unspent_tx_out_t *update_utxo(state_t *state, block_t *block,
				     transaction_t *coinbase_tx);
static int mine_process(state_t *state, block_t *block,
			    block_t *prev_block, transaction_t *coinbase_tx);
int mine_block(state_t *state);

/* cli_save.c */
static int handle_transaction_send(state_t *state, uint32_t amount,
uint8_t pub[EC_PUB_LEN], const char *payment_id,
			   const char *student_id,
			   const char *session_id);

int save(state_t *state);

/* cli_send.c */
int transaction_add(state_t *state);

/* cli_wallet_load.c */
int load_wallet(state_t *state);

/* cli_wallet_save.c */
int save_wallet(state_t *state);

/* get_commands.c */
command_t const *get_commands(void);

/* find_command.c */
command_t const *find_command(char const *name);

/* state_init.c */
void state_init(state_t *state);

/* state_clear.c */
void state_clear(state_t *state);



#endif /* CLI_H */
