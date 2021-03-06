/*! \file   main.c
 *  \brief  Unit tests for AnyNumeralSystemToDecimal() function.
 */

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../ChildProgram/task14.h"


int init_suite()
{ return 0; }

int clean_suite()
{ return 0; }

/*! \brief Test for binary number
 */
void test_AnyNumeralSystemToDecimal_bin()
{
    CU_ASSERT(21 == AnyNumeralSystemToDecimal("10101", 2));
}

/*! \brief Test for octal number
 */
void test_AnyNumeralSystemToDecimal_oct()
{
    CU_ASSERT(511 == AnyNumeralSystemToDecimal("777", 8));
}

/*! \brief Test for decimal number
 */
void test_AnyNumeralSystemToDecimal_dec()
{
    CU_ASSERT(12345 == AnyNumeralSystemToDecimal("12345", 10));
}

/*! \brief Test for hexadecimal number
 */
void test_AnyNumeralSystemToDecimal_hex()
{
    CU_ASSERT(703393 == AnyNumeralSystemToDecimal("ABBA1", 16));
}

/*! \brief Test for number with leading zeroes
 */
void test_AnyNumeralSystemToDecimal_leadingZero()
{
    CU_ASSERT(12345 == AnyNumeralSystemToDecimal("0012345", 10));
}

/*!
 * \brief Main function
 * \details This functions controls and runs tests
 */
int main()
{
    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }

    pSuite = CU_add_suite("Suite", init_suite, clean_suite);

    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "Binary conversion: ",
                             test_AnyNumeralSystemToDecimal_bin)) ||
        (NULL == CU_add_test(pSuite, "Octal conversion: ",
                             test_AnyNumeralSystemToDecimal_oct)) ||
        (NULL == CU_add_test(pSuite, "Decimal conversion: ",
                             test_AnyNumeralSystemToDecimal_dec)) ||
        (NULL == CU_add_test(pSuite, "Hexadecimal conversion: ",
                             test_AnyNumeralSystemToDecimal_hex)) ||
        (NULL == CU_add_test(pSuite, "Decimal conversion with leading zero: ",
                             test_AnyNumeralSystemToDecimal_leadingZero)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}