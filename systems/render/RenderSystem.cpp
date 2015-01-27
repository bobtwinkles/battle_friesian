#include "RenderSystem.hpp"

#include "ogl/OGLUtil.hpp"
#include "systems/GameContext.hpp"
#include "util/ImageLoad.hpp"

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using fri::ogl::Texture;
using fri::system::render::RenderableIndex;
using fri::system::render::RenderSystem;
using fri::system::render::IRenderable;

RenderSystem::RenderSystem() : ISystem() {
  _prog = fri::ogl::CreateShader("base.vert", "base.frag", SHADER_ORTHO);
  _env = new fri::ogl::Environment();
  _env->MakeProgramCurrent(_prog);
  _bg = new fri::ogl::TexturedVertexBuffer(GL_TRIANGLE_STRIP, GL_STATIC_DRAW, nullptr);

  fri::ogl::QueueTexturedRectangle(*_bg, glm::vec2(0.0, 0.0), glm::vec2(1.0, 9.0/16.0),
                                         glm::vec2(0.0, 0.0), glm::vec2(1.0, 1.0));

  _bg->Sync();

  glEnable(GL_BLEND);
  //glEnable(GL_DEPTH_TEST);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glClearColor(0.5f, 0.5f, 0.8f, 0.f);
  //glClearColor(0.7f, 0.5f, 0.5f, 0.f);
}

RenderSystem::~RenderSystem() {
  delete _env;
  delete _prog;
  delete _bg;
}

RenderableIndex RenderSystem::RegisterRenderable(std::shared_ptr<IRenderable> Ren) {
  return _renderables.insert(_renderables.begin(), Ren);
}

void RenderSystem::RemoveRenderable(RenderableIndex & Index) {
  _renderables.erase(Index);
}

static void PrintMatrix(glm::mat4 & Matrix) {
  const float *pSource = (const float*)glm::value_ptr(Matrix);
  std::cout << "--------" << std::endl;
  for (int i = 0; i < 16; ++i) {
    std::cout << pSource[i] << " ";
    if (i % 4 == 3)
      std::cout << std::endl;
  }
}

void RenderSystem::SetBackgroundTexture(std::shared_ptr<Texture> Tex)  {
  _bg->SetTexture(Tex);
}

void RenderSystem::Tick(fri::system::GameContext & Context, double Step) {
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

  glm::mat4 trans = glm::ortho(0.0, 1.0, 0.0, Context.GetAspect(), -1.0, 1.0);
  glm::mat4 ttrans(1.f);
  //ttrans = glm::translate(ttrans, glm::vec3(Context.GetCurrentTime() / 8.0, 0.0, 0.0));
  _env->MakeProgramCurrent(_prog);
  _prog->Upload(NAME_TRANSFORM, trans);
  _prog->Upload(NAME_TEX_TRANSFORM, ttrans);

  _bg->Render(*_env);

  for (auto ren : _renderables) {
    ren->Render(*this);
  }

  GLERR();
}
