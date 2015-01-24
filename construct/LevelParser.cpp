#include "construct/LevelParser.hpp"

#include <memory>

#include "construct/Parser.hpp"
#include "systems/entity/entities/Platform.hpp"
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
      int parse = sscanf(Line, " %1023s", file_path);
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
      float x, y, w, h;
      char file_path[1024];
      int parse = sscanf(Line, " %f %f %f %f %1023s", &x, &y, &w, &h, file_path);
      if (parse < 5) {
        return ParseError(0, 0, "Platform must have \"x y w h image\" image can be NOIMG to indicate that this wall is invisible");
      }
      std::cout << "  Adding platform" << std::endl;
      std::cout << "    Position  " << x << ", " << y << std::endl;
      std::cout << "    Size " << w << "x" << h << std::endl;
      std::cout << "    Image " << file_path << std::endl;
      std::shared_ptr<fri::ogl::Texture> tex = nullptr;
      if (strcmp(file_path, "NOIMG")) {
        tex = fri::LoadImage(file_path);
      }
      auto p = std::make_shared<fri::system::entity::entities::Platform>(Affect, x, y, w, h, tex);
      Affect.GetEntitySystem().RegisterGameObject(p);

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
