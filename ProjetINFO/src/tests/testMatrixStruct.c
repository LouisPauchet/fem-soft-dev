#include <CUnit/CUnit.h>
#include <string.h>

#ifndef Matrix
#include "../include/Matrix.h"
#endif

static const double epsilon = 0.00000000001;

void test_matrixGetSize(void) {
    Matrix TestMatrix;
    TestMatrix.SizeX = 3;
    TestMatrix.SizeY = 2;
    
    CU_ASSERT_EQUAL(matrixGetSize(&TestMatrix,'X'), 3);
    CU_ASSERT_EQUAL(matrixGetSize(&TestMatrix,'Y'), 2);
    CU_ASSERT_NOT_EQUAL(matrixGetSize(&TestMatrix,'Y'), 3);
    CU_ASSERT_NOT_EQUAL(matrixGetSize(&TestMatrix,'X'), 2);
}

void test_matrixSetSize(void) {
    Matrix TestMatrix;
    matrixSetSize(&TestMatrix, 'X', 3);
    matrixSetSize(&TestMatrix, 'Y', 2);
    
    CU_ASSERT_EQUAL(matrixGetSize(&TestMatrix,'X'), 3);
    CU_ASSERT_EQUAL(matrixGetSize(&TestMatrix,'Y'), 2);
    CU_ASSERT_NOT_EQUAL(matrixGetSize(&TestMatrix,'Y'), 3);
    CU_ASSERT_NOT_EQUAL(matrixGetSize(&TestMatrix,'X'), 2);
}

void test_matrixGetName(void) {
    Matrix TestMatrix;
    strcpy(TestMatrix.name, "Nom 1");

    CU_ASSERT_STRING_EQUAL(matrixGetName(&TestMatrix), "Nom 1");
}

void test_matrixSetName(void) {
    Matrix TestMatrix;

    matrixSetName(&TestMatrix, "Test Nom");
    CU_ASSERT_STRING_EQUAL(matrixGetName(&TestMatrix), "Test Nom");
    matrixSetName(&TestMatrix, "");
    CU_ASSERT_STRING_EQUAL(matrixGetName(&TestMatrix), "");
    matrixSetName(&TestMatrix, "aaaaaaaaaaaaaaaaaaaa");
    CU_ASSERT_STRING_EQUAL(matrixGetName(&TestMatrix), "aaaaaaaaaaaaaaaaaaaa");
    matrixSetName(&TestMatrix, "aaaaaaaaaaaaaaaaaaaaaaTestTest");
    CU_ASSERT_STRING_EQUAL(matrixGetName(&TestMatrix), "aaaaaaaaaaaaaaaaaaaa");
}

void test_matrixFieldExist(void) {
    Matrix TestMatrix;
    matrixSetSize(&TestMatrix, 'X', 10);
    matrixSetSize(&TestMatrix, 'Y', 30);
    CU_ASSERT(matrixFieldExist(&TestMatrix, 2, 2));
    CU_ASSERT_FALSE(matrixFieldExist(&TestMatrix, 1000, 1000));
    CU_ASSERT_FALSE(matrixFieldExist(&TestMatrix, 1000, 2));
    CU_ASSERT_FALSE(matrixFieldExist(&TestMatrix, 2, 1000));
    CU_ASSERT(matrixFieldExist(&TestMatrix, 10, 30));
    CU_ASSERT(matrixFieldExist(&TestMatrix, 2, 30));
    CU_ASSERT(matrixFieldExist(&TestMatrix, 10, 2));
}

void test_matrixIsSym(void) {
    Matrix TestMatrix;
    CU_ASSERT_FALSE(matrixIsSym(&TestMatrix));
    TestMatrix.isSym = False;
    CU_ASSERT_FALSE(matrixIsSym(&TestMatrix));
    TestMatrix.isSym = True;
    CU_ASSERT(matrixIsSym(&TestMatrix));
    TestMatrix.isSym = 384993;
    CU_ASSERT_FALSE(matrixIsSym(&TestMatrix));
}

void main(void) {
    
   CU_pSuite MatrixStruct = CU_add_suite("Testing MatrixStruct", NULL, NULL);

   CU_ADD_TEST(MatrixStruct, test_matrixGetSize);
   CU_ADD_TEST(MatrixStruct, test_matrixSetSize);
   CU_ADD_TEST(MatrixStruct, test_matrixGetName);
   CU_ADD_TEST(MatrixStruct, test_matrixSetName);
   CU_ADD_TEST(MatrixStruct, test_matrixFieldExist);
   CU_ADD_TEST(MatrixStruct, test_matrixIsSym);

}
