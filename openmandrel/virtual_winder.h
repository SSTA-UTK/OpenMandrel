#pragma once

#include "winder.h"
#include <GL/glew.h>
#include <memory>

class IndexedMesh {
public:
    struct BufferInitializer {
        void* source;
        GLsizeiptr sourceSize;
        GLint typeSize;
		GLenum type;

        BufferInitializer(float* values, int count);
        BufferInitializer(glm::vec2* vecs, int count);
        BufferInitializer(glm::vec3* vecs, int count);
        BufferInitializer(glm::vec4* vecs, int count);
        BufferInitializer(uint32_t* indices, int count);
    };
    struct LoadedData {
        GLuint vertexArrayObject;
        GLuint* vertexBufferObjects;
        unsigned int bufferCount;
        unsigned int drawCount;
        uint64_t circulationID;
        GLsizei vertices;
        GLsizei indices;
    };
    std::shared_ptr<LoadedData> loadedData;

    IndexedMesh(std::initializer_list<BufferInitializer> vertices, BufferInitializer indices);

    void Bind();
    void Draw();
};

class Virtual4AxisXWinder {
private:
    IndexedMesh mandrel;
    IndexedMesh fibers;
public:
    Virtual4AxisXWinder();
    ~Virtual4AxisXWinder();

    void LoadMandrel();
    void LoadWindingPattern();
    void LoadToolPath();

    // t is between 0.0 and 1.0 representing either fiber length scaling or time scaling, depending on if a toolpath was loaded
    void Render(double t);
};

class Simple3DRenderer {
private:
    GLuint shaderName;
public:
    Simple3DRenderer();

    void Begin(const glm::vec3& cameraPos, const glm::vec3& lookDir);
    void Render();
    void End();
};
