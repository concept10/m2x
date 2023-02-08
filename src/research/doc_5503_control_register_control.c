
// this program emulates the functionality of a control register for a sound chip in a video game console
#include <stdio.h>

typedef enum {
  CHANNEL_1 = 0,
  CHANNEL_2 = 1,
  CHANNEL_3 = 2,
  CHANNEL_4 = 3
} ChannelAssignment;

typedef enum {
  OSCILLATOR_MODE_A = 0,
  OSCILLATOR_MODE_B = 1,
  OSCILLATOR_MODE_C = 2,
  OSCILLATOR_MODE_D = 3
} OscillatorMode;

typedef struct {
  ChannelAssignment channel_assignment;
  OscillatorMode oscillator_mode;
  int halt;
} ControlRegister;

void set_channel_assignment(ControlRegister *reg, ChannelAssignment channel) {
  reg->channel_assignment = channel;
}

void set_oscillator_mode(ControlRegister *reg, OscillatorMode mode) {
  reg->oscillator_mode = mode;
}

void set_halt(ControlRegister *reg, int halt) {
  reg->halt = halt;
}

int main() {
  ControlRegister reg;

  set_channel_assignment(&reg, CHANNEL_2);
  set_oscillator_mode(&reg, OSCILLATOR_MODE_C);
  set_halt(&reg, 1);

  printf("Channel Assignment: %d\n", reg.channel_assignment);
  printf("Oscillator Mode: %d\n", reg.oscillator_mode);
  printf("Halt: %d\n", reg.halt);

  return 0;
}
