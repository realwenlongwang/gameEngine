//
// Created by Wenlong Wang on 3/06/18.
//

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(){
    std::cout << "Calling super shader constructor" << std::endl;
}

char *ShaderProgram::readFile(const char *filename) {
    // Open File
    std::ifstream input(filename);

    // Check file is open
    if(!input.good()) {
        // Print Error
        std::cerr << "Error: Could not open " << filename << std::endl;

        // Return Error
        return 0;
    }

    // Find end of file
    input.seekg(0, std::ios::end);

    // Calculate Size
    size_t size = input.tellg();

    // Allocate required memory
    char *data = new char[size+1];

    // Rewind to beginning
    input.seekg(0, std::ios::beg);

    // Read file into memory
    input.read(data, size);

    // Append '\0'
    data[size] = '\0';

    // Close file
    input.close();

    // Return file contents
    return data;
}

GLuint ShaderProgram::checkShader(GLuint shader) {
    // Compile status
    GLint status = 0;

    // Check compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    // Error detected
    if(status != GL_TRUE) {
        // Get error message length
        int size;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);

        // Get error message
        char *message = new char[size];
        glGetShaderInfoLog(shader, size, &size, message);

        // Print error message
        std::cerr << message << std::endl;

        // Delete message
        delete[] message;

        // Return error
        return GL_FALSE;
    }

    // Return success
    return GL_TRUE;
}

GLuint ShaderProgram::checkProgram(GLuint program) {
    // Link status
    GLint status = 0;

    // Check link status
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    // Error detected
    if(status != GL_TRUE) {
        // Get error message length
        int size;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &size);

        // Get error message
        char *message = new char[size];
        glGetProgramInfoLog(program, size, &size, message);

        // Print error message
        std::cerr << message << std::endl;

        // Delete message
        delete[] message;

        // Return error
        return GL_FALSE;
    }

    // Return success
    return GL_TRUE;
}

GLuint ShaderProgram::loadShader(GLuint type, const char *filename) {
    // Read the shader source from file
    const char *source = readFile(filename);

    // Check shader source
    if(source == 0) {
        // Return Error
        return 0;
    }

    // Create the OpenGL Shaders
    GLuint shader = glCreateShader(type);

    // Load the source into the shaders
    glShaderSource(shader, 1, &source, NULL);

    // Compile the Shaders
    glCompileShader(shader);

    // Check shaders for errors
    if(checkShader(shader) == GL_TRUE) {
        // Log
        std::cout << "Loaded: " << filename << std::endl;
    } else {
        // Print Error
        std::cerr << "Error: could not compile " << filename << std::endl;

        // Delete shader source
        delete[] source;

        // Return Error
        return 0;
    }

    // Delete shader source
    delete[] source;

    // Return shader
    return shader;
}

void
ShaderProgram::loadProgram(const char *vert_file, const char *ctrl_file, const char *eval_file, const char *geom_file,
                           const char *frag_file) {
    // Create new OpenGL program
    programID = glCreateProgram();

    // Shader Handles
    GLuint vert_shader = 0;
    GLuint ctrl_shader = 0;
    GLuint eval_shader = 0;
    GLuint geom_shader = 0;
    GLuint frag_shader = 0;

    // Load Shaders
    if(vert_file != NULL) vert_shader = loadShader(GL_VERTEX_SHADER,          vert_file);
    if(ctrl_file != NULL) ctrl_shader = loadShader(GL_TESS_CONTROL_SHADER,    ctrl_file);
    if(eval_file != NULL) eval_shader = loadShader(GL_TESS_EVALUATION_SHADER, eval_file);
    if(geom_file != NULL) geom_shader = loadShader(GL_GEOMETRY_SHADER,        geom_file);
    if(frag_file != NULL) frag_shader = loadShader(GL_FRAGMENT_SHADER,        frag_file);

    // Attach shaders
    if(vert_shader != 0) {
        glAttachShader(programID, vert_shader);
        shaders.emplace("vertex",vert_shader);
    }
    if(ctrl_shader != 0) {
        glAttachShader(programID, ctrl_shader);
        shaders.emplace("control",ctrl_shader);
    }
    if(eval_shader != 0) {
        glAttachShader(programID, eval_shader);
        shaders.emplace("evaluation",eval_shader);
    }
    if(geom_shader != 0) {
        glAttachShader(programID, geom_shader);
        shaders.emplace("geometry",geom_shader);
    }
    if(frag_shader != 0) {
        glAttachShader(programID, frag_shader);
        shaders.emplace("fragment",frag_shader);
    }

    // Check Vertex Shader
    if(vert_shader == 0) {
        // Delete Shaders
        if(vert_shader != 0) glDeleteShader(vert_shader);
        if(ctrl_shader != 0) glDeleteShader(ctrl_shader);
        if(eval_shader != 0) glDeleteShader(eval_shader);
        if(geom_shader != 0) glDeleteShader(geom_shader);
        if(frag_shader != 0) glDeleteShader(frag_shader);

        // Print Error
        throw std::invalid_argument(SOURCE_ERROR("Error: program missing vertex shader."));

    }

    // Check Fragment Shader
    if(frag_shader == 0) {


        // Delete Shaders
        if(vert_shader != 0) glDeleteShader(vert_shader);
        if(ctrl_shader != 0) glDeleteShader(ctrl_shader);
        if(eval_shader != 0) glDeleteShader(eval_shader);
        if(geom_shader != 0) glDeleteShader(geom_shader);
        if(frag_shader != 0) glDeleteShader(frag_shader);

        // Print Error
        throw std::invalid_argument(SOURCE_ERROR("Error: program missing fragment shader."));
    }

    // Bind attributes with number
    bindAttributes();

    // Link program
    glLinkProgram(programID);

    // Delete Shaders (no longer needed)
    if(vert_shader != 0) glDeleteShader(vert_shader);
    if(ctrl_shader != 0) glDeleteShader(ctrl_shader);
    if(eval_shader != 0) glDeleteShader(eval_shader);
    if(geom_shader != 0) glDeleteShader(geom_shader);
    if(frag_shader != 0) glDeleteShader(frag_shader);

    // Check program for errors
    if(checkProgram(programID) == GL_TRUE) {
        // Print Log
        std::cout << "Loaded: program" << std::endl;
    } else {
        // Print Error
        throw std::invalid_argument(SOURCE_ERROR("Error: could not link program"));
    }

    getAllUniformLocation();
}

void ShaderProgram::start() {
    glUseProgram(programID);

}

void ShaderProgram::stop() {
    glUseProgram(0);
}

void ShaderProgram::cleanUp() {
    stop();
    for(auto shader: shaders) {
        glDetachShader(programID, shader.second);
        glDeleteShader(shader.second);
    }
    glDeleteProgram(programID);

}

GLint ShaderProgram::getAttributeLocation(const char *attributeName) {
    std::string errorMsg(attributeName);
    errorMsg += " not found in the shader!";
    GLint attrLoc = glGetAttribLocation(programID, attributeName);
    // Note: glsl compiler would strip out the unused variables hence their locations will be -1
    if(attrLoc == -1)
        throw std::invalid_argument(SOURCE_ERROR("Attribute name not found in the shader!"));
    return attrLoc;
}

GLint ShaderProgram::getUniformLocation(const char *uniformName) {
    std::string errorMsg(uniformName);
    errorMsg += " not found in the shader!";
    GLint uniLoc = glGetUniformLocation(programID, uniformName);
    // Note: glsl compiler would strip out the unused variables hence their locations will be -1

    if(uniLoc == -1)
        throw std::invalid_argument(SOURCE_ERROR(errorMsg.c_str()));
    return uniLoc;
}



void ShaderProgram::bindAttributes(GLuint attributeNum, const char *attributeName) {
    glBindAttribLocation(programID, attributeNum, attributeName);
}

ShaderProgram::~ShaderProgram() {

}

void ShaderProgram::loadFloat(GLint location, float value) {
    glUniform1f(location, value);
}

void ShaderProgram::loadVec3(GLint location, glm::vec3 value) {
    glUniform3f(location, value.x, value.y, value.z);
}

void ShaderProgram::loadBoolean(GLint location, bool value) {
    float toLoad = 0.0f;
    if(value) {
        toLoad = 1.0f;
    }

    glUniform1f(location, toLoad);
}

void ShaderProgram::loadMatrix(GLint location, glm::mat4 matrix) {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
