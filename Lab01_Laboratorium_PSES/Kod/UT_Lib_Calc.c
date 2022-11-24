/** ==================================================================================================================*\
  @file UT_Lib_Calc.c

  @brief Testy jednostkowe do Lib_Calc
\*====================================================================================================================*/

#include "acutest.h"
#include "Std_Types.h"

#include "Lib_Calc.c"   /* To nie pomyłka - taki include eksponuje zmienne statyczne dla testów */

/**
  @brief Test dodawania

  Funkcja testująca dodawanie w bibliotece. Funkcje testowe acutest nie mogą zwracać ani przyjmować danych!
*/
void Test_Of_Lib_Calc_Add(void)
{
    sint32 result;
    Std_ReturnType retv;

    retv = Lib_Calc_Add(0L, 0L, &result);

    TEST_CHECK(result == 0);       /* Test przejdzie jeżeli wyrażenie w nawiasach jest prawdziwe */
    TEST_CHECK(retv == E_OK);

    retv = Lib_Calc_Add(1L, -1L, &result);

    TEST_CHECK(result == 0);
    TEST_CHECK(retv == E_OK);

    /* TUTAJ DOPISZ WIĘCEJ TESTÓW */

    retv = Lib_Calc_Add(MAX32, MAX32, &result);

    TEST_CHECK(result == -2);
    TEST_CHECK(retv == E_NOT_OK);

    retv = Lib_Calc_Add(MIN32, MIN32, &result);

    TEST_CHECK(result == 0);
    TEST_CHECK(retv == E_NOT_OK);
}


/**
  @brief Test odejmowania

  Funkcja testująca odejmowanie w bibliotece.
*/
void Test_Of_Lib_Calc_Sub(void)
{
    sint32 result;
    Std_ReturnType retv;

    retv = Lib_Calc_Sub(0L, 0L, &result);

    TEST_CHECK(result == 0);
    TEST_CHECK(retv == E_OK);

    retv = Lib_Calc_Sub(1L, -1L, &result);

    TEST_CHECK(result == 2L);
    TEST_CHECK(retv == E_OK);

    /* TUTAJ DOPISZ WIĘCEJ TESTÓW */
    
    retv = Lib_Calc_Sub(MAX32, MIN32, &result);

    TEST_CHECK(result == -1);
    TEST_CHECK(retv == E_NOT_OK);

    retv = Lib_Calc_Sub(MIN32, MAX32, &result);

    TEST_CHECK(result == 1);
    TEST_CHECK(retv == E_NOT_OK);
}

/**
  @brief Test mnożenia

  Funkcja testująca mnożenie w bibliotece.
*/
void Test_Of_Lib_Calc_Mul(void)
{
    sint32 result;
    Std_ReturnType retv;

    retv = Lib_Calc_Mul(0L, 0L, &result);

    TEST_CHECK(result == 0);
    TEST_CHECK(retv == E_OK);

    retv = Lib_Calc_Mul(1L, -1L, &result);

    TEST_CHECK(result == -1L);
    TEST_CHECK(retv == E_OK);

    /* TUTAJ DOPISZ WIĘCEJ TESTÓW */
    
    retv = Lib_Calc_Mul(MAX32, 4, &result);

    TEST_CHECK(result == -4);
    TEST_CHECK(retv == E_NOT_OK);
    retv = Lib_Calc_Mul(MIN32, 4, &result);

    TEST_CHECK(result == 0);
    TEST_CHECK(retv == E_NOT_OK);
}


/**
  @brief Test dzielenia

  Funkcja testująca dzielenie w bibliotece.
*/
void Test_Of_Lib_Calc_Div(void)
{
    sint32 result;
    Std_ReturnType retv;

    retv = Lib_Calc_Div(10L, 2L, &result);

    TEST_CHECK(result == 5);
    TEST_CHECK(retv == E_OK);

    retv = Lib_Calc_Div(-10L, 2L, &result);

    TEST_CHECK(result == -5L);
    TEST_CHECK(retv == E_OK);

    /* TUTAJ DOPISZ WIĘCEJ TESTÓW */
    
    retv = Lib_Calc_Div(1, 0, &result);

    TEST_CHECK(result == MAX32);
    TEST_CHECK(retv == E_NOT_OK);

    retv = Lib_Calc_Div(-1, 0, &result);

    TEST_CHECK(result == MIN32);
    TEST_CHECK(retv == E_NOT_OK);

    retv = Lib_Calc_Div(0, 0, &result);

    TEST_CHECK(result == 0);
    TEST_CHECK(retv == E_NOT_OK);
}


/**
  @brief Test zapisu do pamięci

  Funkcja testująca zapis danej do pamięci w bibliotece.
*/
void Test_Of_Lib_Calc_MemS(void)
{
    Lib_Calc_MemS(1);
    TEST_CHECK(memory_value == 1);

    Lib_Calc_MemS(MAX32);
    TEST_CHECK(memory_value == MAX32);

    Lib_Calc_MemS(MIN32);
    TEST_CHECK(memory_value == MIN32);
}


/**
  @brief Test odczytu z pamięci

  Funkcja testująca odczyt danej do pamięci w bibliotece.
*/
void Test_Of_Lib_Calc_MemR(void)
{
    sint32 result;

    memory_value = 0;
    result = Lib_Calc_MemR();
    TEST_CHECK(result == 0);

    memory_value = MAX32;
    result = Lib_Calc_MemR();
    TEST_CHECK(result == MAX32);

    memory_value = MIN32;
    result = Lib_Calc_MemR();
    TEST_CHECK(result == MIN32);
}


/*
  Lista testów - wpisz tutaj wszystkie funkcje które mają być wykonane jako testy.
*/
TEST_LIST = {
    { "Test of Lib_Calc_Add", Test_Of_Lib_Calc_Add   },   /* Format to { "nazwa testu", nazwa_funkcji } */
    { "Test of Lib_Calc_Sub", Test_Of_Lib_Calc_Sub   },
    { "Test_Of_Lib_Calc_Mul", Test_Of_Lib_Calc_Mul   },
    { "Test_Of_Lib_Calc_Div", Test_Of_Lib_Calc_Div   },
    { "Test_Of_Lib_Calc_MemS", Test_Of_Lib_Calc_MemS },
    { "Test_Of_Lib_Calc_MemR", Test_Of_Lib_Calc_MemR },
    { NULL, NULL }                                      /* To musi być na końcu */
};

