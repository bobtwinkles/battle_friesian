#version 130

uniform sampler2D tex;
uniform mat4 tex_transform;

in vec2 frag_texcoord;
in vec4 frag_color;

out vec4 color;

void main() {
  vec4 transformed_texcoord = tex_transform * vec4(frag_texcoord, 0, 1);
  transformed_texcoord /= transformed_texcoord.w;
  color = frag_color * texture(tex, transformed_texcoord.xy);
}
