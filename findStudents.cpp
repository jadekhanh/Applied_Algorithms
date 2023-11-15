// Partners: John McDonough, Phuong Khanh Tran
#include <iterator>
#include <vector>
#include <iostream>
#include <map>
#include <cmath>
using namespace std;

std::vector<int> findStudents(std::vector<int> id){

    // create a vector contains mods 330
    vector<int> id_mods = id;

    // get the mods of all the elements in the vector
    vector<int>::iterator iter;
    for (iter = id_mods.begin(); iter != id_mods.end(); iter++) {
        *iter = *iter % 330;
    }

    // create a hashmap
    multimap<int, int> hashmap;
    for (int i = 0; i < id.size(); i++) {
        hashmap.insert({id_mods[i], id[i]});
    }

    int first, second;
    vector<int> results;

    int minimum_sum = 331;
    int sum;
    multimap<int, int>::iterator it1;
    multimap<int, int>::iterator it2;

    // iterate through the hashmap
    for (int x = 0; x < 330; x++) {             // go through the list of mods
        if (hashmap.count(x) == 0) {            // skip the current x if there is nothing in the bucket
            continue;
        }
        else {
            for (int y = 0; y < 330; y++) {     // go through the list of mods again
                if (hashmap.count(y) == 0) {    // skip the current y if there is nothing in the bucket
                    continue;
                }
                else {
                    // when x = y
                    if (x == y) {
                        // special case when one remainder has a bucket of 2 dividends
                        if (hashmap.count(y) >= 2) {
                            it1 = hashmap.find(x);  // iterator that points to the first dividend
                            it2 = hashmap.find(y);
                            it2++;                  // iterator that points to the second dividend
                            sum = abs((x + y) % 330);
                        }
                        // skip the current iteration if there is only 1 number in the mod bucket
                        else {
                            continue;   
                        }
                        if (sum < minimum_sum) {
                        minimum_sum = sum;
                        first = it1->second;
                        second = it2->second;
                    }
                    }
                    // when x != y
                    else {
                        it1 = hashmap.find(x);
                        it2 = hashmap.find(y);
                        sum = abs((x + y) % 330);   // same as sum = abs((it1->second + it2->second) % 330);
                    }
                    if (sum < minimum_sum) {
                        minimum_sum = sum;
                        first = it1->second;
                        second = it2->second;
                    }
                }
            }
        }
    }

    // save the results
    results.push_back(first);
    results.push_back(second);
    return results;
}