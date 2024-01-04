#include "LinAlg.c"

#define H 0.001
#define LR 5
#define EPS 0.001

typedef struct NN NN;
struct NN
{
  int layers;
  Matrix **W;
  Matrix **B;
};



NN *NN_Load_Bin(char *filename);
Matrix *Feed_Forward(Matrix *a, Matrix *w, Matrix *b);
Matrix *Backwards_Prop(NN *nn, Matrix *a, Matrix *expected);

void Matrix_Append_Bin(Matrix *m, FILE *fptr);


void ReLU(Matrix *m)
{
  int i = 0;  
  while (i < m->rows)
  {
    int j = 0;
    while (j < m->cols)
    {
      if (m->data[i][j] < 0)
      {
        m->data[i][j] = 0;
      }
      j++;
    }
    i++;
  }
}

Matrix *Feed_Forward(Matrix *a, Matrix *w, Matrix *b)
{
//  printf("a:\n");
//  printMatrix(a);
//  printf("w:\n");
//  printMatrix(w);
  Matrix *wa = Matrix_Multiply(w, a);
//  printf("wa:\n");
//  printMatrix(wa);
  Matrix *waPlusB = Matrix_Add(wa, b);
//  printf("wa+b:\n");
//  printMatrix(waPlusB);
  ReLU(waPlusB);
//  printf("ReLU:\n");
//  printMatrix(waPlusB);
  Matrix_Free(wa);
  return waPlusB;
}

double cost(NN *nn, Matrix *a, Matrix *expected)
{
  int i = 0;
  Matrix *a0 = (Matrix *)malloc(sizeof(Matrix));
  Matrix_Copy(a, a0);
  while (i < nn->layers)
  {
    a0 = Feed_Forward(a0, nn->W[i], nn->B[i]);
    i++;
  }

  Matrix *d = Matrix_Subtract(a0, expected);
  Matrix_Free(a0);
  double sumOfSquares = 0;
  for (int i = 0; i < d->rows; i++) {
    for (int j = 0; j < d->cols; j++) {
      sumOfSquares += (d->data[i][j] * d->data[i][j]);
    }
  }
  Matrix_Free(d);
  
  return sumOfSquares/d->rows;
}

NN *NN_Load_Bin(char *filename)
{
  FILE *fptr = fopen(filename, "rb");
  if (fptr == NULL)
  {
    printf("Could not open file :(\n");
  }
  
  NN *nn = (NN*)malloc(sizeof(NN));


  int layers;
  fread(&layers, sizeof(int), 1, fptr);

  nn->layers = layers;

  nn->W = (Matrix **)malloc(layers * sizeof(Matrix *));
  nn->B = (Matrix **)malloc(layers * sizeof(Matrix *));



  int i = 0;
  while (i < nn->layers)
  {
    int rowsW, colsW, rowsB, colsB;
    fread(&rowsW, sizeof(int), 1, fptr);
    fread(&colsW, sizeof(int), 1, fptr);

    double *arrW = (double *)calloc(rowsW *colsW, sizeof(double));
    fread(arrW, sizeof(double), rowsW *colsW, fptr);

    nn->W[i] = Matrix_Create_Array(arrW, rowsW, colsW);

    fread(&rowsB, sizeof(int), 1, fptr);
    fread(&colsB, sizeof(int), 1, fptr);

    double *arrB = (double *)calloc(rowsB, sizeof(double));
    fread(arrB, sizeof(double), rowsB, fptr);

    nn->B[i] = Matrix_Create_Array(arrB, rowsB, 1);
    i++;
  }
  fclose(fptr);
  return nn;
}

void NN_Save_Bin(NN *nn, char *filename)
{
  FILE *fptr = fopen(filename, "wb");  // Open file for writing in binary mode
  if (fptr == NULL)
  {
      printf("Could not open file for writing :(\n");
      return;  // Exit the function if file opening failed
  }

  fwrite(&nn->layers, sizeof(int), 1, fptr);

  int i = 0;
  while (i < nn->layers)
  {
    Matrix_Append_Bin(nn->W[i], fptr);
    Matrix_Append_Bin(nn->B[i], fptr);
    i++;
  }
  fclose(fptr);  // Close the file
}


void Matrix_Append_Bin(Matrix *m, FILE *fptr)
{
  double *data = Matrix_Flatten(m);

  int rows = m->rows;
  int cols = m->cols;
  fwrite(&rows, sizeof(int), 1, fptr);
  fwrite(&cols, sizeof(int), 1, fptr);
  fwrite(data, sizeof(double), rows * cols, fptr);

  free(data);
}

void NN_Copy(NN *src, NN *dest)
{
  dest->layers = src->layers;
  dest->W = (Matrix**)malloc(dest->layers * sizeof(Matrix*));
  dest->B = (Matrix**)malloc(dest->layers * sizeof(Matrix*));

  int i = 0;
  while (i < dest->layers)
  {
    dest->W[i] = (Matrix *)malloc(sizeof(Matrix));
    dest->B[i] = (Matrix *)malloc(sizeof(Matrix));
    Matrix_Copy(src->W[i], dest->W[i]);
    Matrix_Copy(src->B[i], dest->B[i]);
    i++;
  }
}



void Gradient_Descent(NN *nn, Matrix *input, Matrix *expected)
{
  NN *copy = (NN*)malloc(sizeof(NN));
  NN_Copy(nn, copy);

  double priorCost, newCost, original;

  priorCost = cost(copy, input, expected);
  int i = 0;
  while (i < nn->layers)
  {
    int j = 0;
    while (j < nn->B[i]->rows)
    {
      original = nn->B[i]->data[j][0];
      
      nn->B[i]->data[j][0] = original + EPS;
      newCost = cost(nn, input, expected);

      if (newCost > priorCost)
      {
        nn->B[i]->data[j][0] = original - EPS;
        newCost = cost(nn, input, expected);
      }
      if (newCost > priorCost)
      {
        nn->B[i]->data[j][0] = original;
      }
      j++;
    }
    j = 0;
    while (j < nn->W[i]->rows)
    {
      int k = 0;
      while (k < nn->W[i]->cols)
      {
        original = nn->W[i]->data[j][k];

        nn->W[i]->data[j][k] = original + EPS;
        newCost = cost(nn, input, expected);

        if (newCost > priorCost)
        {
          nn->W[i]->data[j][k] = original - EPS;
          newCost = cost(nn, input, expected);
        }
        if (newCost > priorCost)
        {
          nn->W[i]->data[j][k] = original;
        }
        k++;
      }
      j++;
    }
    i++;
  }
}
