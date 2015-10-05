/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * ECE454 Students: 
 * Please fill in the following team struct 
 */
team_t team = {
    "TeamName",              /* Team name */

    "student1",     /* First member full name */
    "student1@ecf.utoronto.ca",  /* First member email address */

    "",                   /* Second member full name (leave blank if none) */
    ""                    /* Second member email addr (leave blank if none) */
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

/*
 * ECE 454 Students: Write your rotate functions here:
 */ 

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst) 
{
    //naive_rotate(dim, src, dst);
	register int i,j, dim_square = dim * dim;
	for (i = 0; i < dim; ++i) {
        int i_by_dim = i*dim;
		for (j = 0; j < dim; ++j) {
			// dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
            dst[dim_square - dim - j * dim + i] = src[i_by_dim + j];
        }	
	}
}



char rotate_two_descr[] = "second attempt: expand the RIDX and apply code motion";
void attempt_two(int dim, pixel *src, pixel *dst) 
{
    register int i,j, dim_square = dim * dim;
    for (i = 0; i < dim; ++i) {
        int i_by_dim = i*dim;
        for (j = 0; j < dim; ++j) {
            // dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
            dst[dim_square - dim - j * dim + i] = src[i_by_dim + j];
        }   
    }
}

char rotate_three_descr[] = "third attempt: apply loop unrolling";
void attempt_three(int dim, pixel *src, pixel *dst) 
{
    register int i,j, dim_square = dim * dim;
    for ( i = 0; i < dim; ++i ) {
        int i_by_dim = i*dim;
        for (j = 0; j < dim - 7; j += 8) {
            // dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
            int dest_index = dim_square - dim - j * dim + i;
            int src_index = i_by_dim + j;
            
            dst[dest_index]           = src[src_index];
            dst[dest_index - dim]     = src[src_index + 1];
            dst[dest_index - 2 * dim] = src[src_index + 2];
            dst[dest_index - 3 * dim] = src[src_index + 3];
            dst[dest_index - 4 * dim] = src[src_index + 4];
            dst[dest_index - 5 * dim] = src[src_index + 5];
            dst[dest_index - 6 * dim] = src[src_index + 6];
            dst[dest_index - 7 * dim] = src[src_index + 7];
        }   
    }
}

char rotate_four_descr[] = "4th attempt: change loop order";
void attempt_four(int dim, pixel *src, pixel *dst) 
{
    
    int i,j;
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
        dst[RIDX(dim - 1 - i, j, dim)] = src[RIDX(j, i, dim)];
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
    add_rotate_function(&rotate, rotate_descr);   

    add_rotate_function(&attempt_two, rotate_two_descr);   
    add_rotate_function(&attempt_three, rotate_three_descr);   
    add_rotate_function(&attempt_four, rotate_four_descr);   
    //add_rotate_function(&attempt_five, rotate_five_descr);   
    //add_rotate_function(&attempt_six, rotate_six_descr);   
    //add_rotate_function(&attempt_seven, rotate_seven_descr);   
    //add_rotate_function(&attempt_eight, rotate_eight_descr);   
    //add_rotate_function(&attempt_nine, rotate_nine_descr);   
    //add_rotate_function(&attempt_ten, rotate_ten_descr);   
    //add_rotate_function(&attempt_eleven, rotate_eleven_descr);   

    /* ... Register additional rotate functions here */
}

