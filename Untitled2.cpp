#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
    string StudentsName;
    cout << "===========================================\n";
    cout << "   STUDENT ATTENDANCE TRACKER - MILESTONE 1\n";
    cout << "===========================================\n\n";

    cout << "Enter attendance sheet name: ";
    getline(cin, StudentsName);
    cout << "Attendance sheet '" << StudentsName << "' created successfully";



    cout << "Sheet structure created successfully.\n\n";
}
