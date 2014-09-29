#ifndef SHADER_H
#define SHADER_H

#include "Dependence.h"
#include "MathCore.h"

class Shader
{
public:
	Shader();
	Shader(char const* vertex_program_file, char const* fragment_program_file);
	~Shader();

	void Log(GLuint obj);
		
	const char* readFile(char const* path);
	void bind();
	void unbind();

	void setParam( char const* name , Vec2f const& v )
	{
		int loc = glGetUniformLocation( ID , name );
		glUniform2f( loc , v.x , v.y );	
	}

	void setParam( char const* name , Vec3 const& v )
	{
		int loc = glGetUniformLocation( ID , name );
		glUniform3f( loc , v.x, v.y , v.z );	
	}

	void setParam( char const* name , float v1 )
	{
		int loc = glGetUniformLocation( ID , name );
		glUniform1f( loc , v1 );	
	}
	void setParam( char const* name , float v1 , float v2 )
	{
		int loc = glGetUniformLocation( ID , name );
		glUniform2f( loc , v1, v2 );	
	}

	void setParam( char const* name , int v1 )
	{
		int loc = glGetUniformLocation( ID , name );
		glUniform1i( loc , v1 );	
	}

private:	
	GLuint ID;
	GLuint vertex_program;
	GLuint fragment_program;
};
#endif