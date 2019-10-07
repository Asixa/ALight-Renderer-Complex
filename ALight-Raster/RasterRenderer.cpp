#include "RasterRenderer.h"
#include "../Common/include/glm/vec3.hpp"
#define NANOSVG_IMPLEMENTATION
#include "../Common/include/svg/nanosvg.h"
#include <ios>
#include "Math.h"
#include "Point.h"
#include <algorithm>
#include "Trianglation.h"
#include "../Common/include/glm/gtc/type_ptr.inl"
#include "../ALightCreator/Engine.h"
#include "../ALightCreator/Camera.h"

glm::vec4 colorConverter(int hexValue) // yeah... the svg load save the color in hex, so I need to extract rgb form the hex number.
{
	glm::vec4 rgbColor;
	rgbColor.b = ((hexValue >> 16) & 0xFF) / 255.0;  // Extract the RR byte
	rgbColor.g = ((hexValue >> 8) & 0xFF) / 255.0;   // Extract the GG byte
	rgbColor.r = ((hexValue) & 0xFF) / 255.0;        // Extract the BB byte
	rgbColor.w = 1;
	return rgbColor;
}
void ALight_Raster::RasterRenderer::Render()
{
	// Calculate global mvp matrix every frame
	mvp= glm::make_mat4(Engine::GetInstance().scene->objectMatrix)* 
		Camera::main->view*
		Camera::main->projection;
	
	for (auto shape = g_image->shapes; shape != nullptr; shape = shape->next) {
		brushColor = colorConverter(shape->fill.color);
		strokeColor = colorConverter(shape->stroke.color);
		strokeWidth = shape->strokeWidth;
		for (auto path = shape->paths; path != nullptr; path = path->next) {
			DrawPath(path->pts, path->npts);
		}
	}
}


//带符号距离场（signed distance field, SDF）永远判断该点是否在线上，然后通过不同的alpha值 来实现抗锯齿
float SDF(const float px, const float py, const float ax, const float ay, const float bx, const float by, const float r) {
	const auto pax = px - ax,pay = py - ay, bax = bx - ax, bay = by - ay;
	const auto h = fmaxf(fminf((pax * bax + pay * bay) / (bax * bax + bay * bay), 1.0f), 0.0f);
	const auto dx = pax - bax * h, dy = pay - bay * h;
	return sqrtf(dx * dx + dy * dy) - r;
}
void ALight_Raster::RasterRenderer::DrawLine(const int sx, const int sy, const int ex, const int ey, glm::vec3 color,float r) const
{
	const auto x0 = static_cast<int>(floorf(fminf(sx, ex) - r));
	const auto x1 = static_cast<int>(ceilf(fmaxf(sx, ex) + r));
	const auto y0 = static_cast<int>(floorf(fminf(sy, ey) - r));
	const auto y1 = static_cast<int>(ceilf(fmaxf(sy, ey) + r));
	for (auto y = y0; y <= y1; y++)
		for (auto x = x0; x <= x1; x++)
			SetPixel(x, y, glm::vec4(color, fmaxf(fminf(0.5f - SDF(x, y, sx, sy, ex, ey, r), 1.0f), 0.0f)));
}

void ALight_Raster::RasterRenderer::DrawPath(float* pts, int npts)
{
	std::vector<Point*> out; std::vector<Point*> pt;
	
	for (auto i = 0; i < npts - 1; i += 3) { //Polygon points
		const auto p = &pts[i * 2];
		pt.push_back(new Point(glm::vec4(p[0], p[1],-100,1)*mvp));
		pt.push_back(new Point(glm::vec4(p[2], p[3], -100, 1) * mvp));
		pt.push_back(new Point(glm::vec4(p[4], p[5], -100, 1) * mvp));
	}
	//Do the mvp transformation before trianglation
	triangulate(pt, out);
	for(int i=0;i<out.size();i+=3)DrawTriangle(&out[i]); //Draw triangles


	//in this part, I want to draw the outline of the polygon
	for (auto i = 0; i < npts - 1; i += 3) {
		const auto p = &pts[i * 2];
		auto a = new Point(glm::vec4(p[0], p[1], -100, 1) * mvp);
		auto b= new Point(glm::vec4(p[2], p[3], -100, 1) * mvp);
		auto c = new Point(glm::vec4(p[4], p[5], -100, 1) * mvp);
		auto d = new Point(glm::vec4(p[6], p[7], -100, 1) * mvp);
		DrawLine(a->x, a->y, b->x, b->y, strokeColor,strokeWidth/5);
		DrawLine(b->x, b->y, c->x, c->y, strokeColor, strokeWidth/5);
		DrawLine(c->x, c->y, d->x, d->y, strokeColor, strokeWidth/5);
	}
}

void ALight_Raster::RasterRenderer::SetPixel(const int x, int y, const glm::vec4 color) const
{
	if (x<0 || x>width)return;
	if(y<0||y>height)return;
	if (VerticalFlip)y = height - y;
	const auto p = buffer + (y * width + x) * 3;
	p[0] = static_cast<unsigned char>(p[0] * (1 - color.a) + color.r * color.a * 255);
	p[1] = static_cast<unsigned char>(p[1] * (1 - color.a) + color.g * color.a * 255);
	p[2] = static_cast<unsigned char>(p[2] * (1 - color.a) + color.b * color.a * 255);
}

void ALight_Raster::RasterRenderer::Start()
{
	// init the scene

	
	//g_image = nsvgParseFromFile("../Resources/SVG/alpha/02_cube.svg", "px", 96.0f);
	g_image = nsvgParseFromFile("../Resources/SVG/basic/test4.svg", "px", 96.0f);
	//g_image = nsvgParseFromFile("../Resources/SVG/alpha/05_sphere.svg", "px", 96.0f);
	//g_image = nsvgParseFromFile("../Resources/SVG/basic/test6.svg", "px", 96.0f);
	//g_image = nsvgParseFromFile("../Resources/SVG/illustration/07_lines.svg", "px", 96.0f);


	if (g_image == nullptr) printf("Could not open SVG image.\n");
	
}

void ALight_Raster::RasterRenderer::Destroy()
{
	nsvgDelete(g_image);  // Free the memory
}




void ALight_Raster::RasterRenderer::FillTriangle(Point* top, Point* down, Point* left,Point* right, int mode)
{
	if (left->x > right->x)
	{
		const auto t = left;
		left = right;
		right = t;
	}

	switch (mode)
	{
	case 0:
	case 1: {																						//Bottom Flat triangle
																									//      /\
																									//     /  \
																									//    /____\            
		auto dxy_left = (left->x - top->x) * 1.0f / (left->y - top->y);
		auto dxy_right = (right->x - top->x) * 1.0f / (right->y - top->y);
		float xs = top->x, xe = top->x;
		for (auto y = top->y; y <= right->y; y++)
		{
			auto v = (xe - xs == 0) ? 0 : (xe - xs) / (right->x - left->x);
			xs += dxy_left;
			xe += dxy_right;

			ScanLine(Math::Lerp(top->x, left->x, v), Math::Lerp(top->x, right->x, v), (int)y);
		}

		if (mode == 0) {}
		else break;
	}
		case 2:																						//Top Flat  triangle
																									//		_______
																									//      \     /	
																									//       \   /
																									//        \ /
																									//		   V          
		{
	
			auto dxy_left = (down->x - left->x) * 1.0f / (down->y - left->y);
			auto dxy_right = (down->x - right->x) * 1.0f / (down->y - right->y);
			float xs = left->x;
			float xe = right->x;
			for (auto y = left->y; y <= down->y; y++)
			{
				auto v = (xe - xs == 0) ? 0 : (xe - xs) / (right->x - left->x);
				ScanLine(Math::Lerp(down->x, left->x, v), Math::Lerp(down->x, right->x, v), (int)y);
				xs += dxy_left;
				xe += dxy_right;
			}

			break;
		}
	}

}

void ALight_Raster::RasterRenderer::ScanLine(int x1, int x2, int y) // simply draw a horizontal line from (x1,y) to (x2,y)
{
	auto dx = x1 - x2;
	if(y>height)return;
	for (float x=x1;x<=x2;x+=0.5f)
	{
		const auto  xIndex = static_cast<int>(x + 0.5f);
		if (xIndex > 0 && xIndex < width)SetPixel(xIndex, y, brushColor);
	}
}

void ALight_Raster::RasterRenderer::DrawTriangle(Point** vertices)
{
	// sort the vertices by y
	std::qsort(vertices, 3, sizeof(Point*), [](const void* a, const void* b) {return ((Point * *)a)[0]->y - ((Point * *)b)[0]->y; }); 

	
	if (vertices[1]->y == vertices[2]->y)
		FillTriangle(vertices[0], vertices[0] /*NULL*/, vertices[1], vertices[2], 1); // this triangle is BottomFlat triangle, simple
	else if (vertices[0]->y == vertices[1]->y)
		FillTriangle(vertices[0] /*NULL*/, vertices[2], vertices[0], vertices[1], 2); // this triangle is TopFlat triangle
	
	else              // other wise we need to cut it, to generate two triangle
	{
		auto middle_length = (vertices[1]->y - vertices[0]->y) *
			(vertices[2]->x - vertices[0]->x) /
			(vertices[2]->y - vertices[0]->y) +
			vertices[0]->x;
		auto t = (vertices[0]->y - vertices[1]->y) * 1.0f / (vertices[0]->y - vertices[2]->y);
		auto middle = Point::Lerp(vertices[0], vertices[2], t);
		FillTriangle(vertices[0], vertices[2], 
			middle_length > vertices[1]->x ? vertices[1] : middle,middle_length < vertices[1]->x ? vertices[1] : middle, 0);
	}
}

