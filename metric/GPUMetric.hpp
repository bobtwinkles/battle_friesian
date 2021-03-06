#ifndef _METRIC_H_
#define _METRIC_H_

#include <GL/glew.h>
#include "util/Util.hpp"

namespace fri {
  namespace ogl {
    namespace ui {
      class MetricGraph;
    }
  }
  namespace metric {
    class GPUMetric {
      private:
        friend fri::ogl::ui::MetricGraph;
        GLuint _queries[2];
        long * _samples;
        long _min, _max;
        long _seeing_max;
        unsigned int _current_sample;
        unsigned int _num_samples;
        unsigned int _total_samples;
        unsigned int _seeing_max_sample;
        bool _running;
        bool _finalized;
        float _average, _stddev, _continous_average;

        DISALLOW_COPY_AND_ASSIGN(GPUMetric);
      public:
        GPUMetric(unsigned int NumSamples);
        ~GPUMetric();

        void Enter();
        void Leave();
        void Finalize();

        void Reset();

        float GetAverage() const { return _continous_average; };
        float GetStandardDeviation() const;
        inline long GetMin() const { return _min; }
        inline long GetMax() const { return _max; }
        inline unsigned int GetCurrent() const { return _current_sample; }
    };
  }
}

#endif //_METRIC_H_
