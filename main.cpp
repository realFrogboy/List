#include "list.h"
#include "list_unit_test.h"

int DEBUG_LEVEL = 3; // for stack

int main(){
    struct List list;
    list = list_ctor();

    print_list(&list);

    ins_at_the_end(&list, 10);
    print_list(&list);

    ins_at_the_end(&list, 20);
    ins_at_the_end(&list, 30);
    ins_at_the_end(&list, 40);
    ins_at_the_end(&list, 50);
    ins_at_the_end(&list, 60);
    ins_at_the_end(&list, 70);
    ins_at_the_end(&list, 80);
    ins_at_the_end(&list, 90);
    ins_at_the_end(&list, 100);

    print_list(&list);

    ins_at_the_end(&list, 110);
    ins_at_the_end(&list, 120);

    print_list(&list);

    list_unit_test(list);

    list_dtor(&list);

    return 0;
}
