#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// Reading data from file
vector<long long> read_data_from_file(const string &filename) {
  vector<long long> data;
  ifstream input_file(filename);
  if (!input_file.is_open()) {
    cerr << "Error. Couldn't open the file: " << filename << "!" << endl;
    return data;
  }

  long long number;
  while (input_file >> number) { // Reading numbers from file
    data.push_back(number);
  }

  input_file.close();
  cout << "Data was successfully collected " << filename << endl;
  return data;
}

// Function to save numbers into file
void write_data_to_file(const string &filename, const vector<long long> &data) {
  ofstream output_file(filename);
  if (!output_file.is_open()) {
    cerr << "Error. Couldn't save numbers file: " << filename << "!" << endl;
    return;
  }

  for (size_t i = 0; i < data.size(); ++i) {
    output_file << data[i];
    if (i < data.size() - 1) {
      output_file << " ";
    }
  }

  output_file.close();
  cout << "Sorted numbers were successfully saved into the file: " << filename
       << endl;
}

// Function for selection sorting
void selection_sort(vector<long long> &data) {
  size_t n = data.size();
  for (size_t i = 0; i < n - 1; ++i) {
    size_t min_index = i;
    for (size_t j = i + 1; j < n; ++j) {
      if (data[j] < data[min_index]) {
        min_index = j;
      }
    }
    if (min_index != i) {
      swap(data[i], data[min_index]);
    }
  }
  cout << "Sorting ended (Selection Sort)." << endl;
}

// Funcktion for hibbard sorting
vector<int> generate_hibbard_sequence(size_t n) {
  vector<int> sequence;
  int k = 1;
  int gap = pow(2, k) - 1;
  while (gap < n) {
    sequence.push_back(gap);
    ++k;
    gap = pow(2, k) - 1;
  }
  reverse(sequence.begin(), sequence.end()); // Reverse the sequence
  return sequence;
}

// Function for shell sorting using hibbard sequence
void shell_sort(vector<long long> &data) {
  size_t n = data.size();
  vector<int> gaps = generate_hibbard_sequence(n);

  for (int gap : gaps) {
    for (size_t i = gap; i < n; ++i) {
      long long temp = data[i];
      size_t j = i;

      // "Gap" based method for insertion sort
      while (j >= gap && data[j - gap] > temp) {
        data[j] = data[j - gap];
        j -= gap;
      }
      data[j] = temp;
    }
  }
  cout << "Sorting ended (Shell Sort)." << endl;
}

int main() {
  string input_filename = "100k.txt";
  string output_filename1 = "selectionSort.txt";
  string output_filename2 = "shellSort.txt";

  vector<long long> data = read_data_from_file(input_filename);
  cout << endl;

  // If there is not data, end the program
  if (data.empty()) {
    cerr << "Klaida: Duomenų nerasta arba failas tuščias." << endl;
    return 1;
  }

  // Start the program and measure sorting time of selection sort
  auto start_time1 = chrono::high_resolution_clock::now();
  selection_sort(data);
  auto end_time1 = chrono::high_resolution_clock::now();

  cout << endl;
  chrono::duration<double> elapsed = end_time1 - start_time1;
  cout << "Selection Sort worked: " << elapsed.count() << " seconds." << endl
       << endl;

  write_data_to_file(output_filename1, data);
  cout << endl;

  data = read_data_from_file(input_filename);
  cout << endl;

  // Start the program and measure sorting time of shell sort
  auto start_time2 = chrono::high_resolution_clock::now();
  shell_sort(data);
  auto end_time2 = chrono::high_resolution_clock::now();

  cout << endl;
  chrono::duration<double> elapsed2 = end_time2 - start_time2;
  cout << "Shell Sort worked: " << elapsed2.count() << " seconds." << endl
       << endl;

  write_data_to_file(output_filename2, data);

  return 0;
}