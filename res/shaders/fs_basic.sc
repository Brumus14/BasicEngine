$input v_position, v_color0

uniform vec4 iTime;

#include <bgfx_shader.sh>


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

  return 0;
}

void main() {
  vec2 iResolution = vec2(1920, 1080);

  vec2 scale = vec2(2.0 * pow(2.0, -iTime.x), (2.0 / (iResolution.x / iResolution.y)) * pow(2.0, -iTime.x));
  vec2 offset = vec2(-1.2485, -0.03);
  vec2 normalisedCoord = vec2((v_position.x * scale.x) + offset.x, (v_position.y * scale.y) + offset.y);
  int ret = Mandelbrot(normalisedCoord);

  if (ret == 0) {
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


// const int iterations = 9000;
//
// int Mandelbrot(vec2 c) {
//   vec2 z = vec2(0.0, 0.0);
//   vec2 newZ = z;
//
//   for (int i = 0; i < iterations; i++) {
//     newZ.x = pow(z.x, 2.0) - pow(z.y, 2.0) + c.x;
//     newZ.y = (2.0 * z.x * z.y) + c.y;
//
//     z = newZ;
//
//     if (length(z) >= 512.0) { return i; }
//   }
//
//   return 0;
// }
//
// void main() {
//   vec2 iResolution = vec2(1920, 1080);
//
//   vec2 scale = vec2(2.0, 2.0 / (iResolution.x / iResolution.y));
//   vec2 offset = vec2(-1.4, 0);
//   vec2 normalisedCoord = vec2((v_position.x * scale.x) + offset.x, (v_position.y * scale.y) + offset.y);
//   int ret = Mandelbrot(normalisedCoord);
//
//   if (ret == 0) {
//     gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
//   }
//
//   else {
//     float colour = mod(0.01 * float(ret), 1.0);
//     gl_FragColor = vec4(colour, colour, colour, 1.0);
//   }
// }
