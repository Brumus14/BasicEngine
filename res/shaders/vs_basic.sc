$input a_position, a_color0
$output v_position, v_color0

#include <bgfx_shader.sh>

void main() {
	gl_Position = vec4(a_position, 1.0);

  v_position = a_position;
	v_color0 = a_color0;
}
