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
    
    // The addend must be at least 100, and cannot be more than
    // sum - 100, because the augend must be at least 100,
    // and addend + augend = sum.
    uniform_int_distribution<> addend_dist(100, sum - 100);
    unsigned addend = addend_dist(gen);

    unsigned augend = sum - addend;

    // Will be used to take user input
    unsigned input;

    // I want to generate a random snarky response, out of a pool
    // of snarky responses.
    // I need a random number to select which response I will use.
    uniform_int_distribution<> snarky_response_dist(0, 3);
    size_t snarky_response_index = snarky_response_dist(gen);

    // Here are my pools of snarky responses
    string snarky_positive_response_pool[] = {
        "You're a mathematical genius.",
        "Good job. We're all very impressed.",
        "Arithmetic ain't got nothin on you.",
        "Oh bravo. You're an inspiration to us all."
    };
    string snarky_negative_response_pool[] = {
        "Trum says: WRONG!!!",
        "You need help.",
        "You forgot to carry the 1, genius.",
        "Oh COME ON..."
    };

    cout << endl << endl
         << "   " << addend << endl
         << " + " << augend << endl
         << "------" << endl;

    cout << "   ";
    cin >> input;

    if (input != sum)
    {
        string response = snarky_negative_response_pool[snarky_response_index];
        cout << response << endl
             << endl
             << "The answer is " << sum << endl;
    }
    else
    {
        string response = snarky_positive_response_pool[snarky_response_index];
        cout << endl
             << response << endl;
    }    
}

