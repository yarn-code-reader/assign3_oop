#include "sparsemat.h"

// constructor
sparsemat::sparsemat(int r, int c, int **m ) : row(r), col(c), mat(m)
{
cout << "constructor " << endl;
}

sparsemat::sparsemat(string s)
{
    cout << "input Constructor " << endl;
    input(s);
}

// copy constructor
sparsemat::sparsemat(const sparsemat &obj)
{
    cout << "copy constructor " << endl;
    row = obj.row;
    col = obj.col;

    // deep copy
    setMat(obj);
}

void sparsemat::setMat(const sparsemat &obj)
{
    mat = new int *[obj.row];
    for (int i = 0; i < obj.row; i++)
    {
        mat[i] = new int[(obj.mat[i][0] * 2) + 1];
        for (int j = 0; j < (obj.mat[i][0] * 2) + 1; j++)
        {
            mat[i][j] = obj.mat[i][j];
        }
    }
}

sparsemat::sparsemat(sparsemat &&obj)
{
    cout << "move constructor " << endl;
    row = obj.row;
    col = obj.col;
    mat = obj.mat;
    obj.mat = nullptr;
    obj.row = 0;
    obj.col = 0;
}

// destructor
sparsemat::~sparsemat()
{
    cout << "destructor called" << endl;
    if (mat != nullptr)
    {
        for (int i = 0; i < row; i++)
        {
            delete[] mat[i];
        }
        delete[] mat;
    }
}

int sparsemat::get_r()
{
    return row;
}

int sparsemat::get_c()
{
    return col;
}

void sparsemat::input(string ad)
{
    fstream f1;
    f1.open(ad, ios::in);

    if (!f1)
    {
        cout << "No file opened. Error " << endl;
        mat = nullptr;
        return;
    }

    f1 >> row;
    f1 >> col;

    mat = new int *[row];
    int i = -1;
    int temp = 0;
    int j = 1;
    int currentRowNon0 = 0;
    while (!f1.eof())
    {
        f1 >> temp;
        if (j > currentRowNon0)
        {
            i++;
            mat[i] = new int[(temp * 2) + 1];
            currentRowNon0 = (temp * 2) + 1;
            mat[i][0] = temp;
            j = 1;
        }
        else
        {
            //^ j -1 islia kioke j 1 pa assign ha
            mat[i][j - 1] = temp;
        }
        j++;
    }
    f1.close();
}

void sparsemat::output()
{
    if (mat == nullptr)
    {
        cout << " matrix cannot be displayed " << endl;
        return;
    }

    bool found = false;
    int k = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            found = false;
            for (k = 1; k < (mat[i][0] * 2) + 1 && mat[i][0] != 0; k += 2)
            {
                if (j == mat[i][k])
                {
                    found = true;
                    break;
                }
            }

            if (found)
            {
                cout << mat[i][k + 1] << " ";
            }
            else
                cout << "0" << " ";
        }
        cout << endl;
    }
}
// getter and setter of mat

// operator overloading
sparsemat &sparsemat::operator=(const sparsemat &obj)
{
    cout << " assignment operator called " << endl;

    row = obj.row;
    col = obj.col;

    // deep copy
    setMat(obj);
    return *this;
}

void sparsemat::operator=(sparsemat &&obj)
{
    cout << "move assignment operator called " << endl;
    row = obj.row;
    col = obj.col;
    mat = obj.mat;
    obj.mat = nullptr;
    obj.row = 0;
    obj.col = 0;
}

sparsemat sparsemat::operator+(const sparsemat &obj)
{
    if ((row != obj.row || col != obj.col))
    {
        cout << "Given matrices cannot be added " << endl;
        return sparsemat();
    }

    sparsemat resmat;
    resmat.row = row;
    resmat.col = col;
    resmat.mat = new int *[row];
    int count = 0, j = 0, k = 0;
    //^ j keeps track of mat and k keeps track of obj.mat

    for (int i = 0; i < row; i++)
    {
        //^first we count non-zero entries of both matrices
        //^ then we will minus that count for col which are present in both codes
        count = mat[i][0] + obj.mat[i][0];
        j = 1;
        k = 1;
        while (j < (mat[i][0] * 2) && k < ((obj.mat[i][0] * 2)))
        {
            if ((mat[i][j] == obj.mat[i][k]))
            {
                count--;
                //^ this conditions makes sure ka 3 + (-3) ho to wo save na ho aur count -- hojai
                if (mat[i][j + 1] + obj.mat[i][k + 1] == 0)
                {
                    count--;
                }

                j += 2;
                k += 2;
            }

            else if (mat[i][j] < obj.mat[i][k])
                j += 2;
            else
                k += 2;
        }
        resmat.mat[i] = new int[(count * 2) + 1];
        resmat.mat[i][0] = count;
    }

    // values de rahe
    int resmatc = 0; //^ this will keep track of index of res mat
    for (int i = 0; i < row; i++)
    {
        resmatc = 1;
        j = 1;
        k = 1;
        while (j < (mat[i][0] * 2) && k < ((obj.mat[i][0] * 2)))
        {
            if ((mat[i][j] == obj.mat[i][k]))
            {
                //^ this makes sure that if 3 + (-3) to unko store na kare
                if ((mat[i][j + 1] + obj.mat[i][k + 1]) == 0)
                {
                    j += 2;
                    k += 2;
                    continue;
                }
                resmat.mat[i][resmatc] = mat[i][j];
                resmatc++;
                resmat.mat[i][resmatc] = mat[i][j + 1] + obj.mat[i][k + 1];
                resmatc++;
                j += 2;
                k += 2;
            }
            else if (mat[i][j] < obj.mat[i][k])
            {
                resmat.mat[i][resmatc] = mat[i][j];
                resmatc++;
                resmat.mat[i][resmatc] = mat[i][j + 1];
                resmatc++;
                j += 2;
            }
            else if (mat[i][j] > obj.mat[i][k])
            {
                resmat.mat[i][resmatc] = obj.mat[i][k];
                resmatc++;
                resmat.mat[i][resmatc] = obj.mat[i][k + 1];
                resmatc++;
                k += 2;
            }
        }
        //^ these loops make sure that corresponding ka ilawa jo baki entries hain wo matrix mai aa jain
        while (j < ((mat[i][j] * 2) + 1))
        {
            resmat.mat[i][resmatc] = mat[i][j];
            resmatc++;
            resmat.mat[i][resmatc] = mat[i][j + 1];
            resmatc++;
            j += 2;
        }

        while (k < ((obj.mat[i][0] + 2) + 1))
        {
            resmat.mat[i][resmatc] = obj.mat[i][k];
            resmatc++;
            resmat.mat[i][resmatc] = obj.mat[i][k + 1];
            resmatc++;
            k += 2;
        }
    }
    return resmat;
}

sparsemat sparsemat::operator-(sparsemat &obj)
{
    if ((row != obj.row || col != obj.col))
    {
        cout << "Given matrices cannot be added " << endl;
        return sparsemat();
    }
    sparsemat resmat;
    resmat.row = row;
    resmat.col = col;
    resmat.mat = new int *[row];

    int count = 0, j = 0, k = 0;

    for (int i = 0; i < row; i++)
    {
        count = mat[i][0] + obj.mat[i][0];
        j = 1;
        k = 1;
        while (j < (mat[i][0] * 2) && k < ((obj.mat[i][0] * 2)))
        {
            if ((mat[i][j] == obj.mat[i][k]))
            {
                count--;
                if ((mat[i][j + 1] == obj.mat[i][k + 1]))
                    count--;
                j += 2;
                k += 2;
            }
            else if (mat[i][j] < obj.mat[i][k])
                j += 2;
            else
                k += 2;
        }
        resmat.mat[i] = new int[(count * 2) + 1];
        resmat.mat[i][0] = count;
    }

    // values de rahe
    int resmatc = 0;
    for (int i = 0; i < row; i++)

    {
        resmatc = 1;
        j = 1;
        k = 1;
        while (j < (mat[i][0] * 2) && k < ((obj.mat[i][0] * 2)))
        {
            if ((mat[i][j] == obj.mat[i][k]))
            {
                if ((mat[i][j + 1] == obj.mat[i][k + 1]))
                {
                    j += 2;
                    k += 2;
                    continue;
                }
                resmat.mat[i][resmatc] = mat[i][j];
                resmatc++;
                resmat.mat[i][resmatc] = mat[i][j + 1] - obj.mat[i][k + 1];
                resmatc++;
                j += 2;
                k += 2;
            }
            else if (mat[i][j] < obj.mat[i][k])
            {
                resmat.mat[i][resmatc] = mat[i][j];
                resmatc++;
                resmat.mat[i][resmatc] = mat[i][j + 1];
                resmatc++;
                j += 2;
            }
            else if (mat[i][j] > obj.mat[i][k])
            {
                resmat.mat[i][resmatc] = obj.mat[i][k];
                resmatc++;
                resmat.mat[i][resmatc] = 0 - obj.mat[i][k + 1];
                resmatc++;
                k += 2;
            }
        }

        while (j < ((mat[i][j] * 2) + 1))
        {
            resmat.mat[i][resmatc] = mat[i][j];
            resmatc++;
            resmat.mat[i][resmatc] = mat[i][j + 1];
            resmatc++;
            j += 2;
        }

        while (k < ((obj.mat[i][0] + 2) + 1))
        {
            resmat.mat[i][resmatc] = obj.mat[i][k];
            resmatc++;
            resmat.mat[i][resmatc] = 0 - obj.mat[i][k + 1];
            resmatc++;
            k += 2;
        }
    }
    return resmat;
}
sparsemat sparsemat::operator*(sparsemat &obj)
{
    if (col != obj.row)
    {
        cout << "Multplication cannot be performed " << endl;

        return sparsemat();
    }
    sparsemat resmat;
    resmat.row = row;
    resmat.col = obj.col;
    resmat.mat = new int *[row];
    int count = 0;
    int v;            //^ to make syntax easier
    int l = 0, m = 0; //^ to keep track
    //^ l keeps track of entries of row in first mat
    //^ m keeps track of col in second matrix
    bool nonzerofound = false;

    for (int i = 0; i < row; i++)
    {
        count = 0;
        for (int j = 0; j < obj.col; j++)
        {
            l = 1, m = 1;
            v = mat[i][l]; //^yahan sa figure out karega ka entry konsi aur uska col kia phir jo col hoga
            //^us wali r1 mai jaiga to find the corresponding entry
            nonzerofound = false;
            while (l < (mat[i][0] * 2))
            {
                // cout << v << " " << m << endl;
                v = mat[i][l];
                if ((obj.mat[v][m] == j))
                {
                    nonzerofound = true;
                    l += 2;
                    m = 1;
                }
                else if (obj.mat[v][m] < j)
                {
                    m += 2;
                    if (m > ((obj.mat[v][0] * 2)))
                    {
                        m = 1;
                        l += 2;
                    }
                }
                else
                {
                    l += 2;
                    m = 1;
                }
            }
            if (nonzerofound)
            {
                count++;
            }
        }
        resmat.mat[i] = new int[(count * 2) + 1];
        resmat.mat[i][0] = count;
        // cout << "count " << count << " row" << i << endl;
    }

    l = 1, m = 1;
    // *values deni ha
    int k = 1;
    int product = 0;
    for (int i = 0; i < row; i++)
    {
        k = 1;
        for (int j = 0; j < obj.col; j++)
        {
            l = 1, m = 1;
            v = mat[i][l];
            product = 0;
            while (l < (mat[i][0] * 2))
            {
                // 1 cout << "test " << endl;

                v = mat[i][l];
                if ((obj.mat[v][m] == j))
                {
                    product += obj.mat[v][m + 1] * mat[i][l + 1];
                    //   cout << "product " << product << " " << j << endl;
                    l += 2;
                    m = 1;
                }
                //^ m out of bounds na chali jai
                else if (obj.mat[v][m] < j)
                {
                    m += 2;
                    if (m > ((obj.mat[v][0] * 2)))
                    {
                        m = 1;
                        l += 2;
                    }
                }
                else
                {
                    l += 2;
                    m = 1;
                }
            }

            if (product)
            {
                resmat.mat[i][k] = j;
                resmat.mat[i][k + 1] = product;
                k += 2;
            }
        }
    }
    return resmat;
}

sparsemat sparsemat::operator!()
{
    sparsemat resmat;
    resmat.row = col;
    resmat.col = row;
    resmat.mat = new int *[col];
    int count = 0, l = 0, m = 1;

    for (int i = 0; i < col; i++)
    {
        count = 0;
        l = 0;
        m = 1;
        while (l < row)
        {
            if (mat[l][m] == i)
            {
                //  cout << i << " true " << mat[l][m] << " " << mat[l][m + 1] << endl;
                count++;
                l++;
                m = 1;
            }
            else if (mat[l][m] < i)
            {
                m += 2;
                if (m >= ((mat[l][0] * 2) + 1))
                {

                    m = 1;
                    l++;
                }
            }
            else
            {
                l++;
                m = 1;
            }
        }
        //  cout << count << endl;
        resmat.mat[i] = new int[(count * 2) + 1];
        resmat.mat[i][0] = count;
    }

    // values assign kar rahe
    int k = 1;

    for (int i = 0; i < col; i++)
    {
        count = 0;
        l = 0;
        m = 1;
        k = 1;
        while (l < row)
        {
            if (mat[l][m] == i)
            {

                resmat.mat[i][k] = l;
                ;
                resmat.mat[i][k + 1] = mat[l][m + 1];

                //      cout << "idk "<<l << " " <<  mat[l][m + 1] << " "<<endl;
                k += 2;

                l++;
                m = 1;
            }
            else if (mat[l][m] < i)
            {
                m += 2;
                if (m >= ((mat[l][0] * 2) + 1))
                {

                    m = 1;
                    l++;
                }
            }
            else
            {
                l++;
                m = 1;
            }
        }
    }
    return resmat;
}

bool sparsemat::checkNull()
{
    if (mat == nullptr)
    {
        return true;
    }
    return false;
}

int sparsemat::operator()(int i, int j)
{
    if (i >= row || i < 0 || j > (mat[i][0] * 2) + 1 || j < 0)
    {
        cout << "invalid row/col number " << endl;
        return INT_MIN;
    }

    for (int k = 1; k < (mat[i][0] * 2) + 1; k += 2)
    {

        if (mat[i][k] == j)
            return mat[i][k + 1];
    }

    return 0;
}

ostream &operator<<(ostream &output, const sparsemat &obj)
{
    if (obj.mat == nullptr)
    {
        output << "matrix cannot be displayed " << endl;
        return output;
    }

    for (int i = 0; i < obj.row; i++)
    {
        for (int j = 0; j < ((obj.mat[i][0] * 2) + 1); j++)
        {
            output << obj.mat[i][j] << " ";
        }
        output << endl;
    }
    return output;
}

istream &operator>>(istream &in, sparsemat &obj)
{
    cout << "enter name of file that you want to input: ";
    string s;
    in >> s;
    obj.input(s);

    return in;
}
