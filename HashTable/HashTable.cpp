#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Student {
public:
    string ID;
    string firstName;
    string lastName;
    string birthday;
    string gender;

    Student() {}

    Student(const string& id, const string& first, const string& last, const string& bday, const string& g)
        : ID(id), firstName(first), lastName(last), birthday(bday), gender(g) {}
};

class HashTable {
private:
    static const int TABLE_SIZE = 50;
    vector<Student> table[TABLE_SIZE];

    int hashFunction(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash += static_cast<int>(c);
        }
        return hash % TABLE_SIZE;
    }

public:
    void addStudent(const Student& student) {
        int index = hashFunction(student.ID);
        table[index].push_back(student);
    }

    Student findStudent(const string& id) {
        int index = hashFunction(id);
        for (const Student& student : table[index]) {
            if (student.ID == id) {
                return student;
            }
        }
        return Student(); // Return an empty student if not found
    }

    void printAllStudents() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            for (const Student& student : table[i]) {
                cout << "ID: " << student.ID << ", Name: " << student.firstName << " " << student.lastName
                    << ", Birthday: " << student.birthday << ", Gender: " << student.gender << endl;
            }
        }
    }

    void writeToFile(const string& filename) {
        ofstream file(filename);

        if (file.is_open()) {
            for (int i = 0; i < TABLE_SIZE; ++i) {
                for (const Student& student : table[i]) {
                    file << student.ID << " " << student.firstName << " " << student.lastName << " "
                        << student.birthday << " " << student.gender << endl;
                }
            }

            file.close();
        }
        else {
            cerr << "Unable to open the file for writing." << endl;
        }
    }

    void readFromFile(const string& filename) {
        ifstream file(filename);

        if (file.is_open()) {
            // Clear existing data
            for (int i = 0; i < TABLE_SIZE; ++i) {
                table[i].clear();
            }

            string id, first, last, birthday, gender;
            while (file >> id >> first >> last >> birthday >> gender) {
                Student student(id, first, last, birthday, gender);
                addStudent(student);
            }

            file.close();
        }
        else {
            cerr << "Unable to open the file for reading." << endl;
        }
    }
};

int main() {
    HashTable hashTable;

    // Read list of data from the keyboard
    for (int i = 0; i < 10; ++i) {
        string id, first, last, birthday, gender;
        cout << "Enter student data (ID FirstName LastName Birthday Gender): ";
        cin >> id >> first >> last >> birthday >> gender;

        Student student(id, first, last, birthday, gender);
        hashTable.addStudent(student);
    }

    // Write the data list to Danhsach.txt file
    hashTable.writeToFile("D://Danhsach.txt");

    // Read data from Danhsach.txt
    hashTable.readFromFile("D://Danhsach.txt");

    // Input ID number and find a person
    string searchID;
    cout << "Enter ID to find a person: ";
    cin >> searchID;

    Student foundStudent = hashTable.findStudent(searchID);

    if (foundStudent.ID.empty()) {
        cout << "Person not found." << endl;
    }
    else {
        cout << "Person found: ";
        cout << "ID: " << foundStudent.ID << ", Name: " << foundStudent.firstName << " " << foundStudent.lastName
            << ", Birthday: " << foundStudent.birthday << ", Gender: " << foundStudent.gender << endl;
    }

    return 0;
}
