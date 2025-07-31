// string4parse.cpp : Defines the entry point for the application.
//
#include "../include/pch.h"
#include "../include/string4parse.h"

#include<stdio.h>
namespace string4parse {

  string4parse::string4parse(std::string&& source) noexcept {
    _offset = 0;
    _length = source.length();
    std::shared_ptr<Type> tmp(_strdup(source.c_str()));
    _shared_buffer.swap(tmp);
  }

  string4parse::string4parse(string4parse&& other) noexcept 
    : _shared_buffer(std::move(other._shared_buffer))
    , _offset(other._offset)
    , _length(other._length) {
    // Reset the moved-from object
    other._offset = 0;
    other._length = 0;
  }

  string4parse& string4parse::operator=(string4parse&& other) noexcept {
    if (this != &other) {
      _shared_buffer = std::move(other._shared_buffer);
      _offset = other._offset;
      _length = other._length;
      
      // Reset the moved-from object
      other._offset = 0;
      other._length = 0;
    }
    return *this;
  }
}