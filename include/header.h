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

	uint16_t get_id() const {
		return _id;
	}

	uint16_t get_fragment_index() const {
		return _fragment_index;
	}

	uint16_t get_fragments_total() const {
		return _fragments_total;
	}

	uint16_t get_data_size() const {
		return _data_size;
	}

	const std::string& get_data() const & {
		return _data;
	}

	std::string&& get_data() && {
		return std::move(_data);
	}
        /* A.G. Можно не указывать такую перегрузку. Тогда автоматом будет вызвана const &. 
	 *      Такую перегрузку следует указывать только если: вы делаете что-то отличное от const & 
	 *       (удаляете, возвращаете T const &&)*/
	const std::string& get_data() const && {
		return _data;
	}
};

struct ReducedInfo {
	ReducedInfo() = default;
	ReducedInfo(int fragment_count) : recieved_fragments( fragment_count ) {}
	uint16_t recieved_fragment_count = 0;
	std::vector<std::string> recieved_fragments;
};


class Concatenator final {
public:
	std::vector<Fragment> shredder(const std::vector<std::string>& data, uint16_t fragment_total);
	void concatenate(std::vector<Fragment>& data);

	const std::unordered_map<uint16_t, std::string>& get_map() const & {
		return _id_to_data;
	}

	std::unordered_map<uint16_t, std::string>&& get_map() & {
		return std::move(_id_to_data);
	}
        /* A.G. Зачем удалять? */
	std::unordered_map<uint16_t, std::string>&& get_map() && = delete;
	std::unordered_map<uint16_t, std::string>&& get_map() const &&  = delete;


private:
	std::unordered_map<uint16_t, std::string> _id_to_data;
};
