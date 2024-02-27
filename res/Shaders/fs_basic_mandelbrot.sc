$input v_position, v_color0

uniform vec4 iTime;

#include <bgfx_shader.sh>

const vec2 resolution = vec2(1920, 1080);

// const float maxIterations = 512.0;
//
// float mandelbrot(vec2 uv) {
//   vec2 c = 4.0 * uv - vec2(0.7, 0.0);
//   c = c / pow(iTime.x, 4.0) - vec2(0.65, 0.45);
//   highp vec2 z = vec2(0.0);
//   float iter = 0.0;
//
//   for(float i; i < maxIterations; i++) {
//     z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
//
//     if (dot(z, z) > 4.0) {
//       return iter / maxIterations;
//     }
//
//     iter++;
//   }
//
//   return 0.0;
// }
//
// vec3 hash(float m) {
//   float x = fract(sin(m) * 5625.246);
//   float y = fract(sin(m + x) * 2216.486);
//   float z = fract(sin(x + y) * 8276.352);
//   return vec3(x, y, z);
// }
//
// void main() {
//   vec2 uv = vec2(v_position.x, v_position.y / (resolution.x / resolution.y));
//   vec3 col = vec3(0.0);
//
//   float m = mandelbrot(uv);
//   col += hash(m);
//
//   gl_FragColor = vec4(col, 1.0);
// }



const int iterations = 9000;

int Mandelbrot(vec2 c) {
  vec2 z = vec2(0.0, 0.0);
  vec2 newZ = z;

  for (int i = 0; i < iterations; i++) {
    newZ.x = pow(z.x, 2.0) - pow(z.y, 2.0) + c.x;
    newZ.y = (2.0 * z.x * z.y) + c.y;

    z = newZ;

    if (length(z) >= 2048.0) { return i; }
  }

  return iterations;
}

void main() {
  vec2 iResolution = vec2(1920, 1080);

  vec2 scale = vec2(2.0 * pow(2.0, -iTime.x), (2.0 / (iResolution.x / iResolution.y)) * pow(2.0, -iTime.x));
  vec2 offset = vec2(-1.2485, -0.03);
  vec2 normalisedCoord = vec2((v_position.x * scale.x) + offset.x, (v_position.y * scale.y) + offset.y);
  int ret = Mandelbrot(normalisedCoord);

  if (ret == iterations) {
    gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
  }

  else {
    float colour = mod((0.01) * float(ret), 1.0);
    gl_FragColor = vec4(colour, colour, colour, 1.0);
  }

  /*if (abs(fragCoord.x - iResolution.x / 2.0) <= 4.0 && abs(fragCoord.y - iResolution.y / 2.0) <= 4.0) {
    fragColor = vec4(1.0, 0.0, 0.0, 0.5);
  }*/
}
