#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

string get_name(istream& in, ostream& out);
uint16_t get_number_of_students(istream& in, ostream& out);
vector<string> get_students(istream& in, ostream& out);
vector<string> sort_strings(vector<string>&&);
bool file_contents_equal(ifstream&, ifstream&);
void student_line_up(istream&, ostream&, ostream&);

const bool TEST = false;

int main()
{
    if (TEST)
    {
        ifstream test_input;
        test_input.open("test_input.txt", ifstream::in);
        ofstream test_output;
        test_output.open("test_output.txt", ofstream::out);
        stringstream null_out;

        // If we're testing, get input from `test_input`, send output
        // to `test_output` and discard all prompts (send to `null_out`).
        student_line_up(test_input, test_output, null_out);
    }
    else
    {
        // If we're not testing, get input from cin,
        // and send output and prompts to cout.
        student_line_up(cin, cout, cout);
    }

    // If we're testing, assert that the contents of `test_output.txt`
    // are the same as the contents of `test_input.txt`
    if (TEST)
    {
        ifstream test_output;
        test_output.open("test_output.txt", ifstream::in);
        ifstream test_data;
        test_data.open("test_data.txt", ifstream::in);

        if (file_contents_equal(test_output, test_data))
        {
            cout << "Test passed" << endl;
        }
        else
        {
            cout << "Test failed" << endl;
        }

        test_output.close();
        test_data.close();
    }

    return 0;
}

///
/// Gets a list of students from `in`, sorts them by name,
/// and prints the first and last student to `out`.
/// Prompts are sent to `prompt`.
void student_line_up(istream& in, ostream& out, ostream& prompt)
{
    vector<string> students = get_students(in, prompt);

    students = sort_strings(move(students));

    out << "Student in front : " << students[0] << endl
        << "Student in back  : " << students[students.size()-1] << endl;
}

///
/// Gets a name from `in` and returns it.
/// Prompts are sent to `prompt`.
///
string get_name(istream& in, ostream& prompt)
{
    string name;
    prompt << "Please enter a student's name." << endl
        << ">> ";
    in >> name;
    return name;
}

///
/// Gets the number of students from `in`, and returns it.
/// Prompts are sent to `prompt`.
///
uint16_t get_number_of_students(istream& in, ostream& prompt)
{
    uint16_t number = 0;

    while(number < 1 or number > 25)
    {
        prompt << "Please enter the number of students in line." << endl
             << ">> ";
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
/// Populates a `vector<string>` with names of students
/// taken from `in`, and returns it.
/// Prompts are sent to `prompt`.
///
vector<string> get_students(istream& in, ostream& prompt)
{
    uint16_t number_of_students = get_number_of_students(in, prompt);

    vector<string> students(number_of_students);

    for (uint16_t i = 0; i < number_of_students; i++)
    {
        students[i] = get_name(in, prompt);
    }

    return students;
}

///
/// Sorts a vector of strings alphabetically
///
vector<string> sort_strings(vector<string>&& strings)
{
    // For now, bubble sort.
    for (size_t i = 0; i < strings.size(); i++)
    {
        for (size_t j = 1; j < strings.size(); j++)
        {
            if (strings[j-1].compare(strings[j]) > 0)
            {
                string temp = strings[j];
                strings[j] = strings[j-1];
                strings[j-1] = temp;
            }
        }
    }
    return strings;
}

///
/// Returns `true` if the contents of `f1` are the same
/// as the contents of `f2`.
///
bool file_contents_equal(ifstream& f1, ifstream& f2)
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
