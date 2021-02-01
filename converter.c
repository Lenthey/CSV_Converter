/* 
 * CSE30 hw2 code file
 * Name: Zakir Shay
 * PID: A15649809
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "converter.h"

/*
 * main function
 * 
 * Arguments:   argc, argv
 * Operation:   
 * Returns:     
 */
int main(int argc, char **argv) {
    int opt;
    int c_flag = 0;
    int err_opt = 0;

    // unsigned int is not used since atoi() returns int
    int col_size;

    //TODO: handle -c at different positions
    while ((opt = getopt(argc, argv, "c:")) != -1) {
        switch (opt) {
            case 'c':
                c_flag = 1;
                //TODO: atoi
                col_size = atoi(optarg);
                break;
            default:
                err_opt = 1;
        }
    }

    if (err_opt || argc < 4) {
        print_usage(*argv);
    } else if (c_flag) {
        converter(argc, argv, col_size);
    }

    print_usage(*argv);
}

/*
 * converter function
 * 
 * Arguments:   argc, argv
 * Operation:   
 * Returns:     
 */
void converter(int argc, char **argv, int col_size) {
    // record column order for output
    const int OPTION_OFFSET = 3;
    int order_size = argc - OPTION_OFFSET;
    int *order_arr = (int *)malloc(sizeof(int) * (order_size));
    for (int i = 0; i < order_size; i++) {
        //TODO
        // non number argument is not safely handled yet
        // out of boundary value is also not handled yet
        order_arr[i] = atoi(argv[i + OPTION_OFFSET]);
    }

    int entry_count = 0;
    int in_quote = 0;
    char *buf = NULL;
    size_t buf_size = 0;
    char **col_arr = (char **)malloc(sizeof(char *) * col_size);

    while (getline(&buf, &buf_size, stdin) > 0) {
        in_quote = 0;
        entry_count = 1;

        for (int i = 0; i < buf_size; i++) {
            if (buf[i]=='\"') {
                in_quote = ((in_quote == 0) ? 1 : 0);
            } else if (in_quote == 0 && (buf[i]==',' || buf[i]=='\n')) {
                buf[i] = '\0';

                if (entry_count < col_size) {
                    col_arr[entry_count++] = &buf[i+1];
                }
            } else if (buf[i]=='\0') {
                // getline realloc() by doubling the size so there will be grabage value
                // must stop at first \0 to avoid in_quote malfunction
                break;
            }
        }

        // no output for unmatched quotes
        if (in_quote == 1) {
            continue;
        }

        col_arr[0] = &buf[0];

        /*
         * Print reordered values
         */
        for (int i = 0; i < order_size - 1; i++) {
            printf("%s,", col_arr[order_arr[i]-1]);
        }
        printf("%s\n", col_arr[order_arr[order_size-1]-1]);

        // cant free buff. This will cause error. I guess it is because \0 appears in the middle of the string.
        // free(buf);
    }

    free(order_arr);
    free(col_arr);

    exit(EXIT_SUCCESS);
}

/*
 * print_usage function
 * 
 * Arguments:   argc, argv
 * Operation:   
 * Returns:     
 */
void print_usage(char *name) {
    fprintf(stderr, "%s -c input_column_count col# [col#...]\n", name);
    exit(EXIT_FAILURE);
}
