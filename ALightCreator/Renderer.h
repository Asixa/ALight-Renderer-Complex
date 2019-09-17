#pragma once
class  Renderer
{
public:

	virtual void Init() {};
	virtual void RenderLoop() {};
	virtual void Terminate() {};
	virtual unsigned int FrameBuffer() { return 0; };
	virtual void Resize(int w, int h) {};
};