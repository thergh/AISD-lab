#include <vector>
#include <iostream>
#include <iomanip>

void Print2DVectorFloat(std::vector<std::vector<float>> v){
	for(int i = 0; i < v.size(); i++) {
		for(int j = 0; j < v[0].size(); j++) {
			std::cout << std::fixed << std::setprecision(3) << v[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

void PrintVectorFloat(std::vector<float> v) {
	for(int i = 0; i < v.size(); i++) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
}


void PrintVectorInt(std::vector<int> v) {
	for(int i = 0; i < v.size(); i++) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
}