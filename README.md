# My Blockchain
My blockchain is a simple implementation of a blockchain. Users can create **nodes** and chain data together in form of **blocks**. Furthermore, the program will automatically persist the data in memory to the file `bin/saved_nodes.txt`. The file will be then loaded in upon application launch. Note that data will only be persisted if the user exits the program using the `quit` command. The data in memory will be lost if the user exits using the interrupt command –`^c`.

## Compile & Launch

Use make to compile the application

    $ make

and run

    ./bin/my_blockchain

You can also clean with

    $ make clean

## Usage

     <[s0]> ls [-l]

Lists all nodes in the blockchain. `-l` will also list the blocks contained on each node.

     <[s0]> sync

This command will sync the blocks of all nodes in the blockchain. Synced nodes will have the exact same blocks though unorderly.

     <[s0]> quit 

     <[s0]> add node nid 

Adds a node indentified as nid to the blockchain. A nid **MUST** be an number.

     <[s0]> rm node [nid | *]

Removes a node to the blockchain. Passing in a wildcard `*` will delete node in the blockchain.

     <[s0]> add block bid [nid | *] 

Adds a block to a node. Omiting a node identifier will add the block to every available node in the blockchain. Passing in a wildcard `*` will add block in question to every subsquent node created. The `*` command will break whenever users issues a new block command like so `add block block_name nid`.

     <[s0]> rm block bid [nid]

Similarly to `add block`, if the user doesn't specify a `nid` the program will remove the block `bid` from every node in the blockchain. 

## Tests

This program is partially convered by tests.
