#include "list.h"

//-----------------------------------------------------------------------------


List list_ctor()
{
    struct List strc;

    strc.arr = arr_ctor();

    stackCtor(&strc.free_elem);
    for (int num = size_of_list; num >= 1; num--)
    {
        stackPush(&strc.free_elem, num);
    }

    strc.num_of_free_elem = size_of_list;
    strc.head = 1;
    strc.tail = 0;
    strc.capacity = size_of_list;

    return strc;
}

void list_dtor(List *strc)
{
    ASSERT(strc == NULL, "Void ptr");
    ASSERT(strc->capacity == 0, "Repearted list_dtor");

    free(strc->arr);

    stackDtor(&strc->free_elem);

    strc->head = -1;
    strc->tail = -1;
    strc->capacity = 0;
}

Arr *arr_ctor()
{
    struct Arr *arr = (Arr *)calloc(size_of_list + 1, sizeof(Arr));
    ASSERT(arr == NULL, "Can't alloc memeory");

    for (int idx = 0; idx <= size_of_list; idx++) {
        arr[idx].data = 0;
        arr[idx].next = -1;
        arr[idx].prev = -1;
    }

    arr[0].next = 0;
    arr[0].prev = 0;

    return arr;
}


//-----------------------------------------------------------------------------


size_t idx_of_head(List *strc)
{
    ASSERT(strc == NULL, "Void ptr");
    return strc->head;
}

size_t idx_of_tail(List *strc)
{
    ASSERT(strc == NULL, "Void ptr");
    return strc->tail;
}

size_t idx_of_next(List *strc, size_t idx)
{
    ASSERT(strc == NULL, "Void ptr");
    ASSERT(idx <= 0, "Index <= 0");
    return strc->arr[idx].next;
}

size_t idx_of_prev(List *strc, size_t idx)
{
    ASSERT(strc == NULL, "Void ptr");
    ASSERT(idx <= 0, "Index <= 0");
    return strc->arr[idx].prev;
}


//-----------------------------------------------------------------------------


void ins_at_the_beg(List *strc, double val)
{
    ASSERT(strc == NULL, "Void ptr");

    CHECK_AND_REALLOC;

    GET_IDX_OF_FREE_ELEM;

    strc->arr[idx].data = val;
    strc->arr[idx].next = strc->head;
    strc->arr[idx].prev = 0;

    strc->arr[strc->head].prev = idx;

    strc->head = idx;
}

void ins_at_the_end(List *strc, double val)
{
    ASSERT(strc == NULL, "Void ptr");

    CHECK_AND_REALLOC;

    GET_IDX_OF_FREE_ELEM;

    strc->arr[idx].data = val;
    strc->arr[idx].next = 0;
    strc->arr[idx].prev = strc->tail;

    strc->arr[strc->tail].next = idx;

    strc->tail = idx;
}


//-----------------------------------------------------------------------------


void ins_before(List *strc, size_t elem, double val)
{
    ASSERT(strc == NULL, "Void ptr");
    ASSERT((elem <= 0) || (strc->arr[elem].next == -1), "Incorrect element");

    CHECK_AND_REALLOC;

    GET_IDX_OF_FREE_ELEM;

    size_t prev_of_elem = strc->arr[elem].prev;

    strc->arr[idx].data = val;
    strc->arr[idx].next = elem;
    strc->arr[idx].prev = prev_of_elem;

    strc->arr[elem].prev = idx;

    strc->arr[prev_of_elem].next = idx;
}

void ins_after(List *strc, size_t elem, double val)
{
    ASSERT(strc == NULL, "Void ptr");
    ASSERT((elem <= 0) || (strc->arr[elem].next == -1), "Incorrect element");

    CHECK_AND_REALLOC;

    GET_IDX_OF_FREE_ELEM;

    size_t next_of_elem = strc->arr[elem].next;

    strc->arr[idx].data = val;
    strc->arr[idx].next = next_of_elem;
    strc->arr[idx].prev = elem;

    strc->arr[elem].next = idx;

    strc->arr[next_of_elem].prev = idx;
}


//-----------------------------------------------------------------------------


void del_elem(List *strc, size_t elem)
{
    ASSERT(strc == NULL, "Void ptr");
    ASSERT((elem <= 0) || (strc->arr[elem].next == -1), "Incorrect element");

    if (elem == strc->head)
        strc->head = strc->arr[elem].next;

    if (elem == strc->tail)
        strc->tail = strc->arr[elem].prev;

    size_t next_of_elem = strc->arr[elem].next;
    size_t prev_of_elem = strc->arr[elem].prev;

    strc->arr[next_of_elem].prev = prev_of_elem;
    strc->arr[prev_of_elem].next = next_of_elem;

    strc->arr[elem].data = 0;
    strc->arr[elem].next = -1;
    strc->arr[elem].prev = -1;

    stackPush(&strc->free_elem, elem);
    strc->num_of_free_elem++;
}

void del_ALL_elem(List *strc) {
    ASSERT(strc == NULL, "Void ptr");

    for (unsigned idx = 0; idx <= strc->capacity; idx++) {
        strc->arr[idx].data = 0;
        strc->arr[idx].next = -1;
        strc->arr[idx].prev = -1;         
    }
}


//-----------------------------------------------------------------------------


void print_list(List *strc)
{
    ASSERT(strc == NULL, "Void ptr");

    printf("   --- HEAD  --- TAIL  ---\n");
    printf("   --- %5ld --- %5ld\n", strc->head, strc->tail);

    printf("\n   --- DATA  --- NEXT  --- PREV  ---\n");

    for (unsigned num = 0; num <= strc->capacity; num++) {
        printf("%3d--- %5.1f --- %5d --- %5d ---\n", num, strc->arr[num].data, strc->arr[num].next, strc->arr[num].prev);
    }

    printf("\n--- STACK OF FREE ELEM ---\n");
    prinStack(&strc->free_elem);

    printf("%5ld --- NUM OF FREE ELEM\n", strc->num_of_free_elem);
}


//-----------------------------------------------------------------------------


void realloc_list(List *strc) {
    ASSERT(strc == NULL, "Void ptr");

    size_t old_capacity = strc->capacity;
    strc->capacity *= resize_coeff;

    Arr *tmp = (Arr *)realloc(strc->arr, (strc->capacity + 1) * sizeof(Arr));
    if (tmp == NULL) 
        ASSERT(tmp == NULL, "Can't realloc memeory");
    else 
        strc->arr = tmp;

    for (unsigned idx = strc->capacity; idx >= old_capacity + 1; idx--) {
        stackPush(&strc->free_elem, idx);
        strc->num_of_free_elem++;

        strc->arr[idx].data = 0;
        strc->arr[idx].next = -1;
        strc->arr[idx].prev = -1;  
    }
}


//-----------------------------------------------------------------------------


void sort_list_by_prev_slow_slow(List *strc) {
    ASSERT(strc == NULL, "Void ptr");
    qsort(strc->arr, strc->capacity, sizeof(Arr), list_cmp);
}

int list_cmp(const void *a, const void *b) {
    const Arr *ptr_a = (const Arr*)a;
    const Arr *ptr_b = (const Arr*)b;

    if (ptr_a->prev == -1) 
        return 1;
    
    if (ptr_b->prev == -1)
        return -1;
    
    if (ptr_a->prev > ptr_b->prev)
        return 1;
    else if (ptr_a->prev == ptr_b->prev)
        return 0;
    else 
        return -1;
}


//-----------------------------------------------------------------------------


size_t search_elem_slow_slow(List *strc, double val) {
    ASSERT(strc == NULL, "Void ptr");

    for (unsigned num = 1; num <= strc->capacity; num++) {
        if (isequal(strc->arr[num].data, val))
            return num;
    }

    ASSERT(1, "There is no such number in the list");
    return 404;    
}

bool isequal(double a, double b) {
    const double EPSILON = 0.0001; //measurement error
    
    if (fabs(a - b) <= EPSILON)
        return 1;
    else 
        return 0;
}