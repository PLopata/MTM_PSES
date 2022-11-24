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

Std_ReturnType custom_Lib_Calc_Add_Passed(sint32 arg0, sint32 arg1, sint32* resVal){
  *resVal = arg0 + arg1;
  return E_OK;
}

Std_ReturnType custom_Lib_Calc_Add_Failed(sint32 arg0, sint32 arg1, sint32* resVal){
  return E_NOT_OK;
}

Std_ReturnType custom_Lib_Calc_Sub_Passed(sint32 arg0, sint32 arg1, sint32* resVal){
  *resVal = arg0 - arg1;
  return E_OK;
}

Std_ReturnType custom_Lib_Calc_Sub_Failed(sint32 arg0, sint32 arg1, sint32* resVal){
  return E_NOT_OK;
}

Std_ReturnType custom_Lib_Calc_Mul_Passed(sint32 arg0, sint32 arg1, sint32* resVal){
  *resVal = arg0 * arg1;
  return E_OK;
}

Std_ReturnType custom_Lib_Calc_Mul_Failed(sint32 arg0, sint32 arg1, sint32* resVal){
  return E_NOT_OK;
}

Std_ReturnType custom_Lib_Calc_Div_Passed(sint32 arg0, sint32 arg1, sint32* resVal){
  *resVal = arg0 / arg1;
  return E_OK;
}

Std_ReturnType custom_Lib_Calc_Div_Failed(sint32 arg0, sint32 arg1, sint32* resVal){
  return E_NOT_OK;
}


/**
  @brief Reset mocków funckji

  Funkcja resetująca mocki funkcji
*/
void Preconditions(){
  Lib_Calc_MemS_reset();
  Lib_Calc_MemR_reset();
  Lib_Calc_Add_reset();
  Lib_Calc_Sub_reset();
  Lib_Calc_Mul_reset();
  Lib_Calc_Div_reset();
}

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
    sint32 arg2;
    
    // Test correct operation of CALC_ADD
    Preconditions();
    akumulator = 0L;
    arg2 = 10;
    Lib_Calc_Add_fake.custom_fake = custom_Lib_Calc_Add_Passed;
    Lib_Calc_Add_fake.return_val = E_OK;
    Calc_Oper(CALC_ADD, arg2);
    TEST_CHECK(Lib_Calc_Add_fake.call_count == 1);
    TEST_CHECK(Lib_Calc_Add_fake.arg0_val == 0L);
    TEST_CHECK(Lib_Calc_Add_fake.arg1_val == 10L);
    TEST_CHECK(Lib_Calc_Add_fake.return_val == E_OK);
    TEST_CHECK(akumulator == 10L);

    // Test incorrect operation of CALC_ADD
    Preconditions();
    akumulator = 2147483647L;
    Lib_Calc_Add_fake.custom_fake = custom_Lib_Calc_Add_Failed;
    Lib_Calc_Add_fake.return_val = E_NOT_OK;
    Calc_Oper(CALC_ADD, 2147483647L);
    TEST_CHECK(Lib_Calc_Add_fake.call_count == 1);
    TEST_CHECK(Lib_Calc_Add_fake.arg0_val == 2147483647L);
    TEST_CHECK(Lib_Calc_Add_fake.arg1_val == 2147483647L);
    TEST_CHECK(Lib_Calc_Add_fake.return_val == E_NOT_OK);
    TEST_CHECK(akumulator == 0xFFFFFFFFL);
    
    // Test correct operation of CALC_SUB
    Preconditions();
    akumulator = 0L;
    Lib_Calc_Sub_fake.custom_fake = custom_Lib_Calc_Sub_Passed;
    Lib_Calc_Sub_fake.return_val = E_OK;
    Calc_Oper(CALC_SUB, 10);
    TEST_CHECK(Lib_Calc_Sub_fake.call_count == 1);
    TEST_CHECK(Lib_Calc_Sub_fake.arg0_val == 0L);
    TEST_CHECK(Lib_Calc_Sub_fake.arg1_val == 10L);
    TEST_CHECK(Lib_Calc_Sub_fake.return_val == E_OK);
    TEST_CHECK(akumulator == -10L);

    // Test incorrect operation of CALC_SUB
    Preconditions();
    akumulator = -2147483648L;
    Lib_Calc_Sub_fake.custom_fake = custom_Lib_Calc_Sub_Failed;
    Lib_Calc_Sub_fake.return_val = E_NOT_OK;
    Calc_Oper(CALC_SUB, 2147483647L);
    TEST_CHECK(Lib_Calc_Sub_fake.call_count == 1);
    TEST_CHECK(Lib_Calc_Sub_fake.arg0_val == -2147483648L);
    TEST_CHECK(Lib_Calc_Sub_fake.arg1_val == 2147483647L);
    TEST_CHECK(Lib_Calc_Sub_fake.return_val == E_NOT_OK);
    TEST_CHECK(akumulator == 0xFFFFFFFFL);
    
    // Test correct operation of CALC_MUL
    Preconditions();
    akumulator = 2L;
    Lib_Calc_Mul_fake.custom_fake = custom_Lib_Calc_Mul_Passed;
    Lib_Calc_Mul_fake.return_val = E_OK;
    Calc_Oper(CALC_MUL, 10);
    TEST_CHECK(Lib_Calc_Mul_fake.call_count == 1);
    TEST_CHECK(Lib_Calc_Mul_fake.arg0_val == 2);
    TEST_CHECK(Lib_Calc_Mul_fake.arg1_val == 10);
    TEST_CHECK(Lib_Calc_Mul_fake.return_val == E_OK);
    TEST_CHECK(akumulator == 20L);

    // Test incorrect operation of CALC_MUL
    Preconditions();
    akumulator = 2147483647L;
    Lib_Calc_Mul_fake.custom_fake = custom_Lib_Calc_Mul_Failed;
    Lib_Calc_Mul_fake.return_val = E_NOT_OK;
    Calc_Oper(CALC_MUL, 4);
    TEST_CHECK(Lib_Calc_Mul_fake.call_count == 1);
    TEST_CHECK(Lib_Calc_Mul_fake.arg0_val == 2147483647L);
    TEST_CHECK(Lib_Calc_Mul_fake.arg1_val == 4);
    TEST_CHECK(Lib_Calc_Mul_fake.return_val == E_NOT_OK);
    TEST_CHECK(akumulator == 0xFFFFFFFFL);
    
    // Test correct operation of CALC_DIV
    Preconditions();
    akumulator = 200L;
    Lib_Calc_Div_fake.custom_fake = custom_Lib_Calc_Div_Passed;
    Lib_Calc_Div_fake.return_val = E_OK;
    Calc_Oper(CALC_DIV, 10);
    TEST_CHECK(Lib_Calc_Div_fake.call_count == 1);
    TEST_CHECK(Lib_Calc_Div_fake.arg0_val == 200L);
    TEST_CHECK(Lib_Calc_Div_fake.arg1_val == 10);
    TEST_CHECK(Lib_Calc_Div_fake.return_val == E_OK);
    TEST_CHECK(akumulator == 20L);

    // Test incorrect operation of CALC_DIV
    Preconditions();
    akumulator = 20;
    Lib_Calc_Div_fake.custom_fake = custom_Lib_Calc_Div_Failed;
    Lib_Calc_Div_fake.return_val = E_NOT_OK;
    Calc_Oper(CALC_DIV, 0);
    TEST_CHECK(Lib_Calc_Div_fake.call_count == 1);
    TEST_CHECK(Lib_Calc_Div_fake.arg0_val == 20L);
    TEST_CHECK(Lib_Calc_Div_fake.arg1_val == 0);
    TEST_CHECK(Lib_Calc_Div_fake.return_val == E_NOT_OK);
    TEST_CHECK(akumulator == 0xFFFFFFFFL);

    // Test invalid command
    Preconditions();
    akumulator = 11;
    Calc_Oper(4, 0);
    TEST_CHECK(akumulator == 11);

    // Test invalid akumulator
    Preconditions();
    akumulator = 0xFFFFFFFF;
    Calc_Oper(CALC_ADD, -10);
    TEST_CHECK(Lib_Calc_Add_fake.call_count == 0);
    TEST_CHECK(Lib_Calc_Sub_fake.call_count == 0);
    TEST_CHECK(Lib_Calc_Mul_fake.call_count == 0);
    TEST_CHECK(Lib_Calc_Div_fake.call_count == 0);
    TEST_CHECK(akumulator == 0xFFFFFFFF);
}


/**
  @brief Test wykonania wszystkich operacji na pamięci kalkulatora

  Funkcja testująca wykonanie wszystkich operacji na pamięci kalkulatora
*/
void Test_Of_Calc_Mem(void)
{
    // Test correct operation of CALC_MEM_ADD
    Preconditions();
    akumulator = 0L;
    Lib_Calc_MemR_fake.return_val = 10;
    Lib_Calc_Add_fake.custom_fake = custom_Lib_Calc_Add_Passed;
    Lib_Calc_Add_fake.return_val = E_OK;
    Calc_Mem(CALC_MEM_ADD);
    TEST_CHECK(Lib_Calc_MemR_fake.call_count == 1);
    TEST_CHECK(Lib_Calc_MemR_fake.return_val == 10);
    TEST_CHECK(Lib_Calc_Add_fake.call_count == 1);
    TEST_CHECK(Lib_Calc_Add_fake.arg0_val == 0);
    TEST_CHECK(Lib_Calc_Add_fake.arg1_val == 10);
    TEST_CHECK(Lib_Calc_Add_fake.return_val == E_OK);
    TEST_CHECK(Lib_Calc_MemS_fake.call_count == 1);
    TEST_CHECK(Lib_Calc_MemS_fake.arg0_val = 10);
    TEST_CHECK(akumulator == 0L);

    // Test incorrect operation of CALC_MEM_ADD
    Preconditions();
    akumulator = 2147483647L;
    Lib_Calc_MemR_fake.return_val = 2147483647L;
    Lib_Calc_Add_fake.custom_fake = custom_Lib_Calc_Add_Failed;
    Lib_Calc_Add_fake.return_val = E_NOT_OK;
    Calc_Mem(CALC_MEM_ADD);
    TEST_CHECK(Lib_Calc_MemR_fake.call_count == 1);
    TEST_CHECK(Lib_Calc_MemR_fake.return_val == 2147483647L);
    TEST_CHECK(Lib_Calc_Add_fake.call_count == 1);
    TEST_CHECK(Lib_Calc_Add_fake.arg0_val == 2147483647L);
    TEST_CHECK(Lib_Calc_Add_fake.arg1_val == 2147483647L);
    TEST_CHECK(Lib_Calc_Add_fake.return_val == E_NOT_OK);
    TEST_CHECK(Lib_Calc_MemS_fake.call_count == 0);
    TEST_CHECK(akumulator == 2147483647L);
    
    // Test correct operation of CALC_MEM_SUB
    Preconditions();
    akumulator = 0L;
    Lib_Calc_MemR_fake.return_val = 10;
    Lib_Calc_Sub_fake.custom_fake = custom_Lib_Calc_Sub_Passed;
    Lib_Calc_Sub_fake.return_val = E_OK;
    Calc_Mem(CALC_MEM_SUB);
    TEST_CHECK(Lib_Calc_MemR_fake.call_count == 1);
    TEST_CHECK(Lib_Calc_MemR_fake.return_val == 10);
    TEST_CHECK(Lib_Calc_Sub_fake.call_count == 1);
    TEST_CHECK(Lib_Calc_Sub_fake.arg0_val == 0);
    TEST_CHECK(Lib_Calc_Sub_fake.arg1_val == 10);
    TEST_CHECK(Lib_Calc_Sub_fake.return_val == E_OK);
    TEST_CHECK(Lib_Calc_MemS_fake.call_count == 1);
    TEST_CHECK(Lib_Calc_MemS_fake.arg0_val = -10);
    TEST_CHECK(akumulator == 0);

    // Test incorrect operation of CALC_MEM_SUB
    Preconditions();
    akumulator = -2147483648L;
    Lib_Calc_MemR_fake.return_val = 2147483647L;
    Lib_Calc_Sub_fake.custom_fake = custom_Lib_Calc_Sub_Failed;
    Lib_Calc_Sub_fake.return_val = E_NOT_OK;
    Calc_Mem(CALC_MEM_SUB);
    TEST_CHECK(Lib_Calc_MemR_fake.call_count == 1);
    TEST_CHECK(Lib_Calc_MemR_fake.return_val == 2147483647L);
    TEST_CHECK(Lib_Calc_Sub_fake.call_count == 1);
    TEST_CHECK(Lib_Calc_Sub_fake.arg0_val == -2147483648L);
    TEST_CHECK(Lib_Calc_Sub_fake.arg1_val == 2147483647L);
    TEST_CHECK(Lib_Calc_Sub_fake.return_val == E_NOT_OK);
    TEST_CHECK(Lib_Calc_MemS_fake.call_count == 0);
    TEST_CHECK(akumulator == -2147483648L);
    
    // Test correct operation of CALC_MEM_STO
    Preconditions();
    akumulator = 2L;
    Calc_Mem(CALC_MEM_STO);
    TEST_CHECK(Lib_Calc_MemS_fake.call_count == 1);
    TEST_CHECK(Lib_Calc_MemS_fake.arg0_val == 2L);
    TEST_CHECK(akumulator == 2L);

    // Test correct operation of CALC_MEM_STO
    Preconditions();
    Calc_Mem(CALC_MEM_ZERO);
    TEST_CHECK(Lib_Calc_MemS_fake.call_count == 1);
    TEST_CHECK(Lib_Calc_MemS_fake.arg0_val == 0L);
    
    // Test invalid command
    Preconditions();
    akumulator = 10L;
    Calc_Mem(4);
    TEST_CHECK(Lib_Calc_MemS_fake.call_count == 0);
    TEST_CHECK(Lib_Calc_MemR_fake.call_count == 0);
    TEST_CHECK(Lib_Calc_Add_fake.call_count == 0);
    TEST_CHECK(Lib_Calc_Sub_fake.call_count == 0);
    TEST_CHECK(Lib_Calc_Mul_fake.call_count == 0);
    TEST_CHECK(Lib_Calc_Div_fake.call_count == 0);
    TEST_CHECK(akumulator == 10L);
    
    // Test incorrect value of akumulator
    Preconditions();
    akumulator = 0xFFFFFFFF;
    Calc_Mem(CALC_MEM_ADD);
    TEST_CHECK(Lib_Calc_MemS_fake.call_count == 0);
    TEST_CHECK(Lib_Calc_MemR_fake.call_count == 0);
    TEST_CHECK(Lib_Calc_Add_fake.call_count == 0);
    TEST_CHECK(Lib_Calc_Sub_fake.call_count == 0);
    TEST_CHECK(Lib_Calc_Mul_fake.call_count == 0);
    TEST_CHECK(Lib_Calc_Div_fake.call_count == 0);
    TEST_CHECK(akumulator = 0xFFFFFFFFL);
}


/*
  Lista testów - wpisz tutaj wszystkie funkcje które mają być wykonane jako testy.
*/
TEST_LIST = {
    { "Test of Calc_Reset", Test_Of_Calc_Reset },   /* Format to { "nazwa testu", nazwa_funkcji } */
    { "Test of Calc_Set_A", Test_Of_Calc_Set_A },
    { "Test of Calc_Get_A", Test_Of_Calc_Get_A },
    { "Test of Calc_Oper", Test_Of_Calc_Oper },
    { "Test of Calc_Mem", Test_Of_Calc_Mem },
    { NULL, NULL }                                        /* To musi być na końcu */
};
    
