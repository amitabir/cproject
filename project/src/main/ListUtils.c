#include "ListUtils.h"
#include <stdio.h>
#include <stdlib.h>

/* The List struct is made from two fields - a void data pointer and another List struct which is the next
element in the List */
struct List {
	void *data;
	struct List *next;
};

/* Creating a new List and initializing it */
ListRef newList(void* headData) {
	// Allocating memory for the list
	ListRef list = (ListRef) malloc(sizeof(struct List));
	if (list == NULL) {
		// malloc has failed and NULL is returned
		return NULL;
	}
	list->data = NULL;
	// The next element is NULL until new elements are inserted to the list
	list->next = NULL;
	if (headData != NULL) {
		// Inserting the headData to the data field
		list->data = headData;
	} 
		
	return list;
}

/* Returning the data of the head of the list */
void* headData(ListRef list) {
	if (isEmpty(list)) {
		return NULL;
	}
	return (list->data);
}

/* Returning sublist of list which doesn't include the head */
ListRef tail(ListRef list){
	return list->next;
}

/* Appending a new element to the list and returning the elemet */
ListRef append(ListRef list, void* data) {
	if (data == NULL) {
		// data is NULL - return NULL
		return NULL;
	}
	
	// If its an empty list (represented by NULL data) just add the data to the first node
	if (list->data == NULL) {
		list->data = data;
		return list;
	}
	
	// Creating a new list with data
	ListRef newDataList = newList(data);
	if (newDataList == NULL) {
		// malloc has failed - returning NULL
		return NULL;
	}
	// Creating a tempList to go through the list to find the end
	ListRef tempList = list;
	while ((tempList->next) != NULL) {
		tempList = tempList->next;
	}
	// Appending the required list at the end
	tempList->next = newDataList;
	return newDataList;
}

/* We represent an empty list as a list with head data that is NULL */
int isEmpty(ListRef list) {
	return list->data == NULL;
}

/* Going through all the elements is the list and freeing them */
void destroyList(ListRef list, FreeFunc freeData) {
	if (isEmpty(list)) {
		// The list is empty - free the list and we are done
		free(list);
	} else {
		// Advancing through the list and freeing each list seperately
		while (list != NULL) {
			ListRef tempList = list;
			freeData(list->data);
			list = list->next;
			free(tempList);
		}
	}
}
