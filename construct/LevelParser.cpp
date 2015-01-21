#include "construct/Parser.hpp"

#include "systems/render/RenderSystem.hpp"

#include "util/ImageLoad.hpp"

using fri::construct::BuildParseTree;
using fri::construct::IBuilder;
using fri::construct::ParseError;
using fri::construct::ParseTreeNode;
using fri::system::GameContext;

namespace {
  struct BackgroundParser : public IBuilder<GameContext> {
    virtual const char * GetKeyword() const { return "BG"; }
    virtual ParseError Visit(const char * Line, GameContext & Affect) {
      char file_path[1024];
      int parse = sscanf(Line, " %s", file_path);
      if (parse != 1) {
        return ParseError(0, 0, "BG must be followed by a path (no spaces!)");
      }
      std::cout << "  " << "BG will be loaded from " << file_path << std::endl;
      fri::system::render::RenderSystem & rs = Affect.GetRenderSystem();
      rs.SetBackgroundTexture(fri::LoadImage(file_path));
      return ParseError();
    }
  };

  struct PlatformParser : public IBuilder<GameContext> {
    virtual const char * GetKeyword() const { return "PLATFORM"; }
    virtual ParseError Visit(const char * Line, GameContext & Affect) {
      std::cout << "Parse PLATFORM! " << Line << std::endl;
      return ParseError();
    }
  };

  BackgroundParser BG_PARSER;
  PlatformParser   PLATFORM_PARSER;

  ParseTreeNode<GameContext> context_parser = BuildParseTree<GameContext>(std::vector<IBuilder<GameContext>*>( {
          &PLATFORM_PARSER,
          &BG_PARSER,
        }));
}

void fri::construct::ParseLevel(std::istream & Input, GameContext & Context) {
  char input[1024];
  int line = 0;

  while (Input.good()) {
    Input.getline(input, 1024);
    ++line;
    if (input[0] == 0 || input[0] == '#') {
      continue;
    }
    ParseError err = context_parser.Visit(input, Context);
    if (err.DidError()) {
      std::cerr << "Parse failed:" << line << ":" << err.GetError() << std::endl;
      abort();
    }
  }
}
