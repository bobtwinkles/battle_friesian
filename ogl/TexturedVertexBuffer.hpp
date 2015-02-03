#ifndef _OGL_TEXTURED_VERTEX_BUFFER_
#define _OGL_TEXTURED_VERTEX_BUFFER_

#include <GL/glew.h>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "util/Util.hpp"

#include "ogl/Environment.hpp"
#include "ogl/texture/Texture.hpp"

namespace fri {
  namespace ogl {
    struct TexturedVertex {
      float x, y, u, v;
      float r, g, b, a;
    };

    class TexturedVertexBuffer {
      private:
        GLuint _index_buffer;
        GLuint _data_buffer;
        GLuint _vao;
        GLenum _usage;
        GLenum _mode;

        std::shared_ptr<texture::Texture> _texture;

        std::vector<TexturedVertex> _vertices;
        std::vector<GLuint> _indicies;

        bool _verts_ok;

        void _Init();

        DISALLOW_COPY_AND_ASSIGN(TexturedVertexBuffer);
      public:
        TexturedVertexBuffer(GLenum Mode, GLenum Usage, std::shared_ptr<texture::Texture> Texture);
        ~TexturedVertexBuffer();

        void AddVertex(TexturedVertex Vertex);
        void AddVerticies(std::vector<TexturedVertex> Verts, std::vector<GLuint> Inidicies);
        void ClearVertexData();

        void SetTexture(std::shared_ptr<texture::Texture> Tex) { _texture = Tex; }

        ///WARNING: If these methods are used to modify the verticies, this class will no longer be
        /// capable of ensuring the gpu-side structure is in sync
        std::vector<TexturedVertex> & GetVertices() { return _vertices; }
        std::vector<GLuint> & GetIndicies() { return _indicies; }

        void Sync();

        void Render(fri::ogl::Environment & Env) const;
    };

    void QueueTexturedRectangle(TexturedVertexBuffer & Buffer, glm::vec2 PStart, glm::vec2 PEnd
                                                             , glm::vec2 TStart, glm::vec2 TEnd);
  }
}

#endif // _OGL_TEXTURED_VERTEX_BUFFER_
