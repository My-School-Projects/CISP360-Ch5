#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    float cost = 25000;

    cout << "Current: $"
         << setprecision(2) << fixed
         << cost << endl;

    for (int i = 1; i <= 6; i++)
    {
        cost *= 1.04;
        cout << "Year  " << i << ": $"
             << setprecision(2) << fixed
             << cost << endl;
    }
}
