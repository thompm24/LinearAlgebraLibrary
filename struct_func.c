#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix Matrix;
struct Matrix{
  int rows;
  int cols;
  double **data;
  Matrix *Transpose;
};

typedef struct{
  int size;
  double *data;
} Vector;

//Initialising matrices
void Matrix_Create_Empty(Matrix *m, int rows, int cols);
void Matrix_Rand(Matrix *m);
void Matrix_Create_Transpose(Matrix *m);
Matrix *Matrix_Create_Array(double *data, int rows, int cols);

Matrix *Vector_Convert_Matrix(Vector *v);

void Vector_Create_Empty(Vector *v, int size);
void Vector_Create_Rand(Vector *v);
Vector *Vector_Create_Array(double *data, int size);
Matrix *Vector_Create_Transpose(Vector *v);

/*
  Still not finished these:
  Vector *Vector_Product_Dot(Vector *v1, Vector *v2);
  Matrix *Vector_Product_Outer(Vector *v1, Vector *v2);
  Vector *Vector_Transformation(Vector *v, Matrix *m);
*/


//Operations
Matrix *Matrix_Multiply(Matrix *m1, Matrix *m2);

void printMatrix(Matrix *m);

int main(int argc, char *argv)
{
 // Vector *v1 = (Vector *)malloc(sizeof(Vector));
  double a1[4] = {1, 2, 3, 4};
  int row1 = 2;

  Vector *v1 = Vector_Create_Array(a1, 4);
 // Matrix *m1 = (Matrix*)malloc(sizeof(Vector));
  Matrix *m1 = Vector_Convert_Matrix(v1);

  //Matrix *m2 = (Matrix *)malloc(sizeof(Matrix));
  double a2[4] = {5, 6, 7, 8};
  int row2 = 2;

  Vector *v2 = Vector_Create_Array(a1, 4);
  Matrix *m2 = Vector_Convert_Matrix(v2);
  Matrix_Create_Transpose(m2);

  Matrix *m3;
  m3 = Matrix_Multiply(m2->Transpose, m1);

  printMatrix(m3);
}

void printMatrix(Matrix *m)
{
  int i = 0;
  while (i < m->rows)
  {
    int j = 0;
    while (j < m->cols)
    {
      printf("%.2f", m->data[i][j]);
      j++;
      (j == m->cols) ? printf("\n") : printf(" ");
    }
    i++;
  }
}

void Matrix_Create_Empty(Matrix *m, int rows, int cols)
{
  m->rows = rows;
  m->cols = cols;
  m->data = (double **)malloc(rows * sizeof(double *));
  int i = 0;
  while (i < rows)
  {
    m->data[i] = (double *)malloc(cols * sizeof(double));
    i++;
  }
}

void Matrix_Create_Rand(Matrix *m)
{
  int i, j, rows, cols;
  rows = m->rows;
  cols = m->cols;
  i = 0;
  while (i < rows)
  {
    j = 0;
    while (j < cols)
    {
      m->data[i][j] = (double)rand() / RAND_MAX;
      j++;
    }
    i++;
  }
}


void Matrix_Create_Transpose(Matrix *m)
{
  if (m->Transpose != NULL)
  {
    return;
  }
  m->Transpose = (Matrix *)malloc(sizeof(Matrix));
  Matrix_Create_Empty(m->Transpose, m->cols, m->rows);
  int i, j;
  i = 0;
  while (i < m->rows)
  {
    j = 0;
    while (j < m->cols)
    {
      m->Transpose->data[j][i] = m->data[i][j];
      j++;
    }
    i++;
  }
}

void Vector_Create_Empty(Vector *v, int size)
{
  v->size = size;
  v->data = (double *)malloc(size * sizeof(double));
}

void Vector_Create_Rand(Vector *v)
{
  int i, size;
  size = v->size;
  while (i < size)
  {
    v->data[i] = ((double)rand() / RAND_MAX) / (double)rand(); //populate bias with random numbers which can be greater than 0
    i++;
  }
}


Matrix *Vector_Convert_Matrix(Vector *v)
{
  int rows = v->size;
  Matrix *m = (Matrix *)malloc(sizeof(Matrix));
  Matrix_Create_Empty(m, rows, 1);
  int i = 0;
  while (i < rows)
  {
    m->data[i][0] = v->data[i];
    i++;
  }
  return m;
} 


Vector *Vector_Create_Array(double *data, int size) {
  Vector *v = (Vector *)malloc(sizeof(Vector));
  Vector_Create_Empty(v, size);
  int i = 0;
  while (i < (size))
  {
    v->data[i] = data[i];
    i++;
  }
  return v;
}





Matrix *Matrix_Multiply(Matrix *m1, Matrix *m2)
{
  int i, j, k, sumRowColij, rows, cols, rows2cols1;
  Matrix *m3 = (Matrix *)malloc(sizeof(Matrix));
  if (m1->cols != m2->rows)
  {
    printf("ColLen of m1(%d) != RowLen of m2(%d)", m1->cols, m2->rows);
    Matrix_Create_Empty(m3, 1, 1);
    return m3;
  }
  Matrix_Create_Empty(m3, m1->rows, m2->cols);
  rows = m1->rows;
  cols = m2->cols;
  rows2cols1 = m2->rows;
  i = 0;
  while (i < rows)
  {
    j = 0;
    while (j < cols)
    {
      sumRowColij = 0;
      k = 0;
      while (k < rows2cols1)
      {
        sumRowColij = sumRowColij + (m1->data[i][k] * m2->data[k][j]);
        k++;
      }
      m3->data[i][j] = sumRowColij;
      j++;
    }
    i++;
  }
  return m3;
}


Matrix *Matrix_Create_Array(double *data, int rows, int cols) {
  Matrix *m = (Matrix *)malloc(sizeof(Matrix));
  Matrix_Create_Empty(m, rows, cols);
  int i = 0;
  while (i < (rows * cols))
  {
    m->data[i / cols][i % cols] = data[i];
    i++;
  }
  return m;
}


