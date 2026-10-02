ht_tests: hash_table.c unit_tests.c common.h
	gcc -Wextra -Wall hash_table.c unit_tests.c common.h -lcunit -o ht_tests
freq: freq.c hash_table.c common.h
	gcc -Wextra -Wall freq.c hash_table.c common.h -o freq

ll_tests: linked_list.c linked_list_tests.c
	gcc -Wextra -Wall linked_list.c linked_list_tests.c common.h -lcunit -o ll_tests
