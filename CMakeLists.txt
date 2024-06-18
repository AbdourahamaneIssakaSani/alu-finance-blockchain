cmake_minimum_required(VERSION 3.28)
project(BlockChainSummative C)

set(CMAKE_C_STANDARD 11)

add_executable(BlockChainSummative
        blockchain/v0.3/transaction/coinbase_create.c
        blockchain/v0.3/transaction/coinbase_is_valid.c
        blockchain/v0.3/transaction/transaction.h
        blockchain/v0.3/transaction/transaction_create.c
        blockchain/v0.3/transaction/transaction_destroy.c
        blockchain/v0.3/transaction/transaction_hash.c
        blockchain/v0.3/transaction/transaction_is_valid.c
        blockchain/v0.3/transaction/tx_in_create.c
        blockchain/v0.3/transaction/tx_in_sign.c
        blockchain/v0.3/transaction/tx_out_create.c
        blockchain/v0.3/transaction/unspent_tx_out_create.c
        blockchain/v0.3/transaction/update_unspent.c
        blockchain/v0.3/block_create.c
        blockchain/v0.3/block_destroy.c
        blockchain/v0.3/block_hash.c
        blockchain/v0.3/block_is_valid.c
        blockchain/v0.3/block_mine.c
        blockchain/v0.3/blockchain.h
        blockchain/v0.3/blockchain_create.c
        blockchain/v0.3/blockchain_deserialize.c
        blockchain/v0.3/blockchain_destroy.c
        blockchain/v0.3/blockchain_difficulty.c
        blockchain/v0.3/blockchain_serialize.c
        blockchain/v0.3/hash_matches_difficulty.c
        cli/main.c
        cli/exit.c
        cli/cli.h
        cli/help.c
        cli/print_blockchain.c
        cli/load_blockchain.c
        cli/mine_block.c
        cli/save.c
        cli/add_transaction.c
        cli/load_wallet.c
        cli/save_wallet.c
        cli/find_command.c
        cli/get_commands.c
        cli/state_clear.c
        cli/state_init.c
        crypto/ec_create.c
        crypto/ec_from_pub.c
        crypto/ec_load.c
        crypto/ec_save.c
        crypto/ec_sign.c
        crypto/ec_to_pub.c
        crypto/ec_verify.c
        crypto/hblk_crypto.h
        crypto/sha256.c
        utils/provided.h
        utils/endianness.h
        utils/_print_hex_buffer.c
        utils/_genesis.c
        utils/_endianness.c
        utils/_blockchain_print.c
        utils/_transaction_print.c
        utils/_transaction_print_brief.c
        utils/utils.h
        cli/info_tx.c
        cli/create_blockchain.c)

# Find OpenSSL library
find_package(OpenSSL REQUIRED)

# Include directories for OpenSSL
include_directories(${OPENSSL_INCLUDE_DIR})

# Link libraries
target_link_libraries(BlockChainSummative ${OPENSSL_LIBRARIES} /usr/local/lib/libllist.so)
