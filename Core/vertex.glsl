#version 400
#define PI 3.14159265359
layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Color;
uniform vec3 rotation;
out vec4 ex_Color;

mat4 rotationX( in float angle ) {
  return mat4(
    1.0, 0, 0, 0,
    0, cos(angle), -sin(angle), 0,
    0, sin(angle), cos(angle), 0,
    0, 0, 0, 1);
}

mat4 rotationY( in float angle ) {
  return mat4(
    cos(angle), 0, sin(angle), 0,
    0, 1.0, 0, 0,
    -sin(angle), 0, cos(angle), 0,
    0, 0, 0, 1);
}

mat4 rotationZ( in float angle ) {
  return mat4(
    cos(angle), -sin(angle), 0, 0,
    sin(angle), cos(angle), 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1);
}

void main(void)
{
  gl_Position = in_Position * rotationX(rotation.x*PI/180.0) * rotationY(rotation.y*PI/180.0) * rotationZ(rotation.z*PI/180.0);
  ex_Color = in_Color;
}