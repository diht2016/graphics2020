// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
	window = glfwCreateWindow( 1024, 768, "Tutorial 04 - Colored Cube", NULL, NULL);
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

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );

	static GLfloat g_vertex_buffer_data[4*4*6*3] = {
		 0.75, -0.25, -0.75,
		 1.25, -0.25,  1.25,
		 0.75, -0.25,  0.75,
		 1.25, -0.25, -1.25,
		 1.25, -0.25,  1.25,
		 0.75, -0.25, -0.75,
		 
		 1.25, -0.25,  1.25,
		 1.25, -0.25, -1.25,
		 1.25,  0.25,  1.25,
		 1.25,  0.25,  1.25,
		 1.25, -0.25, -1.25,
		 1.25,  0.25, -1.25,
		 
		 1.25,  0.25,  1.25,
		 1.25,  0.25, -1.25,
		 0.75,  0.25,  0.75,
		 0.75,  0.25,  0.75,
		 1.25,  0.25, -1.25,
		 0.75,  0.25, -0.75,
		 
		 0.75,  0.25, -0.75,
		 0.75, -0.25,  0.75,
		 0.75,  0.25,  0.75,
		 0.75, -0.25, -0.75,
		 0.75, -0.25,  0.75,
		 0.75,  0.25, -0.75,
		 
		 
		-0.75, -0.25, -0.75,
		 1.25, -0.25, -1.25,
		 0.75, -0.25, -0.75,
		-1.25, -0.25, -1.25,
		 1.25, -0.25, -1.25,
		-0.75, -0.25, -0.75,
					   
		 1.25, -0.25, -1.25,
		-1.25, -0.25, -1.25,
		 1.25,  0.25, -1.25,
		 1.25,  0.25, -1.25,
		-1.25, -0.25, -1.25,
		-1.25,  0.25, -1.25,
					   
		 1.25,  0.25, -1.25,
		-1.25,  0.25, -1.25,
		 0.75,  0.25, -0.75,
		 0.75,  0.25, -0.75,
		-1.25,  0.25, -1.25,
		-0.75,  0.25, -0.75,
					   
		-0.75,  0.25, -0.75,
		 0.75, -0.25, -0.75,
		 0.75,  0.25, -0.75,
		-0.75, -0.25, -0.75,
		 0.75, -0.25, -0.75,
		-0.75,  0.25, -0.75,
		 
		 
		-0.75, -0.25,  0.75,
		-1.25, -0.25, -1.25,
		-0.75, -0.25, -0.75,
		-1.25, -0.25,  1.25,
		-1.25, -0.25, -1.25,
		-0.75, -0.25,  0.75,
		
		-1.25, -0.25, -1.25,
		-1.25, -0.25,  1.25,
		-1.25,  0.25, -1.25,
		-1.25,  0.25, -1.25,
		-1.25, -0.25,  1.25,
		-1.25,  0.25,  1.25,
		
		-1.25,  0.25, -1.25,
		-1.25,  0.25,  1.25,
		-0.75,  0.25, -0.75,
		-0.75,  0.25, -0.75,
		-1.25,  0.25,  1.25,
		-0.75,  0.25,  0.75,
		
		-0.75,  0.25,  0.75,
		-0.75, -0.25, -0.75,
		-0.75,  0.25, -0.75,
		-0.75, -0.25,  0.75,
		-0.75, -0.25, -0.75,
		-0.75,  0.25,  0.75,
		 
		 
		 0.75, -0.25,  0.75,
		-1.25, -0.25,  1.25,
		-0.75, -0.25,  0.75,
		 1.25, -0.25,  1.25,
		-1.25, -0.25,  1.25,
		 0.75, -0.25,  0.75,
					   
		-1.25, -0.25,  1.25,
		 1.25, -0.25,  1.25,
		-1.25,  0.25,  1.25,
		-1.25,  0.25,  1.25,
		 1.25, -0.25,  1.25,
		 1.25,  0.25,  1.25,
					   
		-1.25,  0.25,  1.25,
		 1.25,  0.25,  1.25,
		-0.75,  0.25,  0.75,
		-0.75,  0.25,  0.75,
		 1.25,  0.25,  1.25,
		 0.75,  0.25,  0.75,
					   
		 0.75,  0.25,  0.75,
		-0.75, -0.25,  0.75,
		-0.75,  0.25,  0.75,
		 0.75, -0.25,  0.75,
		-0.75, -0.25,  0.75,
		 0.75,  0.25,  0.75,
	};

	// One color for each vertex.
	static GLfloat g_color_buffer_data[4*4*6*3] = {0.0f};
	
	// fill with rainbow
	int n_points = 4*4*6;
	float step = 1.0f / n_points;
	for (int i = 0; i < n_points; i++) {
		for (int k = 0; k < 3; k++) {
			float angle = 6.2831853f * (i * step - k / 3.0f);
			float color = (1.0f + cos(angle)) * 0.5f;
			g_color_buffer_data[3 * i + k] = color;
		}
	}

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	float time = 0.0f;
	do {

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
		// Or, for an ortho camera :
		//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
		// Camera matrix
		float r = 4.5f;
		float h = 3.0f * cos(time / 4.0f);
		glm::mat4 View       = glm::lookAt(
									glm::vec3(r * cos(time), h, r * sin(time)),
									glm::vec3(0,0,0), // and looks at the origin
									glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
							   );
		time += 0.003f;
		// Model matrix : an identity matrix (model will be at the origin)
		glm::mat4 Model      = glm::mat4(1.0f);
		// Our ModelViewProjection : multiplication of our 3 matrices
		glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

		// Use our shader
		glUseProgram(programID);
		GLuint MatrixID = glGetUniformLocation(programID, "MVP");
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 4*4*6); // 12*3 indices starting at 0 -> 12 triangles

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

