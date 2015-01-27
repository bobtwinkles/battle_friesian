#ifndef _CONSTRUCT_PARSER_H_
#define _CONSTRUCT_PARSER_H_

#include <string.h>
#include <vector>
#include <iostream>

#include "construct/Builder.hpp"
#include "util/Tree.hpp"

namespace fri {
  namespace construct {
    class ParseError {
      private:
        bool _did_error;
        int _line;
        int _char;
        std::string _error;
      public:
        ParseError(); // no error
        ParseError(int Line, int Char, std::string Error); // error at Line:Char
        ParseError(const ParseError & Other);
        ParseError(const ParseError && Other);
        ParseError & operator=(const ParseError & Other);
        ParseError & operator=(const ParseError && Other);

        ~ParseError() { }

        void Swap(ParseError & Other);

        inline int GetLine() const { return _line; }
        inline int GetChar() const { return _char; }
        inline std::string GetError() const { return _error; }
        inline bool DidError() const { return _did_error; }
    };

    // T is the type of thing that will be affected by parsing
    template<typename T>
    class ParseTree {
      private:
        fri::util::ChainTree<const char, IBuilder<T>*, ' ', nullptr> _parse_tree;
      public:
        ParseTree(std::vector<IBuilder<T>*> Builders) :
          _parse_tree(0, nullptr) {
          // TODO
          for (auto builder : Builders) {
            const char * keyword = builder->GetKeyword();
            int depth = 0;
            int max_depth = strlen(keyword);

            std::cout << "Adding builder for keyword " << keyword << std::endl;

            auto a = _parse_tree.Insert(keyword, max_depth, builder);
          }
        }

        ParseError Visit(const char* Line, T & Context) {
          IBuilder<T> * val = _parse_tree.Get(Line, strlen(Line))->GetValue();
          if (!val) {
            return ParseError(0, 0, "Failed to match a pattern");
          }
          return val->Visit(Line, Context);
        }
    };

  }
}

#endif
