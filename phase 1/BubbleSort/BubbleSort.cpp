#include <iostream>
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
    student(int id = 0, string name = "", double gpa = 0.0) : id(id), name(name), gpa(gpa) {}

    int getId() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    double getGpa() const
    {
        return gpa;
    }

    bool operator<(const student& other) const
    {
        return this->name < other.name;
    }
};

template <typename T, typename Compare>
void bubbleSort(vector<T>& arr, int& comparisons, Compare cmp) {
    for (int i = 0; i < arr.size() - 1; i++) {
        for (int j = 0; j < arr.size() - i - 1; j++) {
            if (cmp(arr[j + 1], arr[j])) {
                comparisons++;
                T temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

template <typename T>
void bubbleSort(vector<T>& arr, int& comparisons) {
    for (int i = 0; i < arr.size() - 1; i++) {
        for (int j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j+1] < arr[j]) {
                comparisons++;
                T temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}


int main()
{
    vector<student> students;
    string path = "../students.txt";

    ifstream file(path);
    if (!file)
    {
        cout << "Error opening file." << endl;
        return 1;
    }

    int nameComparisons{ 0 };
    int gpaComparisons{ 0 };

    int numStudents;
    file >> numStudents;
    file.ignore();

    for (int i = 0; i < numStudents; ++i)
    {
        string name, idStr, gpaStr;
        getline(file, name);
        getline(file, idStr);
        getline(file, gpaStr);

        students.emplace_back(stoi(idStr), name, stod(gpaStr));
    }

    ofstream outputByName("SortedByName.txt");
    ofstream outputByGPA("SortedByGPA.txt");

    auto start = high_resolution_clock::now();
    bubbleSort(students, nameComparisons);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    outputByName << "Algorithm: bubble Sort\n";
    outputByName << "Number of comparisons:" << nameComparisons << "\n";
    outputByName << "Running Time: " << duration.count() << " milliseconds\n";
    outputByName << "Sorted by Name:\n";
    for (const auto& s : students)
    {
        outputByName << s.getName() << "\n"
            << s.getId() << "\n"
            << s.getGpa() << "\n";
    }
    outputByName << endl;

    start = high_resolution_clock::now();
    bubbleSort(students, gpaComparisons, [](const student& s1, const student& s2) -> bool
        { return s1.getGpa() < s2.getGpa(); });
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);

    outputByGPA << "Algorithm: bubble Sort\n";
    outputByGPA << "Number of comparisons:" << gpaComparisons << "\n";
    outputByGPA << "Running Time: " << duration.count() << " milliseconds\n";
    outputByGPA << "Sorted by GPA:\n";
    for (const auto& s : students)
    {
        outputByGPA << s.getGpa() << "\n"
            << s.getId() << "\n"
            << s.getName() << "\n";
    }
    outputByGPA << endl;

    outputByName.close();
    outputByGPA.close();
}