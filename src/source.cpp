#include <header.h>
#include <iostream>
std::vector<Fragment> Concatenator::shredder(const std::vector<std::string>& data, uint16_t fragments_total) {
	/* A.G. А почему? 0 / x = 0. Почему бы не вернуть std::vector.size() == 0??? */
	if (data.empty()) {
		throw std::invalid_argument("Data can't be empty!");
	}
	if (fragments_total == 0) {
		throw std::invalid_argument("Total fragments can't be zero");
	}
	uint16_t id = 0;
	std::vector<Fragment> fragments;
	/* A.G. reserve не правильный забыли помножить кол-во фрагментов */
	fragments.reserve(data.size());
	for (const auto& str : data) {
		uint16_t fragment_size = str.length() / fragments_total;
		/* A.G. Добавьте скобок, сложно читается. Обычно пишут как-то так "int a = ( (condition) ? <true> : <false> )" */
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


void Concatenator::concatenate(std::vector<Fragment>& data) {
	std::unordered_map<uint16_t, ReducedInfo> id_to_redinfo;
	for (auto& fragment : data) {
		auto cur_id = fragment.get_id();
		/* A.G. Много лишнего поиска по мапе. (Все find/emplace/[]/at/erase = поиск по мапе).
		 *      Используйте итератор. И тут можно auto it = map.try_emplace(id, fragmentsTotal).first;
		 */
		if (id_to_redinfo.find(cur_id) == id_to_redinfo.end()) {
			id_to_redinfo.emplace(cur_id, fragment.get_fragments_total());
		}

		if (id_to_redinfo[cur_id].recieved_fragment_count == fragment.get_fragments_total()) {
			_id_to_data.erase(cur_id);
			id_to_redinfo[cur_id].recieved_fragment_count = 0;
		}
		id_to_redinfo[cur_id].recieved_fragment_count++;
		id_to_redinfo[cur_id].recieved_fragments[fragment.get_fragment_index()] = std::move(fragment.get_data());
		
		if (id_to_redinfo[cur_id].recieved_fragment_count == fragment.get_fragments_total()) {
			std::string full_string;
			full_string.reserve((fragment.get_fragments_total() + 1) * fragment.get_data_size());
			for (const auto& str : id_to_redinfo[cur_id].recieved_fragments) {
				full_string.append(str);
			}
			_id_to_data.emplace(cur_id, std::move(full_string));
		}
	}
}

