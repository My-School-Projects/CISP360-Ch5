#include <iostream>
#include <random>
#include <chrono>
using namespace std;

///
/// `answer_t` is the return type used by the four do_math functions.
/// It holds both the correct answer, and the user's given answer.
///
typedef struct {
    unsigned given;
    unsigned correct;
} answer_t;

/// mt19937 is a random number generator (mersenne twister engine)
/// from here on referred to as RNG.
typedef mt19937 rng_t;

time_t get_current_time();
unsigned get_number_in_range(unsigned, unsigned, rng_t&);
string get_snarky_response(bool, rng_t&);
answer_t do_addition(rng_t&);
answer_t do_subtraction(rng_t&);
answer_t do_multiplication(rng_t&);
answer_t do_division(rng_t&);
void respond_to_answer(answer_t, rng_t&);

int main()
{
    // Random number generator (seeded from the system clock)
    rng_t rng(get_current_time());

    while(true)
    {
        char operation;
        answer_t answer;

        cout << "Please enter an operation you would like to practice [+ - * /]"
                 << endl << "or Q to quit."
                 << endl << ">> ";
            cin >> operation;

        switch(operation)
        {
        case '+':
            answer = do_addition(rng);
            respond_to_answer(answer, rng);
            break;
        case '-':
            answer = do_subtraction(rng);
            respond_to_answer(answer, rng);
            break;
        case '*':
            answer = do_multiplication(rng);
            respond_to_answer(answer, rng);
            break;
        case '/':
            answer = do_division(rng);
            respond_to_answer(answer, rng);
            break;
        case 'q':
        case 'Q':
            return 0;
        }
    }
}

///
/// Responds to the user's input with either a "you got it right"
/// or a "you got it wrong" (but snarky).
/// Prints the correct answer if the user got it wrong.
///
void respond_to_answer(answer_t answer, rng_t& rng)
{
    if (answer.given == answer.correct)
    {
        string response = get_snarky_response(true, rng);
        cout << endl
             << response << endl << endl;
    }
    else
    {
        string response = get_snarky_response(false, rng);
        cout << endl
             << response << endl << endl
             << "The answer is " << answer.correct << endl;
    }
}

///
/// Provides the user with an addition problem to solve.
/// All numbers used will be 3 digits (including the answer).
///
/// Returns `answer_t`, which holds both the correct answer,
/// and the answer provided by the user.
///
answer_t do_addition(rng_t& rng)
{
    answer_t answer;
    answer.correct = get_number_in_range(200, 999, rng);
    unsigned n1 = get_number_in_range(100, answer.correct - 100, rng);
    unsigned n2 = answer.correct - n1;

    cout << endl << endl
         << "   " << n1 << endl
         << " + " << n2 << endl
         << "------" << endl;

    cout << "   ";
    cin >> answer.given;

    return answer;
}

///
/// Provides the user with a subtraction problem to solve.
/// All numbers used will be 3 digits (including the answer).
///
/// Returns `answer_t`, which holds both the correct answer,
/// and the answer provided by the user.
///
answer_t do_subtraction(rng_t& rng)
{
    answer_t answer;
    answer.correct = get_number_in_range(100, 899, rng);
    unsigned n1 = get_number_in_range(answer.correct + 100, 999, rng);
    unsigned n2 = n1 - answer.correct;

    cout << endl << endl
         << "   " << n1 << endl
         << " - " << n2 << endl
         << "------" << endl;

    cout << "   ";
    cin >> answer.given;

    return answer;
}

///
/// Provides the user with a multiplication problem to solve.
/// The two multiplier and multiplicand will both be two digits,
/// and the answer will be between 3 or 4 digits long.
///
/// Returns `answer_t`, which holds both the correct answer,
/// and the answer provided by the user.
///
answer_t do_multiplication(rng_t& rng)
{
    answer_t answer;
    unsigned n1 = get_number_in_range(10, 99, rng);
    unsigned n2 = get_number_in_range(10, 99, rng);
    answer.correct = n1 * n2;

    cout << endl << endl
         << "   " << n1 << endl
         << " * " << n2 << endl
         << "-----" << endl
         << " ";

    // if the answer is only 3 digits, pad over one space
    if (answer.correct < 1000)
    {
        cout << " ";
    }
    cin >> answer.given;

    return answer;
}

answer_t do_division(rng_t& rng)
{
    answer_t answer;
    answer.correct = get_number_in_range(10, 99, rng);
    unsigned n2 = get_number_in_range(0, 9, rng);
    unsigned n1 = n2 * answer.correct;

    cout << endl << endl
         << "   " << n1 << endl
         << " /   " << n2 << endl
         << "------" << endl
         << "    ";

    cin >> answer.given;

    return answer;
}

///
/// Returns a random snarky response to the caller.
/// If `answer_correct` is true, it will return a "correct answer" response.
/// If `answer_correct` is false, it will return an "incorrect answer" response.
///
string get_snarky_response(bool answer_correct, rng_t& rng)
{
    // I want to generate a random snarky response, out of a pool
    // of snarky responses.
    // I need a random number to select which response I will use.
    size_t snarky_response_index = get_number_in_range(0, 3, rng);

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

    if (answer_correct)
    {
        return snarky_positive_response_pool[snarky_response_index];
    }
    else
    {
        return snarky_negative_response_pool[snarky_response_index];
    }
}

///
/// Just a simple utility to return a random number from
/// `range_start` to `range_end` (inclusive).
///
unsigned get_number_in_range(unsigned range_start, unsigned range_end, rng_t& rng)
{
    uniform_int_distribution<> distribution(range_start, range_end);
    return distribution(rng);
}

///
/// Get the current system time as a `time_t`.
///
time_t get_current_time()
{
    return chrono::system_clock::to_time_t(chrono::system_clock::now());
}
