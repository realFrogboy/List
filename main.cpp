#include "list.h"
int DEBUG_LEVEL = 3; // for stack

int main() {
    struct List list;
    list = list_ctor();

    ins_at_the_end(&list, 10);
    ins_at_the_end(&list, 20);
    ins_at_the_end(&list, 30);
    ins_at_the_end(&list, 40);
    ins_at_the_end(&list, 50);
    ins_at_the_end(&list, 60);
    ins_at_the_end(&list, 70);
    ins_at_the_end(&list, 80);
    ins_at_the_end(&list, 90);
    ins_at_the_end(&list, 100);
    ins_at_the_end(&list, 110);
    ins_at_the_end(&list, 120);

    del_elem(&list, 1);

    ins_at_the_beg(&list, 3.141);

    ins_after(&list, 3, 200);
    ins_before(&list, 10, 150);

    print_list(&list);

    sort_list_by_prev_slow_slow(&list);
    print_list(&list);

    size_t ret = search_elem_slow_slow(&list, 170);
    printf("%ld\n", ret);

    list_dtor(&list);

    return 0;
}
