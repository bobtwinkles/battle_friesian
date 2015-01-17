#ifndef _OGL_SHADER_H_
#define _OGL_SHADER_H_

#include <istream>
#include <GL/glew.h>
#include <vector>
#include <memory>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "Util.hpp"

//// ----
// Shader features
//// ----
/******************************************************************************\
 * Attributes:
 *   vec4 coordinate;            // .xy is x and y, .zw is texture coordinate
 *   vec4 color;                 // color by which the output is multiplied
 * Uniforms:
 *   uniform mat4 transform;     // transform matrix
 *   uniform mat4 tex_transform; // Texture transform
 *   sampler2D texture;          // texture to render with
\******************************************************************************/
#define SHADER_ORTHO 0x01
/******************************************************************************\
 * Attributes:
 *
 * Uniforms:
 *   float x_fade_start; //start of x fading
 *   float x_fade_end;   //end of x fading
\******************************************************************************/
#define SHADER_GRAPH 0x02
//// ----
// Locations
//// ----
#define LOC_COORDINATE 0
#define LOC_COLOR      1
//// ----
// Names
//// ----
#define NAME_TRANSFORM     "transform"
#define NAME_TEX_TRANSFORM "tex_transform"
#define NAME_TEXTURE       "tex"
#define NAME_X_FADE_START  "x_fade_start"
#define NAME_X_FADE_END    "x_fade_end"

namespace fri {
  namespace ogl {
    class ShaderSource {
      private:
        GLchar * _data;
        GLint _len;

        DISALLOW_COPY_AND_ASSIGN(ShaderSource);
      public:
        ShaderSource(std::istream & SourceStream);
        ShaderSource(const char * fname);
        ~ShaderSource();

        GLchar * GetString() const { return _data; }
        GLint GetLength() const { return _len; }
    };

    class Shader {
      private:
        // OpenGL resources
        GLuint _sid;
        GLenum _type;

        // Our state
        bool _compiled;
        std::vector<std::shared_ptr<ShaderSource>> _sources;

        DISALLOW_COPY_AND_ASSIGN(Shader);
      public:
        Shader(GLenum Type);
        ~Shader();

        /// Returns *this to facilitate method chaining
        Shader & AttachSource(std::shared_ptr<ShaderSource>);
        /// Clears the sources array
        void FreeSources();

        /// Returns *this to facilitate method chaining
        Shader & Compile();
        inline bool IsCompilied() const { return _compiled; }
        inline GLuint GetShaderID() const { return _sid; }
    };

    class ShaderProgram {
      private:
        friend std::ostream & operator<< (std::ostream & Ost, const fri::ogl::ShaderProgram & SP) {
          Ost << "{ShaderProgram: [ID " << SP._sid << "]}";
          return Ost;
        }

        GLuint _sid;

        bool _linked;
        std::vector<std::shared_ptr<Shader>> _shaders;

        int _capabilities;

        void PrintProgramInfoLogAndExit();
        std::ostream & _WriteToStream (std::ostream & Stream);

        GLint FindUniform(const char * name);

        DISALLOW_COPY_AND_ASSIGN(ShaderProgram);
      public:

        ShaderProgram(int Capabilities);
        ~ShaderProgram();

        /// return *this to support method chaining
        ShaderProgram & AddShader(std::shared_ptr<Shader>);
        void ClearShaders();

        /// return *this to support method chaining
        /// Automatically tries to compile all attached shaders
        ShaderProgram & Link();

        /// Bind this shader and make it active
        void Bind();

        /// Upload functions
        void Upload(const char * name, glm::vec2 vec);
        void Upload(const char * name, glm::vec3 vec);
        void Upload(const char * name, glm::vec4 vec);
        void Upload(const char * name, glm::mat4 mat);
        void Upload(const char * name, GLint sampler);
        void Upload(const char * name, GLfloat f);
    };

    ShaderProgram * CreateShader(const char * Vert, const char * Frag, int Capabilities);
  }
}

#endif //_OGL_SHADER_H_
