#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
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


class Concatenator {
public:
	std::vector<Fragment> shredded(const std::vector<std::string>& data, int fragment_size);
private:
	std::unordered_map<uint16_t, std::string> _id_to_data;
};