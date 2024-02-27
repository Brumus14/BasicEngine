$input v_position, v_color0, v_texcoord0

// uniform sampler2D wallTexture;

#include <bgfx_shader.sh>

SAMPLER2D(s_tex, 0);

void main() {
  // gl_FragColor = v_color0;
  gl_FragColor = vec4(texture2D(s_tex, v_texcoord0).rgb, 1.0f);
  // gl_FragColor = vec4(1.0f);
}
