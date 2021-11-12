#ifndef LIST_H_
#define LIST_H_

#include "stack.h"
#include <math.h>

#ifndef CHECK_AND_REALLOC
#define CHECK_AND_REALLOC   if (strc->num_of_free_elem == 0) \
                                realloc_list(strc);          
#endif

#ifndef GET_IDX_OF_FREE_ELEM
#define GET_IDX_OF_FREE_ELEM    int idx = strc->free_elem.data[strc->free_elem.Size]; \
                                stackPop(&strc->free_elem);                           \
                                strc->num_of_free_elem--;                             
#endif

#ifndef ASSERT
#define ASSERT(statement, text) do {                                                                                    \
                                     if (statement) {                                                                   \
                                        printf (" %s:%d, IN FUNCTION %s:\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);  \
                                        printf (#text);                                                                 \
                                    }                                                                                   \
                                } while (0)
#endif

struct Arr {
    double data;
    int next;
    int prev;
};

struct List {
    struct Arr *arr;
    struct Stack free_elem;
    size_t num_of_free_elem;
    size_t head;
    size_t tail;
    size_t capacity;
};

const int size_of_list = 10;
const int resize_coeff = 2;

List list_ctor(); 
void list_dtor(List *strc);
Arr* arr_ctor();

size_t idx_of_head(List *strc);
size_t idx_of_tail(List *strc);
size_t idx_of_next(List *strc, size_t idx);
size_t idx_of_prev(List *strc, size_t idx);

void ins_at_the_beg(List *strc, double val);
void ins_at_the_end(List *strc, double val);

void ins_before(List *strc, size_t elem, double val);
void ins_after(List *strc, size_t elem, double val);

void del_elem(List *strc, size_t elem);

void realloc_list(List *strc);

void sort_list_by_prev_slow_slow(List *strc);
int list_cmp(const void *a, const void *b);

size_t search_elem_slow_slow(List *strc, double val);
bool isequal(double a, double b);

void print_list(List *strc);

#endif
