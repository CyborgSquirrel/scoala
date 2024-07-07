#include <iostream> 
#include <vector> 

template <typename T>
class grades {
private:
	std::vector<T> v;
public:
	grades() = default;
	grades operator+(T grade) {
		grades<T> ng = *this;
		ng.v.push_back(grade);
		return ng;
	}
	typename std::vector<T>::iterator begin() {
		return this->v.begin();
	}
	typename std::vector<T>::iterator end() {
		return this->v.end();
	}
	int getNRGrages() {
		return this->v.size();
	}
};

int main() { 
	grades<int> myg; 
	myg = myg + 10; // adaugam nota 10 la OOP 
	myg = myg + 9;   //adaugam nota 9 la FP 
	double avg = 0.0; 
	for (auto g:myg){  //iteram toate notele 
		 avg+=g; 
	} 
	return avg/myg.getNRGrages();//compute average 
} 
 
