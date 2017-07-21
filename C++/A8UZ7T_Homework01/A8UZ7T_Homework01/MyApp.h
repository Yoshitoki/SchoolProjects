#ifndef MYAPP_H
#define MYAPP_H

#include <GL/glew.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

class CMyApp
{
public:
	CMyApp(void);
	~CMyApp(void);

	bool Init();
	void Clean();

	void Update();
	void Render();

	void KeyboardDown(SDL_KeyboardEvent&);
	void KeyboardUp(SDL_KeyboardEvent&);
	void MouseMove(SDL_MouseMotionEvent&);
	void MouseDown(SDL_MouseButtonEvent&);
	void MouseUp(SDL_MouseButtonEvent&);
	void MouseWheel(SDL_MouseWheelEvent&);
	void Resize(int, int);

protected:
	GLuint m_programID;
	GLuint m_vaoID;
	GLuint m_vboID;

	glm::mat4 m_matWorld;
	glm::mat4 m_matView;
	glm::mat4 m_matProj;

	bool rotate;

	GLuint	m_loc_world;
	GLuint	m_loc_view;
	GLuint	m_loc_proj;

	struct Vertex
	{
		glm::vec3 p;
		glm::vec3 c;
	};
};

#endif