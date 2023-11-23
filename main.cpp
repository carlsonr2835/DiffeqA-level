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

todo
- Better matrix formatter with iomanip
- way to work with fractions? (program is not precise for repeating fractions and may mark them incorrectly as complex/repeated)
- find vectors in cases that eigen values are imaginary and repeated
-ryan: y equation solutions given initial conditions
-magie: format A matrix output

notes:
    THE PROGRAM WILL CRASH for complex numbers when it tries to output them. That is OKAY. I know exactly why that is happening and how to fix it. We just need to be able to print them as strings in the eigenvector functions and ryan's general solution function.

    how 2 run:
        open terminal->cd DiffeqA-level
        g++ main.cpp
        ./a.out
*/

#include "Matrix.hpp"

int main() {
    cout << "Hello! Welcome to the eigen value/eigen vector finder!" << endl << "Please input your A matrix...\n";
    //NOTE: ryan will make print_matrix that looks nice, but that part is currently not in this main.cpp
    //Will not prompt for x1, x2, y1, y2 explicitly at the moment: to use, just input and press enter for x1, x2, y1, y2
    
    //get the A matrix
    double x1, x2, y1, y2;
    Matrix<double> m;
    cin >> x1;
    cin >> x2;
    cin >> y1;
    cin >> y2;
    m.setValues(x1, x2, y1, y2);

    //(DEBUG): print the whole matrix
    cout << "__         __" << endl <<
            "| " << m.getx1() << "      " << m.getx2() << "  |" << endl << 
            "| " << m.gety1() << "      " << m.gety2() << "  |" << endl <<
            "|_         _|" << endl;

    //eigenvalues
    m.find_eigen_values();

    m.print_eigen_values();
    //eigenvectors
    m.find_eigen_vectors();
    m.print_eigen_vectors();

    m.solution_type();
    //print the general solution, ask for initial conditions
    m.print_general_solution();
    cout << "Do you have initial conditions to input? (y/n): "; //no error checking right now. SMART USER!
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
    m.setInitialConditions(independantVariable, dependantVariableX, dependantVariableY);

    //nothing happens with that solving yet...
    
        //after this point is where the y-solution solving and the equilibrium solution classification will need to happen

    return 0;
}