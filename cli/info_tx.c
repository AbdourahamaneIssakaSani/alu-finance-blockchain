//
// Created by abissa on 6/14/24.
//

#include "cli.h"

/**
 * info_tx - entry point for the info_tx command
 * Print all transactions of each block in the blockchain
 *
 * @state: the CLI state
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int info_tx(state_t *state)
{
    if (!state)
        return (EXIT_FAILURE);

    // print transactions of each block
    llist_for_each(state->blockchain->chain, _block_print, 0);

    return (EXIT_SUCCESS);

}
