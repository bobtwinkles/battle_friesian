#include "TexturedVertexBuffer.hpp"

#include "ogl/OGLUtil.hpp"

#include <cassert>

using fri::ogl::TexturedVertex;
using fri::ogl::TexturedVertexBuffer;

TexturedVertexBuffer::TexturedVertexBuffer(GLenum Mode, GLenum Usage, std::shared_ptr<Texture> Texture) :
  _texture(Texture) {
  _mode = Mode;
  _usage = Usage;

  _verts_ok = false;

  _Init();
}

void TexturedVertexBuffer::_Init() {
  GLuint buffers[2];

  glGenBuffers(2, buffers);
  glGenVertexArrays(1, &_vao);

  _index_buffer = buffers[0];
  _data_buffer  = buffers[1];
}

TexturedVertexBuffer::~TexturedVertexBuffer() {
  GLuint buffers[2];
  buffers[0] = _index_buffer;
  buffers[1] = _data_buffer;

  glDeleteBuffers(2, buffers);
  glDeleteVertexArrays(1, &_vao);
}

void TexturedVertexBuffer::AddVertex(TexturedVertex Vertex) {
  _indicies.push_back(_vertices.size());
  _vertices.push_back(Vertex);

  _verts_ok = false;
}

void TexturedVertexBuffer::ClearVertexData() {
  _indicies.clear();
  _vertices.clear();

  _verts_ok = false;
}

void TexturedVertexBuffer::AddVerticies(std::vector<TexturedVertex> Verts, std::vector<GLuint> Indicies) {
  GLuint base = _vertices.size();
  _vertices.insert(_vertices.end(), Verts.begin(), Verts.end());

  auto it = Indicies.begin();
  while (it != Indicies.end()) {
    _indicies.push_back(base + *it);
    ++it;
  }

  _verts_ok = false;
}

void TexturedVertexBuffer::Sync() {
  glBindBuffer(GL_ARRAY_BUFFER, _data_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);

  glBufferData(GL_ARRAY_BUFFER, sizeof(TexturedVertex) * _vertices.size(), _vertices.data(), _usage);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _indicies.size(), _indicies.data(), _usage);

  _verts_ok = true;
}

void TexturedVertexBuffer::Render(const fri::ogl::Environment & Env) const {
  assert(_verts_ok);
  glBindVertexArray(_vao);
  glBindBuffer(GL_ARRAY_BUFFER, _data_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);
  GLERR();

  fri::ogl::ShaderProgram * cs = Env.GetCurrentShaderProgram();

  glActiveTexture(GL_TEXTURE0);
  _texture->Bind();
  cs->Upload(NAME_TEXTURE, 0); // we want to use texture 0

  glEnableVertexAttribArray(LOC_COORDINATE);
  glEnableVertexAttribArray(LOC_COLOR);
  glVertexAttribPointer(LOC_COORDINATE, 4, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), 0);
  glVertexAttribPointer(LOC_COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), OFFSET(4));

  glDrawElements(_mode, _indicies.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(LOC_COORDINATE);
  glDisableVertexAttribArray(LOC_COLOR);

  GLERR();
}


//////////////////////////////////////////
//////////////////////////////////////////
/////////////// Utilities ////////////////
//////////////////////////////////////////
//////////////////////////////////////////

void fri::ogl::QueueTexturedRectangle(TexturedVertexBuffer & Buffer, glm::vec2 PStart, glm::vec2 PEnd
                                                                   , glm::vec2 TStart, glm::vec2 TEnd) {
  TexturedVertex vert;
  std::vector<TexturedVertex> tid;
  std::vector<GLuint> tii;

  vert.r = vert.g = vert.b = vert.a = 1;

  vert.x = PStart.x;
  vert.y = PStart.y;
  vert.u = TStart.x;
  vert.v = TStart.y;
  tid.push_back(vert);

  vert.y = PEnd.y;
  vert.v = TEnd.y;
  tid.push_back(vert);

  vert.x = PEnd.x;
  vert.y = PStart.y;
  vert.u = TEnd.x;
  vert.v = TStart.y;
  tid.push_back(vert);

  vert.y = PEnd.y;
  vert.v = TEnd.y;
  tid.push_back(vert);

  tii.push_back(0);
  tii.push_back(1);
  tii.push_back(2);
  tii.push_back(1);
  tii.push_back(2);
  tii.push_back(3);

  Buffer.AddVerticies(tid, tii);
}
