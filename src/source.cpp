#include <header.h>
#include <iostream>
std::vector<Fragment> Concatenator::shredder(const std::vector<std::string>& data, uint16_t fragments_total) {
	if (data.empty()) {
		//throw exception
	}
	if (fragments_total == 0) {
		//throw exception
	}
	uint16_t id = 0;
	std::vector<Fragment> fragments;
	fragments.reserve(data.size());
	for (const auto& str : data) {
		uint16_t fragment_size = str.length() / fragments_total;
		uint16_t fragment_tail_size = str.length() % fragments_total == 0 ? fragment_size : str.length() % fragments_total + fragment_size;

		for (int i = 0; i < (fragments_total - 1); ++i) {
			fragments.emplace_back(id, i, fragments_total, fragment_size, std::string(str, i*fragment_size, fragment_size));
		}
		fragments.emplace_back(id, fragments_total - 1, fragments_total, fragment_tail_size, std::string(str, (fragments_total - 1)*fragment_size, fragment_tail_size));
		++id;
	}
	auto rng = std::default_random_engine(time(nullptr));
	std::shuffle(fragments.begin(), fragments.end(), rng);
	return fragments;
}

void Concatenator::concatenate(std::vector<Fragment>&& data) {
	for (const auto& fragment : data) {
		
	}
}

