/**===================================================================================================================*\
  @file Lib_Calc.c

  @brief Bibiloteka Lib_Calc - implementacja
  
  Implementacja funkcjonalności podstawowej kalkukatora 4-działaniowego z pamięcią.

  @see Lib_Calc.pdf
\*====================================================================================================================*/

/*====================================================================================================================*\
    Załączenie nagłówków
\*====================================================================================================================*/
#include "Lib_Calc.h"

/*====================================================================================================================*\
    Makra lokalne
\*====================================================================================================================*/
#define MAX32   (2147483647L)
#define MIN32   (-2147483648L)

/*====================================================================================================================*\
    Typy lokalne
\*====================================================================================================================*/

/*====================================================================================================================*\
    Zmienne globalne
\*====================================================================================================================*/

/*====================================================================================================================*\
    Zmienne lokalne (statyczne)
\*====================================================================================================================*/
static sint32 memory_value;     /**< Reprezentacja pamięci kalkulatora [P11] */

/*====================================================================================================================*\
    Deklaracje funkcji lokalnych
\*====================================================================================================================*/

/*====================================================================================================================*\
    Kod globalnych funkcji inline i makr funkcyjnych
\*====================================================================================================================*/

/*====================================================================================================================*\
    Kod funkcji
\*====================================================================================================================*/


/**
  @brief Dodawanie

  Implementacja dodawania liczb 32-bitowych z kontrolą przepełnienia.
  Element projektu: [P2]
*/
Std_ReturnType Lib_Calc_Add(sint32 arg1, sint32 arg2, sint32* result)
{
    sint64 tmp = arg1 + arg2;
    Std_ReturnType ret = E_OK;
    if((tmp > MAX32) || (tmp < MIN32))
    {
        ret = E_NOT_OK;
    }
    *result = (sint32)tmp;
    return ret;
}

/**
  @brief Odejmowanie

  Implementacja odejmowania liczb 32-bitowych z kontrolą przepełnienia.
  Element projektu: [P3]
*/
Std_ReturnType Lib_Calc_Sub(sint32 arg1, sint32 arg2, sint32* result)
{
    Std_ReturnType ret = E_NOT_OK;

    return ret;
}


  
