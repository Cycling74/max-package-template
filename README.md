# max-template

Basic template for Max externals made with the Max C SDK (max-base-sdk), including GitHub Actions for automated CI builds.

## Creating objects
Objects should each be made inside a directory inside of `/source/projects/` like the example. See the max-sdk repository for examples of how to write Max objects with the C SDK.

## Making DSP objects MC compatible
In `/init/object-mappings.txt`, add a line like:
```
max objectfile mc.<your object>~ mc.wrapper~ <your object>~;
```

## Writing documentation

Make sure for each object you write to make a `docs/<your object>.maxref` (see the example for guidance) and a `help/<your object>.maxhelp` (see the example as well).

## Building with CMake
```
mkdir build
cd build
cmake -G Xcode ..  # or cmake -G "Visual Studio 16 2019" or cmake -G Ninja ..
cmake --build .
```