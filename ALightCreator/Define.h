#pragma once
#include "../ALight-OpenGL/GLRenderer.h"
#include "../ALight-Raster/RasterRenderer.h"
#include "../ALight-RayCPU/RayCPURenderer.h"
#define RENDERER ALight_OpenGL::GLRenderer
#define RENDERER ALight_RayCPU::RayCPURenderer
#define RENDERER ALight_Raster::RasterRenderer