#include "Environment.hpp"

int main(int argc, char* args[])
{
  env.Initialize("game!", 480, 270);
  return env.Run();
}

