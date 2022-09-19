/*
   ACADEMIC INTEGRITY PLEDGE

   - I have not used source code obtained from another
     student nor any other unauthorized source, either
     modified or unmodified. Any source code used for
     testing that is another student's has been
     appropriately documented

   - All source code and documentation used in my program
     is either my original work or was derived by me from
     the source code published in the textbook for this
     course or presented in class. Other sources are acknowledged
     without transcribing code verbatim

   - I have not discussed coding details about this project
     with anyone other than my instructor, TA, and my immediate
     project team. I understand that I may discuss the concepts
     of this program with other students and that another student
     may help me debug my program so long as neither of us writes
     anything during the discussion or modifies any computer file
     during the discussion.

   - I have violated neither the spirit nor letter of these
     restrictions.

   Signed: Madisen Zakham Date: 04/19/2022


   COPYRIGHT (C) 2021 student name. All Rights Reserved.
   Project #: project 3 Hashing
   author student Madisen Zakham, mlz25
   version 1.01 04.19.2022
   Files: Complexity_Timer.hpp
          Complexity_Recorder.hpp
          main.cpp
          MLZ_Hash.h


   COPYRIGHT (C) 2018 Will Crissey, Jr. All rights reserved.
   DS316 Sample Project example.
   Author.  Will Crissey, Jr.
   Version. 1.02 06.03.2018.
   Files: DS316_Project_Standard_Code_Example.cpp
          Complexity_Timer.hpp
          Complexity_Recorder.hpp

This program will go over multiple hash tables. It will compare the delete function of each and insert function. Then
go and compare the times it takes for the program to do such tasks.

I reused most of this code from Project 2 and changed it to work for Project 3
I finally got my compiler running so I should did not have problems like I did for Project 2

Also note that this is consolidated for the sake of simplicity. Your code will likely need to be in multiple files

Acknowledgments and special thanks to Dr. David Musser, retired Professor of Computer Science
His wisdom includes a 37-year career combining academic, industry, and research-institute positions, including almost 20 years at Rensselaer.
Coding modifications included the original work with permission: copyright (c) 1997 Rensselaer Polytechnic Institute

 */

//all includes from previous project(project2)
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <limits>
#include <fstream>
#include <iterator>
#include <algorithm>    // std::random_shuffle
#include <string>
#include<bits/stdc++.h>
#include <unordered_set>
#include "Complexity_Timer.hpp"
#include "Complexity_Recorder.hpp"
#include "MLZ_Hash.h"  //my hash
// #include "BAH_Hash.h"  //Bryce Haldeman's hash
// extra code like Bryce's hash is commented out as it is not always needed to run my code


using namespace std;

timer timer1;

// U can be any type we want to test. here it's the type of data in the sequence to be sorted; can be changed to any other type for which assignment (=) and less-than comparisons (<) are defined.
typedef int U;

// experiment will involve timing of 3 algorithms and that the number of "trials" will be 7.
// By a trial is meant timing of the algorithm for inputs of a single length;
// rather than taking a single such measurement we take seven measurements with different randomly generated inputs and compute their median.
// (The median computation is done in class recorder.)
// The median is used here rather than the mean because it is less susceptible to fluctuation due to possibly large fluctuations in the individual times.

const int number_of_algorithms = 2; //increased to 4 for different amount to algorithms. 2 inserts and 2 deletes
const int number_of_trials = 7;

// NOTICE factor is going to influence the "extra" time
const int factor = 5000;

// This template function is to specify which algorithms are used in the timing experiment


// STABLE SORT: sorts the elements in the range [first,last), like sort, but preserves the relative order of the elements with equivalent values-from STL
// SORT: (the Quicksort algorithm, using the median-of-3 method of choosing pivot elements for partitioning)-from STL
// Quick sort: Our user written sorting algorithm

const char* headings[number_of_algorithms] =
{"| Chaining w LinkedList Insert ", //my heading
 "| Chaining w LinkedList Delete "}; //my heading
 //"|      Hopscotch Insert        ", //other experimenter's hash heading
// "|      Hopscotch Delete     " };  //other experimenter's hash heading

int main()
{
    mlzHash h(7);


    int N0, N1, N2, N, K, recurse = 0;
    N1 = 5;    // smallest sequence
    N2 = 6000; // largest sequence

// for our outputting of the results
    ofstream ofs("results.txt");

// this is going to hold the measurements
    vector<recorder<timer> > stats(number_of_algorithms);

// The "U" is the type for the vectors x and y (poorly named, i know). Using the largest sequence multiplied by factor to allocate memory
    vector<U> x, y;
    x.reserve(N2*factor);
    y.reserve(N2*factor);


// The times are taken for short computations by repeating those computations a number of times
// (controlled by the variable repetitions), so that they take long enough to register nonzero times.
// In our example where N1 = 1(meaning a sequence of length 1,000 (or, more generally, 1 * factor),
// then the time will be computed for executing the algorithm 32 times
   int repetitions = max(32/N1, 1);

    cout << "____";
    for (int i = 0; i < number_of_algorithms; ++i)
      cout << headings[i];
    cout << endl;

    cout << "Size";
    for (int i = 0; i < number_of_algorithms; ++i)
      cout << "|            Time              ";
    cout << endl;



    for (N0 = N1; N0 <= N2; N0 *= 2)
    {

        N = N0 * factor;

        K = N/2;

        for (int i = 0; i < N; ++i)
            x.push_back(i);

        cout << setw(4) << N0 << flush;
        ofs << setw(4) << N0;

        int p;

        for (int i = 0; i < number_of_algorithms; ++i)
            stats[i].reset();

        for (int j = 0; j < number_of_trials; ++j)
        {

            random_shuffle(x.begin(), x.end());
            y = x;

// Notice here we repeat the computation repetitions # of times, not for each one, and we record the total time.
// (The repetitions factor is divided out when the time is later reported on the output stream.)
           for (int i = 0; i < number_of_algorithms; ++i)
            {
               timer1.restart();
               for (int k = 0; k < repetitions; ++k)
               {
                 x = y;
                 j++;
                 for(int i : x)
                    {
                     switch (k)
                     {
                         case 0: h.insertItem(i);
                         break;
                         case 1: h.deleteItem(i);
                         break;
                         /*case 2: insert(int); //other experimenter's values
                         break;
                         case 3: delete_key(i); //other experimenter's values
                         break;*/
                     }
                 }
               }
               timer1.stop();
               stats[i].record(timer1);
            }
        } // end of trials loop

        for (int i = 0; i < number_of_algorithms; ++i)
        {
            cout << "     "; //these spaces line the data up with the headings
            stats[i].report(cout, repetitions);
            cout << "         "; //these spaces line the data up with the headings
            stats[i].report(ofs, repetitions);
        }

        cout << endl;
        ofs << endl;

        x.erase(x.begin(), x.end());

        if (repetitions > 1)
            repetitions /= 2;

// Notice we restore the input sequence before each call of the algorithm; b/c these algorithms typically
//  would perform differently on already-sorted sequences than on random ones.

    }
// the number of recursions reveals the call stack implications



}



