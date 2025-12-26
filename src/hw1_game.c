#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "hw1.h"


int main(int argc, char **argv) {
    int control  = 0;

    assert(argc == 4); //we want a size, board state, and a list of keys
	initialize_board(argv[2], argv[3], (int)strtoul(argv[1], NULL, 10));	
    print_board((int)strtoul(argv[1], NULL, 10));
    while(control == 0){
        control = get_move();
    }
	
    return 0;
}