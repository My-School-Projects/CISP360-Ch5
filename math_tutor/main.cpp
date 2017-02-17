#include <iostream>
#include <random>
using namespace std;

void show_problem();

int main()
{
    // The default seed generator
    random_device rd;
    // A random number generator (seeded with rd)
    mt19937 gen(rd());
    
    // We generate random numbers with uniform distributions
    // which are bounded by their minimum and maximum values.
    //
    // We want everything in 3 digit numbers, so
    // the minimum value for the sum is 200 (100 + 100)
    // and the maximum value is 999.
    uniform_int_distribution<> sum_dist(200, 999);
    // Assign sum a random number between 200 and 999
    unsigned sum = sum_dist(gen);
    
    // The addend must be at least 100, and cannot be more than 899,
    // because the augend must be at least 100 and the sum must be less
    // than 1000.
    uniform_int_distribution<> addend_dist(100, 899);
    unsigned addend = addend_dist(gen);

    // The augend must be at least 100, and cannot be more than
    // 999 - addend.
    uniform_int_distribution<> augend_dist(100, 999-addend);
    unsigned augend = augend_dist(gen);
    
    cout << "When you are ready to see the answer, press <Enter>..."
         << endl << endl
         << "   " << addend << endl
         << " + " << augend << endl
         << "------";
    cin.get();

    cout << "   " <<  addend + augend << endl;
}

