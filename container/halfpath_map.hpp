#ifndef GIFTIALAB_UTIL_CONTAINER_HALFPATH_MAP_HPP
#define GIFTIALAB_UTIL_CONTAINER_HALFPATH_MAP_HPP

#include "ordered_vector.hpp"

#include <unordered_map>

namespace giftialab {
namespace util {
namespace container {

template<typename _tKey, typename _tElement, size_t _MaxSz>
class halfpath_map : public std::unordered_map<_tKey, ordered_vector<_tElement, _MaxSz>> {
public:
	typedef ordered_vector<_tElement, _MaxSz> _tValue;
	typedef std::unordered_map<_tKey, _tValue> _tSuper;
	typedef halfpath_map<_tKey, _tElement, _MaxSz> _tThis;
	
	void push_back(const _tKey &key, const _tElement &element) {
		(*this)[key].push_back(element);
	}
	_tValue *seek_path(const _tKey &key) {
		auto &&it = _tSuper::find(key);
		if (it != _tSuper::end()) {
			return &it->second;
		} else {
			return nullptr;
		}
	}
};

} // ns container
} // ns util
} // giftialab

#endif
