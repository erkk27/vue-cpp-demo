# C++ Backend

This is a simple C++ HTTP server using Windows API and standard C++ libraries.

## Requirements

- GCC compiler (MinGW-w64/MSYS2)
- Windows operating system

## Build

This project can be compiled directly using GCC without any external dependencies or build systems.

### Option 1: Simple Compilation (Recommended)

From the `backend` directory, run:

```bash
# Compile the server
g++ -std=c++17 -Wall -Wextra -o cpp_backend main.cpp -lws2_32 -lpthread

# Or use the provided batch file
compile.bat
```

### Option 2: Using CMake

If you prefer using CMake, you can use the provided build script:

```bash
build.bat
```

### Run

After compiling, run the server:

```bash
./cpp_backend
```

The server will start on `http://localhost:18080`.

## API Endpoints

- `GET /api/message` - Returns a JSON response with a greeting message

Example response:
```json
{
  "message": "Hello from C++ backend!"
}
```

## Features

- Simple HTTP server implementation
- CORS support for web frontend
- Multi-threaded request handling
- No external dependencies required 