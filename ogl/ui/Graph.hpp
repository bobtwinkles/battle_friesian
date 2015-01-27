#ifndef _OGL_UI_GRAPH_
#define _OGL_UI_GRAPH_

#include <GL/glew.h>

#include "ogl/Environment.hpp"
#include "ogl/ui/UI.hpp"
#include "util/Util.hpp"

namespace fri {
  namespace metric {
    class GPUMetric;
  }

  namespace ogl {
    namespace ui {
      class MetricGraph {
        private:
          struct Vertex {
            float x, y, u, v;
            float r, g, b, a;
          };

          // Data spec
          unsigned int _num_points;
          fri::metric::GPUMetric & _metric;

          // Opengl stuff
          GLuint _data_buffer;
          GLuint _vao;

          // render data
          Vertex * _verts;

          // view spec
          float _x, _y, _width, _height;

          // We need 4 points starting at _num_points + this offset to render the standard deviation lines
          const unsigned int _STDDEV_LINE_OFFSET = 3;
          // 4 for border stuff and 4 for the stddev lines
          const unsigned int _NUM_EXTRA_POINTS = _STDDEV_LINE_OFFSET + 4;

          // need to update the scale factor first

          DISALLOW_COPY_AND_ASSIGN(MetricGraph);
        public:
          MetricGraph(fri::metric::GPUMetric & Metric, float X, float Y, float Width, float Height);
          ~MetricGraph();

          inline float GetX() const { return _x; }
          inline float GetY() const { return _y; }
          inline float GetWidth() const { return _width; }
          inline float GetHeight() const { return _height; }

          float GetSampleHeight(long Sample) const;

          void Render(const fri::ogl::Environment & Env) const;
      };
    }
  }
}

#endif // _OGL_UI_GRAPH_
