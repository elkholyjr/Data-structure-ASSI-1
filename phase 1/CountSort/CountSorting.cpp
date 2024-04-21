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
int CountSort(vector<T> &arr)
{
    int cnt = 0;
    map<T, int> mp;
    for (int i = 0; i < arr.size(); i++)
    {
        mp[arr[i]]++;
    }
    int tot = 0;
    for (auto &i : mp)
    {
        i.second += tot;
        tot = i.second;
    }
    tot = 0;
    for (auto &i : mp)
    {
        swap(i.second, tot);
    }
    vector<T> final(arr.size());
    for (int i = 0; i < arr.size(); i++)
    {
        final[mp[arr[i]]++] = arr[i];
    }

    arr = final;
    return cnt;
}

template <typename T, typename Compare>
int CountSort(vector<T> &arr, Compare comp)
{
    int cnt = 0;
    map<T, int, Compare> mp(comp);
    for (int i = 0; i < arr.size(); i++)
    {
        mp[arr[i]]++;
    }
    int tot = 0;
    for (auto &i : mp)
    {
        i.second += tot;
        tot = i.second;
    }
    tot = 0;
    for (auto &i : mp)
    {
        swap(i.second, tot);
    }
    vector<T> final(arr.size());
    for (int i = 0; i < arr.size(); i++)
    {
        final[mp[arr[i]]++] = arr[i];
    }

    arr = final;
    return cnt;
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
    nameComparisons = CountSort(students);
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
    gpaComparisons = CountSort(students, [](const student &s1, const student &s2) -> bool
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
