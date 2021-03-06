#include "Matrix.h" // put your solution into Matrix.h

#include <iostream>
#include <cassert>
#include <cmath>


using std::cout;
using std::endl;


void assertAlmostEqual(double v1, double v2)
{
    assert( std::abs(v1 - v2) < 1e-13 );
}


void testCopy()
{
   cout << "Copy Test:                ";

   // Create a 3x4 matrix, where all elements are initialized with 1
   Matrix m1( 3,4,1.0 );
   
   // Create a 2x2 matrix, where all elements are initialized with 2   
   Matrix m2( 3,4,2.0 );

   m2 = m1;

    assert( std::abs((m2-m1)(0,0) - 0.0) < 1e-13 );

   m2 = m2; // test self assignment

   cout << "OK" << endl;
}

void testArithmeticOperators()
{
   cout << "Arithmetic Operator Test: ";

   // Create a 2x2 matrix, where all elements are initialized with zero
   Matrix m1( 2,3,0.0 );
   Matrix m2( 2,3,0.0 );
   Matrix m3(3,4,2.0);    

   Matrix m4 (2,2, 1.0);
   Matrix m5 (2,2 ,1.0);
   Matrix m6 (2,2,1.0);

   m6(1,1) = 0.0;

   cout << "m4 und m6 gleich (false): " << (m4==m6) << endl;
   cout << "m4 und m6 NICHT gliech (true): " << (m4!=m6) << endl;
   cout << "m4 und m5 NICHT gleich (flase): " << (m4 != m5) << endl;

   m1(0,0) = 1.0;
   m1(0,1) = 2.0;
   m1(1,0) = 3.0;
   m1(1,1) = 1.0;

   m2(0,0) = 4.0;
   m2(0,1) = 5.0;
   m2(1,0) = 2.0;
   m2(1,1) = 3.0;
    
   m3(0,3) = 3.0;
 
   cout << endl << "m1 " <<  endl << (m1) << endl;
   cout << endl << "m2 " <<  endl << (m2) << endl;


   Matrix sum  ( m1+m2 );
   Matrix prod ( m2*m3 );
   Matrix prod2(m2*m3);
//    assert( std::abs(sum(0,0) - 5.0) < 1e-13 );
//    assert( std::abs(sum(0,1) - 7.0) < 1e-13 );
//    assert( std::abs(sum(1,0) - 5.0) < 1e-13 );
//    assert( std::abs(sum(1,1) - 4.0) < 1e-13 );

//    assert( std::abs(prod(0,0) - 8.0) < 1e-13 );
//    assert( std::abs(prod(0,1) - 11.0) < 1e-13 );
//    assert( std::abs(prod(1,0) - 14.0) < 1e-13 );
//    assert( std::abs(prod(1,1) - 18.0) < 1e-13 );

	

   m1 += m2;
   assert( std::abs(m1(0,0) - sum(0,0)) < 1e-13 );
   cout << endl << "m1+=m2" <<  endl << (m1) << endl;

   m1 -= m1;
   assert( m1(0,0) == 0.0 );
   cout << endl << "m1-=m1" <<  endl << (m1) << endl;

   cout << "OK" << endl;
}

void testMemoryLayout()
{
   cout << "Memory Layout Test :      ";

   // create uninitialized 3x4 matrix
   Matrix m( 3,4 );
    
    /*
    cout << endl;
    cout << m;
    cout << endl;
    cout << m2;
    cout << endl;
    cout << endl;
     */
    
   // Check if rows are adjacent in memory
   double * ptr1 = &m( 1,2 );
   double * ptr2 = &m( 1,3 );
   assert( (ptr2 - ptr1) == 1 );

   double * ptrEndOfRow0   = &m(0,3);
   double * ptrBeginOfRow1 = &m(1,0);
   assert( (ptrBeginOfRow1-ptrEndOfRow0) == 1 );

   cout << "OK" << endl;
}


void functionTakingConstMatrix( const Matrix & m )
{
    std::cout << m(0,0) << std::endl;
    // Print to cout in the following format:
    // columns should be separated with one or more spaces or tabs, rows with newlines
    std::cout << m << std::endl;
}

void testConstCapabilities()
{
   cout << "Const Capability Test:    ";

   Matrix m( 2,2, 1.0 );
   m(0,1) = 5.0;
   cout << "OK" << endl;

   functionTakingConstMatrix( m );
}

void test(){
    Matrix m1( 2,2,1.0 );
    Matrix m2( 2,2,111.0 );
    
    cout << endl << m1 << endl;
    cout << endl << m2 << endl;
    
    
    m1(0,0) = 1.0;
    m1(0,1) = 2.0;
    m1(1,0) = 3.0;
    m1(1,1) = 1.0;
    
    m2(0,0) = 4.0;
    m2(0,1) = 5.0;
    m2(1,0) = 2.0;
    m2(1,1) = 3.0;
    
    
    Matrix sum  ( m1+m2 );
    Matrix sum2 ( m2+m1 );
    std::cout << "kritisch" << std::endl;
    Matrix temp;
    temp = m1*m2;
    Matrix prod ( temp );
    prod = sum2;
   
    cout << prod << endl;
    // temp = m1*m2; -> cout << temp << endl; -> geht kaputt
    
    //assert( std::abs(sum(0,0) - 5.0) < 1e-13 );
    //assert( std::abs(sum(0,1) - 7.0) < 1e-13 );
    //assert( std::abs(sum(1,0) - 5.0) < 1e-13 );
    //assert( std::abs(sum(1,1) - 4.0) < 1e-13 );
    
    //cout << endl << m1 << endl;
    //cout << endl << m2 << endl;
//    cout << endl << prod << endl;
//    cout << endl << temp << endl;
//    cout << endl << m1*m2 << endl;
    
    /*
    assert( std::abs(prod(0,0) - 8.0) < 1e-13 );
    assert( std::abs(prod(0,1) - 11.0) < 1e-13 );
    assert( std::abs(prod(1,0) - 14.0) < 1e-13 );
    assert( std::abs(prod(1,1) - 18.0) < 1e-13 );
    */
    
    //m1 += m2;
    //assert( std::abs(m1(0,0) - sum(0,0)) < 1e-13 );
    
    //m1 -= m1;
    //assert( m1(0,0) == 0.0 );
    
    cout << "OK" << endl;

}

int main(int argc, char** argv)
{
   // test();
   testArithmeticOperators();
   testCopy();
   testMemoryLayout();
   testConstCapabilities();
}
