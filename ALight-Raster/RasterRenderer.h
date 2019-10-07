#pragma once
#include "../ALightCreator/BufferRenderer.h"
#include "../Common/include/glm/vec4.hpp"
#include "../Common/include/glm/vec3.hpp"
#include "../Common/include/svg/nanosvg.h"
#include "../Common/include/glm/mat4x4.hpp"
#include "Point.h"
using namespace  ALightCreator;
namespace ALight_Raster
{
	class  RasterRenderer:public BufferRenderer
	{
	public:
		void Render() override;														// Called every frame
		void DrawLine(int x1,int y1,int x2,int y2, glm::vec3 color,float r=1) const;
		void DrawPath(float* pts, int npts);
		void SetPixel(int x, int y, glm::vec4 color) const; //Draw a point on buffer
		void Start() override;
		void Destroy() override;
		
		void RasterlizeSVG(NSVGimage* image, float tx, float ty, float scale,
			unsigned char* dst, int w, int h, int stride);
		NSVGimage* g_image = NULL;
		bool VerticalFlip = true; //Due to the buffer, I need to flip it vertically

	private:
		void FillTriangle(Point* top, Point* down, Point* left, Point* right, int mode);
		void ScanLine(int x1, int x2, int y);
		glm::vec4 brushColor,strokeColor;
		float strokeWidth;
		glm::mat4 mvp;
		void DrawTriangle(Point** vertices);
		int Compare(const void* a, const void* b);
	};
}
