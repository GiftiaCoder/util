#ifndef GIFTIALAB_UTIL_SCOPE_GUARD_HPP
#define GIFTIALAB_UTIL_SCOPE_GUARD_HPP

#include <functional>

namespace giftialab {
namespace util {

class scope_guard {
public:
	inline scope_guard(const std::function<void()> &cb) : _alive(true), _cb(cb) {}
       	inline ~scope_guard() {
		if (_alive) {
			_cb();
		}
	}
	inline void dismiss() {
		_alive = false;
	}
private:
	bool _alive;
	const std::function<void()> &_cb;
};

} // ns util
} // giftialab

#endif
