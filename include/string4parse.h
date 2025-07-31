// string4parse.h : Include file project specific include files.

#pragma once
#ifndef _STRING4PARSE_
#define _STRING4PARSE_

#include <string>
#include <stdexcept>

#include <memory>
#include <iterator>
#include <algorithm>

namespace string4parse {
    typedef ptrdiff_t Distance;
    typedef char Type;

    class string4parse {
        std::shared_ptr<Type> _shared_buffer;
        size_t _offset;
        std::size_t _length;

    public:
        // Forward declaration of iterator
        class iterator;

        // Constructors
        string4parse(Type* buff = nullptr) noexcept;
        string4parse(const std::string& buff) noexcept;
        string4parse(std::string&& buff) noexcept;
        string4parse(const string4parse& other) noexcept;
        string4parse(string4parse&& other) noexcept;

        // Assignment operators
        string4parse& operator=(const string4parse& other) noexcept;
        string4parse& operator=(string4parse&& other) noexcept;

        // Iterator functions
        iterator string4parse::begin() const {
          return iterator(*this, 0, 1);
        }

        iterator string4parse::end() const {
          return iterator(*this, _length, 1);
        }

        iterator string4parse::rbegin() const {
          return iterator(*this, _length - 1, -1);
        }

        iterator string4parse::rend() const {
          return iterator(*this, -1, -1);
        }

        // Capacity
        bool empty() const noexcept { return _length == 0; }
        size_t length() const noexcept { return _length; }
        
        // Access
        Type operator[](size_t pos) const {
            if (pos >= _length) throw std::out_of_range("Index out of range");
            return _shared_buffer.get()[_offset + pos];
        }

        // String operations
        std::string to_string() const {
            if (empty()) return std::string();
            return std::string(_shared_buffer.get() + _offset, _length);
        }

        // Destructor
        virtual ~string4parse() noexcept {
          // No need to explicitly free _shared_buffer
          // shared_ptr will handle cleanup
        }

        // Iterator class
        class iterator : public std::iterator<std::bidirectional_iterator_tag, Type> {
            friend class string4parse;
            const string4parse* _owner;
            size_t _position;
            int _direction;  // 1 for forward, -1 for reverse

            iterator(const string4parse& owner, size_t pos, int dir)
                : _owner(&owner), _position(pos), _direction(dir) {}

        public:
            iterator() : _owner(nullptr), _position(0), _direction(1) {}

            Type operator*() const {
                return (*_owner)[_position];
            }

            iterator& operator++() {
                _position += _direction;
                return *this;
            }

            iterator operator++(int) {
                iterator tmp = *this;
                _position += _direction;
                return tmp;
            }

            iterator& operator--() {
                _position -= _direction;
                return *this;
            }

            iterator operator--(int) {
                iterator tmp = *this;
                _position -= _direction;
                return tmp;
            }

            bool operator==(const iterator& other) const {
                return _owner == other._owner && _position == other._position;
            }

            bool operator!=(const iterator& other) const {
                return !(*this == other);
            }

            void advance(Distance n) {
                if (_direction > 0) {
                    _position = std::min(_position + n, _owner->length());
                } else {
                    _position = std::max(static_cast<Distance>(0), 
                                       static_cast<Distance>(_position) + n);
                }
            }
        };
    };

} // namespace string4parse

namespace std {
    // Specialize std::advance for our iterator
    template<>
    void advance(string4parse::string4parse::iterator& it, string4parse::Distance n) {
        it.advance(n);
    }
}

#endif // _STRING4PARSE_
