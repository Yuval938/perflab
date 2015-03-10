/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/*
 * Please fill in the following team struct
   Note this project is designed so we can optionally have
   teams of more than one person but we are not using that
   feature so just put your information in here to be a "team of one"
 */
team_t team = {
    "Project4-8",              /* Team name */

    "Alexander Rice-Reynolds",                 /* First member full name */
    "ricerea@students.wwu.edu",   /* First (and only)  member email address */

    "Benjamin Plotke",                  /* Second member full name (leave blank if none) */
    "benplotke@gmail.com"                    /* Second member email addr (leave blank if none) */

    "Ryan Petrosky"                  /*third member*/
    "petrosr2@students.wwu.edu"
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/*
 * naive_rotate - The naive baseline version of rotate
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst)
{
	int i, j;

	for (i = 0; i < dim; i++)
		for (j = 0; j < dim; j++)
			dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}
char rotate1_descr[] = "rotate with loop unrolled once";
void rotate1(int dim, pixel *src, pixel *dst)
{
	int i, j;
	
	for (i = 0; i < dim; i++){
		for (j = 0; j < dim; j++){
			dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
			j++;
			dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
		}
				
	}	
}
char rotate2_descr[] = "rotate 16 pixel squares at a time to not improve cach hits";
void rotate2(int dim, pixel *src, pixel *dst) {
	int outerColumn, outerRow, innerColumn, innerRow;
	int cachLim = 16;
	for ( outerRow = 0; outerRow < dim; outerRow += cachLim ) {
		for ( outerColumn = 0; outerColumn < dim; outerColumn += cachLim ) {
			int innerRowLim = outerRow + cachLim;
			for ( innerRow = outerRow; innerRow < innerRowLim; innerRow += 1 ) {
				int innerColumnLim = outerColumn + cachLim;
				for ( innerColumn = outerColumn; innerColumn < innerColumnLim; innerColumn += 1 ) {
					dst[RIDX(dim-1-innerColumn, innerRow, dim)] = src[RIDX(innerRow, innerColumn, dim)];
				}
			}
		}
	}
}

char rotate3_descr[] = "rotate 2x2 blocks of 16x16 pixel blocks at a time to not improve cach hits";
void rotate3(int dim, pixel *src, pixel *dst) {
	int blockColumn, blockRow, outerColumn, outerRow, innerColumn, innerRow;
	int cachLim = 16;
	int cachLim2 = 32;
	for ( blockRow = 0; blockRow < dim; blockRow += cachLim2 ) {
		for ( blockColumn = 0; blockColumn < dim; blockColumn += cachLim2 ) {
			int outerRowLim = blockRow + cachLim2;
			for ( outerRow = blockRow; outerRow < outerRowLim; outerRow += cachLim ) {
				int outerColumnLim = blockColumn + cachLim2;
				for ( outerColumn = 0; outerColumn < outerColumnLim; outerColumn += cachLim ) {
					int innerRowLim = outerRow + cachLim;
					for ( innerRow = outerRow; innerRow < innerRowLim; innerRow += 1 ) {
						int innerColumnLim = outerColumn + cachLim;
						for ( innerColumn = outerColumn; innerColumn < innerColumnLim; innerColumn += 1 ) {
							dst[RIDX(dim-1-innerColumn, innerRow, dim)] = src[RIDX(innerRow, innerColumn, dim)];
						}
					}
				}
			}
		}
	}
}

char rotate4_descr[] = "modified rotate 16 pixel squares at a time to not improve cach hits";
void rotate4(int dim, pixel *src, pixel *dst) {
  int outerColumn, outerRow, innerColumn, innerRow;//,innerRowLim, innerColumnLim;
  int cachLim = 8;
  //pixel *d;
  for ( outerRow = 0; outerRow < dim; outerRow += cachLim ) {
    for ( outerColumn = 0; outerColumn < dim; outerColumn += cachLim ) {
      int innerRowLim = outerRow + cachLim;
      for ( innerRow = outerRow; innerRow < innerRowLim; innerRow += 1 ) {
	int innerColumnLim = outerColumn + cachLim;
	//d = &dst[RIDX(outerRow,dim-1,dim)];
	for ( innerColumn = outerColumn; innerColumn < innerColumnLim; innerColumn += 1 ) { 
	  //*d = src[RIDX(innerRow, innerColumn, dim)];
	  //d = d - (dim-1);
	  //*d = src[RIDX(innerRow, innerColumn+1, dim)];
	  //d = d - (dim-1);
	  //dst[RIDX(dim-1-innerColumn, innerRow, dim)] = src[RIDX(innerRow, innerColumn, dim)];
	  //dst[RIDX(dim-2-innerColumn, innerRow, dim)] = src[RIDX(innerRow, innerColumn+1, dim)];
	  //dst[RIDX(dim-3-innerColumn, innerRow, dim)] = src[RIDX(innerRow, innerColumn+2, dim)];
	  //dst[RIDX(dim-4-innerColumn, innerRow, dim)] = src[RIDX(innerRow, innerColumn+3, dim)];
	  //dst[RIDX(dim-5-innerColumn, innerRow, dim)] = src[RIDX(innerRow, innerColumn+4, dim)];
	  //dst[RIDX(dim-6-innerColumn, innerRow, dim)] = src[RIDX(innerRow, innerColumn+5, dim)];
	  //dst[RIDX(dim-7-innerColumn, innerRow, dim)] = src[RIDX(innerRow, innerColumn+6, dim)];
	  //dst[RIDX(dim-8-innerColumn, innerRow, dim)] = src[RIDX(innerRow, innerColumn+7, dim)];
	  //dst[RIDX(dim-9-innerColumn, innerRow, dim)] = src[RIDX(innerRow, innerColumn+8, dim)];
	  //dst[RIDX(dim-10-innerColumn, innerRow, dim)] = src[RIDX(innerRow, innerColumn+9, dim)];
	  //dst[RIDX(dim-11-innerColumn, innerRow, dim)] = src[RIDX(innerRow, innerColumn+10, dim)];
	  //dst[RIDX(dim-12-innerColumn, innerRow, dim)] = src[RIDX(innerRow, innerColumn+11, dim)];
	  //dst[RIDX(dim-13-innerColumn, innerRow, dim)] = src[RIDX(innerRow, innerColumn+12, dim)];
	  //dst[RIDX(dim-14-innerColumn, innerRow, dim)] = src[RIDX(innerRow, innerColumn+13, dim)];
	  //dst[RIDX(dim-15-innerColumn, innerRow, dim)] = src[RIDX(innerRow, innerColumn+14, dim)];
	  //dst[RIDX(dim-16-innerColumn, innerRow, dim)] = src[RIDX(innerRow, innerColumn+15, dim)];
	}
      }
    }
  }
}


char rotate5_descr[] = "modified rotate, block moves down before moving right";
void rotate5(int dim, pixel *src, pixel *dst) {
  int outerColumn, outerRow, innerColumn, innerRow, x;//,y;//,innerRowLim, innerColumnLim;
  int cachLim = 16;
  //pixel *d;
  //for ( outerRow = 0; outerRow < dim; outerRow += cachLim ) {
    for ( outerColumn = 0; outerColumn < dim; outerColumn += cachLim ) {
      for(outerRow = 0; outerRow < dim; outerRow += cachLim ) {
	//int innerRowLim = outerRow + cachLim;
	
      for ( innerRow = outerRow; innerRow < outerRow+cachLim; innerRow += 1 ) {
	//int innerColumnLim = outerColumn + cachLim;
	x = RIDX(innerRow, outerColumn, dim);
      	//y = RIDX(outerColumn, innerRow, dim);
	for ( innerColumn = outerColumn; innerColumn < outerColumn+cachLim; innerColumn += 2 ) { 
	  dst[RIDX(dim-1-innerColumn, innerRow, dim)] = src[x+innerColumn];
	  dst[RIDX(dim-1-innerColumn-1, innerRow, dim)] = src[x+innerColumn+1];

	}
      }
    }
  }
}

char rotate6_descr[] = "32 pixel blocks, code motion on RIDX, unroll inner loop by 4";
void rotate6(int dim, pixel *src, pixel *dst) {

  /*  int i, j, x, y;
  x = RIDX(0, 0, dim);
  for (i = 0; i < dim; i++) {
    y = RIDX(dim-1,i,dim);
    for (j = 0; j < dim; j++) {
      dst[y] = src[x];
      y -= dim;
      x += 1;
    }
  }*/

  int outerColumn, outerRow, innerColumn, innerRow, innerRowLim, innerColumnLim, x;
  int cachLim = 32;
  for( outerRow = 0; outerRow < dim; outerRow += cachLim ) {
    for( outerColumn = 0; outerColumn < dim; outerColumn += cachLim ) {
      //int innerRowLim = outerRow + cachLim;
      innerColumnLim = outerColumn + cachLim;
      for( innerColumn = outerColumn; innerColumn < innerColumnLim; innerColumn += 1 ) {
  //for ( innerRow = outerRow; innerRow < innerRowLim; innerRow += 1 ) {
	//int innerColumnLim = outerColumn + cachLim;
	innerRowLim = outerRow + cachLim;
	x = RIDX(dim-1-innerColumn, outerRow, dim);
	for( innerRow = outerRow; innerRow < innerRowLim; innerRow += 4 ) {
   //for ( innerColumn = outerColumn; innerColumn < innerColumnLim; innerColumn += 1 ) {
	  dst[x] = src[RIDX(innerRow, innerColumn, dim)];
	  dst[x+1] = src[RIDX(innerRow+1, innerColumn, dim)];
	  dst[x+2] = src[RIDX(innerRow+2, innerColumn, dim)];
	  dst[x+3] = src[RIDX(innerRow+3, innerColumn, dim)];
	  x+=4;
	}
      }
    }
  }
}  


/*
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst)
{
    naive_rotate(dim, src, dst);
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_rotate_functions()
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);
    //add_rotate_function(&rotate, rotate_descr);
    //add_rotate_function(&rotate1, rotate1_descr);
    add_rotate_function(&rotate2, rotate2_descr);
	//add_rotate_function(&rotate3, rotate3_descr);
	//add_rotate_function(&rotate4, rotate4_descr);
	//add_rotate_function(&rotate5, rotate5_descr);
    add_rotate_function(&rotate6, rotate6_descr);
	/* ... Register additional test functions here */
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/*
 * initialize_pixel_sum - Initializes all fields of sum to 0
 */
static void initialize_pixel_sum(pixel_sum *sum)
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/*
 * accumulate_sum - Accumulates field values of p in corresponding
 * fields of sum
 */
static void accumulate_sum(pixel_sum *sum, pixel p)
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/*
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum)
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/*
 * avg - Returns averaged pixel value at (i,j)
 */
static pixel avg(int dim, int i, int j, pixel *src)
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++)
	for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++)
	    accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst)
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}

/*
 * smooth - Your current working version of smooth.
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst)
{
    naive_smooth(dim, src, dst);
}


/*********************************************************************
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* ... Register additional test functions here */
}

