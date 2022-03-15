/*
 * Author:		Sarah Rockow
 * Collaborators: 	Amaka Ezuruonye & Jake VanBronkhorst
 * Class: 		CIS 343.02
 * Instructor: 		Professor Woodring
 * Date: 		February 7, 2022
 *
 * Notes:
 *
 * Amaka and I worked on the project together
 * directly. Jake and I double-checked our work
 * and sent small solutions to each other. Jake sent me
 * the sample code for the resize method. Amaka and I coded
 * and talked about the project with each other. 
 *
 */

#include "lite_vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

lite_vector* lv_new_vec(size_t type_size){
	// declare and initialize a new lite_vector

	lite_vector* lv;
	lv = malloc (sizeof(lite_vector));
	lv -> max_capacity = 10;
	lv -> length = 0;
	lv -> type_size = type_size;
	lv -> data = malloc(sizeof(void*) *lv ->max_capacity);

	return lv;
}

/*
 * Free all memory used by the vector
 *
 */
void lv_cleanup(lite_vector* vec){

	// free the variables that were malloc-ed
	free(vec -> data);	
	free(vec);
}

/*
 * Get the current number of elements stored in the vector
 */
size_t lv_get_length(lite_vector* vec){

	// this is just a getter function
	if (vec != NULL) {
		return vec -> length;
	}
	else {
		return 0;
	}
}

/*
 * Clear the contents of the vector and reset it to a default state
 */
bool lv_clear(lite_vector* vec){
	bool condition = false;

	// check to make sure that vec exists
	if (vec != NULL) {
		// set the length to 0 and free the data
		vec -> length = 0;
		free(vec -> data);
		
		// reset lite_vector
		vec -> data = malloc(10 * sizeof(void*));
		vec -> max_capacity = 10;
		

		condition = true;
	}

	return condition;
}

/*
 * Get an element stored in the vector at index
 */
void* lv_get(lite_vector* vec, size_t index){

	// error checking
	if (vec->data[index] == NULL) {
		return NULL;
	}

	// this is just a getter method
	else {
		return vec->data[index];
	}
	return NULL;
}

/**
 *  lv_resize is essentially private since we marked it static.
 *  The job of this function is to attempt to resize the vector.
 *  There may be functions you can call to do this for you, or
 *  you may write it yourself.  Either way it isn't too hard.
 *  With everything though, check to make sure the code worked
 *  and return appropriately.  Do NOT destroy the data if the code
 *  fails.  If the resize cannot complete, the original vector
 *  must remain unaffected.
 **/
static bool lv_resize(lite_vector* vec){
	
	/*
	* memcpy copies n characters from src to dest
	* 
	* With this method, I'm copying the data from
	* vec into vec again, but I'm extending the
	* max_capacity by the type_size
	*
	**/
	
	memcpy(vec, vec, ((vec->max_capacity * vec->type_size) + vec->type_size));
	vec->max_capacity++;

	return true;	
}

	bool lv_append(lite_vector* vec, void* element){	

		bool condition = false;

		/*
		 * if the length < max_capacity, add element
		 * to the last open spot and increment 
		 * length
		 *
		 */
		if (vec->length != vec->max_capacity) {
			vec->length+=1;
			vec->data[vec->length-1] = element;
			
			condition = true;
		}

		/*
		 * if max_capacity == length, resize
		 */
		if (vec->length == vec->max_capacity) {
			lv_resize(vec);
		}

		return condition;

	}

