#include "BufferRenderer.h"
#include <glad/glad.h>
#include <iostream>
#include "Engine.h"

void BufferRenderer::Init()
{
	buffer = new unsigned char[height * width * 3];
	InitFrameBuffer();
}
//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);

/*
	glTexImage2D - the slowest one, recreates internal data structures.
	glTexSubImage2D - a bit faster, but can't change the parameters (size, pixel format) of the image.
	Render-to-texture with FBO - update texture entirely on GPU, very fast. Refer to this answer for more details: https://stackoverflow.com/a/10702468/1065190
	Pixel Buffer Object PBO - for fast uploads from CPU to GPU, not supported (yet) on OpenGL ES.
*/

// glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer);
void BufferRenderer::Update()
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferPointer);
	Render();
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0,0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer); //Show
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void BufferRenderer::Terminate()
{
	free(buffer);
}

unsigned BufferRenderer::FrameBuffer()
{
	return frameColorBuffer;
}



void BufferRenderer::Resize(int w, int h)
{
	//width = w;
	//height = h;
}

void BufferRenderer::InitFrameBuffer()
{	// framebuffer configuration
	// -------------------------
	glGenFramebuffers(1, &framebufferPointer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferPointer);
	// create a color attachment texture
	glGenTextures(1, &frameColorBuffer);
	glBindTexture(GL_TEXTURE_2D, frameColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameColorBuffer, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)

	// glGenRenderbuffers(1, &frameDepthBuffer);
	// glBindRenderbuffer(GL_RENDERBUFFER, frameDepthBuffer);
	// glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // use a single renderbuffer object for both a depth AND stencil buffer.
	// glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, frameDepthBuffer); // now actually attach it
	// // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	// if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	// 	std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	// glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
