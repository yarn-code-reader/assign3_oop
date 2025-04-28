#include <iostream>
#include <fstream>

using namespace std;

class sparsemat
{
private:
    int row;
    int col;
    int **mat;

public:
    // constructor
    //Default values should be specified only in the function declaration (in .h).
    sparsemat(int r = 0, int c = 0, int **m = nullptr) ;
    sparsemat(string s);

    // copy constructor
    sparsemat(const sparsemat &obj);
    void setMat(const sparsemat &obj);
    sparsemat(sparsemat &&obj);

    // destructor
    ~sparsemat();
    int get_r();
    int get_c();
    void input(string ad);
    void output();

    // operator overloading
    sparsemat &operator=(const sparsemat &obj);
    void operator=(sparsemat &&obj);
    sparsemat operator+(const sparsemat &obj);
    sparsemat operator-(sparsemat &obj);
    sparsemat operator*(sparsemat &obj);
    sparsemat operator!();
    friend ostream &operator<<(ostream &output, const sparsemat &obj);
    friend istream &operator>>(istream &in, sparsemat &obj);
    bool checkNull();
    int operator()(int i, int j);
};
