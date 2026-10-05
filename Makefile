
freq: freq.c hash_table.c common.h
	gcc -Wextra -Wall freq.c hash_table.c common.h -o freq

ll_tests: linked_list.c linked_list_tests.c
	gcc -Wextra -Wall linked_list.c linked_list_tests.c common.h -lcunit -o ll_tests

linked_list_coverage: linked_list.c linked_list_tests.c
	gcc -Wextra -Wall --coverage linked_list.c linked_list_tests.c -lcunit -o linked_list_coverage

ll_coverage: linked_list_coverage
	./linked_list_coverage
	gcovr --html-details --branches -o ll_coverage.html

hashtable_coverage: hash_table.c ht_tests.c
	gcc -Wall -Wextra --coverage hash_table.c ht_tests.c -lcunit -o hashtable_coverage

ht_coverage: hashtable_coverage
	./hashtable_coverage
	gcovr --html-details --branches -o ht_coverage.html

clean:
	rm hashtable_coverage
	rm -f linked_list_coverage
	rm -f coverage*
	rm -f ht_coverage*
	rm -f ll_coverage*
	rm -f *.gcda *.gcno *.gcov

