#include <header.h>

std::vector<Fragment> Concatenator::shredder(const std::vector<std::string>& data, uint16_t fragment_size) {
	if (data.empty()) {
		//throw exception
	}
	
	for (const auto& str : data) {
		int fragments_count = str.length() / fragment_size;
		int fragment_tail = str.length() % fragment_size;

	}
}

