#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cassert>

static void resize_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

static void handle_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main(void)
{
	assert(glfwInit());
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow *window = glfwCreateWindow(800, 600, "Snake", nullptr, nullptr);
	assert(window);
	glfwMakeContextCurrent(window);

	assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, resize_callback);

	while (!glfwWindowShouldClose(window))
	{
		handle_input(window);
		
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}