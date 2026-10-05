#include <CUnit/Basic.h>
#include "hash_table.h"
#include "hash_table_iterator.h"
#include "common.h"
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

void test_create_destroy()
{
  // creates and destrys a hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_hash_string, ioopm_string_comp);
  // test if hash table is empty
  CU_ASSERT_PTR_NOT_NULL(ht);
  ioopm_hash_table_destroy(ht);
}

void test_insert_once()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_hash_string, ioopm_string_comp);

  elem_t key = string_elem("abc");
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
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_hash_string, ioopm_string_comp);

  elem_t key = string_elem("abc");
  elem_t value = int_elem(123);
  elem_t value2 = int_elem(456);

  elem_t result = int_elem(-1);
  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, value.i);
  // test overwriting value of key
  ioopm_hash_table_insert(ht, key, value2);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, value2.i);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_destroy_existing_entry()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_hash_string, ioopm_string_comp);

  elem_t key = string_elem("abc");
  elem_t value = int_elem(123);

  elem_t result = int_elem(-1);
  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, value.i);
  // remove entry and test that it is gone
  CU_ASSERT_TRUE(ioopm_hash_table_remove(ht, key, &result));
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, value.i);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_destroy_non_existing_entry()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_hash_string, ioopm_string_comp);

  elem_t key = string_elem("abc");
  elem_t result = int_elem(-1);
  // try removing an entry that does not exist
  CU_ASSERT_FALSE(ioopm_hash_table_remove(ht, key, &result));
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, -1);
  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_destroy_long_list()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_hash_string, ioopm_string_comp);
  elem_t keys[10] = {string_elem("ab"), string_elem("as"), string_elem("aQ"), string_elem("be"), string_elem("bv"),
                     string_elem("bC"), string_elem("bT"), string_elem("ch"), string_elem("cy"), string_elem("cF")};
  elem_t val = int_elem(0);
  // insert a list into the hash table
  for (int i = 0; i < 10; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], val);
    val.i += 1;
  }
  // remove all keys from the hash table
  for (int j = 0; j < 10; j++)
  {
    elem_t result = int_elem(-1);
    ioopm_hash_table_remove(ht, keys[j], &result);
  }
  // test if hash table is empty
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));

  ioopm_hash_table_destroy(ht);
}

void test_hashtable_size()
{
  // test empty
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_hash_string, ioopm_string_comp);
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);

  // test singleton
  elem_t key = string_elem("abc");
  elem_t value = int_elem(123);
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 1);

  // test larger table
  elem_t keys[10] = {string_elem("ac"), string_elem("ag"), string_elem("al"), string_elem("ba"), string_elem("bu"),
                     string_elem("bi"), string_elem("ch"), string_elem("ta"), string_elem("ga"), string_elem("qz")};
  elem_t val = int_elem(0);
  // insert a list into the hash table
  for (int i = 0; i < 10; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], val);
    val.i += 1;
  }
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 11);

  // test after remove
  elem_t result = int_elem(-1);
  ioopm_hash_table_remove(ht, string_elem("al"), &result);

  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 10);

  ioopm_hash_table_destroy(ht);
}

void test_hashtable_is_empty()
{
  // test empty
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_hash_string, ioopm_string_comp);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));

  // insert entry into hash table and test that it is not empty
  elem_t key = string_elem("abc");
  elem_t value = int_elem(123);
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));

  // remove entry and test that the hash table is empty
  elem_t result = int_elem(-1);
  ioopm_hash_table_remove(ht, string_elem("abc"), &result);

  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}

void test_has_key()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_hash_string, ioopm_string_comp);

  elem_t key = string_elem("abc");
  elem_t key2 = string_elem("def");
  elem_t key3 = string_elem("ghi");
  elem_t key4 = string_elem("jkl");
  elem_t value = int_elem(123);
  elem_t value2 = int_elem(456);
  elem_t result = int_elem(-1);

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key2));

  // create new hash table
  ioopm_hash_table_t *ht2 = ioopm_hash_table_create(ioopm_hash_string, ioopm_string_comp);
  // test with more inserts
  ioopm_hash_table_insert(ht2, key, value2);
  ioopm_hash_table_insert(ht2, key2, value2);
  ioopm_hash_table_insert(ht2, key3, value2);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht2, key));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht2, key2));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht2, key3));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht2, key4));

  // create new hash table
  ioopm_hash_table_t *ht3 = ioopm_hash_table_create(ioopm_hash_string, ioopm_string_comp);
  // test that the key has been removed
  ioopm_hash_table_insert(ht3, key, value2);
  ioopm_hash_table_remove(ht3, key, &result);
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht3, key));

  // create new hash table
  ioopm_hash_table_t *ht4 = ioopm_hash_table_create(ioopm_hash_string, ioopm_string_comp);
  // more tests with insert and remove
  ioopm_hash_table_insert(ht4, key, value2);
  ioopm_hash_table_insert(ht4, key2, value2);
  ioopm_hash_table_insert(ht4, key3, value2);
  ioopm_hash_table_remove(ht4, key2, &result);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht4, key));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht4, key2));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht4, key3));

  // destroy hash tables
  ioopm_hash_table_destroy(ht);
  ioopm_hash_table_destroy(ht2);
  ioopm_hash_table_destroy(ht3);
  ioopm_hash_table_destroy(ht4);
}

void test_iterating_over_ht()
{
  // create new hash table and iterator
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_hash_string, ioopm_string_comp);
  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  CU_ASSERT_TRUE(ioopm_hash_table_iterator_at_end(it));
  ioopm_hash_table_iterator_destroy(it);

  elem_t key = string_elem("abc");
  elem_t value = int_elem(123);
  ioopm_hash_table_insert(ht, key, value);
  ioopm_hash_table_iterator_t *it2 = ioopm_hash_table_iterator_create(ht);
  
  // test current iterator position
  CU_ASSERT_TRUE(strcmp(ioopm_hash_table_iterator_current_key(it2).s, key.s) == 0);
  CU_ASSERT_EQUAL(value.i, ioopm_hash_table_iterator_current_value(it2).i);

  // test iterator advance
  ioopm_hash_table_iterator_advance(it2);
  CU_ASSERT_TRUE(ioopm_hash_table_iterator_at_end(it2));

  ioopm_hash_table_iterator_destroy(it2);
  ioopm_hash_table_destroy(ht);
}

void test_iterator_several_entries()
{
  elem_t keys[3] = {string_elem("abc"), string_elem("qwe"), string_elem("asd")};
  elem_t values[3] = {int_elem(0), int_elem(1), int_elem(2)};

  // creates hash table and inserts elements
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_hash_string, ioopm_string_comp);
  for (int i = 0; i != 3; ++i)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }

  // create iterator and check that it iterates over every element in the hash table
  bool visited[3] = {false, false, false};
  int iteration_count = 0;
  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    if (strcmp(ioopm_hash_table_iterator_current_key(it).s, "abc") == 0)
    {
      visited[0] = true;
    }
    if (strcmp(ioopm_hash_table_iterator_current_key(it).s, "qwe") == 0)
    {
      visited[1] = true;
    }
    if (strcmp(ioopm_hash_table_iterator_current_key(it).s, "asd") == 0)
    {
      visited[2] = true;
    }

    if (ioopm_hash_table_iterator_at_end(it))
    {
      puts("at end!");
    }
    ioopm_hash_table_iterator_advance(it);
    iteration_count += 1;
  }

  // test is true if every element was visited
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
  // create hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_hash_string, ioopm_string_comp);
  elem_t keys[10] = {string_elem("ab"), string_elem("as"), string_elem("aQ"), string_elem("be"), string_elem("bv"), string_elem("bC"), string_elem("bT"), string_elem("ch"), string_elem("cy"), string_elem("cF")};
  elem_t val = int_elem(0);
  // insert elements from array keys in hash table
  for (int i = 0; i < 10; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], val);
    val.i += 1;
  }

  // create iterator and check that it iterates over every element in the hash table
  bool visited[3] = {false, false, false};
  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    if (strcmp(ioopm_hash_table_iterator_current_key(it).s, "ab") == 0)
    {
      visited[0] = true;
    }
    if (strcmp(ioopm_hash_table_iterator_current_key(it).s, "as") == 0)
    {
      visited[1] = true;
    }
    if (strcmp(ioopm_hash_table_iterator_current_key(it).s, "bv") == 0)
    {
      visited[2] = true;
    }

    ioopm_hash_table_iterator_advance(it);
  }
  // test is true if every element was visited
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
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ioopm_hash_string, ioopm_string_comp);
  elem_t key1 = string_elem("abc");
  elem_t key2 = string_elem("def");
  elem_t key3 = string_elem("ghi");

  elem_t value1 = string_elem("grodan");
  int arr[] = {1, 2, 3};
  elem_t value2 = ptr_elem(arr);
  elem_t value3 = bool_elem(true);
  // insert elem_t of different types into hash table ht
  ioopm_hash_table_insert(ht, key1, value1);
  ioopm_hash_table_insert(ht, key2, value2);
  ioopm_hash_table_insert(ht, key3, value3);

  // create iterator and check that it iterates over every element in the hash table
  bool visited[3] = {false, false, false};
  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    if (strcmp(ioopm_hash_table_iterator_current_key(it).s, "abc") == 0 && strcmp(ioopm_hash_table_iterator_current_value(it).s, "grodan") == 0)
    {

      visited[0] = true;
    }
    if (strcmp(ioopm_hash_table_iterator_current_key(it).s, "def") == 0 && ioopm_hash_table_iterator_current_value(it).p == arr)
    {
      visited[1] = true;
    }
    if (strcmp(ioopm_hash_table_iterator_current_key(it).s, "ghi") == 0 && ioopm_hash_table_iterator_current_value(it).b == true)
    {
      visited[2] = true;
    }

    ioopm_hash_table_iterator_advance(it);
  }
  // test is true if every element was visited
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

  elem_t key = int_elem(1);
  elem_t key2 = int_elem(2);
  elem_t value = string_elem("Hej");

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key2));

  ioopm_hash_table_destroy(ht);
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
      (CU_add_test(my_test_suite, "Test create destroy", test_create_destroy) == NULL) ||
      (CU_add_test(my_test_suite, "Test insert once", test_insert_once) == NULL) ||
      (CU_add_test(my_test_suite, "Test key in use", test_key_in_use) == NULL) ||
      (CU_add_test(my_test_suite, "Test destroy existing entry", test_destroy_existing_entry) == NULL) ||
      (CU_add_test(my_test_suite, "Test destroy non existing entry", test_destroy_non_existing_entry) == NULL) ||
      (CU_add_test(my_test_suite, "Test destroy long list", test_destroy_long_list) == NULL) ||
      (CU_add_test(my_test_suite, "Test hashtable size", test_hashtable_size) == NULL) ||
      (CU_add_test(my_test_suite, "Test hashtable is empty", test_hashtable_is_empty) == NULL) ||
      (CU_add_test(my_test_suite, "Test has key", test_has_key) == NULL) ||
      (CU_add_test(my_test_suite, "Test iterating over hash table", test_iterating_over_ht) == NULL) ||
      (CU_add_test(my_test_suite, "Test iterator several entries", test_iterator_several_entries) == NULL) ||
      (CU_add_test(my_test_suite, "Test same bucket", test_same_bucket) == NULL) ||
      (CU_add_test(my_test_suite, "Test elem_t", test_elem_t) == NULL) ||
      (CU_add_test(my_test_suite, "Test int key", test_int_key) == NULL) ||
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