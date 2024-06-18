//
// Created by abissa on 6/18/24.
//

#include "cli.h"

void create_blockchain(state_t *state){
    blockchain_t *blockchain = blockchain_create();
    if (blockchain) {
        state->blockchain = blockchain;
        printf("Blockchain created successfully\n");
        _blockchain_print(blockchain);
    } else {
        printf("Failed to create blockchain\n");
        blockchain_destroy(state->blockchain);
    }
}