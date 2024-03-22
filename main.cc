#include <fstream>
#include <iostream>
#include <strings.h>
#include <stdio.h>
using namespace std;

// Print matrix from given size
void print_matrix(int** matrix, int size) {
  // Go over each element and print given element
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      cout.width(6);
      cout << left << *(*(matrix + i) + j);
    }
    cout << endl;
  }
}

// Mallocs and gets new matrix from in file
int** get_matrix(ifstream &in_file, int size) {
  int** matrix = (int **) malloc(sizeof(int*) * size);
  char char_buff[10]; // Buffer for character
  
  // Traverse file and add each row to matrix
  for (int i = 0; i < size; i++) {
    int* matrix_row = (int *) malloc(sizeof(int) * size);
    for (int j = 0; j < size; j++) {
      // Flush buffer
      bzero(char_buff, 10);
      in_file >> char_buff;
      *(matrix_row + j) = stoi(char_buff);
    }

    *(matrix + i) = matrix_row;
  }

  return matrix;
}

// Destroy matrix via free
void destroy_matrix(int** matrix, int size) {
  for (int i = 0; i < size; i++) {
    free(*(matrix + i));
  }

  free(matrix);
}

// Make empty matrix
int** make_empty_matrix(int size) {
  int** matrix = (int **) malloc(sizeof(int*) * size);
  for (int i = 0; i < size; i++) {
    int* matrix_row = (int *) malloc(sizeof(int) * size);
    *(matrix + i) = matrix_row;
  }
  return matrix;
}

// Add two matricies
int** add_matrix(int** m1, int** m2, int size) {
  int** matrix = make_empty_matrix(size);

  for (int i = 0; i < size; i++) 
    for (int j = 0; j < size; j++) 
      *(*(matrix + i) + j) = *(*(m1 + i) + j) + *(*(m2 + i) + j);

  return matrix;
}

// Multiply two matricies
int** mult_matrix(int** m1, int** m2, int size) {
  int** matrix = make_empty_matrix(size);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      *(*(matrix + i) + j) = 0;
      for (int k = 0; k < size; k++) {
	*(*(matrix + i) + j) += *(*(m1 + i) + k) * *(*(m2 + k) + j);
      }
    }
  }

  return matrix;
}

// Subtract two matricies
int** sub_matrix(int** m1, int** m2, int size) {
  int** matrix = make_empty_matrix(size);

  for (int i = 0; i < size; i++) 
    for (int j = 0; j < size; j++) 
      *(*(matrix + i) + j) = *(*(m1 + i) + j) - *(*(m2 + i) + j);

  return matrix;
}

// Update value at position ij with value a
void update_matrix(int** m, int i, int j, int a, int size) {
  // Check if index is outside bounds
  if ((i > size) || (i <= 0) || (j > size) || (j <= 0)) {
    cout << "ERROR: Index out of range" << endl;
  } else {
  *(*(m + i - 1) + j - 1) = a;
  }
}

// Get the maximum value in the matrix
int max_value_matrix(int ** m, int size) {
  int max = 0;

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      // Check if element is bigger and make max if so
      int val = *(*(m + i) + j);
      if (val > max) {
	max = val;
      }
    }
  }

  return max;
}

// Transpose matrix
int** transpose_matrix(int** m, int size) {
  int** matrix = make_empty_matrix(size);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      *(*(matrix + i) + j) = *(*(m + j) + i);
    }
  }

  return matrix;
}

int main() {
  // Character buffer for reading lines of text
  char data[100];
  
  // Open file for reading
  ifstream in_file;
  in_file.open("matrix_input.txt");

  // Get size of array
  in_file >> data;
  int array_size = stoi(data);
  
  // Get matrix
  int** m1 = get_matrix(in_file, array_size);
  int** m2 = get_matrix(in_file, array_size);
  in_file.close();

  // Print matrix
  cout << "Matrix 1: " << endl;
  print_matrix(m1, array_size);
  cout << "\nMatrix 2: " << endl;
  print_matrix(m2, array_size);

  // Add matrix
  int** add_m = add_matrix(m1, m2, array_size);
  cout << "\nResult of addition: " << endl;
  print_matrix(add_m, array_size);
  destroy_matrix(add_m, array_size);

  // Multiply matrix
  int** mul_m = mult_matrix(m1, m2, array_size);
  cout << "\nResult of multiplication: " << endl;
  print_matrix(mul_m, array_size);
  destroy_matrix(mul_m, array_size);

  // Subtract matrix
  int** sub_m = sub_matrix(m2, m1, array_size);
  cout << "\nResult of subtraction: " << endl;
  print_matrix(sub_m, array_size);
  destroy_matrix(sub_m, array_size);

  // Update first entry in matrix to be 2
  update_matrix(m1, 1, 1, 2, 3);
  cout << "\nResult of updating element element 1, 1 to be 2: " << endl;
  print_matrix(m1, array_size);

  // Get and print max value of matrix 1
  int max_value = max_value_matrix(m1, array_size);
  cout << "\nMaximum value for Matrix 1 is: " << max_value << endl;

  // Tranpose and print matrix 1
  int** t_matrix = transpose_matrix(m1, array_size);
  cout << "\n Transpose of Matrix 1: " << endl;
  print_matrix(t_matrix, array_size);
  destroy_matrix(t_matrix, array_size);

  // Destroy matrix
  destroy_matrix(m1, array_size);
  destroy_matrix(m2, array_size);
}

