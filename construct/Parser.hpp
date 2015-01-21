#ifndef _CONSTRUCT_PARSER_H_
#define _CONSTRUCT_PARSER_H_

#include <string>
#include <vector>
#include <istream>

#include "systems/GameContext.hpp"
#include "construct/Builder.hpp"

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
    class ParseTreeNode {
      private:
        std::vector<ParseTreeNode> _children;
        char _char;
        IBuilder<T> * _val;
      public:
        ParseTreeNode(char Char, IBuilder<T> * Parser) {
          _char = Char;
          _val = Parser;
        }

        ParseTreeNode(const ParseTreeNode & Node) {
          _char = Node._char;
          _val = Node._val;
          _children = Node._children;
        }

        ParseTreeNode(const ParseTreeNode && Node) {
          _children = std::move(Node._children);
          _char = Node._char;
          _val = Node._val;
        }

        ~ParseTreeNode() {
        }

        ParseTreeNode<T> & operator=(const ParseTreeNode & Node) {
          ParseTreeNode<T> temp(Node);
          std::swap(temp, *this);
          return *this;
        }

        ParseTreeNode<T> & operator=(const ParseTreeNode && Node) {
          _children = std::move(Node._children);
          _char = Node._char;
          _val = Node._val;
          return *this;
        }

        void AddChild(const ParseTreeNode<T> & Child) {
          std::cout << _char << " will have child at " << Child._char << std::endl;
          if (_children.size() == 0) {
            _children.push_back(Child);
            return;
          }
          auto it = _children.begin();
          while ((*it)._char < Child._char) {
            ++it;
          }
          _children.insert(it, Child);
        }

        ParseTreeNode<T> * GetChild(char C) {
          if (_children.size() == 0) {
            return nullptr;
          }
          int beg = 0;
          int end = _children.size() - 1;
          int cur = (beg + end) / 2;
          while (_children[cur]._char != C) {
            char cur_char = _children[cur]._char;
            if (end - beg <= 1) {
              if (cur_char == C) {
                return &_children[cur];
              } else if (_children[end]._char == C){
                return &_children[end];
              } else {
                return nullptr;
              }
            }
            if (cur_char < C) {
              end = cur;
            } else {
              beg = cur;
            }
            cur = (beg + end) / 2;
          }
          return &_children[cur];
        }

        inline IBuilder<T> * GetVal() const { return _val; }
        inline void SetVal(IBuilder<T> * Val) { _val = Val; }

        ParseError Visit(const char * Line, T & Affect) {
          if (_val) {
            // Advance to find the first whitespace
            while (*Line != ' ' && *Line != '\t' && *Line != 0) ++Line;
            return _val->Visit(Line, Affect);
          }
          ParseTreeNode<T> * child = GetChild(*Line);
          if (child == nullptr) {
            std::cerr << "Couldn't find parser for " << Line << std::endl;;
          }
          return child->Visit(Line + 1, Affect);
        }
    };

    template<typename T>
    ParseTreeNode<T> BuildParseTree(const std::vector<IBuilder<T>*> & Builders) {
      ParseTreeNode<T> root = ParseTreeNode<T>(0, nullptr);
      for (auto builder : Builders) {
        const char * keyword = builder->GetKeyword();
        int depth = 0;
        int max_depth = strlen(keyword);

        std::cout << "Adding builder for keyword " << keyword << std::endl;

        ParseTreeNode<T> * current = &root;
        ParseTreeNode<T> * next = nullptr;
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
          current->AddChild(ParseTreeNode<T>(' ', builder));
        } else {
          if (current->GetVal() != nullptr) { // There is already a thing that thinks it's the lowest possible here
            IBuilder<T> * old = current->GetVal();
            current->SetVal(nullptr); // no longer the lowest

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

            current->AddChild(ParseTreeNode<T>(next_char, old));
          }
          current->AddChild(ParseTreeNode<T>(keyword[depth], builder));
        }
      }
      return root;
    }

    void ParseLevel(std::istream & Input, fri::system::GameContext & Context);
  }
}

#endif
