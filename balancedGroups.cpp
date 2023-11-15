#include "balancedGroups.h"
// your includes here
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

/* your helper function here if you have any */
Assignment balancedGroups_helper(Assignment &choice, std::vector<int> const &birthdays, int i, int n, vector <int> &ga, vector <int> &gb) {
	// calculate sums of each group
	int sum_ga = accumulate(ga.begin(), ga.end(), 0);
	int sum_gb = accumulate(gb.begin(), gb.end(), 0);

	// 2 new vectors representing the scenarios when we add a new element to each group
	vector<int> new_ga (ga);
	vector<int> new_gb (gb);

	int current = birthdays[i];
	// if we add the new element in each new vector
	new_ga.push_back(current);
	new_gb.push_back(current);

	// calculate the sums if we add the new element in each vector
	int sum_new_ga = accumulate(new_ga.begin(), new_ga.end(), 0);
	int sum_new_gb = accumulate(new_gb.begin(), new_gb.end(), 0);

	// the differences in each cases
	int diff_new_a_and_gb = abs(sum_new_ga - sum_gb);
	int diff_new_b_and_ga = abs(sum_new_gb - sum_ga);
	
	// base case where we will choose the option for choice
	if (i == n - 1) {
		if (diff_new_a_and_gb < diff_new_b_and_ga) {
			choice.ga.push_back(current);
			choice.diff = diff_new_a_and_gb;
	}
		else {
			choice.gb.push_back(current);
			choice.diff = diff_new_b_and_ga;
	}
		return choice;
	}

	// First, we divide into 2 choices
	Assignment choice_a = choice;
	Assignment choice_b = choice;
	choice_a.ga.push_back(current);
	choice_b.gb.push_back(current);

	// For each choices, we evaluate them further
	// Option 1: new_ga = {current}, gb = []	
	Assignment option_1 = balancedGroups_helper(choice_a, birthdays, i+1, n, new_ga, gb);
	// Option 2: ga = [], new_gb = {current}
	Assignment option_2 = balancedGroups_helper(choice_b, birthdays, i+1, n, ga, new_gb);	

	// Choose the assignment with the lesser difference
	if (option_1.diff < option_2.diff) {
		return option_1;
	}
	else {
		return option_2;
	}
}

Assignment balancedGroups(std::vector<int> const &birthdays) {
	// create the ultimate assignment that we want to return
	vector<int> ga;
	vector<int> gb;
	Assignment choice(0, ga, gb);
	return balancedGroups_helper(choice, birthdays, 0, birthdays.size(), ga, gb);
}
