# max-package-template

Basic template for Max externals made with the Max C SDK, including GitHub
Actions for automated CI builds.

The SDK dependency ([max-sdk-base](https://github.com/Cycling74/max-sdk-base))
is fetched automatically by CMake at configure time. After running cmake, the
source is available at `build/_deps/max-sdk-base-src/` if you want to browse
headers or scripts.

## Creating objects

Objects should each be made inside a directory inside of `/source/projects/`
like the example. See the [max-sdk
repository](https://github.com/Cycling74/max-sdk) for examples of how to write
Max objects with the C SDK.

## Writing an external's CMakeLists.txt


### Minimal CMakeLists.txt

Each external has its own `CMakeLists.txt`. The minimal form looks like this:

```cmake
set_property(DIRECTORY PROPERTY max::external YES)
set_property(DIRECTORY PROPERTY max::glob ON)
project(myexternal)
```

- `max::external YES` tells the build machinery to treat this directory as
  a Max external.
- `max::glob ON` automatically includes all `.c` and `.cpp` files in the
  directory as source files.
- `project(myexternal)` names the external. The output will be `myexternal.mxo`
  (macOS) or `myexternal.mxe64` (Windows).


### More complex CMakeLists.txt

If you want explicit control over which files are compiled, omit `max::glob`
and list them yourself after `project()`:

```cmake
set_property(DIRECTORY PROPERTY max::external YES)
project(myexternal)

target_sources(myexternal PRIVATE myexternal.cpp helper.cpp)
```

After `project()`, the target named `${PROJECT_NAME}` exists and can be
customized with standard CMake commands such as `target_link_libraries`,
`target_include_directories`, and `target_compile_definitions`.

### Naming MSP (tilde) objects

> Note: Because `~` is not a valid character in a CMake project name, use
> `_tilde` as a suffix instead. The SDK will rename the output file
> automatically:

```cmake
set_property(DIRECTORY PROPERTY max::external YES)
set_property(DIRECTORY PROPERTY max::glob ON)
project(myobject_tilde)  # produces myobject~.mxo / myobject~.mxe64
```

## Making DSP objects MC compatible

In `/init/object-mappings.txt`, add a line like:
```
max objectfile mc.<your object>~ mc.wrapper~ <your object>~;
```

## Writing documentation

Make sure for each object you write to make a `docs/<your object>.maxref` (see
the example for guidance) and a `help/<your object>.maxhelp`.

## Building with CMake

```shell
mkdir build
cd build
cmake -G Xcode ..  # macOS
cmake -G "Visual Studio 17 2022" ..  # Windows
cmake --build . --config Release
```
