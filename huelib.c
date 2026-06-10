/*

HueLib: Color space and chromatic operations library
Copyright (C) 2026 Hugo Barriga

*/

#include "huelib.h"

static float hue_to_rgb(float p, float q, float t)
{
	if (t < 0.0f) t += 1.0f;
	if (t > 1.0f) t -= 1.0f;

	if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
	if (t < 1.0f / 2.0f) return q;
	if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;

	return p;
}

inline RGB color_rgb(float r, float g, float b)
{
	return (RGB){
		.r = r,
		.g = g,
		.b = b
	};
}

inline RGBA color_rgba(float r, float g, float b, float a)
{
	return (RGBA){
		.r = r,
		.g = g,
		.b = b,
		.a = a
	};
}

inline HSV color_hsv(float h, float s, float v)
{
	return (HSV){
		.h = h,
		.s = s,
		.v = v
	};
}

inline HSL color_hsl(float h, float s, float l)
{
	return (HSL){
		.h = h,
		.s = s,
		.l = l
	};
}

inline CMYK color_cmyk(float c, float m, float y, float k)
{
	return (CMYK){
		.c = c,
		.m = m,
		.y = y,
		.k = k
	};
}

RGB color_from_hsv(HSV hsv)
{
	float h = hsv.h;
	float s = hsv.s;
	float v = hsv.v;

	float r, g, b;

	float c_val = v * s;
	float hh = h / 60.0f;
	float x = c_val * (1.0f - fabsf(fmodf(hh, 2.0f) - 1.0f));
	float m = v - c_val;

    if (hh >= 0 && hh < 1) { r = c_val; g = x;     b = 0; }
    else if (hh < 2)       { r = x;     g = c_val; b = 0; }
    else if (hh < 3)       { r = 0;     g = c_val; b = x; }
    else if (hh < 4)       { r = 0;     g = x;     b = c_val; }
    else if (hh < 5)       { r = x;     g = 0;     b = c_val; }
    else                   { r = c_val; g = 0;     b = x; }

	return color_rgb(r + m, g + m, b + m);
}

RGB color_from_hsl(HSL hsl)
{
    float h = hsl.h;
    float s = hsl.s;
    float l = hsl.l;

    float r, g, b;

    if (s == 0.0f) {
        r = g = b = l;
		return color_rgb(r, g, b);
    }

    float q = (l < 0.5f) ? (l * (1.0f + s)) : (l + s - l * s);
    float p = 2.0f * l - q;

    float hk = h / 360.0f;

    float t_r = hk + 1.0f / 3.0f;
    float t_g = hk;
    float t_b = hk - 1.0f / 3.0f;

    r = hue_to_rgb(p, q, t_r);
    g = hue_to_rgb(p, q, t_g);
    b = hue_to_rgb(p, q, t_b);

	return color_rgb(r, g, b);
}

RGB color_from_cmyk(CMYK cmyk)
{
    float k  = cmyk.k;
    float c1 = cmyk.c;
    float m  = cmyk.m;
    float y  = cmyk.y;

    float r = (1.0f - c1) * (1.0f - k);
    float g = (1.0f - m)  * (1.0f - k);
    float b = (1.0f - y)  * (1.0f - k);

	return color_rgb(r, g, b);
}
