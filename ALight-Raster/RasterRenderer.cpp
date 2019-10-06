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

glm::vec4 colorConverter(int hexValue)
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


	
	float view[4], cx, cy, hw, hh, aspect;


	cx = g_image->width * 0.5f;
	cy = g_image->height * 0.5f;
	hw = g_image->width * 0.5f;
	hh = g_image->height * 0.5f;

	if (width / hw < height / hh) {
		aspect = static_cast<float>(height) / static_cast<float>(width);
		view[0] = cx - hw * 1.2f;
		view[2] = cx + hw * 1.2f;
		view[1] = cy - hw * 1.2f * aspect;
		view[3] = cy + hw * 1.2f * aspect;
	}
	else {
		aspect = static_cast<float>(width) / static_cast<float>(height);
		view[0] = cx - hh * 1.2f * aspect;
		view[2] = cx + hh * 1.2f * aspect;
		view[1] = cy - hh * 1.2f;
		view[3] = cy + hh * 1.2f;
	}
	const auto px = (view[2] - view[1]) / static_cast<float>(width);

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
	triangulate(pt, out);
	for(int i=0;i<out.size();i+=3)DrawTriangle(&out[i]);

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
	//g_image = nsvgParseFromFile("../Resources/SVG/alpha/02_cube.svg", "px", 96.0f);
	g_image = nsvgParseFromFile("../Resources/SVG/basic/test4.svg", "px", 96.0f);
	//g_image = nsvgParseFromFile("../Resources/SVG/alpha/05_sphere.svg", "px", 96.0f);
	//g_image = nsvgParseFromFile("../Resources/SVG/basic/test6.svg", "px", 96.0f);
	//g_image = nsvgParseFromFile("../Resources/SVG/illustration/07_lines.svg", "px", 96.0f);


	if (g_image == nullptr) {
		printf("Could not open SVG image.\n");
	}
}

void ALight_Raster::RasterRenderer::Destroy()
{
	nsvgDelete(g_image);
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
	case 1: { //Bottom Flat
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
		case 2: //Top Flat
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

void ALight_Raster::RasterRenderer::ScanLine(int x1, int x2, int y)
{
	auto dx = x1 - x2;
	if(y>height)return;
	for (float x=x1;x<=x2;x+=0.5f)
	{
		const auto  xIndex = static_cast<int>(x + 0.5f);
		if (xIndex > 0 && xIndex < width)
		{
			SetPixel(xIndex, y, brushColor);
		}
	}
}

void ALight_Raster::RasterRenderer::DrawTriangle(Point** vertices)
{
	
	std::qsort(vertices, 3, sizeof(Point*), 
		[](const void* a, const void* b) {return ((Point * *)a)[0]->y - ((Point * *)b)[0]->y; });
	if (vertices[1]->y == vertices[2]->y)
		FillTriangle(vertices[0], vertices[0] /*NULL*/, vertices[1], vertices[2], 1); // BottomFlat
	else if (vertices[0]->y == vertices[1]->y)
		FillTriangle(vertices[0] /*NULL*/, vertices[2], vertices[0], vertices[1], 2); // TopFlat
	else
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

int ALight_Raster::RasterRenderer::Compare(const void* a, const void* b)
{
	return ((Point*)a)->y - ((Point*)b)->y;
}
