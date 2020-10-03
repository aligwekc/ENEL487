// Assignment2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//  Created by Aligwekwe Chiamaka on 2020-09-30.
//  Copyright © 2020 Aligwekwe Chiamaka. All rights reserved.
//Programmer: Aligwekwe Chiamaka
//student ID#: 200372176
//Project : complex number calculator.This file contains the 'main' function. Program execution begins and ends there.
//Date : 2020 - 9 - 29
//initialization of headear files
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
ifstream input_data; // declares input stream
ofstream output_data; //declares output stream

// creating the Datatype for the variables to be used throughout the program
class complex_Num
{
public:
    // initialization of variables that can be used all over the code
    float real;
    float imaginary;

};

//This function is used for the addition of the complex numbers.
void Addition(complex_Num a, complex_Num b, complex_Num* c)
{
    c->real = a.real + b.real;// This is to calculate the real number of the total
    c->imaginary = a.imaginary + b.imaginary;// This is to calculate the imaginary number of the total
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
void Subtraction(complex_Num a, complex_Num b, complex_Num* c)
{
    c->real = a.real - b.real;// This is to calculate the real number of the total
    c->imaginary = a.imaginary - b.imaginary;// This is to calculate the imaginary number of the total

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
void Multiplication(complex_Num a, complex_Num b, complex_Num* c)
{
    c->real = (a.real * b.real) - (a.imaginary * b.imaginary); // This is to calculate the real number of the total
    c->imaginary = (a.real * b.imaginary) + (a.imaginary * b.real); // This is to calculate the imaginary number of the total

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
void Division(complex_Num a, complex_Num b, complex_Num* c)
{
    if ((b.real == 0) && (b.imaginary == 0))//This is to check if the denominator is zero
    {
        cout << "NOT A NUMBER!! " << endl; // displays a message saying the total is a NAN
    }

    else
    {

        c->real = (a.real * b.real + a.imaginary * b.imaginary) / (b.real * b.real + b.imaginary * b.imaginary);// This is to calculate the real number of the total
        c->imaginary = (a.imaginary * b.real - a.real * b.imaginary) / (b.real * b.real + b.imaginary * b.imaginary);// This is to calculate the imaginary number of the total


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


int main()
{
    // intialization of variables
    complex_Num x, y, z, * total = &z;
    char func_Ans = ' ';

    // initial startup help message on how the program works and some useful information to know during the program
    cerr << "This function is used to calculate complex numbers. Input A(addition), S(subtraction), M(multiplication) or D(division) and the two complex numbers you wish to calculate when prompted." << endl;
    cerr << "Enter Q or q, if you would like to quit this program." << endl;
    cerr << "Enter Y or y if you would like to use batch file" << endl;

    while (func_Ans != 'Q' && func_Ans != 'q')// while the user input is not q or Q it should run the program
    {
        cerr << "Enter Exp: ";
        cin >> func_Ans; // users inputs on which funtion

        if (func_Ans == 'Q' || func_Ans == 'q') // user inputs Q or q to terminate program
        {
            return 0; // ends program
        }

        if (func_Ans == 'Y' || func_Ans == 'y')// if the person would want to use batch mode
        {
            input_data.open("input.txt"); // open text file
            if (!input_data)// print out error message if not able to open input file
            {
                cerr << "Cant open the input file!" << endl;
                return 1;
            }
            output_data.open("output.txt"); // open outfile file
            if (!output_data) // print out error message if not able to open output file
            {
                cerr << "Cant open the input file!" << endl;
                return 2;
            }

            while (input_data)// while the input file is open, it should read it
            {
                //collect input fromt the batch file
                input_data >> func_Ans >> x.real >> x.imaginary >> y.real >> y.imaginary;

                if (func_Ans == 'A' || func_Ans == 'a') // if the user inputs A or a for addition in the 'cin>> func_Ans'
                {
                    Addition(x, y, total);//calls the addition function
                }

                else if (func_Ans == 'S' || func_Ans == 's')// if the user inputs S or s for subtraction in the 'cin>> func_Ans'
                {
                    Subtraction(x, y, total);
                }

                else if (func_Ans == 'M' || func_Ans == 'm')// if the user inputs M or m for multiplication in the 'cin>> func_Ans'
                {
                    Multiplication(x, y, total);
                }

                else if (func_Ans == 'D' || func_Ans == 'd')// if the user inputs D or d for division in the 'cin>> func_Ans'
                {
                    Division(x, y, total);
                }
                else  //to close the program when anyother letter is used in the batch file
                {
                    return 0;
                }
            }

            input_data.close(); // close the input file
            output_data.close(); // close the output file
        }


        cin >> x.real >> x.imaginary >> y.real >> y.imaginary; // user inputs the complex numbers to calculate
        //prompting user for value input
        if (func_Ans == 'A' || func_Ans == 'a') // if the user inputs A or a for addition in the 'cin>> func_Ans'
        {
            Addition(x, y, total);//calls the addition function
        }

        else if (func_Ans == 'S' || func_Ans == 's')// if the user inputs S or s for subtraction in the 'cin>> func_Ans'
        {
            Subtraction(x, y, total);
        }

        else if (func_Ans == 'M' || func_Ans == 'm')// if the user inputs M or m for multiplication in the 'cin>> func_Ans'
        {
            Multiplication(x, y, total);
        }

        else if (func_Ans == 'D' || func_Ans == 'd')// if the user inputs D or d for division in the 'cin>> func_Ans'
        {
            Division(x, y, total);
        }
        else // if an invalid character is inputted, display this error message
        {
            cerr << "This operation is not found. Please select A for Addition, S for subtraction, D for division, M for multiplication or Q to quit program." << endl;
        }




    }
    return 0; //end program
}


