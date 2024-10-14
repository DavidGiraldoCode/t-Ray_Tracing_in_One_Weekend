# Ray Tracing in One Weekend (or perhaps more than one)
With this study I aim to deepen my knowledge in fundamental Computer Graphic algorithms and have fun while at it.

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
## Devlog
<p> First sphere and the normals-shaded </p>
<img width="397" alt="image" src="https://github.com/user-attachments/assets/2dc1e07a-5ca4-46b2-a6ed-e8aa2655e91a">
<img width="397" alt="image" src="https://github.com/user-attachments/assets/d7595d90-a7b6-431a-9d25-2700507bbf3f">


<p> Graphics HelloWorld! </p>
<img width="397" alt="image" src="https://github.com/user-attachments/assets/e0af3b5c-bb7d-4c2e-9dc0-0800987342ff">

# Reference
[_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
