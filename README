# MazeRunner

A simple C++ maze game using SDL3 and OpenGL.

---

## Requirements

- C++ compiler supporting C++20 (tested with g++)  
- Make (`mingw32-make` on Windows)  
- SDL3 development libraries  
- OpenGL development libraries  
- GLEW development libraries (for OpenGL function loading)  

---

## Project Structure
```bash
MazeRunner/
├─ src/ # Source code
├─ include/program/ # Program headers
├─ include/GL/ # OpenGL headers (ignored in repo) YOU MUST ADD THIS ON WINDOWS
├─ include/SDL3/ # SDL3 headers (ignored in repo) YOU MUST ADD THIS ON WINDOWS
├─ lib/GL/ # OpenGL libraries (ignored in repo) WINDOWS ONLY
├─ lib/SDL3/ # SDL3 libraries (ignored in repo) WINDOWS ONLY
├─ dll/ # DLLs for Windows runtime (ignored in repo) NEEDED FOR WINDOWS
├─ build/debug/ # Build output (ignored in repo)
├─ Makefile
├─ README.md
├─ Licenses/
```
---

## Setup

### Notes
- The Makefile automatically handles Windows DLLs.  
- On Linux/macOS, `pkg-config` ensures proper compiler and linker flags for SDL3.  
- If you encounter missing library or header errors, double-check your installation paths and ensure `pkg-config` is correctly configured on Linux/macOS.  
---

### Linux/macOS (pkg-config)

1. Install SDL3 and GLEW using your package manager:

#### macOS
```bash
brew install sdl3 glew
```

#### Ubuntu/Linux
```bash
sudo apt install libsdl3-dev libglew-dev
```

#### No need to manually copy headers or libraries. The Makefile automatically detects them using pkg-config.

2. Clone the repository:
```bash
git clone https://github.com/your-username/MazeRunner.git
```

3. Compile the project:
```bash
make
```

4. Run the project:
```bash
./build/debug/mazerunner
```

### Windows 
1. Download SDL3, OpenGL, and GLEW development libraries.

#### Links:
- https://github.com/libsdl-org/SDL/releases/tag/release-3.2.24

- https://glew.sourceforge.net/

2. Copy headers into the following folders:
```bash
include/SDL3/
include/GL/
```

3. Copy library files (.a) into:
```bash
lib/SDL3/
lib/GL/
```
4. Copy runtime DLLs from SDL3/GLEW into the dll/ folder. The Makefile will copy them into build/debug/ automatically.


5. From the project root, build the project:

```bash
make
``` 

6. Run the project:
```bash
./build/debug/mazerunner.exe
```

### Notes
- Make sure your project structure matches the one above. 
---

## Cleaning Build Files
To remove all compiled objects and the executable:

```bash
make clean
```