#include <iostream>
#include <random>
using namespace std;

enum snarky_response_t
{
    positive, negative
};

typedef struct {
    unsigned given;
    unsigned correct;
} answer_t;

typedef mt19937 RNG;

unsigned get_number_in_range(unsigned, unsigned, RNG);
string get_snarky_response(snarky_response_t, RNG);
answer_t do_addition(RNG);
answer_t do_subtraction(RNG);
answer_t do_multiplication(RNG);
answer_t do_division(RNG);

int main()
{
    // The default seed generator
    random_device rd;
    // A random number generator (seeded with rd)
    RNG rng(rd());

    answer_t answer;

    answer = do_addition(rng);

    if (answer.given == answer.correct)
    {
        string response = get_snarky_response(positive, rng);
        cout << endl
             << response << endl;
    }
    else
    {
        string response = get_snarky_response(negative, rng);
        cout << response << endl
             << endl
             << "The answer is " << answer.correct << endl;
    }
}

answer_t do_addition(RNG rng)
{
    answer_t answer;
    answer.correct = get_number_in_range(200, 999, rng);
    unsigned addend = get_number_in_range(100, answer.correct - 100, rng);
    unsigned augend = answer.correct - addend;

    cout << endl << endl
         << "   " << addend << endl
         << " + " << augend << endl
         << "------" << endl;

    cout << "   ";
    cin >> answer.given;

    return answer;
}

unsigned get_number_in_range(unsigned range_start, unsigned range_end, RNG rng)
{
    uniform_int_distribution<> distribution(range_start, range_end);
    return distribution(rng);
}

string get_snarky_response(snarky_response_t response_type, RNG rng)
{
    // I want to generate a random snarky response, out of a pool
    // of snarky responses.
    // I need a random number to select which response I will use.
    uniform_int_distribution<> snarky_response_dist(0, 3);
    size_t snarky_response_index = snarky_response_dist(rng);

    // Here are my pools of snarky responses
    const string snarky_positive_response_pool[] = {
        "You're a mathematical genius.",
        "Good job. We're all very impressed.",
        "Arithmetic ain't got nothin on you.",
        "Oh bravo. You're an inspiration to us all."
    };
    const string snarky_negative_response_pool[] = {
        "Trump says: WRONG!!!",
        "You need help.",
        "You forgot to carry the 1, genius.",
        "Oh COME ON..."
    };

    if (response_type == positive)
    {
        return snarky_positive_response_pool[snarky_response_index];
    } else
    {
        return snarky_negative_response_pool[snarky_response_index];
    }
}
