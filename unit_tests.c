#include <CUnit/Basic.h>
#include "hash_table.h"

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

// These are example test functions. You should replace them with
// functions of your own.
void test_create_destroy()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  CU_ASSERT_PTR_NOT_NULL(ht);
  ioopm_hash_table_destroy(ht);
}

void test_insert_once()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";
  int value = 123;

  // check that key is not in ht
  int result = 0;
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, 0);

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, value);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_key_in_use()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";
  int value = 123;
  int value2 = 456;

  int result = -1;
  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, value);
  ioopm_hash_table_insert(ht, key, value2);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, value2);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_invalid_key()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";
  int value = 123;
  int value2 = 456;

  int result = -1;
  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, value);
  ioopm_hash_table_insert(ht, key, value2);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, value2);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_destroy_existing_entry()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";
  int value = 123;

  int result = -1;
  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, value);
  CU_ASSERT_TRUE(ioopm_hash_table_remove(ht, key, &result));
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, value);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_destroy_long_list()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *keys[10] = {"ab", "as", "aQ", "be", "bv", "bC", "bT", "ch", "cy", "cF"};
  int val = 0;
  for (int i = 0; i < 10; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], val);
    val += 1;
  }

  ioopm_hash_table_destroy(ht);
}

void test_destroy_non_existing_entry()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";
  int result = -1;
  CU_ASSERT_FALSE(ioopm_hash_table_remove(ht, key, &result));
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, -1);
  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_has_key()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";
  char *key2 = "def";
  char *key3 = "ghi";
  char *key4 = "jkl";
  int value = 123;
  int value2 = 456;
  int result = -1;

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key2));

  ioopm_hash_table_t *ht2 = ioopm_hash_table_create();

  ioopm_hash_table_insert(ht2, key, value2);
  ioopm_hash_table_insert(ht2, key2, value2);
  ioopm_hash_table_insert(ht2, key3, value2);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht2, key));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht2, key2));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht2, key3));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht2, key4));

  ioopm_hash_table_t *ht3 = ioopm_hash_table_create();

  ioopm_hash_table_insert(ht3, key, value2);
  ioopm_hash_table_remove(ht3, key, &result);
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht3, key));

  ioopm_hash_table_t *ht4 = ioopm_hash_table_create();

  ioopm_hash_table_insert(ht4, key, value2);
  ioopm_hash_table_insert(ht4, key2, value2);
  ioopm_hash_table_insert(ht4, key3, value2);
  ioopm_hash_table_remove(ht4, key2, &result);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht4, key));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht4, key2));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht4, key3));

  // destroy hash table
  ioopm_hash_table_destroy(ht);
  ioopm_hash_table_destroy(ht2);
  ioopm_hash_table_destroy(ht3);
  ioopm_hash_table_destroy(ht4);
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
      (CU_add_test(my_test_suite, "Test insert once", test_insert_once) == NULL) ||
      (CU_add_test(my_test_suite, "Test key in use", test_key_in_use) == NULL) ||
      (CU_add_test(my_test_suite, "Test destroy existing entry", test_destroy_existing_entry) == NULL) ||
      (CU_add_test(my_test_suite, "Test destroy non existing entry", test_destroy_non_existing_entry) == NULL) ||
      (CU_add_test(my_test_suite, "Test destroy long list", test_destroy_long_list) == NULL) ||
      (CU_add_test(my_test_suite, "Test has key", test_has_key) == NULL) || 0)
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