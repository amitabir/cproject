#include "MiniMax.h"
#include <stdio.h>

/* Implementing the generic MiniMax algorithm, as described in the header file. 
If some of the given methods fails during the execution, an index of (-1) will be returned. */
struct MiniMaxResult getBestChild(
	void *state,
	unsigned int maxDepth,
	ListRef (*getChildren) (void* state),
	FreeFunc freeState,
	int (*evaluate) (void* state),
	int isMaxPlayer,
	int alpha,
	int beta) {
		printf("ALPHA IS %d, BETA IS %d \n", alpha, beta);
		
		struct MiniMaxResult childResult; // result for recursive calls on children
		int currChildIndex = 0; // holds the current child index
		int bestChildIndex = 0; // holds the best child index
		int bestChildValue = isMaxPlayer ? MIN_EVALUATION - 1 : MAX_EVALUATION + 1; // holds the best child value
		ListRef childrenList; // the children list for the state
		void *childState; // the current child state in the list
					
		if (maxDepth == 0) {
			// The end of the recursion
			struct MiniMaxResult totalResult = {bestChildIndex, (*evaluate)(state)};
			return totalResult;
		}
		
		// Use getChildren method to get a list of the state's children
		childrenList = (*getChildren)(state);
		
		if (childrenList == NULL) {
			// Some standart function failed or general error
			struct MiniMaxResult totalResult = {-1, bestChildValue};
			return totalResult;
		}
		
		if (isEmpty(childrenList)) {
			// No children means its a leaf in the tree - evaluate immediately.
			bestChildValue = (*evaluate)(state);
		} else {
			// Find best child for inner nodes
			ListRef tempList = childrenList;
			do {
				childState = headData(tempList);
				childResult = getBestChild(childState, maxDepth - 1, getChildren, freeState, evaluate, !isMaxPlayer, alpha, beta);
				
				// Check if some error occured during recursive calls
				if (childResult.index == -1) {
					return childResult;
				}
				
				// Check if the child is the best
				if (isMaxPlayer) {
					printf("MAX: ");
				} else {
					printf("MIN: ");
				}
				printf("CURRENT CHILD VALUE IS %d \n", childResult.value);
				if ((isMaxPlayer && childResult.value > bestChildValue) 
						|| (!isMaxPlayer && childResult.value < bestChildValue)) {
					bestChildValue = childResult.value;
					printf("UPDATE BEST CHILD VALUE TO %d \n", bestChildValue);
					bestChildIndex = currChildIndex;
				}
				
				// Alpha-Beta pruning
				if (isMaxPlayer) {
					if (bestChildValue > alpha) {
						alpha = bestChildValue;
					}
					if (beta <= alpha) {
						printf("PRUNING max player!!!! \n");
						break;
					}
				} else {
					if (bestChildValue < beta) {
						beta = bestChildValue;
					}
					if (beta <= alpha) {
						printf("PRUNING min player!!!! \n");
						break;
					}
				}

				tempList = tail(tempList);
				currChildIndex++;
			} while (tempList != NULL);
		}
		
		// Free list and states
		destroyList(childrenList, freeState);
		
		// Construct the result
		struct MiniMaxResult totalResult = {bestChildIndex, bestChildValue};
		if (isMaxPlayer) {
			printf("MAX: ");
		} else {
			printf("MIN: ");
		}
		printf("total result is: %d \n", bestChildValue);
		return totalResult;
	}
	

