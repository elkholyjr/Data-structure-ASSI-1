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
void merge(vector<T> &arr, int l, int m, int r, int &comparisons)
{
    const int n1 = m - l + 1;
    const int n2 = r - m;

    vector<T> L, R;
    for (int i = 0; i < n1; i++)
        L.push_back(arr[l + i]);
    for (int j = 0; j < n2; j++)
        R.push_back(arr[m + 1 + j]);

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] < R[j])
        {
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
        }
        comparisons++;
    }

    while (i < n1)
    {
        arr[k++] = L[i++];
    }

    while (j < n2)
    {
        arr[k++] = R[j++];
    }
}

template <typename T, typename Compare>
void merge(vector<T> &arr, int l, int m, int r, int &comparisons, Compare cmp)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<T> L, R;
    for (int i = 0; i < n1; i++)
        L.push_back(arr[l + i]);
    for (int j = 0; j < n2; j++)
        R.push_back(arr[m + 1 + j]);

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (cmp(L[i], R[j]))
        {
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
        }
        comparisons++;
    }

    while (i < n1)
    {
        arr[k++] = L[i++];
    }

    while (j < n2)
    {
        arr[k++] = R[j++];
    }
}

template <typename T>
void mergeSort(vector<T> &arr, int l, int r, int &comparisons)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m, comparisons);
        mergeSort(arr, m + 1, r, comparisons);
        merge(arr, l, m, r, comparisons);
    }
}

template <typename T, typename Compare>
void mergeSort(vector<T> &arr, int l, int r, int &comparisons, Compare cmp)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, comparisons, cmp);
        mergeSort(arr, m + 1, r, comparisons, cmp);
        merge(arr, l, m, r, comparisons, cmp);
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
    mergeSort(students, 0, students.size() - 1, nameComparisons);
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
    mergeSort(students, 0, students.size() - 1, gpaComparisons, [](const student &s1, const student &s2) -> bool
              { return s1.getGpa() < s2.getGpa(); });
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);

    outputByGPA << "Algorithm: Count Sort\n";
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
