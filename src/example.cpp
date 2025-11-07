// sdl_cube.cpp
#include <SDL2/SDL.h>
#include <array>
#include <cmath>
#include <chrono>

struct Vec3 { float x,y,z; };

static inline Vec3 rot_xyz(const Vec3& v, float ax,float ay,float az){
  float cx=std::cos(ax), sx=std::sin(ax);
  float cy=std::cos(ay), sy=std::sin(ay);
  float cz=std::cos(az), sz=std::sin(az);
  Vec3 r=v;
  // X
  float y=r.y*cx - r.z*sx, z=r.y*sx + r.z*cx; r.y=y; r.z=z;
  // Y
  float x=r.x*cy + r.z*sy; z=-r.x*sy + r.z*cy; r.x=x; r.z=z;
  // Z
  x=r.x*cz - r.y*sz; y=r.x*sz + r.y*cz; r.x=x; r.y=y;
  return r;
}

int main(int, char**){
  if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) return 1;

  SDL_Window* win = SDL_CreateWindow(
    "Wire Cube (SDL2)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    960, 720, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
  if (!win) { SDL_Quit(); return 1; }

  SDL_Renderer* ren = SDL_CreateRenderer(
    win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!ren) { SDL_DestroyWindow(win); SDL_Quit(); return 1; }

  // Геометрия куба
  const std::array<Vec3,8> V = {{
    {-1,-1,-1},{ 1,-1,-1},{ 1, 1,-1},{-1, 1,-1},
    {-1,-1, 1},{ 1,-1, 1},{ 1, 1, 1},{-1, 1, 1}
  }};
  const std::array<std::pair<int,int>,12> E = {{
    {0,1},{1,2},{2,3},{3,0},
    {4,5},{5,6},{6,7},{7,4},
    {0,4},{1,5},{2,6},{3,7}
  }};

  bool running = true, paused = false;
  float ax=0.f, ay=0.f, az=0.f;
  float speed_x=0.9f, speed_y=0.7f, speed_z=0.4f;
  float fov = 1.2f;         // «широкоугольность»: больше — шире
  float cam_z = 3.2f;       // камера дальше — меньше перспектива

  auto t0 = std::chrono::steady_clock::now();

  while (running) {
    // --- events ---
    for (SDL_Event e; SDL_PollEvent(&e);) {
      if (e.type == SDL_QUIT) running = false;
      if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_ESCAPE: case SDLK_q: running = false; break;
          case SDLK_SPACE:  paused = !paused; break;
          case SDLK_UP:     speed_x += 0.1f; break;
          case SDLK_DOWN:   speed_x -= 0.1f; break;
          case SDLK_LEFT:   speed_y -= 0.1f; break;
          case SDLK_RIGHT:  speed_y += 0.1f; break;
          case SDLK_EQUALS: case SDLK_PLUS:  fov *= 1.05f; break;
          case SDLK_MINUS:  fov /= 1.05f; break;
        }
      }
    }

    auto t1 = std::chrono::steady_clock::now();
    float dt = std::chrono::duration<float>(t1 - t0).count();
    t0 = t1;

    if (!paused) { ax += speed_x*dt; ay += speed_y*dt; az += speed_z*dt; }

    int W, H;
    SDL_GetRendererOutputSize(ren, &W, &H);
    float cx = W * 0.5f, cy = H * 0.5f;
    float scale = 0.45f * (W < H ? W : H) * fov;

    // --- render ---
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);

    // Проецируем вершины
    std::array<SDL_FPoint,8> P{};
    for (int i=0;i<8;++i){
      Vec3 r = rot_xyz(V[i], ax, ay, az);
      r.z += cam_z;
      float invz = 1.0f / r.z;
      float sx = cx + r.x * invz * scale;
      float sy = cy - r.y * invz * scale;
      P[i] = SDL_FPoint{sx, sy};
    }

    // Рёбра
    for (auto [a,b] : E) {
      SDL_RenderDrawLineF(ren, P[a].x, P[a].y, P[b].x, P[b].y);
    }

    SDL_RenderPresent(ren);
  }

  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
