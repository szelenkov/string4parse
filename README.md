# string4parse

`string4parse` is a small C++ library for working with strings through a
lightweight, iterable value type. It supports construction from C strings and
`std::string`, bounds-checked character access, conversion back to
`std::string`, and forward or reverse iteration.

## Requirements

- CMake 3.24 or newer
- A C++ compiler with C++20 support
- Ninja when using the default CMake preset

GoogleTest is downloaded and built by the CMake configuration for the test
target.

## Building

From the repository root:

```powershell
cmake --preset default
cmake --build --preset default
```

The default preset places build artifacts in `out/build/default`.

## Testing

Run the complete test suite with CTest:

```powershell
ctest --preset default --output-on-failure
```

Run only the configured library test:

```powershell
ctest --preset default -R "^string4parse_test$" --output-on-failure
```

To run one GoogleTest case directly:

```powershell
.\out\build\default\string4parse_test.exe --gtest_filter=String4ParseTest.DefaultConstructor
```

## Usage

Include the public header and construct a `string4parse` object:

```cpp
#include "string4parse.h"

#include <iostream>

int main() {
    string4parse::string4parse value("hello");

    std::cout << value.length() << '\n';
    std::cout << value[0] << '\n';
    std::cout << value.to_string() << '\n';

    for (char character : value) {
        std::cout << character;
    }
}
```

The public API is defined in `include/string4parse.h`, and non-inline
implementation details are in `src/string4parse.cpp`.

## License

This project is released under the CC0 1.0 Universal license. See
[`LICENSE`](LICENSE) for the full text.