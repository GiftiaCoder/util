#ifndef GIFTIALAB_UTIL_CONTAINER_WINDOWED_VECTOR_HPP
#define GIFTIALAB_UTIL_CONTAINER_WINDOWED_VECTOR_HPP

#include <vector>
#include <string>
#include <exception>
#include <stdexcept>

namespace giftialab {
namespace util {
namespace container {

template<typename _tElement, size_t _MaxSz>
class windowed_vector : public std::vector<_tElement> {
public:
    typedef std::vector<_tElement> _tSuper;
    typedef windowed_vector<_tElement, _MaxSz> _tThis;

public:
    windowed_vector() : _virtual_size(0) {
        _tSuper::resize(1);
    }
    windowed_vector(const _tThis &rhs) : _tSuper(rhs), _virtual_size(rhs._virtual_size) {}

    inline void copy(const _tThis &rhs) {
        (*this) = rhs;
    }
    inline void copy(const _tThis &rhs, size_t maxsz) {
        clear();
        for (size_t begidx = rhs.begin_index(maxsz), endidx = rhs.end_index(); begidx != endidx; ++begidx) {
            _tThis::push_back(rhs[begidx]);
        }
    }

    inline void push_back(const _tElement &val) {
        if (_tSuper::size() <= _virtual_size && _virtual_size < _MaxSz) {
            _tSuper::resize(std::min(_tSuper::size() * 2, _MaxSz));
        }
        (*this)[_virtual_size++] = val;
    }

    inline _tElement &operator[] (size_t i) {
#ifdef DEBUG
        if (_virtual_size <= i || (_virtual_size > _MaxSz && i < _virtual_size - _MaxSz)) {
            throw std::invalid_argument("invalid index");
        }
#endif
        return _tSuper::operator[](i % _MaxSz);
    }
    inline const _tElement &operator[] (size_t i) const {
#ifdef DEBUG
        if (_virtual_size <= i || (_virtual_size > _MaxSz && i < _virtual_size - _MaxSz)) {
            throw std::invalid_argument("invalid index");
        }
#endif
        return _tSuper::operator[](i % _MaxSz);
    }

    inline size_t begin_index(size_t num = 0) const {
        if (num == 0) {
            return _virtual_size - size();
        } else {
            return _virtual_size - std::min(num, size());
        }
    }
    inline size_t end_index() const {
        return _virtual_size;
    }

    void clear() {
        _virtual_size = 0;
    }

    inline size_t size() const {
        return std::min(_virtual_size, _MaxSz);
    }
    inline size_t virtual_size() const {
        return _virtual_size;
    }

private:
    size_t _virtual_size;
};

} // ns container
} // ns util
} // giftialab

#endif
