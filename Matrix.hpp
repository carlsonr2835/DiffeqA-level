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
        //Matrix(const Matrix<T>& OTHER);
        //Matrix& operator=(const Matrix<T>& OTHER);
        //~Matrix();
        void setValues(T X1, T X2, T Y1, T Y2);
        void setInitialConditions(T independant, T dependantx, T dependanty);
        T getx1();
        T getx2();
        T gety1();
        T gety2();
        void find_eigen_values(); //full process
        void print_eigen_values();
        void find_eigen_vectors();
        void print_eigen_vectors();
        void print_matrix();
        void print_general_solution();
        void solution_type();
        void find_c();

    private:
        //A matrix values
        T x1;
        T x2;
        T y1;
        T y2;
        //eigen roots and their properties
        double eigenRootLeftSide;
        double eigenRootRightSide;
        bool complexEigenValues;
        bool repeatedEigenValues;
        //full eigen values which are used for printing only
        string eigenValue1;
        string eigenValue2;
        //eigen vectors
        vector<T> v1;
        vector<T> v2;
        // complex vectors
        vector<string> complexV1;
        vector<string> complexV2;
        //initial conditions
        T independantVariable;
        vector<T> dependantVariables;
        T c1;
        T c2;
};

//not currently initializing templated member variables...it seems fine
template <typename T>
Matrix<T>::Matrix() { //initialize everything to default
    eigenRootLeftSide = 0.0;
    eigenRootRightSide - 0.0;
    complexEigenValues = false;
    repeatedEigenValues = false;
    eigenValue1 = "";
    eigenValue2 = "";
}

//Matrix(const Matrix<T>& OTHER);
//Matrix& operator=(const Matrix<T>& OTHER);
//~Matrix();

template <typename T>
void Matrix<T>::setValues(T X1, T X2, T Y1, T Y2) {
    x1 = X1;
    x2 = X2;
    y1 = Y1;
    y2 = Y2;
}

template <typename T>
void Matrix<T>::setInitialConditions(T independant, T dependantx, T dependanty) {
    independantVariable = independant;
    dependantVariables.push_back(dependantx);
    dependantVariables.push_back(dependanty);
}

/////////these getters are may end up being uncessesary but Ryan is leaving them in for future matrix formatting ideas
template <typename T>
T Matrix<T>::getx1() {
    return x1;
}

template <typename T>
T Matrix<T>::getx2() {
    return x2;
}

template <typename T>
T Matrix<T>::gety1() {
    return y1;
}

template <typename T>
T Matrix<T>::gety2() {
    return y2;
}
////////

//computes determinant, finds lambda quadratic equation, solves eigenvalues, marks if repeated or complex, is NOT ACCURATE for repeating fractions
template <typename T>
void Matrix<T>::find_eigen_values() {
    //find A - lambda*I
        //=det({x1-L, x2}, {y1, y2-L})
        //no math needed here
        cout << "\nA-λI:\n";
        cout << "__         __" << endl <<
        "| " << x1 << "-λ    " << x2 << "  |" << endl << 
        "| " << y1 << "      " << y2 << "-λ|" << endl <<
        "|_         _|" << endl;
    //find det(A - lambda*I)
    cout << "\ndet(A - λI):\n";
    cout << "(" << x1 << "-λ)(" << y2 << "-λ) - (" << x2 << ")(" << y1 << ")\n";

    //quatratic terms:
    double a = 1;
    double b = x1*-1 + y2*-1;
    double c = (x1 * y2) - (x2 * y1);
    //output the standard form quadratic equation
    cout << "=λ^2 + " << b << "λ + " << c << endl;

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
        if (eigenRootLeftSide == 0) {
            eigenValue1 = "i" + to_string(eigenRootRightSide);
            eigenValue2 = "-i" + to_string(eigenRootRightSide);
        }
        else {
            eigenValue1 = to_string(eigenRootLeftSide) + "+i" + to_string(eigenRootRightSide);
            eigenValue2 = to_string(eigenRootLeftSide) + "-i" + to_string(eigenRootRightSide);
        }
    }
    else {
        eigenValue1 = to_string(eigenRootLeftSide + eigenRootRightSide);
        eigenValue2 = to_string(eigenRootLeftSide - eigenRootRightSide);
    }
}

//utilizes strings to avoid ugly formatting for the complex roots
template <typename T>
void Matrix<T>::print_eigen_values() {
    if (repeatedEigenValues) {
        cout << "Your eigen value is: " << eigenValue1 << " (repeated roots)\n";
    } else {
        cout << "Your eigen values are: " << eigenValue1 << ", " << eigenValue2 << endl;;
    }
}

template <typename T>
void Matrix<T>::find_eigen_vectors() {
    if (!complexEigenValues) { //real roots
        if(!repeatedEigenValues) {
            //hopefully cheekily finding eigenvectors using slickboy moves
            //found y using the equation Ax + By = 0
            //in this case, assuming x = 1, y = -A/B
            v1.push_back(1);
            v1.push_back( (-1)*(x2/( x1-(eigenRootLeftSide + eigenRootRightSide) )) );

            v2.push_back(1);
            v2.push_back((-1)*(x2/(x1-(eigenRootLeftSide - eigenRootRightSide))));

        } else { // repeated
            v1.push_back(1);
            v1.push_back((-1)*((x1-(eigenRootLeftSide + eigenRootRightSide))/x2));
            
            v2.push_back(0);
            v2.push_back(1);
        }

    } else { //complex roots
    // assume the previous equation
        // complex roots follow the appearance of -(x1 - a + bi)/x2  (condesing (x1-a) to a)
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
        cout << "Eigen Value " << eigenValue1 << " has the vector: <";
        cout << v1.at(0) << ", ";
        cout << v1.at(1) << ">" << endl;
        //v2
        cout << "Eigen Value " << eigenValue2 << " has the vector: <";
        cout << v2.at(0) << ", ";
        cout << v2.at(1) << ">" << endl;
    }
    else {
        //v1
        cout << "Eigen Value " << eigenValue1 << " has the vector: <";
        cout << complexV1.at(0) << ", ";
        cout << complexV1.at(1) << ">" << endl;
        //v2
        cout << "Eigen Value " << eigenValue2 << " has the vector: <";
        cout << complexV2.at(0) << ", ";
        cout << complexV2.at(1) << ">" << endl;
    }
    cout << endl;
}

template <typename T>
void Matrix<T>::print_matrix() {

}

template <typename T>
void Matrix<T>::print_general_solution() {
    if (complexEigenValues) {        
        cout << "Your solution\n\ty(t) = ";
        cout << "c1e^(" << to_string(eigenRootLeftSide) << "t)<";
        cout << "cos(" << to_string(eigenRootRightSide) << "t),";
        cout << to_string(eigenRootLeftSide) << "cos(" << to_string(eigenRootRightSide) << "t)";
        cout << " - " << to_string(eigenRootRightSide) << "sin(" << to_string(eigenRootRightSide) << "t)>";
        cout << " + c2e^(" << to_string(eigenRootLeftSide) << "t)<";
        cout << "sin(" << to_string(eigenRootRightSide) << "t),";
        cout << to_string(eigenRootRightSide) << "cos(" << to_string(eigenRootRightSide) << "t)";
        cout << " + " << to_string(eigenRootLeftSide) << "sin(" << to_string(eigenRootRightSide) << "t)>";
    }
    else if (repeatedEigenValues) {
        cout << "Your solution\n\ty(t) = c1e^(" << eigenValue1 << "t)<";
        cout << v1.at(0) << ","  << v1.at(1) << ">";
        cout << " + c2(e^(" << eigenValue1 << "t)<";
        cout << v1.at(0) << "," << v1.at(1) << ">";
        cout << " + e^(" << eigenValue1 << "t)<";
        cout << v2.at(0) << "," << v2.at(1) << ">)\n";
    }
    else { //real vectors
        cout << "Your solution\n\ty(t) = c1e^(" << eigenValue1 << "t)<";
        cout << v1.at(0) << ","  << v1.at(1) << ">";
        cout << " + c2e^(" << eigenValue1 << "t)<";
        cout << v2.at(0) << "," << v2.at(1) << ">\n";
    }
}

template<typename T>
void Matrix<T>::solution_type() {
    cout << "This is classified as ";

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
        else if (t = 0) {
            cout << "a Center" << endl;
            cout << "In a spring system this would be an example of Undamping";
        } else cout << "We cannot identify this solution on the trace determinate plane. This may be a case of Only-Damping.";
    }

    cout << endl << endl;
}

#endif