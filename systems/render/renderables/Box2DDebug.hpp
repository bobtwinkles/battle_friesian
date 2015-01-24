#ifndef _SYSTEM_RENDER_RENDERABLES_BOX2D_DEBUG_H_
#define _SYSTEM_RENDER_RENDERABLES_BOX2D_DEBUG_H_

#include <vector>
#include <Box2D/Common/b2Draw.h>

#include "systems/render/Renderable.hpp"
#include "ogl/TexturedVertexBuffer.hpp"

namespace fri {
  namespace system {
    namespace render {
      class Box2DDebug : public b2Draw, public IRenderable {
        private:
          fri::ogl::TexturedVertexBuffer _solid_buffer;
          std::vector<fri::ogl::TexturedVertex> & _solid_vertices;
          std::vector<GLuint> & _solid_indicies;
          fri::ogl::TexturedVertexBuffer _line_buffer;
          std::vector<fri::ogl::TexturedVertex> & _line_vertices;
          std::vector<GLuint> & _line_indicies;
        public:
          Box2DDebug();
          ~Box2DDebug();

          virtual void Render(RenderSystem & System);

          virtual void DrawPolygon(const b2Vec2* Vertices, int32 VertexCount, const b2Color& Color);
          virtual void DrawSolidPolygon(const b2Vec2* Vertices, int32 VertexCount, const b2Color& Color);
          virtual void DrawCircle(const b2Vec2 & Center, float32 Radius, const b2Color& Color);
          virtual void DrawSolidCircle(const b2Vec2 & Center, float32 Radius, const b2Vec2 & Axis, const b2Color& Color);
          virtual void DrawSegment(const b2Vec2 & P1, const b2Vec2 & P2, const b2Color& Color);
          virtual void DrawTransform(const b2Transform & Trans);
      };
    }
  }
}

#endif
