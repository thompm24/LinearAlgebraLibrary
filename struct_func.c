#include <stdio.h>
#include <stdlib.h>
#include "math.c"


typedef struct Matrix Matrix;
typedef struct Vector Vector;
struct Matrix
{
  int rows;
  int cols;
  double **data;
  Matrix *Transpose;
  double determinant;
};

struct Vector
{
  int size;
  double *data;
  double Norm;
  Vector *Normalise;
  Matrix *Transpose;
} ;



//                        Function Definitions




//	Initialising Matrices


//Initialise empty matrix
void Matrix_Create_Empty(Matrix *m, int rows, int cols);

//Initialise matrix of random values
void Matrix_Rand(Matrix *m);

//Initialise matrix from array
Matrix *Matrix_Create_Array(double *data, int rows, int cols);

//Allocates memory and  creates transpose attribute of and matrix;
void Matrix_Generate_Transpose(Matrix *m);

void Matrix_Generate_Determinant(Matrix *m);

//Initialise matrix from an array Matrix *Matrix_Create_Array(double *data, int rows, int cols);

//Convert vector to a v-size x 1 matrix
Matrix *Vector_Convert_Matrix(Vector *v);

//Convert vector to a 1 x v->size matrix


//	Initialising Vectors


//Initialise empty vector
void Vector_Create_Empty(Vector *v, int size);

//Initialise vector of random values
void Vector_Create_Rand(Vector *v);

//Initialise vector from array
Vector *Vector_Create_Array(double *data, int size);

//Assign v->Norm
void Vector_Generate_Norm(Vector *v);

void Vector_Generate_Normalise(Vector *v);

void Vector_Generate_Tranpose(Vector *v);

//	Matrix Operations


//Multiply 2 matrices
Matrix *Matrix_Multiply(Matrix *m1, Matrix *m2);

//Add 2 matrices
Matrix *Matrix_Add(Matrix *m1, Matrix *m2);

//Scale matric by n
Matrix *Matrix_Scale(Matrix *m, double n);

//Transform a vector with a matrix
Matrix *Matrix_Transform(Matrix *m, Vector *v);

//Print matrix line-by-line
void printMatrix(Matrix *);


//	Vector Operations


//Add 2 vectors
Vector *Vector_Add(Vector *v1, Vector *v2);

//Scalle a vector by n
Vector *Vector_Scale(Vector *v, double n);

//Get dot product of 2 vectors
double Vector_Product_Dot(Vector *v1, Vector *v2);

//Get outer product of 2 vectors
Matrix *Vector_Product_Outer(Vector *v1, Vector *v2);

//Print vector
void printVector(Vector *v);




//                        Function Definitions




void printVector(Vector *v)
{
  int i = 0;
  int size = v->size;
  while (i < size)
  {
    printf("%.2f", v->data[i]);
    i++;
    (i == size) ? printf("\n") : printf(" ");
  }
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

Matrix *Vector_Transform_Matrix(Matrix *m, Vector *v)
{
  Matrix *mv = Vector_Convert_Matrix(v);
  return Matrix_Multiply(m, mv);
}

double Vector_Product_Dot(Vector *v1, Vector *v2)
{
  Matrix *m1 = Vector_Convert_Matrix(v1);
  Matrix_Generate_Transpose(m1);
  Matrix *m3 = Vector_Transform_Matrix(m1->Transpose, v2);
  return m3->data[0][0];
}
Matrix *Vector_Product_Outer(Vector *v1, Vector *v2)
{
  Matrix *m1 = Vector_Convert_Matrix(v1);
  Matrix *m2 = Vector_Convert_Matrix(v2);
  Matrix_Generate_Transpose(m2);
  return Matrix_Multiply(m1, m2->Transpose);
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


void Matrix_Generate_Transpose(Matrix *m)
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

Matrix *Matrix_Add(Matrix *m1, Matrix *m2)
{
  int rows = m1->rows;
  int cols = m1->cols;

  if (rows != m2->rows || cols != m2->cols)
  {
    fprintf(stderr, "Failed matrix addition, matrices do not share dimensions");
    printMatrix(m1);
    printMatrix(m2);
    return NULL;
  }
  Matrix *m3 = (Matrix *)malloc(sizeof(Matrix));
  if (m3 == NULL)
  {
    perror("Failed to allocate memory\n");
    return NULL;
  }
  Matrix_Create_Empty(m3, rows, cols);

  int i = 0;
  while (i < rows)
  {
    int j = 0;
    while (j < cols)
    {
      m3->data[i][j] = m1->data[i][j] + m2->data[i][j];
      j++;
    }
    i++;
  }
  return m3;
}

Vector *Vector_Add(Vector *v1, Vector *v2)
{
  int size = v1->size;
  Vector *v3 = (Vector *)malloc(sizeof(Vector));
  if (v3 == NULL)
  {
    perror("Failed to allocate memory\n");
    return NULL;
  }
  Vector_Create_Empty(v3, size);
  int i = 0;
  while (i < size)
  {
    v3->data[i] = v1->data[i] + v2->data[i];
    i++;
  }
  return v3;
}

void Vector_Generate_Norm(Vector *v)
{
  int size = v->size;
  double sumOfSquares = Vector_Product_Dot(v, v);
  v->Norm = sqrtd(sumOfSquares);
}

void Vector_Generate_Transpose(Vector *v)
{
  v->Transpose = Matrix_Create_Array(v->data, 1, v->size);
}

Matrix *Matrix_Transform(Matrix *m, Vector *v)
{
  Matrix *mv = Vector_Convert_Matrix(v);
  return Matrix_Multiply(m, mv);
}
