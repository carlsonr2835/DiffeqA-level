/*
Authors: Ryan Carlson & Marjorie Acheson

Description: 
    This program prompts the user for a 2x2 matrix. It then finds the eigen values through det(A-λI) and solving this expression for the roots.
    It uses class data members to hold the A matrix and the root values which are left expanded to avoid doing calculations with i. It prints and 
    formats the eigenvalue results.

    The Matrix class uses the eigenvalues to find the eigen vectors, printing these for the user. It classifies the type of equilibrium
    solution on the trace-determinant plane and also prints the general solution without solving for initial conditions. This is not something
    we added simply because solving algebraically would have been too hard to code.

    Note: This program only accepts integers and decimals as input, so it is not 100% accurate with irrational numbers (see #58 on the 
        symbolic solution techniques)

Log:
    - 11/13 Ryan created this file and coded it to solve for real eigenvalues
    - 11/14 Ryan changed the eigen values function to also find complex eigenvalues. Created formatted output for eigenvalues, added a lot of comments including this one right here.
    - 11/15 Maggie created functions find_eigen_vectors and print_eigen_vectors. These only currently work in the case that both values are real. To do this I also created a templated Vector struct for printing ease. May delete this struct later seeing as it isn't a big contributor at the moment; Will determine once imaginary and repeated cases are added.
    - 11/18 Maggie created repeated root case and structured find_eigen_vectors and print_eigen_vectors for all possible input
    - 11/18 Ryan Worked on the formatting for the y-solution part. Also included a repeated root value in the matrix struct
    - 11/19 Ryan modified the entire file to be object oriented with a Matrix class for better abstraction, fixed (I think) issues that were coming up with complex roots and repeated roots not being marked properly, added Matrix member variables that made printing easier, and finished properly formatting the general solution. Templated the class.
    - 11/22 Maggie created imaginary eigen vectors (added string vectors in order to print complex solutions), coded all possible trace-determinate solutions as well as what each solution's spring type would be if it can be classified as a spring system.
    - 11/24 Ryan updated the y-solution to output correct solution for real, repeated, and complex roots, created an error checking function for A-matrix input
    - 11/27 Maggie did a not good enough job at eigenvectors for complex roots. I have vastly improved it and the function even has the capabilities of simplifying the answer now. It has worked for all of the examples I could find. I have found ways to break the code (choosing random values to plug in the A matrix), but I'm not sure if it is supposed to work in this instance. I believe they should because I can work through the problems by hand just fine, so I will be working on this.
    - 11/28 Maggie coded the brunt of the matrix printing code. It is still pretty basic and will only someone correctly print the initial A matrix. I will need to add input parameters so it's a more versative function.
    - 11/29 Maggie finished coding the print_matrix function with good formattting and now works for all inputs
    - 11/30 Ryan cleaned up the code, added some comments for clarification, and worked on making the output more readable
    - 12/10 Maggie added explanation for eigen vectors in all possible cases
    - 12/11 Ryan went back in and rechecked each solution against the symbolic solutions techniques, fixed a few formatting issues

Notes:
    run:
        open terminal->cd DiffeqA-level
        g++ main.cpp
        ./a.out or ./a.exe
*/

#include "Matrix.hpp"

//this function is for getting T input (int or double for this project) from the user and has an error-checking loop to avoid input-mismatch
template <typename T>
T get_data_with_error_check(string prompt, T var) {
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
    cout << "Please input your A matrix formatted as follows (integers and decimals allowed)...\n";
    
    //get the A matrix
    double x1, x2, y1, y2;
    Matrix<double> m;
    /*^the class has a lot of templated data members including some numbers that are the results of division calculations. 
    Unless we are using numbers that we KNOW divide evenly, this should be initialized as a double. The drawback is everything prints with
    6 decimal places.*/
    m.print_matrix("x1", "x2", "y1", "y2");
    cout << endl;

    x1 = get_data_with_error_check("\tx1: ", x1);
    x2 = get_data_with_error_check("\tx2: ", x2);
    y1 = get_data_with_error_check("\ty1: ", y1);
    y2 = get_data_with_error_check("\ty2: ", y2);
    
    m.setValues(x1, x2, y1, y2);

    // A matrix print
    cout << endl << "This is your A Matrix:";
    m.print_matrix(to_string(x1), to_string(x2), to_string(y1), to_string(y2));
    cout << endl;
    
    //eigenvalues
    cout << endl << endl << "Now let's determine your eigen values using the following methods:";
    m.find_eigen_values();
    m.print_eigen_values();

    //eigenvectors
    cout << endl << endl << "Using these eigen values, we can find the eigen vectors with the equation (A-λI)*<x,y> = <0,0>:\n\n";
    m.find_eigen_vectors();
    m.print_eigen_vectors();

    //solution type
    m.solution_type();

    //general solution
    m.print_general_solution();

    return 0;
}