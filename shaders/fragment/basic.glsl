#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

in vec2 v_TextCoord;

void main() {
  vec4 textColor = texture(u_Texture, v_TextCoord);
  if (textColor[3] > 0) {
    color = u_Color;
  } else {
    discard;
  }
}