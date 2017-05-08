#include <array>
#include <exception>
#include <vector>
#include "Complex.h"
#include "Matrix.h"

using namespace std;

int main()
{

    Complex c1;
    Complex c2;
    Complex c3(1,1);

    cout << "Testing Complex Class:" << endl;
    cout << "c1, c2, c3: " << c1 << ", " << c2 << ", " << c3 << endl;

    cout << "\nPlease enter values for c1, c2 (ex: 1+5.3i 1.2-i):" << endl;
    cin >> c1 >> c2; // the sample output is for the example input

    cout << "c1, c2, c3: " << c1 << ", " << c2 << ", " << c3 << endl;

    cout << "\nThe real parts of c1, c2, c3: " << c1.getReal() << ", " << c2.getReal()
         << ", " << c3.getReal() << endl;

    cout << "\n~c3: " << (~c3) << endl;
    cout << "c1 + c3: " << (c1 + c3) << endl;

    cout << "\nc1 - c3: " << (c1 - c3) << endl;
    cout << "c1 += (-c3): " << (c1 += (-c3)) << endl;
    cout << "c1 / c3: " << (c1 / c3) << endl;

    cout << "\n2 * c1 + 7: " << (2 * c1 + 7) << endl;
    cout << "3 / c3: " << (3 / c3) << endl;
    cout << "c2 * c3: " << (c2 * c3) << endl;

    cout << "\nSetting c1 to c3..." << endl;
    c1 = c3;
    cout << "c1 == c3: " << (c1 == c3 ? "true" : "false") << endl;
    cout << "c2 == c3: " << (c2 == c3 ? "true" : "false") << endl;

    // because we can't rely on C++11 vector list initialization...
    array<Complex, 4> v0_init = {Complex(-1,0), Complex(3,4), Complex(0,1), Complex(1,0)};
    vector<Complex> mat_vals(v0_init.begin(), v0_init.end());

    Matrix mat1;
    Matrix mat2(2, mat_vals);
    Matrix mat3(2);

    cout << "\n\nTesting Matrix Class:" << endl;
    cout << "mat1:\n" << mat1 << endl;
    cout << "mat2:\n" << mat2 << endl;
    cout << "mat3:\n" << mat3 << endl;

    try
    {
        cout << "\nChanging mat2 to a 0x0 matrix..." << endl;
        mat2 = Matrix(0);
    }
    catch (const invalid_argument& e)
    {
        cerr << "Error Caught: " << e.what() << endl;
    }

    cout << "\nChanging mat2 to a 3x3 matrix..." << endl;
    mat2.size(3);
    cout << "mat2 is now the following " << mat2.size() << "x" << mat2.size() << " matrix:" << endl;
    cout << mat2 << endl;

    cout << "\nChanging mat2 back to a 2x2 matrix..." << endl;
    mat2.size(2);
    cout << "mat2 is now the following " << mat2.size() << "x" << mat2.size() << " matrix:" << endl;
    cout << mat2 << endl;

    cout << "\nSetting mat3(1,1) to 7+2i..." << endl;
    mat3(1,1) = Complex(7,2);
    cout << "mat3 is now:" << endl;
    cout << mat3 << endl;

    try
    {
        cout << "\nAccessing mat3(2,1)..." << endl;
        mat3(2,1) = Complex(7.1, 0);
    }
    catch (const out_of_range& e)
    {
        cerr << "Error Caught: " << e.what() << endl;
    }

    Matrix mat4;
    unsigned int user_size;
    cout << "\nTesting user input:" << endl;
    cout << "How large would you like to make your matrix?: ";
    cin >> user_size;  // 2 was entered for the sample output
    mat4.size(user_size);
    
    cout << "Please enter the " << (user_size * user_size)
         << " terms required to create your matrix on a single line "
         << "\n(ex: 1+2i 1+0i 0-5i 3.2+5.25i):\n";
    mat4.size(user_size);
    cin >> mat4; // here, the sample output user entered the first 3 sample numbers (they forgot 1)
    cout << "The matrix you entered was:\n" << mat4 << endl;

    cout << "\nMatrix Math:" << endl;
    cout << "~mat2:\n" << (~mat2) << endl;
    try
    {
        cout << "\nTrying to add mat1 to mat3..." << endl;
        cout << "mat1 + mat3:" << endl << (mat1 + mat3) << endl;
    }
    catch (const domain_error& e)
    {
        cerr << "Error Caught: " << e.what() << endl;
    }

    cout << "\nmat2 + mat3:\n" << (mat2 + mat3) << endl;
    cout << "\nmat2 - mat3:\n" << (mat2 - mat3) << endl;
    cout << "\nmat3 += (-mat2):\n" << (mat3 += (-mat2)) << endl;
    cout << "\nmat3 / mat3(1,0):\n" << (mat3 / mat3(1,0)) << endl;

    cout << "\n2 * mat2:\n" << (2 * mat2) << endl;

    cout << "\nmat2 is now:\n" << mat2 << endl;
    cout << "\nmat3 is now:\n" << mat3 << endl;

    cout << "\nmat3 * mat2 / 2:\n" << (mat3 * mat2 / 2) << endl;

    cout << "\nSetting mat1 to mat3..." << endl;
    mat1 = mat3;
    cout << "mat1 == mat3: " << (mat1 == mat3 ? "true" : "false") << endl;
    cout << "mat2 == mat3: " << (mat2 == mat3 ? "true" : "false") << endl;
}