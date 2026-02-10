#include <iostream>
#include <fstream>
using namespace std;

class Student
{
    char name[30];
    int roll;
    int marks[3];
    float per;

public:
    // Add student record
    void addStudent()
    {
        ofstream fout("student.txt", ios::app);//app-Write data at the end of the file
        if (!fout)
        {
            cout << "Error opening file.\n";
            return;
        }

        cout << "Enter Student Name: ";
        cin.getline(name, 30);

        cout << "Enter Roll Number: ";
        cin >> roll;

        for (int i = 0; i < 3; i++)
        {
            cout << "Enter marks of subject " << i + 1 << ": ";
            cin >> marks[i];
        }

        calculatePercentage();

        fout << name << " "
             << roll << " "
             << marks[0] << " "
             << marks[1] << " "
             << marks[2] << " "
             << per << endl;

        fout.close();
        cout << "\nStudent record added successfully.\n";
    }

    // Calculate percentage
    void calculatePercentage()
    {
        int total = 0;
        for (int i = 0; i < 3; i++)
            total += marks[i];

        per = total / 3.0;
    }

    // Display one student
    void displayData()
    {
        cout << "\nName: " << name;
        cout << "\nRoll No: " << roll;
        for (int i = 0; i < 3; i++)
            cout << "\nSubject " << i + 1 << " Marks: " << marks[i];
        cout << "\nPercentage: " << per << "%\n";
    }

    // Read from file
    bool readFromFile(ifstream &fin)
    {
        return (fin >> name >> roll >> marks[0] >> marks[1] >> marks[2] >> per);
    }

    // Write to file 
    void writeToFile(ofstream &fout)
    {
        fout << name << " "
             << roll << " "
             << marks[0] << " "
             << marks[1] << " "
             << marks[2] << " "
             << per << endl;
    }

    int getRoll()
    {
        return roll;
    }
};

// Display all students
void displayAll()
{
    Student s;
    ifstream fin("student.txt");

    if (!fin)
    {
        cout << "File not found.\n";
        return;
    }

    while (s.readFromFile(fin))
    {
        s.displayData();
    }

    fin.close();
}

// Search student
void searchStudent()
{
    Student s;
    int r;
    bool found = false;

    ifstream fin("student.txt");
    if (!fin)
    {
        cout << "File not found.\n";
        return;
    }

    cout << "Enter Roll Number to Search: ";
    cin >> r;

    while (s.readFromFile(fin))
    {
        if (s.getRoll() == r)
        {
            s.displayData();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nStudent not found.\n";

    fin.close();
}

// Delete student
void deleteStudent()
{
    Student s;
    int r;
    bool found = false;

    ifstream fin("student.txt");
    ofstream fout("temp.txt");

    if (!fin || !fout)
    {
        cout << "File error.\n";
        return;
    }

    cout << "Enter Roll Number to Delete: ";
    cin >> r;

    while (s.readFromFile(fin))
    {
        if (s.getRoll() == r)
            found = true;   // skip record
        else
            s.writeToFile(fout);//Write the data in temp. txt
    }

    fin.close();
    fout.close();

    remove("student.txt");
    rename("temp.txt", "student.txt");

    if (found)
        cout << "\nStudent record deleted successfully.\n";
    else
        cout << "\nStudent not found.\n";
}

int main()
{
    Student s;
    int choice;

    do
    {
        cout << "\n----- Student Management System (TEXT FILE) -----";
        cout << "\n1. Add Student";
        cout << "\n2. Display All Students";
        cout << "\n3. Search Student";
        cout << "\n4. Delete Student";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            s.addStudent();
            break;
        case 2:
            displayAll();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            deleteStudent();
            break;
        case 5:
            cout << "\nExiting program...\n";
            break;
        default:
            cout << "\nInvalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}