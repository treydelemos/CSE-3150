
#include <iostream>
#include <cstring>   // for strlen, strcpy

using std::cout, std::cin, std::endl, std::strcpy;
// TODO: function prototypes
void addStudent(char* name, double gpa, char* names[], double gpas[], int& size, int capacity); 
void updateGPA(double* gpaPtr, double newGpa);
void printStudent(const char* name, const double& gpa);
double averageGPA(const double gpas[], int size);

// TODO: implement addStudent
void addStudent(char* name, double gpa, char* names[], double gpas[], int& size, int capacity) {
    if (size >= capacity) {
        throw "List full";
    }
    
    size_t len = strlen(name);
    char* copy = new char[len + 1];  // +1 for null terminator
    strcpy(copy, name);
    names[size] = copy;
    gpas[size] = gpa;
    size++;
}
// TODO: implement updateGPA
void updateGPA(double* gpaPtr, double newGpa) {
    if (gpaPtr != nullptr) {
        *gpaPtr = newGpa;
    }
}
// TODO: implement printStudent
void printStudent(const char* name, const double& gpa) {
    cout << name << ": " << gpa << endl;
}
// TODO: implement averageGPA
double averageGPA(const double gpas[], int size) {
    if (size == 0) {
        throw "No students";
    }
    
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += gpas[i];
    }
    return sum / size;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./program <capacity>" << std::endl;
        return 1;
    }

    int capacity = std::stoi(argv[1]);
    char* names[capacity];
    double gpas[capacity];
    int size = 0;

    int choice;
    do {
        std::cout << "Menu:\n";
        std::cout << "1. Add student\n";
        std::cout << "2. Update GPA\n";
        std::cout << "3. Print all students\n";
        std::cout << "4. Compute average GPA\n";
        std::cout << "5. Quit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                char name[256];
                double gpa;
                cout << "Enter name: ";
                cin.ignore();  // Clear the newline from previous input
                cin.getline(name, sizeof(name));
                if (std::strlen(name) == 0) {
                    cout << "Name cannot be empty\n" << endl;
                    break;
                }
                cout << "Enter GPA: " << endl;
                cin >> gpa;
                try {
                    addStudent(name, gpa, names, gpas, size, capacity);
                } catch (const char* msg) {
                    cout << msg << endl;
                }
                break;
            }
            case 2: {
                // TODO: implement menu logic
                int index;
                double newGpa;
                cout << "Enter student index 0-" << size-1 << ": " << endl;
                cin >> index;
                if (index >= 0 && index < size) {
                    cout << "Enter new GPA: " << endl;
                    cin >> newGpa;
                    updateGPA(&gpas[index], newGpa);
                } else {
                    cout << "Invalid index" << endl;
                }
                break;
            }
            case 3: {
                // TODO: implement menu logic
                for (int i = 0; i < size; i++) {
                    printStudent(names[i], gpas[i]);
                }
                break;
            }
            case 4: {
                // TODO: implement menu logic
                try {
                    double avg = averageGPA(gpas, size);
                    cout << "Average GPA: " << avg << " (rounded: " << static_cast<int>(avg + 0.5) << ")" << endl;
                } catch (const char* msg) {
                    cout << msg << endl;
                }
                break;
            }
            case 5: {
                std::cout << "Goodbye!" << std::endl;
                break;
            }
            default: {
                std::cout << "Invalid choice" << std::endl;
            }
        }
    } while (choice != 5);

    // TODO: free memory
    for (int i = 0; i < size; i++) {
    delete[] names[i];
}
    return 0;
}