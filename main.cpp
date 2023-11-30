/*
Authors: Ryan Carlson & Marjorie Acheson
Description: 
    This program prompts the user for a 2x2 matrix. It then finds the eigen values through det(A-λI) and solving this expression for the roots.
    It uses structs to hold the A matrix and the root values which are left expanded to avoid doing calculations with i. It prints and 
    formats the eigenvalue results.

    In the future, this program may also find eigenvectors, classify equilibrium solutions, and print the final y function (also able to
    handle initial conditions). We may create a user interface through SFML...or not.
Log:
    - 11/13 Ryan created this file and coded it to solve for real eigenvalues
    - 11/14 Ryan changed the unsimplified_root_finder to also find complex eigenvalues. Created formatted output for eigenvalues, added a lot of comments including this one right here.
    - 11/15 Maggie created functions find_eigen_vectors and print_eigen_vectors. These only currently work in the case that both values are real. To do this I also created a templated Vector struct for printing ease. May delete this struct later seeing as it isn't a big contributor at the moment; Will determine once imaginary and repeated cases are added.
    - 11/18 Maggie created repeated root case and structured find_eigen_vectors and print_eigen_vectors for all possible input
    - 11/18 Ryan Worked on the formatting for the y-solution part. Also included a repeated root value in the matrix struct
    - 11/19 Ryan modified the entire file to be object oriented with a Matrix class for better abstraction, fixed (I think) issues that were coming up with complex roots and repeated roots not being marked properly, added Matrix member variables that made printing easier, and finished properly formatting the general solution. Templated the class.
    - 11/22 Maggie created imaginary eigen vectors (added string vectors in order to print complex solutions), coded all possible trace-determinate solutions as well as what each solution's spring type would be if it can be classified as a spring system.
    - 11/24 Ryan updated the y-solution to output correct solution for real, repeated, and complex roots, created an error checking function for A-matrix input
    - 11/27 Maggie did a not good enough job at eigenvectors for complex roots. I have vastly improved it and the function even has the capabilities of simplifying the answer now. It has worked for all of the examples I could find. I have found ways to break the code (choosing random values to plug in the A matrix), but I'm not sure if it is supposed to work in this instance. I believe they should because I can work through the problems by hand just fine, so I will be working on this.
    - 11/28 Maggie coded the brunt of the matrix printing code. It is still pretty basic and will only someone correctly print the initial A matrix. I will need to add input parameters so it's a more versative function.
    - 11/29 Maggie finished coding the print_matrix function with good formattting and now works for all inputs

todo
- way to work with fractions? (program is not precise for repeating fractions and may mark them incorrectly as complex/repeated)

notes:
    how 2 run:
        open terminal->cd DiffeqA-level
        g++ main.cpp
        ./a.out
    
    issues based on the solutions list: ##### Hey ryan I didn't wanna touch this in case it wasn't referring to the vectors, but all vectors should now be working for the master list problems that are complex (CHECKED THOROUGHLY)
        #51 CORRECT
        #52 CORRECT
        #53 v2 signs are flipped, but I'm pretty sure that doesn't matter
        #54 real part sign on v2 is wrong
        #55 incorrect v2.y sign on the real number only
        #56 incorrect v2.y sign, the complex number over the real denominator can be simplified
        #57 CORRECT
        #58 rounding in eigenvalue messing this up
*/

#include "Matrix.hpp"

template <typename T>
T get_int_with_error_check(string prompt, T var) {
    while (true) {
        cout << prompt;
        cin >> var;
        if (cin.fail()) {
            cout << "Incorrect input. Try again...\n";
            cin.clear();
            cin.ignore();
        }
        else {
            return var;
        }
    }
}

int main() {
    cout << "Hello! Welcome to the eigen value/eigen vector finder!" << endl;
    cout << "Please input your A matrix formatted as follows...\n";
    
    
    //get the A matrix
    double x1, x2, y1, y2;
    Matrix<double> m;
//bruh
    m.print_matrix("x1", "x2", "y1", "y2");
    cout << endl;

    x1 = get_int_with_error_check("\tx1: ", x1);
    x2 = get_int_with_error_check("\tx2: ", x2);
    y1 = get_int_with_error_check("\ty1: ", y1);
    y2 = get_int_with_error_check("\ty2: ", y2);
    
    m.setValues(x1, x2, y1, y2);

    // A matrix print
    m.print_matrix(to_string(x1), to_string(x2), to_string(y1), to_string(y2));
    
    //eigenvalues
    m.find_eigen_values();

    m.print_eigen_values();
    //eigenvectors
    m.find_eigen_vectors();
    m.print_eigen_vectors();

    m.solution_type();
    //print the general solution, ask for initial conditions
    m.print_general_solution();
    /*cout << "Do you have initial conditions to input? (y/n): "; //no error checking right now. SMART USER!
    string answer = "";
    cin >> answer;
    if (answer != "y" && answer != "Y") {
        cout << "bye now!\n";
        return 0;
    }
    double independantVariable, dependantVariableX, dependantVariableY;
    cout << "Independant variable: ";
    cin >> independantVariable;
    cout << "Dependant x: ";
    cin >> dependantVariableX;
    cout << "Dependant y: ";
    cin >> dependantVariableY;
    m.setInitialConditions(independantVariable, dependantVariableX, dependantVariableY);*/

    //nothing happens with that solving yet...
    
        //after this point is where the y-solution solving and the equilibrium solution classification will need to happen

    return 0;
}