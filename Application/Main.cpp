#include "pch.h"
#include <glad/glad.h>
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Program.h"

int main(int argc, char** argv) {

	ew::Renderer renderer;
	renderer.startup();
	renderer.create("OpenGL", 800, 600);

	float vertices[] = {
		-0.5f, -0.5f, 0, 1.0f, 0, 0,
		0.0f, 0.5f, 0, 0, 1.0f, 0,
		0.5f, -0.5f, 0, 0, 0, 1.0f
	};

	ew::Program program; 
	program.createShaderFromFile("shaders\\basic.vert", GL_VERTEX_SHADER); 
	program.createShaderFromFile("shaders\\basic.frag", GL_FRAGMENT_SHADER); 
	program.link();
	program.use();



	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//const char* str = vertexShaderSource.c_str();
	//glShaderSource(vertexShader, 1, &str, nullptr);
	//glCompileShader(vertexShader);

	//GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//str = fragmentShaderSource.c_str();
	//glShaderSource(fragmentShader, 1, &str, nullptr);
	//glCompileShader(fragmentShader);

	//GLuint program = glCreateProgram();
	//glAttachShader(program, vertexShader);
	//glAttachShader(program, fragmentShader);
	//glLinkProgram(program);

	//glUseProgram(program);


	bool quit = false; 

	while (!quit) {
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				quit = true;
			}
		}
		SDL_PumpEvents(); 

		renderer.beginFrame();

		glDrawArrays(GL_TRIANGLES, 0, 3);

		renderer.endFrame();
	}
	return 0;
}