#include <CUnit/Basic.h>
#include "linked_list.h"
#include "list_iterator.h"

int init_suite(void)
{
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void)
{
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

void test_create_destroy()
{
  ioopm_list_t *l = ioopm_list_create();
  CU_ASSERT_PTR_NOT_NULL(l);
  ioopm_list_destroy(l);
}

void test_list_is_empty()
{
  ioopm_list_t *l = ioopm_list_create();
  CU_ASSERT_TRUE(ioopm_list_is_empty(l));
  ioopm_list_destroy(l);
}

void test_append()
{
  ioopm_list_t *l = ioopm_list_create();
  for (int i = 0; i < 12; i++)
  {
    ioopm_list_append(l, i);
  };
  CU_ASSERT_EQUAL(ioopm_list_get(l, 5), 5);
  ioopm_list_destroy(l);
}

void test_prepend()
{
  ioopm_list_t *l = ioopm_list_create();
  for (int i = 0; i < 10; i++)
  {
    ioopm_list_prepend(l, i);
  };

  CU_ASSERT_EQUAL(ioopm_list_get(l, 5), 4);
  ioopm_list_destroy(l);
}

void test_append_prepend()
{
  ioopm_list_t *l = ioopm_list_create();
  for (int i = 0; i < 10; i++)
  {
    ioopm_list_append(l, i);
    ioopm_list_prepend(l, i);
  };
  CU_ASSERT_EQUAL(ioopm_list_head(l), 9);
  CU_ASSERT_EQUAL(ioopm_list_last(l), 9);
  ioopm_list_destroy(l);
}

void test_insert()
{
  ioopm_list_t *l = ioopm_list_create();
  for (int i = 0; i < 10; i++)
  {
    ioopm_list_insert(l, i, i);
  };
  CU_ASSERT_EQUAL(ioopm_list_get(l, 5), 5);
  ioopm_list_destroy(l);
}

void test_remove()
{
  ioopm_list_t *l = ioopm_list_create();
  for (int i = 0; i < 10; i++)
  {
    ioopm_list_insert(l, i, i);
  };
  int size = ioopm_list_size(l);

  // remove last elem
  int removed = ioopm_list_remove(l, 9);
  CU_ASSERT_EQUAL(ioopm_list_size(l), (size - 1));
  CU_ASSERT_EQUAL(removed, 9);

  // remove middle elem
  removed = ioopm_list_remove(l, 4);
  CU_ASSERT_EQUAL(ioopm_list_size(l), (size - 2));
  CU_ASSERT_EQUAL(removed, 4);

  // remove
  removed = ioopm_list_remove(l, 5);
  CU_ASSERT_EQUAL(removed, 6);
  CU_ASSERT_EQUAL(ioopm_list_size(l), (size - 3));
  ioopm_list_destroy(l);
}

void test_iter_basic()
{
  ioopm_list_t *l = ioopm_list_create();
  for (int i = 0; i < 10; i++)
  {
    ioopm_list_insert(l, i, i);
  };

  ioopm_list_iterator_t *iter = ioopm_list_iterator_create(l);

  int j = 0;
  while (!ioopm_list_iterator_at_end(iter))
  {
    CU_ASSERT_EQUAL(ioopm_list_iterator_current(iter), j);
    ioopm_list_iterator_advance(iter);
    j++;
  }

  ioopm_list_iterator_destroy(iter);
  ioopm_list_destroy(l);
}

int main()
{
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite, clean_suite);
  if (my_test_suite == NULL)
  {
    // If the test suite could not be added, tear down CUnit and exit
    CU_cleanup_registry();
    return CU_get_error();
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (
      (CU_add_test(my_test_suite, "test create destroy", test_create_destroy) == NULL) ||
      (CU_add_test(my_test_suite, "test list is empty", test_list_is_empty) == NULL) ||
      (CU_add_test(my_test_suite, "test append", test_append) == NULL) ||
      (CU_add_test(my_test_suite, "test prepend", test_prepend) == NULL) ||
      (CU_add_test(my_test_suite, "test append prepend", test_append_prepend) == NULL) ||
      (CU_add_test(my_test_suite, "test insert", test_insert) == NULL) ||
      (CU_add_test(my_test_suite, "test remove", test_remove) == NULL) ||
      (CU_add_test(my_test_suite, "test iter basic", test_iter_basic) == NULL) ||
      0)
  {
    // If adding any of the tests fails, we tear down CUnit and exit
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
}