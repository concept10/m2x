const ChannelAssignment = {
    CHANNEL_1: 0,
    CHANNEL_2: 1,
    CHANNEL_3: 2,
    CHANNEL_4: 3,
  };
  
  const OscillatorMode = {
    OSCILLATOR_MODE_A: 0,
    OSCILLATOR_MODE_B: 1,
    OSCILLATOR_MODE_C: 2,
    OSCILLATOR_MODE_D: 3,
  };
  
  class ControlRegister {
    constructor() {
      this.channel_assignment = null;
      this.oscillator_mode = null;
      this.halt = null;
    }
  
    setChannelAssignment(channel) {
      this.channel_assignment = channel;
    }
  
    async setOscillatorMode(mode) {
      return new Promise((resolve) => {
        setTimeout(() => {
          this.oscillator_mode = mode;
          resolve();
        }, 1000);
      });
    }
  
    setHalt(halt) {
      this.halt = halt;
    }
  }
  
  const reg = new ControlRegister();
  reg.setChannelAssignment(ChannelAssignment.CHANNEL_2);
  
  reg.setOscillatorMode(OscillatorMode.OSCILLATOR_MODE_C)
    .then(() => {
      reg.setHalt(1);
  
      console.log(`Channel Assignment: ${reg.channel_assignment}`);
      console.log(`Oscillator Mode: ${reg.oscillator_mode}`);
      console.log(`Halt: ${reg.halt}`);
    });
  