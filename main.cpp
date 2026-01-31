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
int numSheet = 0;
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
void readDataFromFile(string);
string showExistingFiles();
void M2MenuChoice(int);

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

    int choice=1;
    M2MenuChoice(choice);
    return 0;
}

void M2MenuChoice(int choice){
    while(choice == 1){ //1.Create new attendance sheet.
        createNewAttendanceSheet();
        choice = MainMenuM2();
        database[numSheet] = sheetName + ".csv"; //Add the created attendance sheet to the db (the
        numSheet++;                              //db is an array with names of files as elements).
    }

    if (choice == 2){ //2.Load existing files.
        string loadingFileName;
        if (numSheet == 1){
            loadingFileName = sheetName + ".csv";
            readDataFromFile(loadingFileName); //Immediately load the only existing file
        }                                             //if there exists only one file.
        else if (numSheet > 1){
            //If there are more than one existing file, display the names
            //of the files and let user choose which file to load.
            loadingFileName = showExistingFiles();
            readDataFromFile(loadingFileName); //Load the chosen file.
        }
    }
    else { //3.Exit program.
        return;
    }
}

//Function to show all existing files and let user choose the file to load.
string showExistingFiles(){
    int fileToLoad;
    string loadingFileName;
    cout << "-------------------------------------------\n";
    cout << "\tExisting Files" << endl;
    cout << "-------------------------------------------\n";
    for (int i = 0; i < numSheet; i++){
        cout << i + 1 << ". " << database[i] << endl;
    } //Show the existing files, numbered.
    do{
        cout << "\nPlease choose which file to load [1-" << numSheet << "]: ";
        cin >> fileToLoad;
    }while(fileToLoad < 1 || fileToLoad > numSheet); //User choose which file to load
    loadingFileName = database[fileToLoad - 1];   //by choosing the number.
    return loadingFileName;
}

//Function to read attendance data from the attendance csv file.
void readDataFromFile(string filename){
    ifstream readFile;
    readFile.open(filename);
    string loadedFile;
    if (!readFile){
        cout << "\nError opening the file \"" << filename << "\"." << endl;
        //If file fail to open, user prompted to choose
        //either to exit or load the files again.

        /* help idk if this part is needed

        int choice;
        cout << "\n-------------------------------------------\n";
        cout << "Main Menu Milestone 2\n";
        cout << "-------------------------------------------\n";
        cout << "1. Load Existing Attendance Sheet(s)\n";
        cout << "2. Exit Program\n\n";
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

        choice++;
        M2MenuChoice(choice);
        */
    }
    else {
        while(readFile){
            getline(readFile, loadedFile); //Read and show file contents (attendance data).
            cout << loadedFile << endl;
        }
        // ADD FUNCTION TO EDIT SHEET HERE
    }
    readFile.close();
}

void createNewAttendanceSheet(){

    if (numRows >= MAX_SHEET) {
            cout << "Error: Maximum row limit reached.\n";
            return;
        }

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
        if (i != (numColumns - 1)){ //Add comma between elements (add comma only when
            cout << ", ";           //it is not the last element).
        }
    }
    cout << endl;

    //Loop through each rows and columns to display the elements (attendance data).
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
    string filename;
    filename = sheetName + ".csv";
    outputFile.open(filename);

    if(!outputFile){
        cout << "\nError opening the file \"" << filename << "\"." << endl;
    }
    else{
        outputFile << "\n-------------------------------------------\n";
        outputFile << "             Attendance Sheet\n";
        outputFile << "-------------------------------------------\n";

        for (int i = 0; i < numColumns; i++){
            outputFile << columnNames[i];
            if (i != (numColumns - 1)){
                outputFile << ", ";
            }
        }
        outputFile << endl;

        for (int row = 0; row < numRows; row++){
            for (int column = 0; column < numColumns; column++){
                outputFile << sheetData[row][column];
                if (column != (numColumns - 1)){
                    outputFile << ", ";
                }
            }
            outputFile << endl;
        }
        cout << "\nThe file \"" << filename << "\" has been created. Please check your folders." << endl;
        
        //Reset the sheetData[] array to create new attendance sheet.
        //Only reset sheetData[] after data has been saved into a file.
        for (int i = 0; i < numColumns; i++){
            columnNames[i] = "";
        }

        for (int row = 0; row < numRows; row++){
            for (int column = 0; column < numColumns; column++){
                sheetData[row][column] = "";
            }
        }

        numRows = 0;
    }
    outputFile.close();
}