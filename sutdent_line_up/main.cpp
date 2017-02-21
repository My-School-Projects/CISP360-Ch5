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
vector<string> sort_students(vector<string>&&);
bool file_contents_equal(ifstream&, ifstream&);

int main()
{
    {
        ifstream test_input;
        test_input.open("test_input.txt", ifstream::in);
        ofstream test_output;
        test_output.open("test_output.txt", ofstream::out);
        stringstream null_out;

        auto students = get_students(test_input, null_out);

        students = sort_students(move(students));

        for (size_t i = 0; i < students.size(); i++)
        {
            test_output << students[i] << endl;
        }

        test_input.close();
        test_output.close();
    }
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
/// Get a name from the user
///
string get_name(istream& in, ostream& out)
{
    string name;
    out << "Please enter a student's name." << endl
        << ">> ";
    in >> name;
    return name;
}

///
/// Get the number of students from the user
///
uint16_t get_number_of_students(istream& in, ostream& out)
{
    uint16_t number = 0;

    while(number < 1 or number > 25)
    {
        out << "Please enter the number of students in line." << endl
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

vector<string> get_students(istream& in, ostream& out)
{
    uint16_t number_of_students = get_number_of_students(in, out);

    vector<string> students(number_of_students);

    for (uint16_t i = 0; i < number_of_students; i++)
    {
        students[i] = get_name(in, out);
    }

    return students;
}

///
/// Sorts the students alphabetically
///
vector<string> sort_students(vector<string>&& students)
{
    // For now, bubble sort.
    for (size_t i = 0; i < students.size(); i++)
    {
        for (size_t j = 1; j < students.size(); j++)
        {
            if (students[j-1].compare(students[j]) > 0)
            {
                string temp = students[j];
                students[j] = students[j-1];
                students[j-1] = temp;
            }
        }
    }
    return students;
}

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
