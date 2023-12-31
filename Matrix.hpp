#include <iostream>
#include <string>
#include <vector>
#include <cmath> //sqrt

using namespace std;

#ifndef MATRIX_HPP
#define MATRIX_HPP

template <typename T>
class Matrix {
    public:
        Matrix();
        void setValues(T X1, T X2, T Y1, T Y2);
        void find_eigen_values(); //Ryan
        void print_eigen_values(); //Ryan
        void find_eigen_vectors(); //Maggie
        void print_eigen_vectors(); //Maggie
        void print_matrix(string X1, string X2, string Y1, string Y2); //Maggie
        void print_general_solution(); //Ryan
        void solution_type(); //Maggie

    private:
        //A matrix values
        T x1, x2, y1, y2;
        //eigen roots and their properties
        double eigenRootLeftSide;
        double eigenRootRightSide;
        bool complexEigenValues;
        bool repeatedEigenValues;
        //full eigen values which are used for printing only (to avoid math with i)
        string eigenValue1;
        string eigenValue2;
        //eigen vectors
        vector<T> v1;
        vector<T> v2;
        // complex vectors
        vector<string> complexV1;
        vector<string> complexV2;
};

//this doesn't really do anything :)
template <typename T>
Matrix<T>::Matrix() { //initialize everything to default
    eigenRootLeftSide = 0.0;
    eigenRootRightSide = 0.0;
    complexEigenValues = false;
    repeatedEigenValues = false;
    eigenValue1 = "";
    eigenValue2 = "";
}

template <typename T>
void Matrix<T>::setValues(T X1, T X2, T Y1, T Y2) {
    x1 = X1;
    x2 = X2;
    y1 = Y1;
    y2 = Y2;
}

//computes determinant, finds lambda quadratic equation, solves eigenvalues, marks if repeated or complex, is NOT ACCURATE for repeating fractions
template <typename T>
void Matrix<T>::find_eigen_values() {
    //find A - lambda*I
        //=det({x1-L, x2}, {y1, y2-L})
        //no math needed here
        cout << "\nA-λI:\n";
        print_matrix(to_string(x1)+"-λ", to_string(x2), to_string(y1), to_string(y2)+"-λ");
        
    //find det(A - lambda*I)
    cout << endl << "\ndet(A - λI):\n\n";
    cout << "\t(" << x1 << "-λ)(" << y2 << "-λ) - (" << x2 << ")(" << y1 << ")\n";

    //quatratic terms:
    double a = 1;
    double b = x1*-1 + y2*-1;
    double c = (x1 * y2) - (x2 * y1);
    //output the standard form quadratic equation
    cout << "\t=λ^2 + " << b << "λ + " << c << endl << endl;

    //repeated root case
    if ((abs(b*b) - 4*c) == 0) {
        repeatedEigenValues = true;
    }

    //find left side of the +/ in the quadratic equation
    eigenRootLeftSide = (-1 * b) / (2 * a);

    //calculate the right quantity, sqrt(b^2-4ac)/2a, which MIGHT be imaginary
    eigenRootRightSide = 4 * a * c;
    eigenRootRightSide = (b * b) - eigenRootRightSide;
    //check for negative root
    if (eigenRootRightSide < 0) {
        //store that the root is complex so that we can determine when to print an i
        complexEigenValues = true;
        //make the root real so we can store the rightside value in the root struct and finish evaluating the rightside
        eigenRootRightSide *= -1;
    }
    //finish evaluatingt the rightside regardless of whether it is complex (because we stored the i in the struct)
    eigenRootRightSide = sqrt(eigenRootRightSide);
    eigenRootRightSide = eigenRootRightSide / (2 * a);
    
    //build the strings which are used for print functions
    if (complexEigenValues) {
        if (eigenRootLeftSide == 0) { //complex only
            eigenValue1 = "i" + to_string(eigenRootRightSide);
            eigenValue2 = "-i" + to_string(eigenRootRightSide);
        }
        else {
            eigenValue1 = to_string(eigenRootLeftSide) + "+i" + to_string(eigenRootRightSide);
            eigenValue2 = to_string(eigenRootLeftSide) + "-i" + to_string(eigenRootRightSide);
        }
    }
    else { //real
        eigenValue1 = to_string(eigenRootLeftSide + eigenRootRightSide);
        eigenValue2 = to_string(eigenRootLeftSide - eigenRootRightSide);
    }
}

//utilizes strings to make it easier to print. Eigen value doubles stay sepatated as complex numbers so we can do math with them
template <typename T>
void Matrix<T>::print_eigen_values() {
    if (repeatedEigenValues) {
        cout << "Your eigen value is:\n\n\t" << eigenValue1 << " (repeated roots)\n";
    } else {
        cout << "Your eigen values are:\n\n\t" << eigenValue1 << ", " << eigenValue2 << endl;;
    }
}

template <typename T>
void Matrix<T>::find_eigen_vectors() {
    if (!complexEigenValues) { //real roots
        if(!repeatedEigenValues) {
            // printing things to be pretty
            cout << "For value " << eigenValue1 << " you get: ";
            print_matrix(to_string(x1-(eigenRootLeftSide+eigenRootRightSide)), to_string(x2), to_string(y1), to_string(y2-(eigenRootLeftSide+eigenRootRightSide)));
            cout << " * <x,y> = <0,0>" << endl;

            cout << endl << "For value " << eigenValue2 << " you get: ";
            print_matrix(to_string(x1-(eigenRootLeftSide-eigenRootRightSide)), to_string(x2), to_string(y1), to_string(y2-(eigenRootLeftSide-eigenRootRightSide)));
            cout << " * <x,y> = <0,0>" << endl;

            cout << endl << "Now we have to solve out for x and y with the equations: " << endl;
            cout << x1-(eigenRootLeftSide+eigenRootRightSide) << "x + " << x2 << "y = 0" << endl;
            cout << x1-(eigenRootLeftSide-eigenRootRightSide) << "x + " << x2 << "y = 0" << endl;

            cout << endl << "Assuming the value of x to be one, we get the vectors: " << endl;

            //hopefully cheekily coding eigenvectors using slickboy moves
            //found y using the equation Ax + By = 0
            //in this case, assuming x = 1, y = -A/B
            v1.push_back(1);
            v1.push_back( (-1)*(x2/( x1-(eigenRootLeftSide + eigenRootRightSide) )) );

            v2.push_back(1);
            v2.push_back((-1)*(x2/(x1-(eigenRootLeftSide - eigenRootRightSide))));

        } else { // repeated
            cout << "For value " << eigenValue1 << " you get: ";
            print_matrix(to_string(x1-(eigenRootLeftSide+eigenRootRightSide)), to_string(x2), to_string(y1), to_string(y2-(eigenRootLeftSide+eigenRootRightSide)));
            cout << " * <x,y> = <0,0>" << endl;

            cout << endl << "Now we have to solve out for x and y with the equation: " << endl;
            cout << x1-(eigenRootLeftSide+eigenRootRightSide) << "x + " << x2 << "y = 0" << endl;

            v1.push_back(1);
            v1.push_back((-1)*((x1-(eigenRootLeftSide + eigenRootRightSide))/x2));

            cout << "Since we don't have a second value, we need to use the equation (A-λI)*<n,m> = <x,y>: " << endl;
            print_matrix(to_string(x1-(eigenRootLeftSide+eigenRootRightSide)), to_string(x2), to_string(y1), to_string(y2-(eigenRootLeftSide+eigenRootRightSide)));
            cout << " * <n,m> = <" << v1[0] << "," << v1[1] << ">" << endl;

            cout << endl << "Assuming the value of n to be zero, we can find the second vector" << endl;
            
            v2.push_back(0);
            v2.push_back(1/x2);
        }

    } else { //complex roots
        cout << "For value " << eigenValue1 << " you get: ";
        print_matrix(to_string(x1) + "-" + eigenValue1, to_string(x2), to_string(y1), to_string(y2) + "-" + eigenValue1);
        cout << " * <x,y> = <0,0>" << endl;

        cout << endl << "For value " << eigenValue2 << " you get: ";
        print_matrix(to_string(x1) + "-" + eigenValue2, to_string(x2), to_string(y1), to_string(y2) + "-" + eigenValue2);
        cout << " * <x,y> = <0,0>" << endl;

        cout << endl << "Now we have to solve out for x and y with the equations: " << endl;
        cout << "(" << to_string(x1) + "-" + eigenValue1 << ")x + " << x2 << "y = 0" << endl;
        cout << "(" << to_string(y2) + "-" + eigenValue2 << ")x + " << x2 << "y = 0" << endl;

        cout << endl << "Assuming the value of x to be one, we get the vectors: " << endl;

    // assume the previous equation
        // complex roots follow the appearance of -(x1 - a + bi)/x2 
        // with this in mind, I need to account for several simplified cases
        // 1) normal      -> -(x1 - (a + bi))/x2    -(x1 + (a + bi))/x2
        // 2) a=x1        ->  (bi)/x2               -(x1 + (a + bi))/x2
        // 3) a=-x1       -> -(x1 - (a + bi))/x2    -(bi)/x2
        // 4) x2=1        -> -(x1 - (a + bi))       -(x1 + (a + bi))
        // 5) a=x1 & x2=1 -> -(bi)                  -(x1 + (a + bi))
        // 6) I have also accounted for if (x1 - a) and b are divisible by x2 to simplify further
        
    // simplying fraction if needed
        // starting variables as if not simplifiable
        T left = (-1)*(x1-eigenRootLeftSide);
        T right = eigenRootRightSide;
        int leftD = left/x2;
        int rightD = right/x2;
        string division = ("/" + to_string(x2));
        if ((leftD == left/x2) && (rightD == eigenRootRightSide/x2)) { // if simplifiable
            left = leftD;
            right = rightD;
            division = "";
        }

        string real = ""; // assuming a and x1 cancel
        string imaginary = "i"; // assuming simplification to i
        if (left != x2 && right != x2) { // if it doesn't simplify to i
            if (left != 0) real = (to_string(left) + "+"); // and x1 did not cancel
            if (abs(right) != 1.0) imaginary = (to_string(abs(right)) + "i"); // checks b
        }

        complexV1.push_back("1");
        complexV1.push_back("(" + real + imaginary + ")" + division);

        real = ""; // assuming a and x1 cancel
        imaginary = "-i"; // assuming simplification to -i
        if (left != x2 && right != x2) { // did not simplify to -i
            if (left != 0) real = (to_string(left)); // a and x1 did not cancel
            if (abs(right) != 1) imaginary = ("-" + to_string(abs(right)) + "i"); // checks b
        }
        
        complexV2.push_back("1");
        complexV2.push_back("(" + real + imaginary + ")" + division);
    }
}

template <typename T>
void Matrix<T>::print_eigen_vectors() {
    cout << endl;
    if(!complexEigenValues) {
        //v1
        cout << "\tEigen Value " << eigenValue1 << " has the vector: <";
        cout << v1.at(0) << ", ";
        cout << v1.at(1) << ">" << endl;
        //v2
        cout << "\tEigen Value " << eigenValue2 << " has the vector: <";
        cout << v2.at(0) << ", ";
        cout << v2.at(1) << ">" << endl;
    }
    else {
        //v1
        cout << "\tEigen Value " << eigenValue1 << " has the vector: <";
        cout << complexV1.at(0) << ", ";
        cout << complexV1.at(1) << ">" << endl;
        //v2
        cout << "\tEigen Value " << eigenValue2 << " has the vector: <";
        cout << complexV2.at(0) << ", ";
        cout << complexV2.at(1) << ">" << endl;
    }
    cout << endl;
}

template <typename T>
void Matrix<T>::print_matrix(string X1, string X2, string Y1, string Y2) { 
    //vector<int> lengths = {(int)(X1.length()),(int)(X2.length()),(int)(Y1.length()),(int)(Y2.length())}; //this works on Maggie's windows machine but not Ryan's mac
    vector<int> lengths;
    lengths.push_back((int)(X1.length())); //this works for everyone. We are a happy family
    lengths.push_back((int)(X2.length()));
    lengths.push_back((int)(Y1.length()));
    lengths.push_back((int)(Y2.length()));

    int longestCol1 = lengths[0];
    if (lengths[2] > longestCol1) {
        longestCol1 = lengths[2];
    }

    int longestCol2 = lengths[1];
    if (lengths[3] > longestCol2) {
        longestCol2 = lengths[3];
    }

//line 1
    cout << endl << "/ " << X1;
    for (int i = 0; i < 2 + (longestCol1 - lengths[0]); i ++) {cout << " ";}
    cout << X2;
    for (int i = 0; i < longestCol2 - lengths[1]; i ++) {cout << " ";}
    cout << " \\" << endl;

//line 2
    cout << "\\ " << Y1;
    for (int i = 0; i < 2 + (longestCol1 - lengths[2]); i ++) {cout << " ";}
    cout << Y2;
    for (int i = 0; i < longestCol2 - lengths[3]; i ++) {cout << " ";}
    cout << " /";
}

template <typename T>
void Matrix<T>::print_general_solution() {
    //prints complex vectors in their cos and sin forms as seen in the symbolic solution techniques solutions
    if (complexEigenValues) {       
        cout << "Your solution:\n\n\ty(t) = ";
        cout << "c1e^(" << to_string(eigenRootLeftSide) << "t)<";
        cout << "cos(" << to_string(eigenRootRightSide) << "t),";
        cout << to_string(eigenRootLeftSide) << "cos(" << to_string(eigenRootRightSide) << "t)";
        cout << " - " << to_string(eigenRootRightSide) << "sin(" << to_string(eigenRootRightSide) << "t)>";
        cout << "\n\t\t + c2e^(" << to_string(eigenRootLeftSide) << "t)<";
        cout << "sin(" << to_string(eigenRootRightSide) << "t),";
        cout << to_string(eigenRootRightSide) << "cos(" << to_string(eigenRootRightSide) << "t)";
        cout << " + " << to_string(eigenRootLeftSide) << "sin(" << to_string(eigenRootRightSide) << "t)>\n\n";
    } //gnarly output!
    else if (repeatedEigenValues) {
        cout << "Your solution:\n\n\ty(t) = c1e^(" << eigenValue1 << "t)<";
        cout << v1.at(0) << ","  << v1.at(1) << ">";
        cout << " + c2(e^(" << eigenValue1 << "t)<";
        cout << v1.at(0) << "," << v1.at(1) << ">";
        cout << " + e^(" << eigenValue1 << "t)<";
        cout << v2.at(0) << "," << v2.at(1) << ">)\n\n";
    }
    else { //real vectors
        cout << "Your solution:\n\n\ty(t) = c1e^(" << eigenValue1 << "t)<";
        cout << v1.at(0) << ","  << v1.at(1) << ">";
        cout << " + c2e^(" << eigenValue1 << "t)<";
        cout << v2.at(0) << "," << v2.at(1) << ">\n\n";
    }
}

template<typename T>
void Matrix<T>::solution_type() {
    cout << "Solution type:\n\n";
    cout << "\tThis is classified as ";

    if (complexEigenValues) { // complex
        T a = eigenRootLeftSide;
        T b = eigenRootRightSide;

        if (a == 0) {
            cout << "a Neutrally Stable Center" << endl;
            cout << "In a spring system this would be a case of Undamping";
        }else if ( (a < 0) && (b != 0) ) {
            cout << "a Stable Spiral Sink" << endl;
            cout << "In a spring system this would be an example of Under-Damping";
        } else if ( (a > 0) && (b != 0) ) cout << "an Unstable Spiral Source";
    } else if (repeatedEigenValues) { // repeated
        T t = (x1 + y2); // trace

        if (t < 0) {
            cout << "a Stable Degenerate Sink" << endl;
            cout << "In a spring system this would be an example of Critical-Damping";
        } else if (t > 0) cout << "an Unstable Degenerate Source";
    } else { // real and different
        T D = (x1 * y2) - (x2 * y1); // determinant
        T t = (x1 + y2); // trace
        T wb1 = eigenRootLeftSide + eigenRootRightSide;
        T wb2 = eigenRootLeftSide - eigenRootRightSide;

        if (D < 0) cout << "a Saddle";
        else if ( (wb1 < 0) && (wb2 < 0) ) {
            cout << "a Real Stable Sink" << endl;
            cout << "In a spring system this would be an example of Over-Damping";
        } else if ( (wb1 > 0) && (wb2 > 0) ) cout << "a Real Unstable Sink";
        else if (t == 0) {
            cout << "a Center" << endl;
            cout << "In a spring system this would be an example of Undamping";
        } else cout << "We cannot identify this solution on the trace determinate plane. This may be a case of Only-Damping.";
    }

    cout << endl << endl;
}

//hi there

#endif