#include "countOOO.h"
// your includes here
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

/*	
	References:

	I used the following websites to get the idea of how to compute inversion count using merge sort:

	https://www.geeksforgeeks.org/inversion-count-in-array-using-merge-sort/

	https://www.tutorialspoint.com/cplusplus-program-to-implement-merge-sort
*/

// helper functions
// calculate the number of inversions when merging two subvectors together
int merge(vector<int>& listB, int left, int middle, int right) {

	int order = 0;
	// divide listB into 2 subvectors
	int first_size = middle + 1 - left;
	int second_size = right - middle;
	vector<int> first;
	for (int i = 0; i < first_size; i ++) {
		first.push_back(listB[left + i]);
	}
	vector<int> second;
	for (int i = 0; i < second_size; i ++) {
		second.push_back(listB[middle + 1 + i]);
	}

	int i = 0;
	int j = 0;
	int index = left;					// index of the updated listB

	while (i < first_size && j < second_size) {
		// if the ith element of left is <= than jth element of right
		if (first[i] <= second[j]) {
			listB[index] = first[i];	// append the ith element of first vector into listB
			i++;						// go to the next element of first vector
		} 
		// if the ith element of left is > than jth element of right
		else {
			listB[index] = second[j];	// append the jth element of second vector into listB
			order += first_size - i;		// only update order when the element is out of order /// ???
			j++;						// go to the next element of second vector
		}
		index++;						// continue updating the next element of listB
	}

	// copy the remaining elements of first, if i hasn't reached the last element of first
	while (i < first_size) {
		listB[index] = first[i];
		i++;
		index++;
	}

	// copy the remaining elements of second, if j hasn't reached the last element of second 
	while (j < second_size) {
		listB[index] = second[j];
		j++;
		index++;
	}

	return order;
}

// compute the total number of inversions via merge sort
int mergesort(vector<int>& listB, int left, int right) {	
	int order = 0;
	if (left < right) {
		int middle = (left + right)/2;

		// recursively sort the left half of the vector, count the number of inversions
		order += mergesort(listB, left, middle);

		// recursively sort the right half of the vector, count the number of inversions
		order += mergesort(listB, middle + 1, right);	

		// takes 2 sorted subvectors and merge them into a single vector
		// there can be an element in the right subvector that is smaller than an element in the left subvector, so must count the inversions here too
		order += merge(listB, left, middle, right);
	
	}
	return order;
}

// countOOO computes the number of pairs of elements in rankedListA that are out of order in rankedListB
int countOOO(std::vector<std::string> rankedListA, std::vector<std::string> rankedListB) {
	// create a map for list A; list A is the standard list
	multimap<string, int> mapA;

	// map each string in list A an integer value
	for (int i = 0; i < rankedListA.size(); i++) {
        mapA.insert({rankedListA[i], i});
    }

	// return vector B with the integer values of list B
	vector<int> listB;
	for (auto& key: rankedListB) {
    	auto it = mapA.find(key);
    	if (it != mapA.end()) {
        	listB.push_back(it->second);
		}
	}

	// return the result
	int order = mergesort(listB, 0, listB.size() - 1); // left = first index, right = last index

	return order;
}

// int main() {
// 	// expect 2
// 	vector<string> rankedListA = {"Natural", "Glory", "Hustler", "Legendary"};
// 	vector<string> rankedListB = {"Hustler", "Natural", "Glory", "Legendary"};
// 	// expect 6
// 	// vector<string> rankedListA = {"Hustler", "Legendary", "Natural", "Glory"};
// 	// vector<string> rankedListB = {"Glory", "Natural", "Legendary", "Hustler"};
// 	cout << countOOO(rankedListA, rankedListB) << endl;
// 	return 0;
// }