/*

HueLib: Color space and chromatic operations library
Copyright (C) 2026 Hugo Barriga

*/

#ifndef HUELIB_H
#define HUELIB_H

#include <stdint.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

// --------------
//  Color spaces
// --------------
typedef struct { float r, g, b; }    RGB;
typedef struct { float r, g, b, a; } RGBA;

typedef struct { float h, s, v; }    HSV;
typedef struct { float h, s, l; }    HSL;
typedef struct { float c, m, y, k; } CMYK;

// ----------------
//  Packed formats
// ----------------
typedef uint16_t RGB565;
typedef uint32_t RGB888;
typedef uint32_t RGBA8888;
typedef uint32_t ARGB8888;
typedef uint32_t BGRA8888;

// --------------------------
//  Color space constructors
// --------------------------
RGB color_rgb(float r, float g, float b);
RGBA color_rgba(float r, float g, float b, float a);
HSV color_hsv(float h, float s, float v);
HSL color_hsl(float h, float s, float l);
CMYK color_cmyk(float c, float m, float y, float k);

// --------------------
//  Conversions to RGB
// --------------------
RGB color_from_hsv(HSV c);
RGB color_from_hsl(HSL c);
RGB color_from_cmyk(CMYK c);

// ----------------------
//  Conversions from RGB
// ----------------------
HSV color_to_hsv(RGB c);
HSL color_to_hsl(RGB c);
CMYK color_to_cmyk(RGB c);

// ---------------
//  Alpha channel
// ---------------
RGBA color_with_alpha(RGB c, float a);
RGBA color_opaque(RGB c);

// --------------------------
//  Packed format conversion
// --------------------------
RGB color_unpack_rgb565(RGB565 c);
RGB565 color_pack_rgb565(RGB c);

RGB color_unpack_rgb888(RGB888 c);
RGB888 color_pack_rgb888(RGB c);

RGBA color_unpack_rgba8888(RGBA8888 c);
RGBA8888 color_pack_rgba8888(RGBA c);

RGBA color_unpack_argb8888(ARGB8888 c);
ARGB8888 color_pack_argb8888(RGBA c);

RGBA color_unpack_bgra8888(BGRA8888 c);
BGRA8888 color_pack_bgra8888(RGBA c);

#ifdef __cplusplus
}
#endif

#endif // HUELIB_H
