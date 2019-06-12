#include <header.h>
struct wrap_int {
	int a;
};
int main() {
	//Concatenator concat;
	//std::vector<std::string> str;
	//str.push_back("data1");
	//str.push_back("MAMA");
	//str.push_back("sor");
	//concat.concatenate(concat.shredder(str, 2));
	std::unordered_map<int, wrap_int> a;
	wrap_int b;
	b.a = 1;
	a.insert(std::make_pair(1, b));
	auto& nen = a[1];
	a.erase(1);
	a.at(1);
}