#ifndef _CONSTRUCT_BUILDER_H_
#define _CONSTRUCT_BUILDER_H_

#include <string>

namespace fri {
  namespace construct {
    class ParseError;

    // T is the type of thing that will be affected by parsing
    template<typename T>
    class IBuilder {
      private:
        //
      public:
        IBuilder() {}
        ~IBuilder() {}

        virtual const char * GetKeyword() const = 0;
        // The line will start with the keyword
        virtual ParseError Visit(const char * Line, T & Affect) = 0;
    };
  }
}

#endif // _CONSTRUCT_BUILDER_H_
