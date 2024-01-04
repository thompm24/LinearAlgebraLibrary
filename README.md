
This is my linear algebra library written in C, designed for educational and development purposes. It provides functionalities for matrix and vector operations, ideal for students, educators, and developers interested in mathematics and computer science.
This repository also contains my own math.c file which I am using for all mathematical function not already in stdlib.h.

Structures:
Structures include:

    struct Matrix
    {
      int rows;
      int cols;
      double **data;
      Matrix *Transpose;
      double Determinant;
      double *Norm;
      Matrix *Unit;
    };

    struct Vector
    {
      int size;
      double *data;
      double Norm;
      Vector *Unit;
      Matrix *Transpose;
    };

Structure attributes can be generated when necessary:

    void Matrix_Create_Empty(Matrix *m, int rows, int cols);
    void Matrix_Create_Rand(Matrix *m, int rows, int cols);
    void Matrix_Generate_Transpose(Matrix *m);
    void Matrix_Generate_Norm(Matrix *m);
    void Matrix_Generate_Unit(Matrix *m);
    void Matrix_Generate_Determinant(Matrix *m);
    void Matrix_Copy(Matrix *src, Matrix *dest);

    void Vector_Create_Empty(Vector *v, int size);
    void Vector_Create_Rand(Vector *v, int size);
    void Vector_Generate_Norm(Vector *v);
    void Vector_Generate_Unit(Vector *v);
    void Vector_Generate_Transpose(Vector *v);


Matrix Operations:

    Support for basic matrix operations such as:

      Addition           Matrix *Matrix_Add(Matrix *m1, Matrix *m2);
                      
      Scaling            Matrix *Matrix_Scale(Matrix *m, double n);

      Multiplication     Matrix *Matrix_Multiply(Matrix *m1, Matrix *m2);

      Determinant        double Matrix_Determinant(Matrix *m);

      ReLU               Matrix *Matrix_ReLU(Matrix *m);

      Pairwise Multiple  Matrix *Matrix_Pairwise_Multiplication(Matrix *m1, Matrix  *m2);

      Create from Array  Matrix *Matrix_Create_Array(double *data, int rows, int cols);

      Convert to Array   double *Matrix_Flatten(Matrix *m);

      Save to bin file   void Matrix_Save(Matrix *m, char *filename);

      Load from bin file Matrix *Matrix_Create_Bin(char *filename);
  
    In progress:
      Inversion
      Eigenvalues and eigenvectors
      Reduced Row Echelon Form

Vector Operations:

    Support for basic vector operations such as:

      Addition           Vector *Vector_Add(Vector *v1, Vector *v2);

      Scaling            Vector *Vector_Scale(Vector *v1, Vector *v2);

      Inner Product      double *Vector_Product_Dot(Vector *v1, Vector *v2);

      Outer Product      Matrix *Vector_Product_Outer(Vector *v1, Vector *v2);

      Create from Array  Vector *Vector_Create_Array(double *data, int size);
      
      Compare Spans      int Vector_Compare_Span(Vector *v1, Vector *v2);




    In progress: 
      Angle between 2 vectors
      Projection
      Distance between 2 vectors
      If 2 vectors are orthogonal



To use struct_func in your project, simply include the header file in your C source code:
#include "struct_func.c"
