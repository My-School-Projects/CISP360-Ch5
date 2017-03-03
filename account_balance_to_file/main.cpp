#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

void accout_balance(istream&, ostream&, ostream&);
float input(istream&, ostream&, bool, string);

int main()
{
	ofstream out;
	out.open("output.txt");

    accout_balance(cin, out, cout);

	out.close();
	getchar();
    return 0;
}

///
/// Gets information about account transactions from `in`,
/// and displays the account balance to `out`.
/// Prompts are sent to `prompt`.
///
/// @arg in - The stream to get input from (usually cin, or a file)
/// @arg out - The stream to print output to, (usually cout, or a file)
/// @arg prompt - The stream to print prompts to, (usually cout)
///
void accout_balance(istream& in, ostream& out, ostream& prompt)
{
    float monthly_interest_rate = input(in, prompt, false, "Please enter the annual interest rate for the account.\n>> %");
    monthly_interest_rate /= 1200;
    float balance = input(in, prompt, false, "What was the starting balance?\n>> $");
    unsigned months_since_opened = input(in, prompt, true, "How many months has the account been open?\n>> ");
    float deposited = 0, withdrawn = 0, interest_earned = 0;

    for (unsigned i = 1; i <= months_since_opened; i++)
    {
        deposited += input(in, prompt, false, "Please enter the amount deposited during month " + to_string(i) + ": \n>> $");

        withdrawn += input(in, prompt, false, "Please enter the amount withdrawn during month " + to_string(i) + ": \n>> $");

        balance = balance + deposited - withdrawn;
        interest_earned = balance * monthly_interest_rate;
        balance += interest_earned;
    }

    out << setprecision(2) << fixed
		<< "Ending balance  : $" << balance << endl
        << "Total deposited : $" << deposited << endl
        << "Total withdrawn : $" << withdrawn << endl
        << "Interest earned : $" << interest_earned << endl;
}

///
/// Gets a number from `in`. If `integral` is true, it will only accept whole numbers.
///
/// @arg in - The stream to get input from (usually cin, or a file)
/// @arg prompt_stream - The stream to print prompts to, (usually cout)
/// @arg integral - If true, only whole numbers will be accepted as valid input
/// @arg prompt - The prompt to be displayed to `prompt_stream` when requesting input
///
/// @return The number read from `in`
///
float input(istream& in, ostream& prompt_stream, bool integral, string prompt)
{
    float number = -1;
    while(number < 0)
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
