#pragma once

#define NOMINMAX
// BASIC
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <memory>
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <functional>

// shortcut
#define DataMap std::map
#define DataArray std::vector
#define DataString std::string
// OPENGL
#include <GLAD/glad.h>
//#include <GLEW\glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>

// SDL
#include <SDL.h>
#include <SDL_image.h>
typedef uint8_t CHART;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef intptr_t intptr;
typedef uintptr_t uintptr;

#define LOG_ERROR "Error"
#define LOG_WARNING "Warning"
#define LOG_TYPE_RENDERER "Renderer"
#define LOG_TYPE_IO "IO"
#define DEBUG_LOG(category, level, message, ...) \
	fprintf(stderr, "[%s] ", category); \
	fprintf(stderr, "[%s] (%s:%d): ", level, __FILE__, __LINE__); \
	fprintf(stderr, message, ##__VA_ARGS__); \
	fprintf(stderr, "\n")
#define NULL_COPY_AND_ASSIGN(T) \
	T(const T& other) {(void)other;} \
	void operator=(const T& other) { (void)other; }