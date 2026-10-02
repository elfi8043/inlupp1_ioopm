#include <CUnit/Basic.h>
#include "hash_table.h"
#include "hash_table_iterator.h"
#include <assert.h>

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

size_t string_knr_hash(const char *str)
{
  size_t result = 0;
  while (*str != '\0')
  {
    result = result * 31 + ((unsigned char)*str);
    str++;
  }
  return result;
}

void test_insert_once()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";
  elem_t value = int_elem(123);

  // check that key is not in ht
  elem_t result = int_elem(0);
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, 0);

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, value.i);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_key_in_use()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";
  elem_t value = int_elem(123);
  elem_t value2 = int_elem(456);

  elem_t result = int_elem(-1);
  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, value.i);
  ioopm_hash_table_insert(ht, key, value2);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, value2.i);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_invalid_key()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";
  elem_t value = int_elem(123);
  elem_t value2 = int_elem(456);

  elem_t result = int_elem(-1);
  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, value.i);
  ioopm_hash_table_insert(ht, key, value2);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, value2.i);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_destroy_existing_entry()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";
  elem_t value = int_elem(123);

  elem_t result = int_elem(-1);
  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, value.i);
  CU_ASSERT_TRUE(ioopm_hash_table_remove(ht, key, &result));
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, value.i);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_destroy_long_list()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *keys[10] = {"ab", "as", "aQ", "be", "bv", "bC", "bT", "ch", "cy", "cF"};
  elem_t val = int_elem(0);
  for (int i = 0; i < 10; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], val);
    val.i += 1;
  }

  ioopm_hash_table_destroy(ht);
}

void test_destroy_non_existing_entry()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";
  elem_t result = int_elem(-1);
  CU_ASSERT_FALSE(ioopm_hash_table_remove(ht, key, &result));
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, -1);
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
  elem_t value = int_elem(123);
  elem_t value2 = int_elem(456);
  elem_t result = int_elem(-1);

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

void test_hashtable_size()
{
  // test empty
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);

  // test singleton
  char *key = "abc";
  elem_t value = int_elem(123);
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 1);

  // test larger table
  char *keys[10] = {"ac", "ag", "al", "ba", "bu", "bi", "ch", "ta", "ga", "qz"};
  elem_t val = int_elem(0);
  for (int i = 0; i < 10; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], val);
    val.i += 1;
  }
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 11);

  // test after remove
  elem_t result = int_elem(-1);
  ioopm_hash_table_remove(ht, "al", &result);

  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 10);

  ioopm_hash_table_destroy(ht);
}

void test_hashtable_is_empty()
{
  // test empty
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));

  char *key = "abc";
  elem_t value = int_elem(123);
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));

  elem_t result = int_elem(-1);
  ioopm_hash_table_remove(ht, "abc", &result);

  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}

void test_iterating_over_ht()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  CU_ASSERT_TRUE(ioopm_hash_table_iterator_at_end(it));
  ioopm_hash_table_iterator_destroy(it);

  char *key = "abc";
  elem_t value = int_elem(123);
  ioopm_hash_table_insert(ht, key, value);
  ioopm_hash_table_iterator_t *it2 = ioopm_hash_table_iterator_create(ht);

  CU_ASSERT_TRUE(strcmp(ioopm_hash_table_iterator_current_key(it2), key) == 0);

  CU_ASSERT_EQUAL(value.i, ioopm_hash_table_iterator_current_value(it2).i);

  ioopm_hash_table_iterator_advance(it2);
  CU_ASSERT_TRUE(ioopm_hash_table_iterator_at_end(it2));

  ioopm_hash_table_iterator_destroy(it2);
  ioopm_hash_table_destroy(ht);
}

void test_iterator_several_entries()
{
  char *keys[3] = {"abc", "qwe", "asd"};
  elem_t values[3] = {int_elem(0), int_elem(1), int_elem(2)};

  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  for (int i = 0; i != 3; ++i)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }

  bool visited[3] = {false, false, false};
  int iteration_count = 0;
  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    if (strcmp(ioopm_hash_table_iterator_current_key(it), "abc") == 0)
    {
      visited[0] = true;
    }
    if (strcmp(ioopm_hash_table_iterator_current_key(it), "qwe") == 0)
    {
      visited[1] = true;
    }
    if (strcmp(ioopm_hash_table_iterator_current_key(it), "asd") == 0)
    {
      visited[2] = true;
    }

    if (ioopm_hash_table_iterator_at_end(it))
    {
      puts("at end!");
    }
    ioopm_hash_table_iterator_advance(it);
    iteration_count += 1;
    // assert(!(iteration_count >= 3) && "iteration count too high!");
  }

  for (int j = 0; j < 3; j++)
  {
    CU_ASSERT_TRUE(visited[j]);
  }

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);
  CU_ASSERT_EQUAL(iteration_count, 3);
}

void test_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *keys[10] = {"ab", "as", "aQ", "be", "bv", "bC", "bT", "ch", "cy", "cF"};
  elem_t val = int_elem(0);
  for (int i = 0; i < 10; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], val);
    val.i += 1;
  }

  bool visited[3] = {false, false, false};
  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    if (strcmp(ioopm_hash_table_iterator_current_key(it), "ab") == 0)
    {
      visited[0] = true;
    }
    if (strcmp(ioopm_hash_table_iterator_current_key(it), "as") == 0)
    {
      visited[1] = true;
    }
    if (strcmp(ioopm_hash_table_iterator_current_key(it), "bv") == 0)
    {
      visited[2] = true;
    }

    ioopm_hash_table_iterator_advance(it);
  }
  for (int i = 0; i < 3; i++)
  {
    CU_ASSERT_TRUE(visited[i]);
  }
  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);
}

void test_elem_t()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *key1 = "abc";
  char *key2 = "def";
  char *key3 = "ghi";

  elem_t value1 = string_elem("grodan");
  int arr[] = {1, 2, 3};
  elem_t value2 = ptr_elem(arr);
  elem_t value3 = bool_elem(true);

  ioopm_hash_table_insert(ht, key1, value1);
  ioopm_hash_table_insert(ht, key2, value2);
  ioopm_hash_table_insert(ht, key3, value3);

  bool visited[3] = {false, false, false};
  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    if (strcmp(ioopm_hash_table_iterator_current_key(it), "abc") == 0 && strcmp(ioopm_hash_table_iterator_current_value(it).s, "grodan") == 0)
    {

      visited[0] = true;
    }
    if (strcmp(ioopm_hash_table_iterator_current_key(it), "def") == 0 && ioopm_hash_table_iterator_current_value(it).p == arr)
    {
      visited[1] = true;
    }
    if (strcmp(ioopm_hash_table_iterator_current_key(it), "ghi") == 0 && ioopm_hash_table_iterator_current_value(it).b == true)
    {
      visited[2] = true;
    }

    ioopm_hash_table_iterator_advance(it);
  }
  for (int i = 0; i < 3; i++)
  {
    CU_ASSERT_TRUE(visited[i]);
  }
  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);
}

void test_int_key()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_hash_int, ioopm_int_comp);

  char *key = 1;
  char *key2 = 2;
  char *key3 = 3;
  char *key4 = 4;
  elem_t value = string_elem("Hej");
  elem_t value2 = string_elem("där");
  elem_t result = int_elem(-1);

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key2));
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
      (CU_add_test(my_test_suite, "Test hashtable size", test_hashtable_size) == NULL) ||
      (CU_add_test(my_test_suite, "Test hashtable is empty", test_hashtable_is_empty) == NULL) ||
      (CU_add_test(my_test_suite, "Test has key", test_has_key) == NULL) ||
      (CU_add_test(my_test_suite, "Test iterating over table", test_iterating_over_ht) == NULL) ||
      (CU_add_test(my_test_suite, "Test iterator several", test_iterator_several_entries) == NULL) ||
      (CU_add_test(my_test_suite, "Test same bucket", test_same_bucket) == NULL) ||
      (CU_add_test(my_test_suite, "Test iterating over hashtable", test_iterating_over_ht) == NULL) ||
      (CU_add_test(my_test_suite, "Test elem_t", test_elem_t) == NULL) || 0)
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