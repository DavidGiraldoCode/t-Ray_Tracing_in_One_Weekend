# Ray Tracing in One Weekend (or perhaps more than one)

## To build the project in Debug mode:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
build/Debug/myRayTracer > Renders/render.ppm
```
Here we are telling CMake to generate files for a Debug build. And the command compiles the project and creates the executable in build/Debug/

## To build in Release mode for optimized performance:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config release
build/Release/myRayTracer > Renders/render.ppm
```

## File structure
```bash
/myRayTracerProject
│
├── CMakeLists.txt            
├── /build                    # Generated build folder (after running cmake)
├── /Source                   
│   └── main.cpp              
└── /Renders

```

# Reference
[_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html)