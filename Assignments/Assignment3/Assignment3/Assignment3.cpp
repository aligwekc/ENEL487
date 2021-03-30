//Created by Aligwekwe Chiamaka on 2020-10-20.
//Copyright © 2020 Aligwekwe Chiamaka. All rights reserved.
//Programmer: Aligwekwe Chiamaka
//student ID#: 200372176
//Assignment3.cpp : This is a complex number calculator Program.
//Date : 2020 - 10 - 20

//initialization of headear files
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
using namespace std;
ifstream input_data; // declares input stream
ofstream output_data; //declares output stream
#define pi 3.141592

// creating the Datatype for the variables to be used throughout the program
class COMPLEX_NUM
{
public:
    // initialization of variables that can be used all over the code 
    float real;
    float imaginary;
    /**
     Default constructor
     */
   COMPLEX_NUM();

    /**
     Constructor
     */
   COMPLEX_NUM(double rl, double imgy);
};

COMPLEX_NUM::COMPLEX_NUM()
{
    real = 0;
    imaginary = 0;
}

COMPLEX_NUM::COMPLEX_NUM(double real, double imaginary)
{
    real = real;
    imaginary = imaginary;
}
//This function is used for the addition of the complex numbers.
void addition(COMPLEX_NUM a, COMPLEX_NUM b, COMPLEX_NUM* c)
{
    c->real = a.real + b.real;
    c->imaginary = a.imaginary + b.imaginary;
    if (c->imaginary >= 0) // if the imaginary number is a not a negative number. Then output a positive sign
    {

        cout << c->real << " + j " << c->imaginary << endl;
    }

    else if (c->imaginary < 0)// if the imaginary number is a negative number. Then output the negative sign as with the number
    {
        c->imaginary *= -1;
        cout << c->real << " - j " << c->imaginary << endl;
    }
}

//This function is used for the subtraction of the complex numbers.
void subtraction(COMPLEX_NUM a, COMPLEX_NUM b, COMPLEX_NUM* c)
{
    c->real = a.real - b.real;
    c->imaginary = a.imaginary - b.imaginary;

    if (c->imaginary >= 0) // if the imaginary number is a not a negative number. Then output a positive sign
    {

        cout << c->real << " + j " << c->imaginary << endl;
    }

    else if (c->imaginary < 0)// if the imaginary number is a negative number. Then output the negative sign as with the number
    {
        c->imaginary *= -1;
        cout << c->real << " - j " << c->imaginary << endl;
    }
}


//This function is used for the multiplication of the complex numbers.
void multiplication(COMPLEX_NUM a, COMPLEX_NUM b, COMPLEX_NUM* c)
{
    c->real = (a.real * b.real) - (a.imaginary * b.imaginary);
    c->imaginary = (a.real * b.imaginary) + (a.imaginary * b.real);

    if (c->imaginary >= 0) // if the imaginary number is a not a negative number. Then output a positive sign
    {
        cout << c->real << " + j " << c->imaginary << endl;
    }

    else if (c->imaginary < 0)// if the imaginary number is a negative number. Then output the negative sign as with the number
    {
        c->imaginary *= -1;
        cout << c->real << " - j " << c->imaginary << endl;
    }
}

//This function is used for the division of the complex numbers.
void division(COMPLEX_NUM a, COMPLEX_NUM b, COMPLEX_NUM* c)
{
    if ((b.real == 0) && (b.imaginary == 0))//This is to check if the denominator is zero
    {
        cerr << "NOT A REAL NUMBER! " << endl;
    }

    else
    {

        c->real = (a.real * b.real + a.imaginary * b.imaginary) / (b.real * b.real + b.imaginary * b.imaginary);
        c->imaginary = (a.imaginary * b.real - a.real * b.imaginary) / (b.real * b.real + b.imaginary * b.imaginary);


        if (c->imaginary >= 0) // if the imaginary number is a not a negative number. Then output a positive sign
        {
            cout << c->real << " + j " << c->imaginary << endl;
        }

        else if (c->imaginary < 0)// if the imaginary number is a negative number. Then output the negative sign as with the number
        {
            c->imaginary *= -1;
            cout << c->real << " - j " << c->imaginary << endl;
        }
    }
}
// returns the magnitude of the complex numbers
void magnitude(COMPLEX_NUM a)
{
    float z;
    z = sqrt(pow(a.real, 2) + pow(a.imaginary, 2));

    cout << z << endl;
}

//this function calculates the exponential of the complex number and displays the answer when the function is called 
void exponent(COMPLEX_NUM a, COMPLEX_NUM* c)
{
  
    c->real = exp(a.real) * cos(a.imaginary);
    c->imaginary = exp(a.real) * sin(a.imaginary);
    if (c->imaginary >= 0) // if the imaginary number is a not a negative number. Then output a positive sign
    {
        cout << c->real << " + j " << c->imaginary << endl;
    }

    else if (c->imaginary < 0)// if the imaginary number is a negative number. Then output the negative sign as with the number
    {
        c->imaginary *= -1;
        cout << c->real << " - j " << c->imaginary << endl;
    }
}

//This function calculates the inverse of the complex numbers and displays the answer when the function is called
void inverse(COMPLEX_NUM a, COMPLEX_NUM* c)
{
 
    c->real = a.real / (pow(a.real, 2) + pow(a.imaginary, 2));
    c->imaginary = -a.imaginary / (pow(a.real, 2) + pow(a.imaginary, 2));
    if (c->imaginary >= 0) // if the imaginary number is a not a negative number. Then output a positive sign
    {
        cout << c->real << " + j " << c->imaginary << endl;
    }

    else if (c->imaginary < 0)// if the imaginary number is a negative number. Then output the negative sign as with the number
    {
        c->imaginary *= -1;
        cout << c->real << " - j " << c->imaginary << endl;
    }
}

//This function calculates the angle of the complex number in radians and displays the angle when the function is called
void argument(COMPLEX_NUM a)
{
   float angle;
    angle = atan(a.imaginary / a.real);
    if (a.real < 0)
    {
        if (a.imaginary >= 0)
        {
            angle = angle + pi;
        }
        else
        {
            angle = angle - pi;
        }
    }
    angle = angle / (pi * 180);
    cout << angle << endl;

}

//This function calculates the angle of the complex number in degrees and displays the angle when the function is called
void argumentdegree(COMPLEX_NUM a)
{
    float angle;
    angle = atan(a.imaginary / a.real);
    if (a.real < 0)
    {
        if (a.imaginary >= 0)
        {
            angle = angle + pi;
        }
        else
        {
            angle = angle - pi;
        }
    }
    cout << angle << endl;
}
// This function collects the users input and sorts the data 
void parse(char a[100], float& real1, float& imaginary1,
    float& real2, float& Imaginary2)
{
    char temp_real1[25], temp_imaginary1[25], temp_real2[25], temp_imaginary2[25], r[25];
    sscanf_s(a, "%s %s %s %s %s", temp_real1, temp_imaginary1, temp_real2, temp_imaginary2, r);
    real1 = strtof(temp_real1, NULL);
    imaginary1 = strtof(temp_imaginary1, NULL);
    real1= strtof(temp_real2, NULL);
    imaginary1 = strtof(temp_imaginary2, NULL);
    strcpy(a, r);

}
int main()
{
    // intialization of variables
    COMPLEX_NUM z, * total = &z;
    float real1, imaginary1, real2, imaginary2;
    string input;
    char function[100];
   

    // initial startup help message on how the program works and some useful information to know during the program
    cerr << "This function is used to calculate complex numbers. Input A(addition), S(subtraction), M(multiplication) or D(division) and the two complex numbers you wish to calculate when prompted." << endl;
    cerr << "Enter T or t if you would like to calculate either the abs(modulus), arg(argument), argDeg(argument in degrees), exp(exponent of magnitude), inv(reciprocal of complex numbers) of the complex numbers and enter two values only with a command before it." << endl;
    cerr << "Enter Q or q, if you would like to quit this program." << endl;
    cerr << "Enter Y or y if you would like to use batch file or N or n if you would like to use interactive mode" << endl;

    do 
    {
        if (input == "Y" || input == "y")// if the person would want to use batch mode
        {
            input_data.open("input.txt"); // open text file
            if (!input_data)// print out error message if not able to open input file
            {
                cerr << "Cant open the input file!" << endl;
                return 1;
            }
            else
            {
                output_data.open("output.txt"); // open outfile file
                if (!output_data) // print out error message if not able to open output file
                {
                    cerr << "Cant open the input file!" << endl;
                    return 2;
                }
            }
            while (input_data)// while the input file is open, it should read it
            {
                getline(input_data, input);
            }
        }

        if (input == "N" || input == "n")
        {
            cerr << "Enter Exp: ";
            getline(cin, input);
        }

        if (input == "q" || input == "Q")
        {
            return 0;
        }
        if (input.size() != 0)
        {
            for (int j = 0; j < input.size(); j++)
            {
                function[j] = input.at(j);
            }
            for (int j = input.size(); j < 100; j++)
            {
                function[j] = input.at(j);
            }
            parse(function, real1, imaginary1, real2, imaginary2);
            input = function;
        }

        COMPLEX_NUM complex_set1(real1, imaginary1);
        COMPLEX_NUM complex_set2(real2, imaginary2);

        if (input == "A" || input == "a") // if the user inputs A or a for addition in the 'cin>> input'
        {
            addition(complex_set1, complex_set2, total);
        }

        else if (input == "S" || input == "s")// if the user inputs S or s for subtraction in the 'cin>> input'
        {
            subtraction(complex_set1, complex_set2, total);
        }

        else if (input == "M" || input == "m")// if the user inputs M or m for multiplication in the 'cin>> input'
        {
            multiplication(complex_set1, complex_set2, total);
        }

        else if (input == "D" || input == "d")// if the user inputs D or d for division in the 'cin>> input'
        {
            division(complex_set1, complex_set2, total);
        }
        else if (input == "ABS" || input == "abs") // if the user inputs ABs or abs for magnitude in the 'cin>> func_Ans'
        {
            magnitude(complex_set1);
        }
        else if (input == "arg" || input == "ARG")
        {
            argument(complex_set1);
        }
        else if (input == "argDeg" || input == "ARGDEG")
        {
            argument(complex_set1);
        }
        else if (input == "exp" || input == "EXP")
        {
            exponent(complex_set1, total);
        }
        else if (input == "inv" || input == "INV")
        {
            inverse(complex_set1, total);
        }
        else // if an invalid character is inputted, display this error message
        {
            cerr << "This operation is not found. Please select A for Addition, S for subtraction, D for division, M for multiplication or Q to quit program." << endl;
        }


    } while (input != "q" && input != "Q");

    //while (func_Ans != 'Q' && func_Ans != 'q')// while the user input is not q or Q it should run the program
    //{
    //    cerr << "Enter Exp: ";
    //    cin >> func_Ans; // users inputs on which funtion

    //    if (func_Ans == 'Q' || func_Ans == 'q') // user inputs Q or q to terminate program
    //    {
    //        return 0; // ends program
    //    }

    //    else if (func_Ans == 'Y' || func_Ans == 'y')// if the person would want to use batch mode
    //    {
    //            input_data.open("input.txt"); // open text file
    //            if (!input_data)// print out error message if not able to open input file
    //            {
    //                cerr << "Cant open the input file!" << endl;
    //                return 1;
    //            }
    //            else 
    //            {
    //                output_data.open("output.txt"); // open outfile file
    //                if (!output_data) // print out error message if not able to open output file
    //                {
    //                    cerr << "Cant open the input file!" << endl;
    //                    return 2;
    //                }
    //            }
    //            while (input_data)// while the input file is open, it should read it
    //            {

    //                //collect input from the batch file
    //                input_data >> func_Ans >> complex_set1 >> complex_set2;

    //                if (func_Ans == 'A' || func_Ans == 'a') // if the user inputs A or a for addition in the 'cin>> func_Ans'
    //                {
    //                    addition(x, y, total);
    //                }

    //                else if (func_Ans == 'S' || func_Ans == 's')// if the user inputs S or s for subtraction in the 'cin>> func_Ans'
    //                {
    //                    subtraction(x, y, total);
    //                }

    //                else if (func_Ans == 'M' || func_Ans == 'm')// if the user inputs M or m for multiplication in the 'cin>> func_Ans'
    //                {
    //                    multiplication(x, y, total);
    //                }

    //                else if (func_Ans == 'D' || func_Ans == 'd')// if the user inputs D or d for division in the 'cin>> func_Ans'
    //                {
    //                    division(x, y, total);
    //                }
    //                else if (func_Ans == 'ABS' || func_Ans == 'abs') // if the user inputs ABS or abs for magnitude in the 'cin>> func_Ans'
    //                {
    //                    magnitude(x);
    //                }
    //                else  //to close the program when anyother letter is used in the batch file
    //                {
    //                    return 0;
    //                }
    //            }

    //            input_data.close(); // close the input file
    //            output_data.close(); // close the output file
    //    }

    //   
    //    cin >> x.real >> x.imaginary >> y.real >> y.imaginary; // user inputs the complex numbers to calculate
    //    if (func_Ans == 'A' || func_Ans == 'a') // if the user inputs A or a for addition in the 'cin>> func_Ans'
    //    {
    //        addition(x, y, total);
    //    }

    //    else if (func_Ans == 'S' || func_Ans == 's')// if the user inputs S or s for subtraction in the 'cin>> func_Ans'
    //    {
    //        subtraction(x, y, total);
    //    }

    //    else if (func_Ans == 'M' || func_Ans == 'm')// if the user inputs M or m for multiplication in the 'cin>> func_Ans'
    //    {
    //        multiplication(x, y, total);
    //    }

    //    else if (func_Ans == 'D' || func_Ans == 'd')// if the user inputs D or d for division in the 'cin>> func_Ans'
    //    {
    //        division(x, y, total);
    //    }
    //    else if (func_Ans == 'ABS' || func_Ans == 'abs') // if the user inputs ABs or abs for magnitude in the 'cin>> func_Ans'
    //    {
    //        magnitude(x);
    //    }
    //    else // if an invalid character is inputted, display this error message
    //    {
    //        cerr << "This operation is not found. Please select A for Addition, S for subtraction, D for division, M for multiplication or Q to quit program." << endl;
    //    }

    //}
    input_data.close(); // close the input file
    output_data.close(); // close the output file
    return 0; //end program
}


