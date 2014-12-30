#include "UI.hpp"

#include <glm/gtc/matrix_transform.hpp>

static fri::ogl::ShaderProgram * graph;

void fri::ogl::ui::UIInit() {
  graph = fri::ogl::CreateShader("graph.vert", "graph.frag", SHADER_ORTHO | SHADER_GRAPH);
}

fri::ogl::ShaderProgram * fri::ogl::ui::GetGraphShader() {
  return graph;
}

void BeginUIRendering(fri::ogl::Environment & env, int Width, int Height) {
  fri::ogl::ShaderProgram * program = fri::ogl::ui::GetGraphShader();
  env.MakeProgramCurrent(program);

  glm::mat4 trans = glm::ortho(0.f, (float)Width, 0.f, (float)Height, 10.f, -10.f);
  program->Upload(NAME_TRANSFORM, trans);
}
