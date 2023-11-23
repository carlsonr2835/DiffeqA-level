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
        eigenValue1 = to_string(eigenRootLeftSide) + "+i" + to_string(eigenRootRightSide);
        eigenValue2 = to_string(eigenRootLeftSide) + "-i" + to_string(eigenRootRightSide);
    }
    else {
        eigenValue1 = to_string(eigenRootLeftSide + eigenRootRightSide);
        eigenValue2 = to_string(eigenRootLeftSide - eigenRootRightSide);
    }
    //DEBUG
    //cout << endl << "Before Returned r.isComplex: " << complexEigenValues << endl << endl;
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

//Sorry Maggie I had to modify some stuff to get the code to run in a class. I hope this still makes sense. I modified as little as possible but I had to use all the class member variable names instead of your variable names
template <typename T>
void Matrix<T>::find_eigen_vectors() {
    if (!complexEigenValues) { //real roots
        if ((eigenRootLeftSide + eigenRootRightSide) != (eigenRootLeftSide - eigenRootRightSide)) { //equivalent to if(!repeatedEigenValues?)
            //hopefully cheekily finding eigenvectors using slickboy moves
            //found y using the equation Ax + By = 0
            //in this case, assuming x = 1, y = -A/B
            v1.push_back(1);
            v1.push_back((-1)*(x2/(x1-(eigenRootLeftSide + eigenRootRightSide))));

            v2.push_back(1);
            v2.push_back((-1)*(x2/(x1-(eigenRootLeftSide - eigenRootRightSide))));

        } else {
            v1.push_back(1);
            v1.push_back((-1)*((x1-(eigenRootLeftSide + eigenRootRightSide))/x2));
            
            v2.push_back(0);
            v2.push_back(1);
        }

    } else {
        if (x2 == 1) { // removing the division
            if (x1 == eigenRootLeftSide) { // if the left value is 0, removed
                complexV1.push_back("1");
                complexV1.push_back("(" + to_string(eigenRootRightSide) + "i)");

                complexV2.push_back("1");
                complexV2.push_back("(" + to_string(eigenRootRightSide) + "i)");
            } else { // no division, yes left value
                complexV1.push_back("1");
                string value = to_string((-1)*(x1-(eigenRootLeftSide)));
                complexV1.push_back("(" + value + " + " + to_string(eigenRootRightSide) + "i)");

                complexV2.push_back("1");
                value = to_string(x1-(eigenRootLeftSide));
                complexV2.push_back("(" + value + " - " + to_string(eigenRootRightSide) + "i)");
            }

        } else if (x1 == eigenRootLeftSide) { // division and no left value
            complexV1.push_back("1");
            complexV1.push_back("(" + to_string(eigenRootRightSide) + "i) / " + to_string(x2));

            complexV2.push_back("1");
            complexV2.push_back("(" + to_string(eigenRootRightSide) + "i) / " + to_string(x2));
        } else { // the whole enchalada
            complexV1.push_back("1");

            string value = to_string((-1)*(x1-(eigenRootLeftSide)));
            complexV1.push_back("(" + value + " + " + to_string(eigenRootRightSide) + "i) / " + to_string(x2));

            complexV2.push_back("1");

            value = to_string(x1-(eigenRootLeftSide));
            complexV2.push_back("(" + value + " - " + to_string(eigenRootRightSide) + "i) / " + to_string(x2));
        }
    }
}

//I also modified this a little bit. You may need to put in some code you may or may not have already planned to add to print complex eigenvalues
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

//Ryan has plans for this one
template <typename T>
void Matrix<T>::print_matrix() {

}

template <typename T>
void Matrix<T>::print_general_solution() {
    cout << "General solution\n\ty(t)=c1*v1*e^(λ1*t)+c2*v2*e^(λ2*t)\n";
    cout << "Your solution\n\ty(t)=c1*<" << v1.at(0) << ", " << v1.at(1) << ">";
    cout << "*e^((" << eigenValue1 << ")*t)";
    cout << "+c2<" << v2.at(0) << ", " << v2.at(1) << ">";
    cout << "*e^((" << eigenValue2 << ")*t)\n\n";
}

template<typename T>
void Matrix<T>::solution_type() {
    cout << "This is classified as ";

    if (complexEigenValues) {
        T a = eigenRootLeftSide;
        T b = eigenRootRightSide;

        if (a == 0) {
            cout << "a Neutrally Stable Center" << endl;
            cout << "In a spring system this would be a case of Undamping";
        }else if ( (a < 0) && (b != 0) ) {
            cout << "a Stable Spiral Sink" << endl;
            cout << "In a spring system this would be an example of Under-Damping";
        } else if ( (a > 0) && (b != 0) ) cout << "an Unstable Spiral Source";
    } else if (repeatedEigenValues) {
        T t = (x1 + y2);

        if (t < 0) {
            cout << "a Stable Degenerate Sink" << endl;
            cout << "In a spring system this would be an example of Critical-Damping";
        } else if (t > 0) cout << "an Unstable Degenerate Source";
    } else {
        T D = (x1 * y2) - (x2 * y1);
        T t = (x1 + y2);
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