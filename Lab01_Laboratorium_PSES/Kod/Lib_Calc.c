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
    sint64 tmp = ((sint64)arg1) + ((sint64)arg2);
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
    sint64 tmp = ((sint64)arg1) - ((sint64)arg2);
    Std_ReturnType ret = E_OK;
    if((tmp > MAX32) || (tmp < MIN32))
    {
        ret = E_NOT_OK;
    }
    *result = (sint32)tmp;
    return ret;
}

/**
  @brief Mnożenie

  Implementacja mnożenia liczb 32-bitowych z kontrolą przepełnienia.
  Element projektu: [P4]
*/
Std_ReturnType Lib_Calc_Mul(sint32 arg1, sint32 arg2, sint32* result)
{
    sint64 tmp = ((sint64)arg1) * ((sint64)arg2);
    Std_ReturnType ret = E_OK;
    if((tmp > MAX32) || (tmp < MIN32))
    {
        ret = E_NOT_OK;
    }
    *result = (sint32)tmp;
    return ret;
}
  
/**
  @brief Dzielenie

  Implementacja dzielenia liczb 32-bitowych z kontrolą dzielenia przez 0.
  Element projektu: [P5], [P6], [P7], [P8]
*/
Std_ReturnType Lib_Calc_Div(sint32 arg1, sint32 arg2, sint32* result)
{
    Std_ReturnType ret = E_OK;
    if(arg2 == 0)
    {
        if(arg1 > 0)
        {
            *result = (sint32)MAX32;
            ret = E_NOT_OK;
        }
        else if(arg1 < 0)
        {
            *result = (sint32)MIN32;
            ret = E_NOT_OK;
        }
        else 
        {
            *result = (sint32)0;
            ret = E_NOT_OK;
        }
        
    }
    else
    {
        sint64 tmp;
         tmp = ((sint64)arg1) / ((sint64)arg2);
         *result = (sint32)tmp;
    }
    return ret;
}

/**
  @brief Zapis do pamięci

  Implementacja zapisu danej do pamięci
  Element projektu: [P9]
*/
void Lib_Calc_MemS(sint32 mem)
{
    memory_value = mem;
}


/**
  @brief Odczyt z pamięci

  Implementacja odczytu danej z pamięci
  Element projektu: [P10]
*/
sint32 Lib_Calc_MemR(void)
{
    return memory_value;
}