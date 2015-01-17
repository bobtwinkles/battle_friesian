#version 130

uniform mat4 transform;

in vec4 coordinates;
in vec4 color;

out vec2 frag_texcoord;
out vec4 frag_color;

void main() {
  frag_texcoord = coordinates.zw;
  frag_color = color;
  gl_Position = transform * vec4(coordinates.xy, 0, 1);
}
