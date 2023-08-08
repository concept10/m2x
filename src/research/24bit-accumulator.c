#include <glib.h>

typedef struct {
    guint32 accumulator;
} Accumulator;

typedef struct {
    GObject parent_instance;
    Accumulator *accumulator;
} AccumulatorObject;

G_DEFINE_TYPE(AccumulatorObject, accumulator_object, G_TYPE_OBJECT);

static void accumulator_object_init(AccumulatorObject *obj) {
    obj->accumulator = g_malloc(sizeof(Accumulator));
    obj->accumulator->accumulator = 0;
}

static void accumulator_object_finalize(GObject *object) {
    AccumulatorObject *obj = ACCUMULATOR_OBJECT(object);
    g_free(obj->accumulator);
    G_OBJECT_CLASS(accumulator_object_parent_class)->finalize(object);
}

static void accumulator_object_class_init(AccumulatorObjectClass *klass) {
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->finalize = accumulator_object_finalize;
}

AccumulatorObject *accumulator_object_new(void) {
    return g_object_new(ACCUMULATOR_TYPE_OBJECT, NULL);
}

void accumulator_add(AccumulatorObject *obj, guint32 value) {
    obj->accumulator->accumulator += value;
    if (obj->accumulator->accumulator > 0xFFFFFF) {
        obj->accumulator->accumulator &= 0xFFFFFF;
    }
}

guint32 accumulator_get_value(AccumulatorObject *obj) {
    return obj->accumulator->accumulator;
}

int main() {
    g_type_init();
    AccumulatorObject *accumulator = accumulator_object_new();

    accumulator_add(accumulator, 0x123456);
    accumulator_add(accumulator, 0x789ABC);

    guint32 result = accumulator_get_value(accumulator);
    g_print("Accumulator value: 0x%06X\n", result);

    g_object_unref(accumulator);

    return 0;
}