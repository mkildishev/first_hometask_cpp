#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <exception>
#include <algorithm>
#include <random>
#include <ctime> 
struct Fragment final {

private:
	uint16_t _id;
	uint16_t _fragment_index;
	uint16_t _fragments_total;
	uint16_t _data_size;
	std::string _data;

public:
	Fragment(uint16_t id, uint16_t fragment_index,
		uint16_t fragments_total, uint16_t data_size, std::string&& data) :
		_id(id), _fragment_index(fragment_index), _fragments_total(fragments_total),
		_data_size(data_size), _data(std::move(data)) {
	}

	const std::string& get_data() const & {
		return _data;
	}

	std::string&& get_data() && {
		return std::move(_data);
	}

	const std::string& get_data() const && {
		return _data;
	}
};



class Concatenator final {
public:
	std::vector<Fragment> shredder(const std::vector<std::string>& data, uint16_t fragment_size);
	void concatenate(std::vector<Fragment>&& data);

private:
	std::unordered_map<uint16_t, std::string> _id_to_data;
};