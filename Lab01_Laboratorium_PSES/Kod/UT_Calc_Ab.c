/** ==================================================================================================================*\
  @file UT_Calc_Ab.c

  @brief Testy jednostkowe do Calc_Ab
\*====================================================================================================================*/
#include "Std_Types.h"

#include "acutest.h"
#include "fff.h"

#include "Calc_Ab.c"

DEFINE_FFF_GLOBALS;

FAKE_VOID_FUNC(Lib_Calc_MemS, sint32);
FAKE_VALUE_FUNC(sint32, Lib_Calc_MemR);
FAKE_VALUE_FUNC(Std_ReturnType, Lib_Calc_Add, sint32, sint32, sint32*);
FAKE_VALUE_FUNC(Std_ReturnType, Lib_Calc_Sub, sint32, sint32, sint32*);
FAKE_VALUE_FUNC(Std_ReturnType, Lib_Calc_Mul, sint32, sint32, sint32*);
FAKE_VALUE_FUNC(Std_ReturnType, Lib_Calc_Div, sint32, sint32, sint32*);

/**
  @brief Test zerowania modułu

  Funkcja testująca reset modułu.
*/
void Test_Of_Calc_Reset(void)
{
    akumulator = 0xFFFFFFFFL;

    Calc_Reset();

    TEST_CHECK(Lib_Calc_MemS_fake.call_count == 1);
    TEST_CHECK(Lib_Calc_MemS_fake.arg0_val == 0L);
    TEST_CHECK(akumulator == 0L);
}

/**
  @brief Test zapisu danych do akumulatora

  Funkcja testująca zapis danych do akumulatora
*/
void Test_Of_Calc_Set_A(void)
{
    akumulator = 0x00000000L;
    Calc_Set_A(10);
    TEST_CHECK(akumulator == 10L);

    akumulator = 0x00000000L;
    Calc_Set_A(0xFFFFFFFFL);
    TEST_CHECK(akumulator == 0xFFFFFFFFL);
    
    akumulator = 0xFFFFFFFFL;
    Calc_Set_A(0x10L);
    TEST_CHECK(akumulator == 0xFFFFFFFFL);
}

/**
  @brief Test odczytu danych z akumulatora

  Funkcja testująca odczyt danych z akumulatora
*/
void Test_Of_Calc_Get_A(void)
{
    Std_ReturnType retVal;
    sint32 result;
    
    akumulator = 0L;
    retVal = Calc_Get_A(&result);
    TEST_CHECK(result == 0L);
    TEST_CHECK(retVal == E_OK);

    akumulator = 10L;
    retVal = Calc_Get_A(&result);
    TEST_CHECK(result == 10L);
    TEST_CHECK(retVal == E_OK);

    akumulator = 0xFFFFFFFFL;
    retVal = Calc_Get_A(&result);
    TEST_CHECK(result == 10L);        //previous value
    TEST_CHECK(retVal == E_NOT_OK);
}

/**
  @brief Test wykonania wszystkich operacji

  Funkcja testująca wykonanie wszystkich operacji
*/
void Test_Of_Calc_Oper(void)
{
    akumulator = 0L;
    Calc_Oper(CALC_ADD, 10);
    TEST_CHECK(akumulator == 10L);

    akumulator = 2147483647L;
    Calc_Oper(CALC_ADD, 2147483647L);
    TEST_CHECK(akumulator == 0xFFFFFFFFL);
    
    akumulator = 0L;
    Calc_Oper(CALC_SUB, 10);
    TEST_CHECK(akumulator == -10L);

    akumulator = -2147483648L;
    Calc_Oper(CALC_SUB, 2147483647L);
    TEST_CHECK(akumulator == 0xFFFFFFFFL);
    
    akumulator = 2L;
    Calc_Oper(CALC_MUL, 10);
    TEST_CHECK(akumulator == 20L);

    akumulator = 2147483647L;
    Calc_Oper(CALC_MUL, 4);
    TEST_CHECK(akumulator == 0xFFFFFFFFL);
    
    akumulator = 200L;
    Calc_Oper(CALC_DIV, 10);
    TEST_CHECK(akumulator == 20L);

    akumulator = 20;
    Calc_Oper(CALC_DIV, 0);
    TEST_CHECK(akumulator == 0xFFFFFFFFL);

    akumulator = 11;
    Calc_Oper(4, 0);
    TEST_CHECK(akumulator == 11);
}


/**
  @brief Test wykonania wszystkich operacji na pamięci kalkulatora

  Funkcja testująca wykonanie wszystkich operacji na pamięci kalkulatora
*/
void Test_Of_Calc_Mem(void)
{
    akumulator = 0L;
    //memory_value = 10;
    Calc_Mem(CALC_ADD);
    TEST_CHECK(akumulator == 10L);

    akumulator = 2147483647L;
    Calc_Oper(CALC_ADD, 2147483647L);
    TEST_CHECK(akumulator == 0xFFFFFFFFL);
    
    akumulator = 0L;
    Calc_Oper(CALC_SUB, 10);
    TEST_CHECK(akumulator == -10L);

    akumulator = -2147483648L;
    Calc_Oper(CALC_SUB, 2147483647L);
    TEST_CHECK(akumulator == 0xFFFFFFFFL);
    
    akumulator = 2L;
    Calc_Oper(CALC_MUL, 10);
    TEST_CHECK(akumulator == 20L);

    akumulator = 2147483647L;
    Calc_Oper(CALC_MUL, 4);
    TEST_CHECK(akumulator == 0xFFFFFFFFL);
    
    akumulator = 200L;
    Calc_Oper(CALC_DIV, 10);
    TEST_CHECK(akumulator == 20L);

    akumulator = 20;
    Calc_Oper(CALC_DIV, 0);
    TEST_CHECK(akumulator == 0xFFFFFFFFL);

    akumulator = 11;
    Calc_Oper(4, 0);
    TEST_CHECK(akumulator == 11);
}


/*
  Lista testów - wpisz tutaj wszystkie funkcje które mają być wykonane jako testy.
*/
TEST_LIST = {
    { "Test of Calc_Reset", Test_Of_Calc_Reset },   /* Format to { "nazwa testu", nazwa_funkcji } */
    { "Test of Calc_Set_A", Test_Of_Calc_Set_A },
    { "Test of Calc_Get_A", Test_Of_Calc_Get_A },
    { "Test of Calc_Oper", Test_Of_Calc_Oper },
    //{ "Test of Calc_Mem", Test_Of_Calc_Mem },
    { NULL, NULL }                                        /* To musi być na końcu */
};
    
