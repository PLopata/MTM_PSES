/** ==================================================================================================================*\
  @file Calc_Ab.c

  @brief Implementacja kalkulatora
  
  Implementacja kalkukatora 4-działaniowego z pamięcią.

  @see Calc_Ab.pdf
\*====================================================================================================================*/

/*====================================================================================================================*\
    Załączenie nagłówków
\*====================================================================================================================*/
#include "Lib_Calc.h"

/*====================================================================================================================*\
    Makra lokalne
\*====================================================================================================================*/

/*====================================================================================================================*\
    Typy lokalne
\*====================================================================================================================*/
typedef enum {              /**< Typ służący do wyboru rodzaju operacji [P4]*/
    CALC_ADD,
    CALC_SUB,
    CALC_MUL,
    CALC_DIV
} Calc_Operation_T;

typedef enum {              /**< Typ służący do wyboru rodzaju operacji na pamięci [P8]*/
    CALC_MEM_ADD, 
    CALC_MEM_SUB, 
    CALC_MEM_STO, 
    CALC_MEM_ZERO
} Calc_MemOp_T;
/*====================================================================================================================*\
    Zmienne globalne
\*====================================================================================================================*/

/*====================================================================================================================*\
    Zmienne lokalne (statyczne)
\*====================================================================================================================*/
static sint32 akumulator;     /**< Akumulator kalkulatora [P2] */

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
  @brief Zerowanie modułu

  Funkcja zeruje wartość akumulatora i pamięci.
  Realizuje [P9]
*/
void Calc_Reset(void)
{
    akumulator = 0L;
    Lib_Calc_MemS(0L);
}

/**
  @brief Zapis danej do akumulatora

  Funkcja realizuje zapis danej do akumulatora. Nie nadpisuje wartości 0xFFFFFFFF.
  Realizuje [P3]
*/
void Calc_Set_A(sint32 a)
{
    if(akumulator != 0xFFFFFFFF){
        akumulator = a;
    }
}

/**
  @brief Odczyt danej z akumulatora

  Funkcja realizuje odczyt danej z akumulatora. Nie nadpisuje wartości 0xFFFFFFFF.
  Realizuje [P3]
*/
Std_ReturnType Calc_Get_A(sint32 *a)
{
    Std_ReturnType ret = E_OK;

    if(akumulator == 0xFFFFFFFFL){
        ret = E_NOT_OK;
        return ret;
    }
    else
    {
        *a = (sint32) akumulator;
        return ret;
    }
}


/**
  @brief Wykonanie operacji matematycznej

  Funkcja wywołuje operacje matematyczne na akumulatorze oraz podanym operandzie. 
  Realizuje [P5]
*/
void Calc_Oper(Calc_Operation_T op, sint32 arg2)
{
    sint32 result;
    Std_ReturnType outValid = E_OK;

    if(akumulator != 0xFFFFFFFF)
    {
        switch(op)
        {
            case CALC_ADD:
                outValid = Lib_Calc_Add(akumulator, arg2, &result);
                break;
            case CALC_SUB:
                outValid = Lib_Calc_Sub(akumulator, arg2, &result);
                break;
            case CALC_MUL:
                outValid = Lib_Calc_Mul(akumulator, arg2, &result);
                break;
            case CALC_DIV:
                outValid = Lib_Calc_Div(akumulator, arg2, &result);
                break;
            default:
                return;
        }

        if(outValid == E_OK)
        {
            Calc_Set_A(result);
        }
        else
        {
            Calc_Set_A(0xFFFFFFFF);
        }
    }
    return;
}

/**
  @brief Wykonanie operacji matematycznej

  Funkcja wywołuje operacje na pamięci kalkulatora
  Realizuje [P5]
*/
void Calc_Mem(Calc_MemOp_T op)
{
    sint32 arg2, result;
    Std_ReturnType outValid = E_OK;

    if(akumulator != 0xFFFFFFFF)
    {
        switch(op)
        {
            case CALC_MEM_ADD:
                arg2 = Lib_Calc_MemR();
                outValid = Lib_Calc_Add(akumulator, arg2, &result);
                if(outValid == E_OK)
                {
                    Lib_Calc_MemS(result);
                }
                break;
            case CALC_MEM_SUB:
                arg2 = Lib_Calc_MemR();
                outValid = Lib_Calc_Sub(akumulator, arg2, &result);
                if(outValid == E_OK)
                {
                    Lib_Calc_MemS(result);
                }
                break;
            case CALC_MEM_STO:
                Lib_Calc_MemS(akumulator);
                break;
            case CALC_MEM_ZERO:
                Lib_Calc_MemS(0);
                break;
            default:
                break;
        }
    }
}