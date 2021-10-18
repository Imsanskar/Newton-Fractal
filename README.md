# Newton-Fractal
Rendering of a Newton Fractal using OpenGL
### System Requirements
-  Operating System : Linux/ Windows
-  Programming Language : C/C++
-  Graphics API : OpenGL 4.4
-  Library : GLFW
-  OpenGL Loader: GLAD
- Build system: Solution file(Visual Studio), CMake & Makefile(build.bat)

### Build Process(Windows)
#### Visual Studio
- Set your working directory as ```$(ProjectDir)build``` 
![vs](screenshots/vs-config.png)
- Build using visual studio in **Release** mode and run the exe in ```build``` directory

#### Command Line(Windows)
You either need to use ```x64 Command prompt for VS``` or need to install ```clang``` to build the project using command line.
- Navigate to the source directory from the command line 
- Run the ```build.bat``` file from the project directory

### Outputs
Fractal for z^3 - 1 with a = 1
![out](screenshots/fractal-zoom-out.png)  
![in](screenshots/fractal-zoom-in.png)

### Controls
```Scroll```- For zoom in and out  
```W A S D```-Movement

### References
[Newton Fractal Wiki](https://en.wikipedia.org/wiki/Newton_fractal)  
[3b1b Video](https://youtu.be/-RdOwhmqP5s)
