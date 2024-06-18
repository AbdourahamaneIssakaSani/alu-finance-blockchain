//
// Created by abissa on 6/11/24.
//

#ifndef UTILS_H
#define UTILS_H
#include "../blockchain/v0.3/blockchain.h"

void _print_hex_buffer(uint8_t const *buf, size_t len);

static int _tx_in_print(tx_in_t const *in, unsigned int idx,
    char const *indent);

int _tx_out_print(tx_out_t const *out, unsigned int idx,
    char const *indent);

int _transaction_print_brief_loop(transaction_t const *transaction,
    unsigned int idx, char const *indent);

void _transaction_print_brief(transaction_t const *transaction);

int _transaction_print_loop(transaction_t const *transaction,
    unsigned int idx, char const *indent);

static int _block_print_brief(block_t const *block, unsigned int index,
    char const *indent);

int _block_print(block_t const *block, unsigned int index,
    char const *indent);

void _blockchain_print(blockchain_t const *blockchain);

void _blockchain_print_brief(blockchain_t const *blockchain);


#endif //UTILS_H
