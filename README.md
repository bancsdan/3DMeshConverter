# 3DMeshConverter

## Cloning the repo

You need to clone recursively, since the project uses GTest for testing.
```
git clone --recursive https://github.com/bancsdan/3DMeshConverter.git
```
## Building the converter

Have CMake > 3.7 installed.
Was tested with clang-6.0, gcc-8.4 and MSVC-19.26.

In the root of the project:
```
mkdir build
cd build
cmake ..
cmake --build .
```
On windows to build Release version:
```
cmake --build . --config Release
```

## Using the converter

```
Options:
  -h,--help                   Print this help message and exit
  --scale [FLOAT,FLOAT,FLOAT] Specifies the (x,y,z) scale of the scaling. Default is (1,1,1).
  --rotate [FLOAT,FLOAT,FLOAT,FLOAT]
                              Specifies the (x,y,z,angle) axis of the rotation and the angle in radians.
  --translate [FLOAT,FLOAT,FLOAT]
                              Specifies the (x,y,z) amount of the translation.
  --is_point_inside [FLOAT,FLOAT,FLOAT]
                              Specifies the (x,y,z) coordinates of the point you wish to know if it is inside the mesh or not.
  --input TEXT REQUIRED       The path to the input file.
  --output TEXT REQUIRED      The path to the output file.
```

Example on windows:
```
./converter_cli.exe --input ./example.obj --output ./example.stl --is_point_inside 20 20 20 --rotate 1 0 0 1.7 --scale 1 5 1
```

## Running the tests

It is fairly simple, the only thing to pay attention to is that you have to run them from the build/ directory
since Cmake copies a test file into the build directory.

```
./path_to_tests_binary/converter_tests
```
