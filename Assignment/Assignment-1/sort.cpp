#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "sort.h"
using namespace std;

int ivector_length(int* v, int n)
{
  int sum;

  sum = 0;
  for (int i = 0; i < n; i++)
    sum += (v[i] < 0) ? -v[i] : v[i];

  return sum;
}

/*
 * insertion sort
 */
void insertion_sort(int** A, int n, int l, int r)
{ 
  int i;
  int* key;

  for (int j = l+1; j <= r; j++)
  {
    key = A[j];
    i = j - 1;

  while ((i >= l) && (ivector_length(A[i], n) > ivector_length(key, n)))
  {
    A[i+1] = A[i];
    i = i - 1;
  }

    A[i+1] = key;
  }
}


/*
*   TO IMPLEMENT: Improved Insertion Sort for problem 1.
*/
void insertion_sort_im(int **A, int n, int l, int r)
{
  int i, *key, tempKey;
  int * precomputesLengthVector;
  precomputesLengthVector = new int [r-l+1];
  for(int i = 0; i<=r; i++)  //precomputes length before sort
  {
    precomputesLengthVector[i] = ivector_length(A[i], n);
  }
  for (int j = l+1; j<=r; j++)
  {
    key = A[j];
    tempKey = precomputesLengthVector[j];
    i = j-1;
    while((i >= l) && (precomputesLengthVector[i] > tempKey))
    {
      A[i+1] = A[i];
      precomputesLengthVector[i+1] = precomputesLengthVector[i];
      i = i - 1;
    }
    A[i+1] = key;
    precomputesLengthVector[i+1] = tempKey;
  }
  delete precomputesLengthVector; //release
}

/*
*   TO IMPLEMENT: Improved Merge Sort for problem 2.
*/
void merge_sort_rec(int **A, int **tempVector, int Left, int Right, int n)
{
  if (Left >= Right)
  {
    return;
  }
  int temp = Left;
  int mid = ((Right - Left) / 2) + Left;
  int Left1 = Left;
  int Right1 = mid;
  int Left2 = mid + 1;
  int Right2 = Right;
  merge_sort_rec(A, tempVector, Left1, Right1, n);
  merge_sort_rec(A, tempVector, Left2, Right2, n);
  while (Left1 <= Right1 && Left2 <= Right2)
  {
    int sum1 = ivector_length(A[Left1], n);
    int sum2 = ivector_length(A[Left2], n);
    //check result
    //cout << "ALeft1: " << *A[Left1] <<" and ALeft2: " << *A[Left2] << endl;
    //cout << "sum1: " << sum1 <<" and sum2: " << sum2 << endl;
    if (sum1 < sum2)
    {
      tempVector[temp++] = A[Left1++];
    }
    else
    {
      tempVector[temp++] = A[Left2++];
    }
  }
  //check result
  //int o = 0;
  //for(o = 0; o < m; o++)
  //{
    //cout << "tempVector[o]: " << *tempVector[o] << endl;
  //}
  while (Left1 <= Right1)
  {
    tempVector[temp++] = A[Left1++];
  }
  while (Left2 <= Right2)
  {
    tempVector[temp++] = A[Left2++];
  }
  for (temp = Left; temp <= Right; temp++)
  {
    A[temp] = tempVector[temp];
  }
}

void merge_sort(int **A, int n, int l, int r)
{
  int **tempVector;
  tempVector = new int *[r + 1];
  for (int i = 0; i < r + 1; i++)
  {
    tempVector[i] = new int[n];
  }
  merge_sort_rec(A, tempVector, l, r, n);
  delete tempVector; //release
}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */
bool check_sorted(int** A, int n, int l, int r)
{
  for (int i = l+1; i <= r; i++)
    if (ivector_length(A[i-1], n) > ivector_length(A[i], n))
      return false;
  return true;
}


/*
 * generate sorted/reverse/random arrays of type hw1type
 */
int** create_ivector(int n, int m)
{
  int** iv_array;

  iv_array = new int*[m];
  for (int i = 0; i < m; i++)
    iv_array[i] = new int[n];

  return iv_array;
}

void remove_ivector(int** iv_array, int m)
{
  for (int i = 0; i < m; i++)
    delete[] iv_array[i];
  delete[] iv_array;
}

int** create_sorted_ivector(int n, int m)
{
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = (i+j)/n;

  return iv_array;
}

int** create_reverse_sorted_ivector(int n, int m)
{
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = ((m-i)+j)/n;

  return iv_array;
}

int** create_random_ivector(int n, int m, bool small)
{
  random_generator rg;
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      {
	rg >> iv_array[i][j];
	if (small)
	  iv_array[i][j] %= 100;
	else
	  iv_array[i][j] %= 65536;
      }

  return iv_array;
}

