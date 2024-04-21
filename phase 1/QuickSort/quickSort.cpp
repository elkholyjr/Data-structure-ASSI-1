#include <iostream>
#include <fstream>
#include <vector>
#include <map>
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

    bool operator<(const student &other) const
    {
        return this->name < other.name;
    }
};

template <typename T>
int partition(vector<T> &arr, int low, int high, int &comparisons)
{
    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
        comparisons++;
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

template <typename T, typename Compare>
int partition(vector<T> &arr, int low, int high, int &comparisons, Compare compare)
{
    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (compare(arr[j], pivot))
        {
            i++;
            swap(arr[i], arr[j]);
        }
        comparisons++;
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

template <typename T>
void quickSort(vector<T> &arr, int low, int high, int &comparisons)
{
    if (low < high)
    {
        int pi = partition(arr, low, high, comparisons);

        quickSort(arr, low, pi - 1, comparisons);
        quickSort(arr, pi + 1, high, comparisons);
    }
}

template <typename T, typename Compare>
void quickSort(vector<T> &arr, int low, int high, int &comparisons, Compare compare)
{
    if (low < high)
    {
        int pi = partition(arr, low, high, comparisons, compare);

        quickSort(arr, low, pi - 1, comparisons, compare);
        quickSort(arr, pi + 1, high, comparisons, compare);
    }
}

int main()
{
    vector<student> students;

    ifstream file("../students.txt");
    if (!file)
    {
        cout << "Error opening file." << endl;
        return 1;
    }

    int nameComparisons{0};
    int gpaComparisons{0};

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
    // Sorting by name || insertion sort
    quickSort(students, 0, students.size() - 1, nameComparisons);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    outputByName << "Algorithm: Count Sort\n";
    outputByName << "Number of comparisons:" << nameComparisons << "\n";
    outputByName << "Running Time: " << duration.count() << " milliseconds\n";
    outputByName << "Sorted by Name:\n";
    for (const auto &s : students)
    {
        outputByName << s.getName() << "\n"
                     << s.getId() << "\n"
                     << s.getGpa() << "\n";
    }
    outputByName << endl;

    start = high_resolution_clock::now();
    // Sorting by GPA || insertion sort
    quickSort(students, 0, students.size() - 1, gpaComparisons, [](const student &s1, const student &s2) -> bool
              { return s1.getGpa() < s2.getGpa(); });
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);

    outputByGPA << "Algorithm: Quick Sort\n";
    outputByGPA << "Number of comparisons:" << gpaComparisons << "\n";
    outputByGPA << "Running Time: " << duration.count() << " milliseconds\n";
    outputByGPA << "Sorted by GPA:\n";
    for (const auto &s : students)
    {
        outputByGPA << s.getName() << "\n"
                    << s.getId() << "\n"
                    << s.getGpa() << "\n";
    }
    outputByGPA << endl;

    outputByName.close();
    outputByGPA.close();

    return 0;
}
