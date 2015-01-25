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
        fri::util::Tree<char, IBuilder<T>*> _parse_tree;
        // Keep track of all the nodes we allocate so we can delete them
        std::vector<fri::util::Tree<char, IBuilder<T>*>*> _nodes;
      public:
        ParseTree(std::vector<IBuilder<T>*> Builders) :
          _parse_tree(0, nullptr) {
          // TODO
          for (auto builder : Builders) {
            const char * keyword = builder->GetKeyword();
            int depth = 0;
            int max_depth = strlen(keyword);

            std::cout << "Adding builder for keyword " << keyword << std::endl;

            fri::util::Tree<char, IBuilder<T>*> * current = &_parse_tree;
            fri::util::Tree<char, IBuilder<T>*> * next = &_parse_tree;
            fri::util::Tree<char, IBuilder<T>*> * create;
            // Descend to the lowest part of the tree
            while (depth < max_depth && (next = current->GetChild(keyword[depth])) != nullptr) {
              current = next;
              ++depth;
            }

            if (depth == max_depth) { // we are shorter than the depth of the tree... oops
              if (current->GetChild(' ') != nullptr) {
                std::cerr << "Duplicate key " << keyword << std::endl;
                abort();
              }

              create = new fri::util::Tree<char, IBuilder<T>*>(' ', builder);
              _nodes.push_back(create);
              current->AddChild(create);
            } else {
              if (current->GetValue() != nullptr) { // There is already a thing that thinks it's the lowest possible here
                IBuilder<T> * old = current->GetValue();
                current->SetValue(nullptr); // no longer the lowest

                const char * old_keyword = old->GetKeyword();

                if (!strcmp(old_keyword, keyword)) {
                  std::cout << "Duplicate key " << keyword << std::cerr;
                  abort();
                }

                char next_char;
                if (strlen(old_keyword) >= depth) {
                  next_char = ' ';
                } else {
                  next_char = old_keyword[depth];
                }

                create = new fri::util::Tree<char, IBuilder<T>*>(next_char, old);
                _nodes.push_back(create);
                current->AddChild(create);
              }
              create = new fri::util::Tree<char, IBuilder<T>*>(keyword[depth], builder);
              _nodes.push_back(create);
              current->AddChild(create);
            }
          }
        }

        ~ParseTree() {
          for (auto i : _nodes) {
            delete i;
          }
        }

        ParseError Visit(const char* Line, T & Context) {
          fri::util::Tree<char, IBuilder<T>*> * curr = &_parse_tree;
          fri::util::Tree<char, IBuilder<T>*> * next = &_parse_tree;
          int depth = 0;
          while (!curr->GetValue() && Line[depth] && (next = curr->GetChild(Line[depth]))) {
            curr = next;
            ++depth;
          }
          if (!Line[depth]) {
            return ParseError(0, depth, "Reached end of line without matching parser");
          }
          IBuilder<T> * val = curr->GetValue();
          if (!val) {
            return ParseError(0, depth, "Failed to match a pattern");
          }
          return val->Visit(Line, Context);
        }
    };

  }
}

#endif
