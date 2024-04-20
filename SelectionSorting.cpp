#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

class student
{
private:
    int id;
    string name;
    double gpa;

public:
    student(int id, string name, double gpa) : id(id), name(name), gpa(gpa) {}

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    double getGpa() const {
        return gpa;
    }

    bool operator<(const student& other) const {
        if (name == other.name) {
            return gpa < other.gpa;
        }
        return name < other.name;
    }
};

template<typename T>
void ByNameSelectionSort(vector<T>& arr, int& cnt) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
            ++cnt;
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

template<typename T, typename Compare>
void ByGpaSelectionSort(vector<T>& arr, Compare comp, int& cnt) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (comp(arr[j], arr[minIndex])) {
                minIndex = j;
            }
            ++cnt;
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

int main() {
    vector<student> students;

    ifstream file("students.txt");
    if (!file) {
        cout << "Error opening file." << endl;
        return 1;
    }

    int nameComparisons = 0;
    int gpaComparisons = 0;

    int numStudents;
    file >> numStudents;
    file.ignore();

    for (int i = 0; i < numStudents; ++i) {
        string name, idStr, gpaStr;
        getline(file, name);
        getline(file, idStr);
        getline(file, gpaStr);

        students.emplace_back(stoi(idStr), name, stod(gpaStr));
    }

    ofstream outputByName("SortedByName.txt");
    ofstream outputByGPA("SortedByGPA.txt");

    auto start = high_resolution_clock::now();
    // Sorting by name || selection sort
    ByNameSelectionSort(students, nameComparisons);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    outputByName << "Algorithm: Selection Sort\n";
    outputByName << "Number of comparisons:" << nameComparisons<<"\n";
    outputByName << "Running Time: " << duration.count() << " milliseconds\n";
    outputByName << "Sorted by Name:\n";
    for (const auto& s : students) {
        outputByName << s.getName() << "\n" << s.getId() << "\n" << s.getGpa() << "\n";
    }
    outputByName << endl;

    start = high_resolution_clock::now();
    // Sorting by GPA || selection sort
    ByGpaSelectionSort(students, [](const student& s1, const student& s2) {
        return s1.getGpa() < s2.getGpa();
    }, gpaComparisons);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);

    outputByGPA << "Algorithm: Selection Sort\n";
    outputByGPA << "Number of comparisons:" << gpaComparisons<<"\n";
    outputByGPA << "Running Time: " << duration.count() << " milliseconds\n";
    outputByGPA << "Sorted by GPA:\n";
    for (const auto& s : students) {
        outputByGPA << s.getName() << "\n" << s.getId() << "\n" << s.getGpa() << "\n";
    }
    outputByGPA << endl;

    outputByName.close();
    outputByGPA.close();

    return 0;
}
