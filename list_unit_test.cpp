#include "list_unit_test.h"

void list_unit_test(List list){
    char com[30] = ""; 
    int val1 = 0, val2 = 0;   
    GET_COMMAND;

    while (strcmp(com, "q")) {
    
        if (strcmp(com, "idx_of_head") == 0){
            size_t res = idx_of_head(&list);

            printf("%ld <-- HEAD\n", res);
            
            CLEAN_BUFFER;
            GET_COMMAND;
                
            continue;
        }

        else if (strcmp(com, "idx_of_tail") == 0){
            size_t res = idx_of_tail(&list);

            printf("%ld <-- TAIL\n", res);
            
            CLEAN_BUFFER;
            GET_COMMAND;
                
            continue;
        }

        else if (strcmp(com, "idx_of_next") == 0){
            size_t res = idx_of_next(&list, val1);

            printf("%ld <-- NEXT\n", res);
            
            CLEAN_BUFFER;
            GET_COMMAND;
                
            continue;
        }

        else if (strcmp(com, "idx_of_prev" ) == 0){
            size_t res = idx_of_prev(&list, val1);

            printf("%ld <-- PREV\n", res);
            
            CLEAN_BUFFER;
            GET_COMMAND;
                
            continue;
        }

        else if (strcmp(com, "ins_at_the_beg") == 0){
            ins_at_the_beg(&list, val1);

            print_list(&list);
            
            CLEAN_BUFFER;
            GET_COMMAND;
            
            continue;
        }

        else if (strcmp(com, "ins_at_the_end") == 0){
            ins_at_the_end(&list, val1);

            print_list(&list);
            
            CLEAN_BUFFER;
            GET_COMMAND;
            
            continue;
        }

        else if (strcmp(com, "ins_before") == 0){
            ins_before(&list, val1, val2);

            print_list(&list);
            
            CLEAN_BUFFER;
            GET_COMMAND;
            
            continue;
        }

        else if (strcmp(com, "ins_after") == 0){
            ins_after(&list, val1, val2);

            print_list(&list);
            
            CLEAN_BUFFER;
            GET_COMMAND;
            
            continue;
        }

        else if (strcmp(com, "del_elem") == 0){
            del_elem(&list, val1);

            print_list(&list);
            
            CLEAN_BUFFER;
            GET_COMMAND;
            
            continue;
        }

        else if (strcmp(com, "del_ALL_elem") == 0){
            del_ALL_elem(&list);

            print_list(&list);
            
            CLEAN_BUFFER;
            GET_COMMAND;
            
            continue;
        }

        else if (strcmp(com, "sort_list_by_prev_slow_slow") == 0){
            sort_list_by_prev_slow_slow(&list);

            print_list(&list);
            
            CLEAN_BUFFER;
            GET_COMMAND;
            
            continue;
        }

        else if (strcmp(com, "search_elem_slow_slow") == 0){
            size_t res = search_elem_slow_slow(&list, val1);

            printf("%ld <-- IDX OF ELEM\n", res);
            
            CLEAN_BUFFER;
            GET_COMMAND;
            
            continue;
        }
    }
}