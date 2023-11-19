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
todo
- make a really nice matrix formatter cause this is super uglay
- it can't take in nonintegers. this must change eventually. This is what templates are for!!!
- find vectors in cases that eigen values are imaginary and repeated
- make a string for the eigenvalues
-ryan: object orient this shit
-ryan: y equation solutions given initial conditions
-maggie: eigen vectors
-maggie: classify equilibrium solutions
*/
#include <iostream>
#include <cmath> //sqrt
#include <string>

using namespace std;

//a struct will hold the A matrix the user will input. This is for ease of fetching things.
struct A {
    int x1, x2, y1, y2;
};

//I believe this is unused but I left it in cause I didn't know if the identity matrix is a standard or not
/*struct I {
    int x1 = 1;
    int x2 = 0;
    int y1 = 0;
    int y2 = 1;
};*/

//This is in a struct because these three quantities get passed around between functions
struct Root {
    double rootLeftValue; //separate from right so that it's easy to print complex numbers
    double rootRightValue;
    bool isComplex;
    bool isRepeated;
};

template<class T>
struct Vector {
    T x,y;
};

//finds the two quantities on either side of the +-, keeps them separate, determines if complex
Root unsimplified_root_finder(int a, int b, int c) {
    Root r;

    //calculate the left quantity, -b/2a, which is guaranteed to be real
    double left = (-1 * b) / (2 * a);
    r.rootLeftValue = left;

    //calculate the right quantity, sqrt(b^2-4ac)/2a, which MIGHT be imaginary
    double right = 4 * a * c;
    right = (b * b) - right;
    //check for negative root
    if (right < 0) {
        //store that the root is complex so that we can determine when to print an i
        r.isComplex = true;
        //make the root real so we can store the rightside value in the root struct and finish evaluating the rightside
        right *= -1;
    }
    //finish evaluatingt the rightside regardless of whether it is complex (because we stored the i in the struct)
    right = sqrt(right);
    right = right / (2 * a);
    r.rootRightValue = right;

    if (right == 0) {
        r.isRepeated = true;
    }
    else {
        r.isRepeated = false;
    }

    //we now have all three parts of the root expression: left side, right side, and if it is complex
    return r;
}

//takes a root struct that holds a left side, right side, and if its complex, formats everything!
void print_eigen_values(Root r) { //this looks confusing but trust the process
    if (r.isRepeated) {
        cout << "Your eigen value is: ";
        cout << r.rootLeftValue;
        cout << " (repeated root)\n";
    }
    cout << "Your eigen values are: ";
    //printing for if the root is NOT complex (finishing the math we left off by separating left and right)
    if (!r.isComplex) { //prints "root1, root2"
        cout << r.rootLeftValue + r.rootRightValue; //the + part of the +/
        cout << ", ";
        cout << r.rootLeftValue - r.rootRightValue; //the - part of the +-
        cout << endl;
    }
    //printing for if the root is complex (this is why we left left and right separate)
    else { //prints "left+iright, left-iright"
        cout << r.rootLeftValue;
        cout << "+i";
        cout << r.rootRightValue;
        cout << ", ";
        cout << r.rootLeftValue;
        cout << "-i";
        cout << r.rootRightValue;
        cout << endl;
    }
    return;
}

template<typename T>
Vector<T> find_eigen_vectors(T Lr, T Rr, A& a, bool complex) {
    if (!complex) {
        if ((Lr+Rr) != (Lr-Rr)) {
            //hopefully cheekily finding eigenvectors using slickboy moves
            //found y using the equation Ax + By = 0
            //in this case, assuming x = 1, y = -A/B
            Vector<T> result1;
            result1.x = 1;
            result1.y = (-1)*(a.x2/(a.x1-(Lr+Rr)));

            Vector<T> result2;
            result2.x = 1;
            result2.y = (-1)*(a.x2/(a.x1-(Lr-Rr)));
            
            print_eigen_vectors(result1, Lr+Rr);
            print_eigen_vectors(result2, Lr-Rr);

        } else {
            Vector<T> result1;
            result1.x = 1;
            result1.y = (-1)*((a.x1-(Lr+Rr))/a.x2);
            
            Vector<T> result2;
            result2.x = 0;
            result2.y = 1;

            print_eigen_vectors(result1, Lr-Rr);
            print_eigen_vectors(result2, Lr-Rr);
        }

    } else {
        cout << "here";
    }
}

template<typename T>
void print_eigen_vectors(Vector<T>& vector, T value) {
    cout << "Eigen Value " << value << " has the vector: <";
    cout << vector.x << ", ";
    cout << vector.y << ">" << endl;
}


//smart user for now :))))
//assumes following the format Y'=AY where A is a 2x2 matrix and there is an initial condition <-that part isn't coded yet

int main () {
    //declare two variables for the A matrix
    A a;

    //prompt user for the matrix A
    cout << "Hello! Welcome to the eigen value/eigen vector finder!" << endl << "Please input your A matrix...\n";
    //the visual formatting is WIP and is just there right now so users know what to do. May be changed later
        //it prints the inputed values as you go

    //get x1
    cout << "__         __" << endl <<
            "| x1     x2 |" << endl << 
            "| y1     y2 |" << endl <<
            "|_         _|" << endl;
    cout << "Input x1:";
    cin >> a.x1;
    //get x2
    cout << "__         __" << endl <<
            "| " << a.x1 << "      x2 |" << endl << 
            "| y1     y2 |" << endl <<
            "|_         _|" << endl;
    cout << "Input x2:";
    cin >> a.x2;
    //get y1
    cout << "__         __" << endl <<
            "| " << a.x1 << "      " << a.x2 << "  |" << endl << 
            "| y1     y2 |" << endl <<
            "|_         _|" << endl;
    cout << "Input y1:";
    cin >> a.y1;
    //get y2
    cout << "__         __" << endl <<
            "| " << a.x1 << "      " << a.x2 << "  |" << endl << 
            "| " << a.y1 << "      y2 |" << endl <<
            "|_         _|" << endl;
    cout << "Input y2:";
    cin >> a.y2;
    //print the whole matrix
    cout << "__         __" << endl <<
            "| " << a.x1 << "      " << a.x2 << "  |" << endl << 
            "| " << a.y1 << "      " << a.y2 << "  |" << endl <<
            "|_         _|" << endl;

    //calculate the eigenvalues
        //find A - lambda*I
            //=det({x1-L, x2}, {y1, y2-L})
            //no math needed here
            cout << "\nA-λI:\n";
            cout << "__         __" << endl <<
            "| " << a.x1 << "-λ    " << a.x2 << "  |" << endl << 
            "| " << a.y1 << "      " << a.y2 << "-λ|" << endl <<
            "|_         _|" << endl;
        //find det(A - lambda*I)
        cout << "\ndet(A - λI):\n";
        cout << "(" << a.x1 << "-λ)(" << a.y2 << "-λ) - (" << a.x2 << ")(" << a.y1 << ")\n";

        //quatratic terms:
            //a (squared term): 1 (I think always?)
            //b (linear term): A.x1 + A.y2
            //c (const): A.x2 * A.y1 + A.x1 * A.y2
        int a1 = 1;
        int b1 = a.x1*-1 + a.y2*-1;
        int c1 = (a.x1 * a.y2) - (a.x2 * a.y1);
        //output the standard form quadratic equation
        cout << "=λ^2 + " << b1 << "λ + " << c1 << endl;

        //send these values to a quadratic formula function (which works for complex)
        Root r = unsimplified_root_finder(a1, b1, c1); //r now holds the roots
        //send to this function for proper formatting
        print_eigen_values(r);

        // add case where if root is a repeated root once ryan has coded that
        if (r.isComplex) {
            find_eigen_vectors(r.rootLeftValue, r.rootRightValue, a, true);
        } else { // do beautiful magically amazing things
            find_eigen_vectors(r.rootLeftValue, r.rootRightValue, a, false);
        }
        
        cout << "General solution\n\ty(t)=c1*v1*e^(λ1*t)+c2*v2*e^(λ2*t)\n";
        cout << "Your solution\n\ty(t)=c1*<" << /*print v1.x here*/ "v1.x, " << /*print v1.y here*/ "v1.y>";
        cout << "*e^(" << /*print L1 here*/ "λ1*t)";
        cout << "+c2<" << /*print v2.x here*/"v2.x, " << /*print v2.y here*/"v2.y>";
        cout << "*e^(" << /*print L2 here*/"λ2*t)\n\n";

        cout << "Do you have initial conditions you would like to input? (y/n): ";
        string answer = "";
        cin >> answer;
        if (answer != "y" && answer != "Y") {
            "Bye!\n";
            return 0;
        }
        int independant = 0;
        int dependant = 0;
        cout << "Enter independent variable: ";
        cin >> independant;
        cout << "Enter dependent variable: ";
        cin >> dependant;

        //add this math part

    return 0;
}