#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
using namespace std;

const bool TEST = false;

void accout_balance(istream&, ostream&, ostream&);
float input(istream&, ostream&, string);
bool file_contents_equal(fstream&, ifstream&);

int main()
{
    if (TEST)
    {
        ifstream test_input;
        test_input.open("test_input.txt");
        fstream test_output;
        test_output.open("test_output.txt");
        stringstream null_out;

        // If we're testing, get input from `test_input`, send output
        // to `test_output`, and discard all prompts (send to `null_out`).
        accout_balance(test_input, test_output, null_out);

        ifstream test_data;
        test_data.open("test_data.txt");

        // We then test if the contents of `test_output` are the same
        // as the contents of `test_data`. If they are, everything worked
        // as expected. If not, something's wrong.
        if (file_contents_equal(test_output, test_data))
        {
            cout << "Test passed" << endl;
        }
        else
        {
            cout << "Test failed" << endl;
        }

        test_input.close();
        test_output.close();
        test_data.close();
    }
    else
    {
        // If we're not testing, get input from `cin`,
        // and send output and prompts to `cout`.
        accout_balance(cin, cout, cout);
    }

    return 0;
}

///
/// Gets information about account transactions from `in`,
/// and displays the account balance to `out`.
/// Prompts are sent to `prompt`.
///
void accout_balance(istream& in, ostream& out, ostream& prompt)
{
    float monthly_interest_rate = input(in, prompt, "Please enter the annual interest rate for the account.\n>> %");
    monthly_interest_rate /= 1200;


}

float input(istream& in, ostream& prompt_stream, string prompt)
{
    float number = -1;
    while(number < 1)
    {
        prompt_stream << prompt;
        in >> number;
        // If the user enters alphabetical characters instead of
        // numerics, `in` will go into an error state, and will stop recieving input.
        // To fix this, we call `in.clear()` to reset the error flags,
        // and `in.ignore(BIG_NUMBER, '\n')` to ignore all characters entered up until the newline.
        in.clear();
        in.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return number;
}

///
/// Returns `true` if the contents of `f1` are the same
/// as the contents of `f2`.
///
bool file_contents_equal(fstream& f1, ifstream& f2)
{
    string s1, s2;
    while(f1.good())
    {
        getline(f1, s1);
        getline(f2, s2);
        if (s1.compare(s2) != 0)
            return false;
    }
    return true;
}
