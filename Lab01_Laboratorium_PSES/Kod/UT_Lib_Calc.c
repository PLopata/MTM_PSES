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
}

/*
  Lista testów - wpisz tutaj wszystkie funkcje które mają być wykonane jako testy.
*/
TEST_LIST = {
    { "Test of Lib_Calc_Add", Test_Of_Lib_Calc_Add },   /* Format to { "nazwa testu", nazwa_funkcji } */
    { "Test of Lib_Calc_Sub", Test_Of_Lib_Calc_Sub },
    { NULL, NULL }                                      /* To musi być na końcu */
};

