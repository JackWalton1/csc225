/*
 * Defines functions for manipulating square integer matrices.
 * CSC 225, Assignment 7
 * Given code, Fall '20
 */

#include "matrix.h"

/* matscl: Multiplies each element of a matrix by a scalar. */
void matscl(int *mat, unsigned int n, int c) {
    /* TODO: Complete this function, given:
     *  mat - A pointer to the first element in a multidimensional array
     *  n   - The height and width of the matrix
     *  c   - The constant scalar
     * ...multiply each element in "mat" by "c". */
    int i;
    for (i = 0; i < n * n; i++){
        *mat = *mat * c;
        mat++;
    }
}

/* matpscl: Multiplies each element of a matrix by a scalar. */
void matpscl(int **mat, unsigned int n, int c) {
    /* TODO: Complete this function, given:
     *  mat - An array of pointers to arrays of integers
     *  n   - The height and width of the matrix
     *  c   - The constant scalar
     * ...multiply each element in "mat" by "c". */
    int row, col;
    for (row = 0; row < n ; row++){
        for (col = 0; col < n ; col++){
            mat[row][col] = mat[row][col] * c;
        }
    }
}

/* mattrn: Transposes a matrix about its diagonal, in-place. */
void mattrn(int *mat, unsigned int n) {
    /* TODO: Complete this function, given:
     *  mat - A pointer to the first element in a multidimensional array
     *  n   - The height and width of the matrix
     * ...transpose "mat" about its diagonal. */
    int row, col, newi, i, tmp, mult1, mult2;
    mult1 = n - 1;
    for (i = 0; i < n * n; i++){
        row = i/n;
        col = i%n;
        if (col > row){
            mult2 = col - row;
            newi = mult1 * mult2;
            tmp = *mat;
            *mat = *(mat + newi);
            *(mat + newi) = tmp;
            }
        mat++;
    }
}

/* matptrn: Transposes a matrix about its diagonal, in-place. */
void matptrn(int **mat, unsigned int n) {
    /* TODO: Complete this function, given:
     *  mat - An array of pointers to arrays of integers
     *  n   - The height and width of the matrix
     * ...transpose "mat" about its diagonal. */
    int row, col, tmp;
    for (row = 0; row < n; row++){
        for (col = 0; col < n; col++){
            if (col > row){
                tmp = mat[row][col];
                mat[row][col] = mat[col][row];
                mat[col][row] = tmp;
            }
        }
    }
}

/* matadd: Adds two matrices, placing their sum into a third. */
void matadd(int *mata, int *matb, int *matc, unsigned int n) {
    /* TODO: Complete this function, given:
     *  mata - A pointer to the first element in a multidimensional array
     *  matb - A pointer to the first element in a multidimensional array
     *  matc - A pointer to the first element in a multidimensional array
     *  n    - The height and width of the matrices
     * ...compute "matc = mata + matb". */
    int i, add1, add2;
    for (i = 0; i < n * n; i++){
        add1 = *mata;
        add2 = *matb;
        *matc = add1 + add2;
        mata++;
        matb++;
        matc++;
    }
   
}

/* matpadd: Adds two matrices, placing their sum into a third. */
void matpadd(int **mata, int **matb, int **matc, unsigned int n) {
    /* TODO: Complete this function, given:
     *  mata - An array of pointers to arrays of integers
     *  matb - An array of pointers to arrays of integers
     *  matc - An array of pointers to arrays of integers
     *  n    - The height and width of the matrices
     * ...compute "matc = mata + matb". */
    int row, col, add1, add2;
    for (row = 0; row < n ; row++){
        for (col = 0; col < n ; col++){
            add1 = mata[row][col];
            add2 = matb[row][col];
            matc[row][col] = add1 + add2;
        }
    }
}

/* matmul: Multiplies two matrices, placing their product into a third. */
void matmul(int *mata, int *matb, int *matc, unsigned int n) {
    /* TODO: Complete this function, given:
     *  mata - A pointer to the first element in a multidimensional array
     *  matb - A pointer to the first element in a multidimensional array
     *  matc - A pointer to the first element in a multidimensional array
     *  n    - The height and width of the matrices
     * ...compute "matc = mata * matb". */
    int i, row, col, sum, mult1, mult2;
    for (row = 0; row < n; row++){
        for (col = 0; col < n; col++){
            sum = 0;

            /* Multiply row variable (and maybe second variable "i"
            * if used in matb as a row variable)
            * by the size "n" of the table to get to the correct index
            * of mata and matb */
            for (i = 0; i < n; i++){
                mult1 = *((mata + row * n) + i);
                mult2 = *((matb + i * n) + col);
                sum += mult1 * mult2;
            }
            /* Store sum of product of mata's row and
             * matb's column to matc's cells. (Using the same
             * method of multiplying row variable by size "n") */
            *((matc + row * n) + col) = sum;
        }
    }
}

/* matpmul: Multiplies two matrices, placing their product into a third. */
void matpmul(int **mata, int **matb, int **matc, unsigned int n) {
    /* TODO: Complete this function, given:
     *  mata - An array of pointers to arrays of integers
     *  matb - An array of pointers to arrays of integers
     *  matc - An array of pointers to arrays of integers
     *  n    - The height and width of the matrices
     * ...compute "matc = mata * matb". */
    int row, col, i;

    /* This nested for loop just clears matc */
    for (row = 0; row< n; row++){
        for (col = 0; col < n; col++){
            matc[row][col] = 0;
        }
    }

    /* Variable "i" is interchangeable as row or col as need be */
    for (row = 0; row < n; row++) {
        for (col = 0; col < n; col++) {
            for (i = 0; i < n; i++) {
                matc[row][col] += mata[row][i] * matb[i][col];
            }
        }
    }
}
