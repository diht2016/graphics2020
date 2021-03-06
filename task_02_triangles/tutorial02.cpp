// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include <common/shader.hpp>

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Task 02 - not very red triangles", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Create and compile our GLSL program from the shaders
	GLuint program0 = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader0.fragmentshader" );
	GLuint program1 = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader1.fragmentshader" );


	static const GLfloat g_vertex_buffer_data[] = { 
		-0.7f, -0.4f, 0.0f,
		-0.5f, -0.7f, 0.0f,
		 0.5f,  0.7f, 0.0f,
		 0.7f, -0.4f, 0.0f,
		 0.5f, -0.7f, 0.0f,
		-0.5f,  0.7f, 0.0f,
	};

	GLuint VertexArray;
	glGenVertexArrays(1, &VertexArray);
	glBindVertexArray(VertexArray);
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	do{

		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glUseProgram(program0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glUseProgram(program1);
		glDrawArrays(GL_TRIANGLES, 3, 3);
		
		glDisable(GL_BLEND);
		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO
	glDeleteVertexArrays(1, &VertexArray);
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(program0);
	glDeleteProgram(program1);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

