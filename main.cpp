#include "sparsemat.h"

int main()
{
    int choice = 0;
    bool flag = false, menuLoop = true;
    sparsemat obj1("mat1.txt"), obj2("mat2.txt");
 
    do
    {
        cout << endl;
        cout << "Enter 1 for addition of matrices" << endl;
        cout << "Enter 2 for transpose of matrices" << endl;
        cout << "Enter 3 for multiplication of matrices" << endl;
        cout << "Enter 4 for subtraction of matrices" << endl;
        cout << "Enter 5 to display any entry of any matrix" << endl;
        cout << "Enter 6 to exit" << endl;
        cout << endl;
        cout << "enter choice ";
        cin >> choice;

        while (choice <= 0 || choice > 6)
        {
            cout << "invalid choice, please enter from (1 - 6): " << endl;
            cin >> choice;
        }

        if (choice == 1) //& addition
        {
            sparsemat obj3;     // default
            obj3 = obj1 + obj2; // no copy(pbr) -> deafult(res) -> temp(if RVO off) move constructor -> destructor for res -> move assignment -> destructor for temp6

            cout << "First Matrix " << endl
                 << obj1 << endl;
            obj1.output();
            cout << endl;
            cout << "Second Matrix " << endl
                 << obj2 << endl;
            obj2.output();
            cout << endl;
            cout << "Resultant Matrix In Matrix form: " << endl;
            obj3.output();

            cout << "Resultant Matrix In Sparse Form: " << endl
                 << obj3 << endl;
            ;
        }

        else if (choice == 2) //& transpose
        {
            cout << "Enter 1 for the transpose of matrix 1 " << endl;
            cout << "Enter 2 for the transpose of matrix 2 " << endl;

            //^ input validation
            do
            {
                cout << "Enter your choice from given choices  " << endl;
                cin >> choice;
                if (choice > 0 && choice < 3)
                {
                    flag = true;
                }
            } while (flag == false);

            if (choice == 1)
            {
                sparsemat obj3 = !obj1;
                cout << "First Matrix " << endl
                     << obj1 << endl;
                obj1.output();
                cout << endl;

                cout << endl;
                cout << "Resultant Matrix In Matrix form: " << endl;
                obj3.output();

                cout << "Resultant Matrix In Sparse Form: " << endl
                     << obj3 << endl;
                ;
            }
            else
            {
                sparsemat obj3 = !obj2;

                cout << "Second Matrix " << endl
                     << obj2 << endl;
                obj2.output();
                cout << endl;
                cout << "Resultant Matrix In Matrix form: " << endl;
                obj3.output();

                cout << "Resultant Matrix In Sparse Form: " << endl
                     << obj3 << endl;
                ;
            }
        }
        else if (choice == 3) //& multiplication
        {

            cout << "Multiplication of given matrices is : " << endl;
            cout << "First Matrix " << endl
                 << obj1 << endl;
            obj1.output();
            cout << endl;
            cout << "Second Matrix " << endl
                 << obj2 << endl;
            obj2.output();
            cout << endl;
            sparsemat obj3 = obj2 * obj1;

            cout << "Resultant Matrix In Matrix form: " << endl;
            obj3.output();
            cout << "Resultant Matrix In Sparse Form: " << endl
                 << obj3 << endl;
        }
        else if (choice == 4) //& subtraction
        {

            //^ input validation
            do
            {
                cout << "Enter 1 for the  matrix 1 - matrix 2 " << endl;
                cout << "Enter 2 for the matrix 2 - matrix 1" << endl;
                cout << "Enter your choice from given choices  " << endl;
                cin >> choice;
                if (choice > 0 && choice < 3)
                {
                    flag = true;
                    cout << endl;
                }
            } while (flag == false);
            sparsemat obj3;
            if (choice == 1)
            {
                obj3 = obj1 - obj2;
            }
            else
            {
                obj3 = obj2 - obj1;
            }

            cout << "Subtraction of given matrices is :" << endl;

            cout << "First Matrix " << endl
                 << obj1 << endl;
            obj1.output();
            cout << endl;
            cout << "Second Matrix " << endl
                 << obj2 << endl;
            obj2.output();
            cout << endl;

            cout << "Resultant Matrix In Matrix form: " << endl;
            obj3.output();

            cout << "Resultant Matrix In Sparse Form: " << endl
                 << obj3 << endl;
            ;
        }

        else if (choice == 5) //&() operator overloading 
        {
            do
            {
                cout << "Enter 1 for matrix 1 " << endl;
                cout << "Enter 2 for the matrix 2" << endl;
                cout << "Enter your choice from given choices  " << endl;
                cin >> choice;
                if (choice > 0 && choice < 3)
                {
                    flag = true;
                    cout << endl;
                }
            } while (flag == false);

            cout << "enter row number ";
            int i = 0;
            cin >> i;
            cout << "enter col number ";
            int j = 0;
            cin >> j;


            
            int val = 0;
            if (choice == 1)
            {
                val = obj1(i, j);
            }
            else if (choice == 2)
            {
                val = obj2(i, j);
            }

            if (val != INT_MIN)
            { // Only print if the value is valid
                cout << "Value at (" << i << ", " << j << ") " << val << endl;
                ;
            }
        }

        else if (choice == 6)
        {
            cout << "terminating program..." << endl;
            menuLoop = false;
            break;
        }

        choice = -1;

    } while (menuLoop);

    return 0;
}
