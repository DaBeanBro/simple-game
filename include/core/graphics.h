#ifndef GRAPHICS_H
#define GRAPHICS_H

// Graphics related method definitions

//
struct Vector2 {
    float x;
    float y;
};

struct Vector3 {
    float x;
    float y;
    float z;
};

struct Vector2 vector2_add(struct Vector2 a, struct Vector2 b);
struct Vector2 vector2_subtract(struct Vector2 a, struct Vector2 b);

#endif
