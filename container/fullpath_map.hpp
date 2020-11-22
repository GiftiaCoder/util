#ifndef GIFTIALAB_UTIL_CONTAINER_FULLPATH_MAP_HPP
#define GIFTIALAB_UTIL_CONTAINER_FULLPATH_MAP_HPP

#include "halfpath_map.hpp"

namespace giftialab {
namespace util {
namespace container {


template<typename _tKey, typename _tElement, size_t _MaxSz>
class fullpath_map : public std::unordered_map<_tKey, halfpath_map<_tKey, _tElement, _MaxSz>> {
public:
	typedef halfpath_map<_tKey, _tElement, _MaxSz> _tValue;
	typedef ordered_vector<_tElement, _MaxSz> _tPaths;
	typedef std::unordered_map<_tKey, _tValue> _tSuper;
	typedef fullpath_map<_tKey, _tElement, _MaxSz> _tThis;
	
	void push_back(const _tKey &key_beg, const _tKey &key_end, const _tElement &element) {
		(*this)[key_beg].push_back(key_end, element);
	}
	_tPaths *seek_path(const _tKey &key_beg, const _tKey &key_end) {
		auto &&it = _tSuper::find(key_beg);
		if (it != _tSuper::end()) {
			return it->second.seek_path(key_end);
		} else {
			return nullptr;
		}
	}
};

} // ns container
} // ns util
} // giftialab

#endif
