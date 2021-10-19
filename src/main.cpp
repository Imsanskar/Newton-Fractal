#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Renderer.h>
#include "Math/matrix.h"
#include "Math/vec.h"



int main() {
	glfwInit();

	Renderer renderer;
	UserContext context;
	context.renderer = &renderer;

	const int width = 1920, height = 1400;
	renderer.width = width;
	renderer.height = height;
	float aspectRatio = float(width) / float(height);
	GLFWwindow* window = glfwCreateWindow(width, height, "Newton Fractal", NULL, NULL);

	//open gl settings
	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetWindowUserPointer(window, &context);
	glfwSetScrollCallback(window, scrollCallBack);

	Shader shader("../resources/shaders/fractalVert.glsl", "../resources/shaders/fractalFrag.glsl");

	float vertices[] = {
		-1.0f, -1.0f,
		1.0f, -1.0f,
		-1.0f, 1.0f,
		1.0f, 1.0f,
	};

	uint32_t indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		0, 2, 3    // second triangle
	};

	VertexBuffer vb(vertices, sizeof(vertices));
	IndexBuffer indexBuffer(indices, sizeof(indices));
	VertexBufferLayout vbLayout;
	vbLayout.push<float>(2);
	VertexArray va;
	va.addBuffer(vb, vbLayout);

	//shader set width height
	MathLib::vec2 rectMin(-8.5f, -7.0f);	
	MathLib::vec2 rectMax(4.0f, 7.0f);	

	context.rectMin = rectMin;
	context.rectMax = rectMax;

	shader.bind();
	glCheckError(shader.setUniform("width", static_cast<float>(width)));
	glCheckError(shader.setUniform("height", static_cast<float>(height)));
	glCheckError(shader.setUniform("rectMin", rectMin));
	glCheckError(shader.setUniform("rectMax", rectMax));
	//set the array of the roots
	shader.setUniform("roots[0]", MathLib::vec2(1, 0));
	shader.setUniform("roots[1]", MathLib::vec2(-0.5, pow(3, 0.5) / 2));
	shader.setUniform("roots[2]", MathLib::vec2(-0.5, - pow(3, 0.5) / 2));

	//set the color for each root
	shader.setUniform("colors[0]", MathLib::vec3(3, 138, 138) / 255);
	shader.setUniform("colors[1]", MathLib::vec3(138, 3, 138) / 255);
	shader.setUniform("colors[2]", MathLib::vec3(138, 138, 3) / 255);

	shader.unbind();


	while (!glfwWindowShouldClose(window)){
		glClearColor(0.3f, 0.3f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		UserContext *context = (UserContext *)glfwGetWindowUserPointer(window);

		shader.bind();
		glCheckError(shader.setUniform("width", static_cast<float>(renderer.width)));
		glCheckError(shader.setUniform("height", static_cast<float>(renderer.height)));
		glCheckError(shader.setUniform("rectMin", context->rectMin));
		glCheckError(shader.setUniform("rectMax", context->rectMax));
		shader.unbind();

		renderer.draw(va, indexBuffer, shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
		renderer.processKeyboardInput(window);
	}
}