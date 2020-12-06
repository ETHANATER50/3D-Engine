#include "pch.h"
#include <glad/glad.h>
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Program.h"
#include "Engine/Graphics/Texture.h"

int main(int argc, char** argv) {

	ew::Renderer renderer;
	renderer.startup();
	renderer.create("OpenGL", 800, 600);

	float vertices[] = {
		-0.5f, -0.5f, 0, 1.0f, 0, 0, 0, 0,
		0.0f, 0.5f, 0, 0, 1.0f, 0, 0.5f, 1.0f, 
		0.5f, -0.5f, 0, 0, 0, 1.0f, 1.0f, 0
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),(void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glm::mat4 transform = glm::mat4(1.0f);
	program.setUniform("transform", transform);

	ew::Texture texture;
	texture.createTexture("textures\\llama.jpg");
	

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


		transform = glm::rotate(transform, 0.001f, glm::vec3(0, 0, 1));
		program.setUniform("transform", transform);

		renderer.beginFrame();

		glDrawArrays(GL_TRIANGLES, 0, 3);

		renderer.endFrame();
	}
	return 0;
}