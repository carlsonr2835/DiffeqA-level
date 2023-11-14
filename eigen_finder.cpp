/*
todo
- the spacing for the ascii matrix will get messed up if not all single digits
-only works for real eigenvalues now
*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct {
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;
} A ;

struct {
    int x1 = 1;
    int x2 = 0;
    int y1 = 0;
    int y2 = 1;
} I;

vector<double> quadratic(int a, int b, int c) { //I don't think it is going to like imaginary numbers
    vector<double> stuff;

    double right = 4 * a * c;
    right = (b * b) - right;
    right = sqrt(right);
    right = right / (2 * a);
    //cout << "right: " << right << endl;

    double left = (-1 * b) / (2 * a);
    //cout << "left: " << left << endl;

    stuff.push_back(left + right);
    stuff.push_back(left - right);

    return stuff;
}


//smart user for now
int main () {
    //follows the format Y'=AY where A is a 2x2 matrix and there is an initial condition
    //prompt user for the matrix A
    cout << "Hello! Welcome to the eigen value/eigen vector finder!" << endl << "Please input your A matrix...\n";
    //get x1
    cout << "__         __" << endl <<
            "| x1     x2 |" << endl << 
            "| y1     y2 |" << endl <<
            "|_         _|" << endl;
    cout << "Input x1:";
    cin >> A.x1;
    //get x2
    cout << "__         __" << endl <<
            "| " << A.x1 << "      x2 |" << endl << 
            "| y1     y2 |" << endl <<
            "|_         _|" << endl;
    cout << "Input x2:";
    cin >> A.x2;
    //get y1
    cout << "__         __" << endl <<
            "| " << A.x1 << "      " << A.x2 << "  |" << endl << 
            "| y1     y2 |" << endl <<
            "|_         _|" << endl;
    cout << "Input y1:";
    cin >> A.y1;
    //get y2
    cout << "__         __" << endl <<
            "| " << A.x1 << "      " << A.x2 << "  |" << endl << 
            "| " << A.y1 << "      y2 |" << endl <<
            "|_         _|" << endl;
    cout << "Input y2:";
    cin >> A.y2;
    //print whole matrix
    cout << "__         __" << endl <<
            "| " << A.x1 << "      " << A.x2 << "  |" << endl << 
            "| " << A.y1 << "      " << A.y2 << "  |" << endl <<
            "|_         _|" << endl;

    //calculate the eigenvalues
        //find A - lambda*I
            //=det({x1-L, x2}, {y1, y2-L})
            //no code needed
            cout << "__         __" << endl <<
            "| " << A.x1 << "-L    " << A.x2 << "  |" << endl << 
            "| " << A.y1 << "      " << A.y2 << "-L|" << endl <<
            "|_         _|" << endl;
        //find det(A - lambda*I)
        cout << "(" << A.x1 << "-L)(" << A.y2 << "-L) - (" << A.x2 << ")(" << A.y1 << ")\n";

        //calculate the eigen values
            //quatratic terms:
                //a (squared term): 1 (I think always?)
                //b (linear term): A.x1 + A.y2
                //c (const): A.x2 * A.y1 + A.x1 * A.y2
        int a = 1;
        int b = A.x1*-1 + A.y2*-1;
        int c = (A.x1 * A.y2) - (A.x2 * A.y1);
            
        cout << "L^2 + " << b << "L + " << c << endl;

        vector<double> roots;
        roots = quadratic(a, b, c);

        cout << "Your eigen values are: " << roots.at(0) << ", " << roots.at(1) << endl;

    return 0;
}