/**
 * @file testMain.c
 * @author your name (you@domain.com)
 * @brief Fonction principale permettant de lancer les tests avec CUnit.
 * @version 0.1
 * @date 2022-05-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "./testHeader.h"

int init_suite_success(void)
{
	return 0;
}

int clean_suite_success(void)
{
	return 0;
}

void main(void) {

    CU_pSuite MatrixStruct = NULL;
    CU_pSuite EFMathematics = NULL;
    CU_pSuite MatrixCalc = NULL;


    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    //Test Unité MatrixStruct
    MatrixStruct = CU_add_suite("Testing MatrixStruct", init_suite_success, clean_suite_success);
    
    CU_ADD_TEST(MatrixStruct, test_matrixGetSize);
    CU_ADD_TEST(MatrixStruct, test_matrixSetSize);
    CU_ADD_TEST(MatrixStruct, test_matrixFieldExist);
    CU_ADD_TEST(MatrixStruct, test_matrixIsSym);


    //Test Unité MatrixCalc

    MatrixCalc = CU_add_suite("Testing matrixCalc Unit", init_suite_success, clean_suite_success);
    CU_ADD_TEST(MatrixCalc, test_matrixIsEqual);
    CU_ADD_TEST(MatrixCalc, test_matrixSum);
    CU_ADD_TEST(MatrixCalc, test_matrixScalar);
    CU_ADD_TEST(MatrixCalc, test_matrixProduct);
    CU_ADD_TEST(MatrixCalc, test_matrixSolve);
    

    //Test Programme TD4 en boite noire avec l'exemple du sujet.


    EFMathematics = CU_add_suite("Testing EFMathamatics in black box", init_suite_success, clean_suite_success);
    CU_ADD_TEST(EFMathematics, testBlindEF_exemple1);
    CU_ADD_TEST(EFMathematics, testBlindEF_exemple2);
    CU_ADD_TEST(EFMathematics, testBlindEF_exemple1_sym);
    //CU_ADD_TEST(EFMathematics, testBlindEF_exemple2_sym);






    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();


}