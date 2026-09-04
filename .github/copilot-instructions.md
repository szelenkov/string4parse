# Copilot instructions for string4parse

## Build and test

This is a C++14 project managed with CMake. The `string4parse_lib` target is
compiled as C++20, while compiler extensions are disabled. The default CMake
preset uses Ninja and writes artifacts to `out/build/default`.

Configure and build from the repository root:

```powershell
cmake --preset default
cmake --build --preset default
```

Run the CTest suite:

```powershell
ctest --preset default --output-on-failure
```

The configured test is `string4parse_test`. Run only that CTest test with:

```powershell
ctest --preset default -R "^string4parse_test$" --output-on-failure
```

For a single GoogleTest case, run the built executable directly:

```powershell
.\out\build\default\string4parse_test.exe --gtest_filter=String4ParseTest.DefaultConstructor
```

Use `--gtest_list_tests` to inspect available GoogleTest suite and case names.
There is no lint or formatter target configured in the repository.

## Architecture

- `include/string4parse.h` is the public API. It defines the
  `string4parse::string4parse` value type, capacity/access operations,
  conversion to `std::string`, and the nested bidirectional iterator.
- `src/string4parse.cpp` contains the non-inline ownership and move-operation
  implementation. Instances retain a shared character buffer plus an offset
  and length, allowing the object to represent a view into storage.
- `CMakeLists.txt` builds the library target `string4parse_lib` and links it
  into the `string4parse_test` executable.
- `tests/string4parse_test.cpp` contains the meaningful library tests.
  `tests/test.cpp` is a minimal standalone GoogleTest example and is not part
  of the CMake test target.
- GoogleTest is fetched by CMake's `ExternalProject_Add` configuration. The
  vcpkg manifest also declares `gtest`, `openssl`, and `zlib`, but the current
  CMake file does not create application targets for OpenSSL or zlib.

## Repository conventions

- Keep the public header and implementation split: public declarations and
  small inline operations belong in `include/string4parse.h`; non-inline
  method definitions belong in `src/string4parse.cpp`.
- Use the `string4parse` namespace and the existing `Type`/`Distance` aliases
  when extending the API.
- Preserve the iterator model: `begin()`/`end()` walk forward and
  `rbegin()`/`rend()` walk backward; iterator advancement is customized through
  the `std::advance` specialization already provided by the header.
- Add or update behavior tests in `tests/string4parse_test.cpp`; the CMake
  target currently discovers tests through CTest and runs the GoogleTest
  executable as one test.
- Use the checked-in CMake presets rather than inventing a separate build
  directory. `ninja-multi` is available when a multi-configuration Ninja
  generator is needed.
