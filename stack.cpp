#include "stack.h"

extern int DEBUG_LEVEL;

ERRORS stackCtor (Stack* st)
{
    ERROR_INFO(st == 0, "ERROR: Void ptr on stack\n");

    st->capacity = START_STACK_SIZE; 
    st->Size = 0;

    st->data = (double*) calloc (st->capacity + 2, sizeof (double));
    ERROR_INFO(st->data == NULL, "ERROR: Can't alloc memory\n");

    st->data++;

    st->leftCanary = CANARY; 
    st->rightCanary = CANARY;
    PUT_CANARY;

    CHECK_STACK;

    return NO_ERRORS;
}


//-----------------------------------------------------------------------------


ERRORS stackPush (Stack* st, double value)
{
    CHECK_STACK;

    if (st->Size >= st->capacity)
        reallocate (st, st->capacity * RESIZE_COEFFICIENT);

    *(st->data + st->Size) = value;
    
    st->Size++;

    CHECK_STACK;

    return NO_ERRORS;
}


//-----------------------------------------------------------------------------


ERRORS stackPop (Stack* st)
{
    CHECK_STACK;

    if ((st->Size <= st->capacity/RESIZE_COEFFICIENT) && (st->capacity != START_STACK_SIZE))
        reallocate (st, st->capacity/RESIZE_COEFFICIENT);
    
    st->data[st->Size] = POISON;
    
    --st->Size;
    PUT_CANARY;

    CHECK_STACK;

    return NO_ERRORS;
}


//-----------------------------------------------------------------------------


ERRORS stackDtor (Stack* st)
{
    CHECK_STACK;

    free (--st->data);
    st->Size = -1;

    return NO_ERRORS;
}


//-----------------------------------------------------------------------------


ERRORS reallocate (Stack* st, const size_t newSize) //static
{
    CHECK_STACK;

    st->capacity = newSize;
    st->data--;

    double *tmp = (double*) realloc (st->data, (st->capacity + 2) * sizeof(double));
    if (tmp != NULL)
    {   
        st->data = tmp;
        st->data++;
    }
    else
        ERROR_INFO(tmp == NULL, "ERROR: Can't realloc memory\n");

    PUT_CANARY;

    CHECK_STACK;

    return NO_ERRORS;
}


//-----------------------------------------------------------------------------


void stackDump (int error)
{
    switch (error)
    {
        case STACK_UNDERFLOW:
            printf ("\t\tERROR CODE: Stack Underflow\n");
            break;

        case STACK_OVERFLOW:
            printf ("\t\tERROR CODE: Stack Overflow\n");
            break;

        case VOID_STACK:
            printf ("\t\tERROR CODE: Pointer on tack is NULL\n");
            break;
        
        case ALLOC_ERROR:
            printf ("\t\tERROR CODE: Can't alloc meemory\n");
            break;
        
        case REALLOC_ERROR:
            printf ("\t\tERROR CODE: Can't realloc meemory\n");
            break;
        
        case DATA_CANARY_LEFT_ERROR:
            printf ("\t\tERROR CODE: Data's left canary was changed\n");
            break;
        
        case DATA_CANARY_RIGHT_ERROR:
            printf ("\t\tERROR CODE: Data's right canary was changed\n");
            break;
        
        case STACK_CANARY_LEFT_ERROR:
            printf ("\t\tERROR CODE: Stack's left canary was changed\n");
            break;
        
        case STACK_CANARY_RIGHT_ERROR:
            printf ("\t\tERROR CODE: Stack's right canary was changed\n");
            break;
        
        case DATA_HASH_ERROR:
            printf ("\t\tERROR CODE: Data's hash changed\n");
            break;
        
        case CAPACITY_HASH_ERROR:
            printf ("\t\tERROR CODE: Capacity's hash changed\n");
            break;
        
        case SIZE_HASH_ERROR:
            printf ("\t\tERROR CODE: Size's hash changed\n");
            break;

        case POISON_ERROR:
            printf ("\t\tERROR CODE: Poision number changed\n");
            break;
        
        case MEMSET_ERROR:
            printf ("\t\tERROR CODE: Can't memset memory\n");
            break;

    } //to write
}


//-----------------------------------------------------------------------------


ERRORS stackOK (const Stack* st, long long hash_data, long long hash_capacity, long long hash_size)
{
    if ((DEBUG_LEVEL == 1) || (DEBUG_LEVEL == 2) || (DEBUG_LEVEL == 3))
    {
        if (!st) return VOID_STACK;                                               
        if (st->capacity < st->Size) return STACK_OVERFLOW;
    }

    if ((DEBUG_LEVEL == 2) || (DEBUG_LEVEL == 3))
    {
        if (*(canary_t*)(st->data - 1) != CANARY) return DATA_CANARY_LEFT_ERROR;                 
        if (*(canary_t*)(st->data + st->capacity) != CANARY) return DATA_CANARY_RIGHT_ERROR; 
        if (st->leftCanary != CANARY) return STACK_CANARY_LEFT_ERROR;             
        if (st->rightCanary != CANARY) return STACK_CANARY_RIGHT_ERROR;
    }

    if (DEBUG_LEVEL == 3) {
        if (calc_hash_double (st->data) != hash_data) return DATA_HASH_ERROR;
        if (calc_hash_size_t (&st->capacity) != hash_capacity) return CAPACITY_HASH_ERROR;
        if (calc_hash_size_t (&st->Size) != hash_size) return SIZE_HASH_ERROR;
    }

    return NO_ERRORS;
}


//-----------------------------------------------------------------------------


void prinStack (const Stack* st)
{
    for (unsigned num = 0; num < st->Size; num++)
    {
        printf ("%f\n", *(st->data + num));
    }

    printf ("%ld --- %ld\n", st->Size, st->capacity);
}


//-----------------------------------------------------------------------------


long long calc_hash_double (const double *val)  
{            
    const int ret_size = 32;
    long long ret = 0x555555;
    const int per_char = 7;

    while (*val)
    {
        ret ^=*(int*)val++;
        ret = ((ret << per_char) | (ret >> (ret_size -per_char)));
    }

    return ret;  
}

long long calc_hash_size_t (const size_t *val)  
{            
    const int ret_size = 32;
    long long ret = 0x555555;
    const int per_char = 7;

    while (*val)
    {
        ret ^=*val++;
        ret = ((ret << per_char) | (ret >> (ret_size -per_char)));
    }

    return ret;  
}