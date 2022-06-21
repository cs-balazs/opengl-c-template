#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textCoord;

uniform mat4 u_MVP;

out vec2 v_TextCoord;

void main() {
  gl_Position = position * u_MVP;
  v_TextCoord = textCoord;
}