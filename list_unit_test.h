#ifndef LIST_UNIT_TEST_H_
#define LIST_UNIT_TEST_H_

#include "list.h"

#ifndef GET_COMMAND
#define GET_COMMAND printf("Enter a command. To exit press \"q\".\n");   \
                    scanf("%s %d %d", com, &val1, &val2);
#endif

#ifndef CLEAN_BUFFER
#define CLEAN_BUFFER while (getchar() != '\n') {}
#endif

void list_unit_test(List list);

#endif