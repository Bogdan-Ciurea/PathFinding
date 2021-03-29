/************************************************************************
    University of Leeds
    School of Computing
    COMP1921 - Programming project
    Coursework 2
    File: unit_tests.c
    Student Name: Bogdan Alexandru Ciurea
    Student ID: 201438333
    Email: sc20bac@leeds.ac.uk
    Date Work Commenced: 3rd Mar 2021
*************************************************************************/

#include "unity.h"
#include "functions.h"
#include <float.h>

void test_random(){
    readFromFile("Final_Map.map");
    extern int indexStart, indexFinish;
    indexStart = -1; indexFinish = -1;
    randomNodes();
    int x = 1;
    if(indexStart == indexFinish || indexStart == -1)
        x = 0;
    TEST_ASSERT_EQUAL_INT_MESSAGE( 1, x, "The numbers are not random!" );
}

void test_input_is_number(){
    TEST_ASSERT_EQUAL_INT_MESSAGE( inputIsNumber("--123"), 0, "The input is not a number!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( inputIsNumber("1234.123.123"), 0, "The input is not a number!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( inputIsNumber("asd"), 0, "The input is not a number!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( inputIsNumber("123asd"), 0, "The input is not a number!" );

    TEST_ASSERT_EQUAL_INT_MESSAGE( inputIsNumber("12345"), 1, "The input is a number!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( inputIsNumber("-12345"), 1, "The input is a number!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( inputIsNumber("-123.45"), 1, "The input is a number!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( inputIsNumber("123.45"), 1, "The input is a number!" );

}

void test_reading_nodes(){
    readFromFile("Final_Map.map");

    TEST_ASSERT_MESSAGE( nodeInNodes(53.801600, -1.564000) == -1, "Node does not exist!" ); //node at the edge
    TEST_ASSERT_MESSAGE( nodeInNodes(100, -1) == -1,"Node does not exist!" ); //node outside
    TEST_ASSERT_MESSAGE( nodeInNodes(53.802060, -1.547648) == -1,"Node does not exist!" ); //node inside

    TEST_ASSERT_EQUAL_INT_MESSAGE( nodeInNodes(53.809295, -1.555582) == -1, 0, "Node exists!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( nodeInNodes(53.809470, -1.553787) == -1, 0, "Node exists!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( nodeInNodes(53.805273, -1.562772) == -1, 0, "Node exists!" );
}

void test_nonexistent_file(){
    TEST_ASSERT_EQUAL_INT_MESSAGE( readFromFile("Hello.c"), 0, "This file should not exist!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( readFromFile("main.c"), 0, "This file should have invalid format!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( readFromFile("Final_Map.map"), 1, "This file has to exsit!" );
}

void test_distances(){
    readFromFile("Final_Map.map");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE( distBetweenNodes(0, 1), 11.006410,  "Incorrect distance!");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE( distBetweenNodes(2, 3), 11.029994,  "Incorrect distance!");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE( distBetweenNodes(0, 2), DBL_MAX,  "Incorrect distance!");
}


void setUp(){

}
void tearDown(){

}

int main(){
    UNITY_BEGIN();
    RUN_TEST(test_nonexistent_file);
    RUN_TEST(test_input_is_number);
    RUN_TEST(test_reading_nodes);
    RUN_TEST(test_random);
    RUN_TEST(test_distances);

    return UNITY_END();
}
