#include "pch.h"
#include "Engine/Engine.h"

int main(int argc, char** argv) {

	ew::Engine engine;
	engine.startup();

	//float vertices[] = {
	//	-0.5f, -0.5f, 0, 1.0f, 0, 0, 0, 0,
	//	0.0f, 0.5f, 0, 0, 1.0f, 0, 0.5f, 1.0f, 
	//	0.5f, -0.5f, 0, 0, 0, 1.0f, 1.0f, 0
	//};

	static float vertices[] = {
		-1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f,  1.0f, 0.0f, 1.0f,

		-1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f,  1.0f, -1.0f, 1.0f, 1.0f
	};

	static GLushort indices[] = {
		0, 1, 2, 
		2, 3, 0,

		1, 5, 6, 
		6, 2, 1,

		7, 6, 5, 
		5, 4, 7,

		4, 0, 3,
		3, 7, 4,

		4, 5, 1,
		1, 0, 4,

		3, 2, 6,
		6, 7, 3
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (800 / 600.0f), 0.01f, 1000.0f);

	glm::vec3 eye{ 0, 0, 5 };
	glm::mat4 camera = glm::lookAt(eye, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

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

		engine.update();
		
		float angle = 0;
		if (engine.getSystem<ew::InputSystem>()->getButtonState(SDL_SCANCODE_E) == ew::InputSystem::ButtonState::HELD) {
			angle = 2.0f;
		}
		if (engine.getSystem<ew::InputSystem>()->getButtonState(SDL_SCANCODE_Q) == ew::InputSystem::ButtonState::HELD) {
			angle = -2.0f;
		}
		model = glm::rotate(model, angle * engine.getTimer().deltaTime(), glm::vec3(0, 1, 0));

		if (engine.getSystem<ew::InputSystem>()->getButtonState(SDL_SCANCODE_A) == ew::InputSystem::ButtonState::HELD) {
			eye.x -= 4 * engine.getTimer().deltaTime();
		}
		if (engine.getSystem<ew::InputSystem>()->getButtonState(SDL_SCANCODE_D) == ew::InputSystem::ButtonState::HELD) {
			eye.x += 4 * engine.getTimer().deltaTime();
		}
		if (engine.getSystem<ew::InputSystem>()->getButtonState(SDL_SCANCODE_W) == ew::InputSystem::ButtonState::HELD) {
			eye.z -= 4 * engine.getTimer().deltaTime();
		}
		if (engine.getSystem<ew::InputSystem>()->getButtonState(SDL_SCANCODE_S) == ew::InputSystem::ButtonState::HELD) {
			eye.z += 4 * engine.getTimer().deltaTime();
		}
		//if (engine.getSystem<ew::InputSystem>()->getButtonState(SDL_SCANCODE_Q) == ew::InputSystem::ButtonState::HELD) {
		//	eye.y -= 4 * engine.getTimer().deltaTime();
		//}
		//if (engine.getSystem<ew::InputSystem>()->getButtonState(SDL_SCANCODE_E) == ew::InputSystem::ButtonState::HELD) {
		//	eye.y += 4 * engine.getTimer().deltaTime();
		//}
		camera = glm::lookAt(eye, eye + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

		glm::mat4 mvp = projection * camera * model;

		program.setUniform("transform", mvp);

		engine.getSystem<ew::Renderer>()->beginFrame();

		GLsizei numElements = sizeof(indices) /sizeof(GLushort);

		glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_SHORT, 0);

		engine.getSystem<ew::Renderer>()->endFrame();
	}
	engine.shutdown();

	return 0;
}