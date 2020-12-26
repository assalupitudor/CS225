/* Your code here! */
#include "dsets.h"
#include <iostream>

void DisjointSets::addelements(int num) {
	for (int i = 0; i < num; i++) {
		elements.push_back(-1); 
	}
}

int DisjointSets::find(int elem) {
	if (elements[elem] < 0) { 
        return elem; 
    } else {
		int root = find(elements[elem]); 
		elements[elem] = root; 
		return root;
	}
}

void DisjointSets::setunion(int a, int b) {
	int root_a = find(a); 
	int root_b = find(b);
	if (root_a == root_b) { return; }
	int new_size = elements[root_a] + elements[root_b];
	if (elements[root_a] <= elements[root_b]) { 
		elements[root_b] = root_a; 
		elements[root_a] = new_size; 
	} else { 
		elements[root_a] = root_b; 
		elements[root_b] = new_size; 
	}
}

int DisjointSets::size(int elem) {
	return -elements[find(elem)]; 
}