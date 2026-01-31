// *********************************************************
// Program: TC1L_GROUP38_A1.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT2L and TT3L
// Trimester: 2530
// Member_1: 252UC241MK | ADRIANA NUR ZAHRA BINTI MOHD HELMI | ADRIANA.NUR.ZAHRA1@student.mmu.edu.my | 0132080445
// Member_2: 252UC242N8 | CHIAM JUIN HOONG | CHIAM.JUIN.HOONG1@student.mmu.edu.my | 0125450314
// Member_3: 252UC243DZ | NURSYAHIRAH AQILAH BINTI AINUL HISHAM | NURSYAHIRAH.AQILAH.AINUL1@student.mmu.edu.my | 0194482144
// Member_4: 252UC243DY | QAISARAH BINTI SHAMSUL AZRAN | QAISARAH.SHAMSUL.AZRAN1@student.mmu.edu.my | 0134130145
// *********************************************************
// Task Distribution
// Member_1:
// Member_2:
// Member_3:
// Member_4:
// *********************************************************

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <fstream>
using namespace std;

// Constants
const int MAX_COLUMNS = 10;
const int MAX_ROWS = 100;
const int MAX_SHEET = 100;

// Global Variables
string sheetName = "";
string columnNames[MAX_COLUMNS];
string columnTypes[MAX_COLUMNS];
string database[MAX_SHEET];
string sheetData[MAX_ROWS][MAX_COLUMNS];
int numColumns = 0;
int numRows = 0;
bool sheetExist = false;

// Function Prototypes
void createSheet();
void insertRow();
void viewSheetCSV();
void createCSVfile(string);
bool isValidInt(string value);
bool isValidText(string value);
void createNewAttendanceSheet();
void MainMenuM1();
int MainMenuM2();
void readDataFromFile(string, int);
string showExistingFiles(int);
void M2MenuChoice(int, int);
void editSheetMenuM2();
void displayCurrentSheet(const string& heading);
void printSheetRawCSV();
int  findStudentIdCol();
string getIntInputLine(const string& prompt);
void deleteAttendanceRow();
void countRowsOutput();
void loadAttendanceFile(string filename);

int main()
{
    //Create database first > Immediately create attendance sheet > Show menu to
    //choose whether to add more attendance sheet to the db or to load and edit
    //the existing attendance sheet (also referred to as files).
    string termName;
    cout << "============================================\n";
    cout << "  STUDENT ATTENDANCE TRACKER - MILESTONE 2\n";
    cout << "============================================\n\n";

    cout << "Create School Term (Database)" << endl;
    cout << "-------------------------------------------\n";
    cout << "Enter term name: ";
    cin >> termName;
    cout << "Database \"" << termName << "\" created and loaded." << endl << endl;
    cin.ignore();

    int choice=1, sheet=0;
    M2MenuChoice(choice, sheet);
    return 0;
}

void M2MenuChoice(int choice, int sheet){
    while(choice == 1){ //1.Create new attendance sheet.
        createNewAttendanceSheet();
        choice = MainMenuM2();
        database[sheet] = sheetName + ".csv"; //Add the created attendance sheet to the db (the
        sheet++;                              //db is an array with names of files as elements).
    }

    if (choice == 2){ //2.Load existing files.
        string loadingFileName;
        if (sheet == 1){
            loadingFileName = sheetName + ".csv";
            readDataFromFile(loadingFileName, sheet); //Immediately load the only existing file
        }                                             //if there exists only one file.
        else if (sheet > 1){
            //If there are more than one existing file, display the names
            //of the files and let user choose which file to load.
            loadingFileName = showExistingFiles(sheet);
            readDataFromFile(loadingFileName, sheet); //Load the chosen file.
        }
    }
    else { //3.Exit program.
        return;
    }
}

//Function to show all existing files and let user choose the file to load.
string showExistingFiles(int sheet){
    int fileToLoad;
    string loadingFileName;
    cout << "-------------------------------------------\n";
    cout << "\tExisting Files" << endl;
    cout << "-------------------------------------------\n";
    for (int i = 0; i < sheet; i++){
        cout << i + 1 << ". " << database[i] << endl;
    } //Show the existing files, numbered.
    do{
        cout << "\nPlease choose which file to load [1-" << sheet << "]: ";
        cin >> fileToLoad;
    }while(fileToLoad < 1 || fileToLoad > sheet); //User choose which file to load
    loadingFileName = database[fileToLoad - 1];   //by choosing the number.
    return loadingFileName;
}

//Function to read attendance data from the attendance csv file.
void readDataFromFile(string filename, int sheet){
    ifstream readFile;
    readFile.open(filename);
    string loadedFile;
    if (!readFile){
        cout << "\nError opening the file \"" << filename << "\"." << endl;
    }
    else {
        cout << "\nReading attendance data from file...\n";
        cout << "Successfully loaded: " << filename << "\n\n";

        // Load the file contents into columnNames[] and sheetData[] arrays
        // This allows the data to be edited
        loadAttendanceFile(filename);

        viewSheetCSV(); // Display the loaded sheet to the user
        editSheetMenuM2();
}

    readFile.close();
}

void createNewAttendanceSheet(){
    int choice;

    cout << "============================================\n";
    cout << "  STUDENT ATTENDANCE TRACKER - MILESTONE 1\n";
    cout << "============================================\n";

    createSheet();
    insertRow();

    while(true)
    {
        MainMenuM1();
        cout << "\nPlease Enter Your Choice: ";
        cin >> choice;

        while (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Error: Invalid input. Please enter a valid number.\n\n";
            cin >> choice;
        }
        cin.ignore();

        switch (choice)
        {
        case 1:
            insertRow();
            break;

        case 2:
            viewSheetCSV();
            break;

        case 3:
            createCSVfile(sheetName);
            return;

        default:
            cout << "\nError: Invalid menu choice. Please try again.\n\n";
            break;
        }
    }
}

//Function to display menu choices after attendance sheet created and filled.
int MainMenuM2(){
    int choice;
    cout << "\n-------------------------------------------\n";
    cout << "Main Menu Milestone 2\n";
    cout << "-------------------------------------------\n";
    cout << "1. Create New Attendance Sheet\n";
    cout << "2. Load Existing Attendance Sheet(s)\n";
    cout << "3. Exit Program\n\n";
    cout << "Please Enter Your Choice: ";
    cin >> choice;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error: Invalid input. Please enter a valid number.\n\n";
        cin >> choice;
    }
    cin.ignore();

    return choice;
}

void createSheet() {
    cout << "\nEnter attendance sheet name: ";
    getline(cin, sheetName);
    cout << "Attendance sheet \"" << sheetName << "\" created successfully." << endl << endl;

    do {
        cout << "Define number of columns (max 10): ";
        cin >> numColumns;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid INT value. Please enter a number.\n";
            numColumns = 0;
        }
        else if (numColumns < 1 || numColumns > MAX_COLUMNS) {
            cout << "Invalid INT value. Please enter a value between 1 and "
                 << MAX_COLUMNS << ".\n";
        }

    } while (numColumns < 1 || numColumns > MAX_COLUMNS);

    cin.ignore();

    // loop through each column and get name and type
    for (int i = 0; i < numColumns; i++) {
        cout << "Enter column " << (i + 1) << " name: ";
        getline(cin, columnNames[i]);

        do {
            cout << "Enter column " << (i + 1) << " type (INT or TEXT): ";
            getline(cin, columnTypes[i]);

            if (columnTypes[i] != "INT" && columnTypes[i] != "TEXT") {
                cout << "Invalid type. Please enter INT or TEXT.\n";
            }
        } while (columnTypes[i] != "INT" && columnTypes[i] != "TEXT");
    }

    sheetExist = true;
    cout << "Sheet structure created successfully." << endl << endl;
}

bool isValidInt(string value) {
    if (value.empty()) return false;

    for (int i = 0; i < value.length(); i++) {
        if (!isdigit(value[i])) {
            return false;
        }
    }
    return true;
}

void insertRow() {
    string input;

    while (true) {
        cout << "\n-------------------------------------------\n";
        cout << "Insert New Attendance Row\n";
        cout << "-------------------------------------------\n";

        if (numRows >= MAX_ROWS) {
            cout << "Error: Maximum row limit reached.\n";
            return;
        }

        for (int col = 0; col < numColumns; col++) {
            while (true){
                cout << "Enter " << columnNames[col] << ": ";
                getline(cin, input);

            if (columnTypes[col] == "INT") {
                if (!isValidInt(input)) {
                    cout << "Error: Invalid INT value. Please enter a number.\n";
                    continue;
                }
            }
            else if (columnTypes[col] == "TEXT") {
                if (!isValidText(input)) {
                    cout << "Error: Invalid TEXT value. Please enter text.\n";
                    continue;
                }
            }

            sheetData[numRows][col] = input;
            break;
            }
        }

        numRows++;
        cout << "Row inserted successfully.\n\n";

        cout << "Insert another row? (Y/N): ";
        getline(cin, input);

        if (input != "Y" && input != "y") {
            break;
        }
    }
}

bool isValidText(string value) {
    if (value.empty()) return false;

    for (int i = 0; i < value.length(); i++) {
        if (!isdigit(value[i])) {
            return true;
        }
    }
    return false;
}

//Function to view the attendance data in CSV, not in file.
void viewSheetCSV() {
    cout << "\n-------------------------------------------\n";
    cout << "     View Attendance Sheet (CSV Mode)\n";
    cout << "-------------------------------------------\n";

    for (int i = 0; i < numColumns; i++){ //Loop through each elements in the columnName[]
        cout << columnNames[i];           //array to display the column names.
        if (i != (numColumns - 1)){ //Add comma between elements
            cout << ", ";
        }
    }
    cout << endl;

    //Loop through each rows and columns to display the elements
    for (int row = 0; row < numRows; row++){
        for (int column = 0; column < numColumns; column++){
            cout << sheetData[row][column];
            if (column != (numColumns - 1)){ //Again, add comma between elements.
                cout << ", ";
            }
        }
        cout << endl;
    }
}

void MainMenuM1()
{
    cout << "\n-------------------------------------------\n";
    cout << "Main Menu Milestone 1\n";
    cout << "-------------------------------------------\n";
    cout << "1. Insert More Rows\n";
    cout << "2. View Attendance Sheet (CSV)\n";
    cout << "3. Save Sheet in CSV File and Exit\n";
}

//Function to save the attendance data into a csv file.
//The idea is the same as the viewSheetCSV() function but instead of
//outputting on the terminal, we write into a file.
void createCSVfile(string sheetName){
    ofstream outputFile;
    string filename = sheetName + ".csv";
    outputFile.open(filename);

    if(!outputFile){
        cout << "\nError opening the file \"" << filename << "\"." << endl;
    }
    else{
        // Header (CSV)
        for (int i = 0; i < numColumns; i++){
            outputFile << columnNames[i];
            if (i != (numColumns - 1)) outputFile << ",";
        }
        outputFile << "\n";

        // Rows (CSV)
        for (int row = 0; row < numRows; row++){
            for (int col = 0; col < numColumns; col++){
                outputFile << sheetData[row][col];
                if (col != (numColumns - 1)) outputFile << ",";
            }
            outputFile << "\n";
        }

        cout << "\nThe file \"" << filename << "\" has been created. Please check your folders." << endl;

        // Reset for next sheet
        for (int i = 0; i < numColumns; i++) columnNames[i] = "";
        for (int r = 0; r < numRows; r++)
            for (int c = 0; c < numColumns; c++)
                sheetData[r][c] = "";

        numRows = 0;
    }
    outputFile.close();
}

void editSheetMenuM2() {
    while (true) {
        int choice;
        cout << "\n-------------------------------------------\n";
        cout << "Main Menu Milestone 2 (Edit Loaded Sheet)\n";
        cout << "-------------------------------------------\n";
        cout << "1. Display Current Sheet\n";
        cout << "2. Delete Attendance Row\n";
        cout << "3. Count Rows\n";
        cout << "4. Exit to Main Menu\n\n";
        cout << "Please Enter Your Choice: ";

        cin >> choice;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Error: Invalid input. Please enter a valid number.\n\n";
            cin >> choice;
        }
        cin.ignore();

        if (choice == 1) {
            displayCurrentSheet("Current Attendance Sheet");
        }
        else if (choice == 2) {
            deleteAttendanceRow();
        }
        else if (choice == 3) {
            countRowsOutput();
        }
        else if (choice == 4) {
            return;
        }
        else {
            cout << "Error: Invalid menu choice.\n";
        }
    }
}

void displayCurrentSheet(const string& heading) {
    cout << "\n-------------------------------------------\n";
    cout << heading << "\n";
    cout << "-------------------------------------------\n";
    printSheetRawCSV();
}

void printSheetRawCSV() {
    // Header
    for (int i = 0; i < numColumns; i++) {
        cout << columnNames[i];
        if (i != numColumns - 1) cout << ", ";
    }
    cout << endl;

    // Rows
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numColumns; c++) {
            cout << sheetData[r][c];
            if (c != numColumns - 1) cout << ", ";
        }
        cout << endl;
    }
}

int findStudentIdCol() {
    for (int i = 0; i < numColumns; i++) {
        string name = columnNames[i];
        for (int k = 0; k < (int)name.length(); k++) {
            name[k] = tolower(name[k]);
        }

        if (name == "studentid" || name == "student id" || name == "student_id") {
            return i;
        }
    }
    return -1;
}

string getIntInputLine(const string& prompt) {
    string s;
    while (true) {
        cout << prompt;
        getline(cin, s);

        if (!isValidInt(s)) {
            cout << "Error: Invalid integer. Try again.\n\n";
            continue;
        }
        return s;
    }
}

// Deletes an attendance row based on StudentID
// Rows below the deleted record are shifted up
void deleteAttendanceRow() {
    cout << "\n-------------------------------------------\n";
    cout << "Delete Attendance Row\n";
    cout << "-------------------------------------------\n";

    int sidCol = findStudentIdCol(); // Find the column that containts StudentID
    if (sidCol == -1) {
        cout << "Error: StudentID column not found.\n";
        return;
    }

    string sid = getIntInputLine("Enter StudentID to delete: ");

    int targetRow = -1; // Search for matching row
    for (int r = 0; r < numRows; r++) {
        if (sheetData[r][sidCol] == sid) {
            targetRow = r;
            break;
        }
    }

    if (targetRow == -1) {
        cout << "Error: StudentID does not exist.\n";
        return;
    }

    for (int r = targetRow; r < numRows - 1; r++) { // Shift rows upward to remove the selected row
        for (int c = 0; c < numColumns; c++) {
            sheetData[r][c] = sheetData[r + 1][c];
        }
    }

    for (int c = 0; c < numColumns; c++) {
        sheetData[numRows - 1][c] = "";
    }

    numRows--;

    cout << "Row deleted successfully.\n";

    cout << "\nUpdated Sheet:\n";
    printSheetRawCSV();
}

// Displays the total number of attendance records currently stored
void countRowsOutput() {
    cout << "\n-------------------------------------------\n";
    cout << "Count Rows\n";
    cout << "-------------------------------------------\n";
    cout << "Number of rows: " << numRows << endl;
}

// Splits a CSV line by comma
int splitLine(string line, string tokens[], int maxTokens) {
    int count = 0;
    stringstream ss(line);
    string token;

    // Get each token separated by commas
    while (getline(ss, token, ',') && count < maxTokens) {
        tokens[count++] = token; // Add token to array
    }

    return count;
}

// Loads attendance data from a CSV file into memory
// Assumes the first column is StudentID (INT)
void loadAttendanceFile(string filename) {
    ifstream f(filename);
    if (!f) {
        cout << "Error: Cannot open file.\n";
        return;
    }

    // Clear old data
    for (int i = 0; i < MAX_COLUMNS; i++) columnNames[i] = "";
    for (int r = 0; r < MAX_ROWS; r++)
        for (int c = 0; c < MAX_COLUMNS; c++)
            sheetData[r][c] = "";

    numRows = 0;
    numColumns = 0;

    string line;
    string tokens[MAX_COLUMNS];

    // Read header
    if (getline(f, line)) {
        numColumns = splitLine(line, tokens, MAX_COLUMNS);
        for (int i = 0; i < numColumns; i++) {
            columnNames[i] = tokens[i];
        }
    }

    // Read data rows
    while (getline(f, line) && numRows < MAX_ROWS) {
        int cols = splitLine(line, tokens, MAX_COLUMNS);

        // First column must be StudentID
        if (cols <= 0 || !isValidInt(tokens[0])) continue;

        for (int c = 0; c < numColumns; c++) {
            sheetData[numRows][c] = (c < cols) ? tokens[c] : "";
        }
        numRows++;
    }

    f.close();
}
