#include <iostream>

int main() {
  constexpr int   ramp_len = 10;
  constexpr float ramp[ramp_len] {0.0f,0.1f,0.4f,0.7f,0.6f,0.9f,0.11f,0.17f,0.21f};

  for (int ramps = 0; ramps < 10; ++ramps) {
    for (int i =0; i < ramp_len; ++i) {
      // moving average filter
      float avg  = ramp[i == 0 ? ramp_len - 1 : i];
      avg       += ramp[i                        ];
      avg       += ramp[i == ramp_len - 1 ? 0 : i];
      avg       /= 3;
      std::cout << avg << std::endl;
    }
  }

}
