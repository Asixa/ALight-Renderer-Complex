#pragma once
class  Renderer
{
public:

	virtual void init_shader(){};
	virtual void init_texture() {};
	virtual void init_data() {};
	virtual void render_loop() {};
	virtual void terminate() {};
	virtual unsigned int frame_buffer() { return 0; };
	virtual void on_change_size(int w, int h){};
};