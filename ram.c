#include <glib-object.h>

#define RAM_BANK_SIZE 65536
#define NUM_BANKS 2

typedef struct {
    GObject parent;
    guint8 *banks[NUM_BANKS];
    guint8 active_bank;
} RamEmulator;

typedef struct {
    GObjectClass parent_class;
} RamEmulatorClass;

G_DEFINE_TYPE(RamEmulator, ram_emulator, G_TYPE_OBJECT)

static void ram_emulator_init(RamEmulator *self) {
    for (int i = 0; i < NUM_BANKS; i++) {
        self->banks[i] = g_malloc(RAM_BANK_SIZE);
    }
    self->active_bank = 0;
}

static void ram_emulator_class_init(RamEmulatorClass *klass) {}

RamEmulator *ram_emulator_new(void) {
    return g_object_new(RAM_TYPE_EMULATOR, NULL);
}

void ram_emulator_select_bank(RamEmulator *self, guint8 bank) {
    if (bank < NUM_BANKS) {
        self->active_bank = bank;
    }
}

void ram_emulator_write_byte(RamEmulator *self, guint16 address, guint8 data) {
    if (address < RAM_BANK_SIZE) {
        self->banks[self->active_bank][address] = data;
    }
}

guint8 ram_emulator_read_byte(RamEmulator *self, guint16 address) {
    if (address < RAM_BANK_SIZE) {
        return self->banks[self->active_bank][address];
    }
    return 0;
}

int main() {
    RamEmulator *ram = ram_emulator_new();

    ram_emulator_select_bank(ram, 0);
    ram_emulator_write_byte(ram, 0x1234, 0xAB);

    ram_emulator_select_bank(ram, 1);
    guint8 data = ram_emulator_read_byte(ram, 0x1234);

    g_print("Read data: 0x%02X\n", data);

    g_object_unref(ram);
    return 0;
}