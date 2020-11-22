#ifndef GIFTIALAB_UTIL_CONTAINER_ORDERED_VECTOR_HPP
#define GIFTIALAB_UTIL_CONTAINER_ORDERED_VECTOR_HPP

#include "windowed_vector.hpp"

namespace giftialab {
namespace util {
namespace container {


template<typename _tElement, size_t _MaxSz>
class ordered_vector : public windowed_vector<_tElement, _MaxSz> {
public:
    typedef windowed_vector<_tElement, _MaxSz> _tSuper;
    typedef ordered_vector<_tElement, _MaxSz> _tThis;

    ordered_vector() : _tSuper() {}
    ordered_vector(const _tThis &rhs) : _tSuper(rhs) {}

    void push_back(const _tElement &val) {
        if (_tSuper::size() > 0 && val < (*this)[_tThis::end_index() - 1]) {
            throw std::invalid_argument("val to be push_back should be increasement");
        }
        _tSuper::push_back(val);
    }

    template<typename _fComparator, typename _fPicker>
    void intersection(const _tThis &lhs, const _tThis &rhs, _fComparator &&cmp, _fPicker &&picker, size_t cntlimit = 0) {
        _tSuper::clear();

        size_t lb = lhs.begin_index(cntlimit), le = lhs.end_index();
        size_t rb = rhs.begin_index(cntlimit), re = rhs.end_index();
        while (lb != le && rb != re) {
            const _tElement &lv = lhs[lb], &rv = rhs[rb];
            int ret = cmp(lv, rv);
            if (ret > 0) {
                ++lb;
            } else if (ret < 0) {
                ++rb;
            } else {
                push_back(picker(lv, rv));
                ++lb;
                ++rb;
            }
        }
    }
};

} // ns container
} // ns util
} // giftialab

#endif
