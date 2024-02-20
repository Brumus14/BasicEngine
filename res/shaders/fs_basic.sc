$input v_position, v_color0

#include <bgfx_shader.sh>

// void main() {
//   // gl_FragColor = v_color0;
//
//   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
// }

const int iterations = 9;

int Mandelbrot(vec2 c) {
  vec2 z = vec2(0.0, 0.0);
  vec2 newZ = vec2(0.0, 0.0);

  for (int i = 0; i < iterations; i++) {
    newZ.x = pow(z.x, 2.0) - pow(z.y, 2.0) + c.x;
    newZ.y = (2.0 * z.x * z.y) + c.y;

    z = newZ;

    if (length(z) >= 64.0) { return i; }
  }

  return 0;
}

void main() {
  vec2 iResolution = vec2(800, 600);
  float iTime = 1.0;

  float scale = (4.0 / iResolution.x);
  vec2 offset = vec2(-1.4, 0);
  vec2 normalisedCoord = vec2(((v_position.x - (iResolution.x / 2.0)) * scale) + offset.x, ((v_position.y - (iResolution.y / 2.0)) * scale) + offset.y);
  int ret = Mandelbrot(normalisedCoord);

  if (ret == 0) {
    gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
  }

  else {
    float colour = 0.01 * float(ret);
    gl_FragColor = vec4(colour, colour, colour, 1.0);
  }
}
