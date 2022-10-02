#include "definitions.hpp"

class Shader
{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath)
    {
        string vertexCode;
        string fragmentCode;

        ifstream vertexShaderFile;
        ifstream fragmentShaderFile;

        vertexShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
        fragmentShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

        try
        {
            vertexShaderFile.open(vertexPath);
            fragmentShaderFile.open(fragmentPath);

            stringstream vertexShaderStream;
            stringstream fragmentShaderStream;

            vertexShaderStream << vertexShaderFile.rdbuf();
            fragmentShaderStream << fragmentShaderFile.rdbuf();

            vertexShaderFile.close();
            fragmentShaderFile.close();

            vertexCode = vertexShaderStream.str();
            fragmentCode = fragmentShaderStream.str();
        }
        catch(ifstream::failure& e)
        {
            cerr << "ERROR::SHADER::UNSUCCESSFUL FILE READ: " << e.what() << endl;
        }

        const char* vertexShaderCode = vertexCode.c_str();
        const char* fragmentShaderCode = fragmentCode.c_str();

        unsigned int vertex;
        unsigned int fragment;
        int success;
        char infoLog[512];

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexShaderCode, NULL);
        glCompileShader(vertex);

        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            cerr << "ERROR::SHADER::VERTEX::FAILED TO COMPILE" << endl;
        }

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
        glCompileShader(fragment);

        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            cerr << "ERROR::SHADER::FRAGMENT::FAILED TO COMPILE" << endl;
        }

        ID = glCreateProgram();

        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);

        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            cerr << "ERROR::SHADER::PROGRAM::FAILED TO LINK\n" << infoLog << endl;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);

    }

    void Use() 
    {
        glUseProgram(ID);
    }

    void setBool(const string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
    }

    void setInt(const string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
    }

    void setFloat(const string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    } 
};