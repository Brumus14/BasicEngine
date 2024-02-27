$input a_position, a_color0, a_texCoord0
$output v_position, v_color0, v_texCoord0


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

#include <bgfx_shader.sh>

void main() {
  vec4 projectedPosition = projection * view * model * vec4(a_position, 1.0);

	gl_Position = projectedPosition;
	// gl_Position = vec4(a_position, 1.0f);

  v_position = a_position;
	v_color0 = a_color0;
  v_texCoord0 = a_texCoord0;
}
