#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Constants 
const int MAX_COLUMNS = 10;
const int MAX_ROWS = 100;

// Global Variables
string sheetName = "";
string columnNames[MAX_COLUMNS];
string columnTypes[MAX_COLUMNS];
string data[MAX_ROWS][MAX_COLUMNS];
int numColumns = 0;
int numRows = 0;

// Function Prototypes
void createSheet();
void insertRow();
void viewSheetCSV();
bool isValidInt(string value);

int main()
{
    cout << "===========================================\n";
    cout << "   STUDENT ATTENDANCE TRACKER - MILESTONE 1\n";
    cout << "===========================================\n\n";

    createSheet();
    insertRow();
    viewSheetCSV();
}

void createSheet() {
    cout << "Enter attendance sheet name: ";
    getline(cin, sheetName);
    cout << "Attendance sheet \"" << sheetName << "\" created successfully." << endl << endl;

    // define number of columns
    do {
        cout << "Define number of columns (max 10): ";
        cin >> numColumns;

        if (numColumns < 1 || numColumns > MAX_COLUMNS) {
            cout << "Invalid INT value. Please enter a value between 1 and " << MAX_COLUMNS << "." << endl;
        }
    } while (numColumns < 1 || numColumns > MAX_COLUMNS);

    cin.ignore();

    // loop through each column and get name and type
    for (int i=0; i < numColumns; i++) {
        cout << "Enter column " << (i + 1) << " name: ";
        getline(cin, columnNames[i]);

        cout << "Enter column " << (i + 1) << " type (INT or TEXT): ";
        getline(cin, columnTypes[i]);
    }

    cout << "Sheet structure created successfully." << endl << endl;
}

void insertRow() {
    cout << "-------------------------------------------\n";
    cout << "Insert New Attendance Row\n";
    cout << "-------------------------------------------\n";
}

void viewSheetCSV() {
    cout << "-------------------------------------------\n";
    cout << "View Attendance Sheet (CSV Mode)\n";
    cout << "-------------------------------------------\n";
}