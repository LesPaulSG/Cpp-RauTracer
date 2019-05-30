#pragma once
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "geometry.h"

const int WIDTH = 3840;   //Screen parameters
const int HEIGHT = 2160;

struct Light {
	Light(const Vec3f& p, const float i) : position(p), intensity(i) {}
	Vec3f position;
	float intensity;
};

struct Material {
	Material(const float r, const Vec4f& a, const Vec3f& color, const float spec) : refractive_index(r), albedo(a), diffuse_color(color), specular_exponent(spec) {}
	Material() : refractive_index(1), albedo(1, 0, 0, 0), diffuse_color(), specular_exponent() {}
	float refractive_index;
	Vec4f albedo;
	Vec3f diffuse_color;
	float specular_exponent;
};

struct Sphere {
	Vec3f center;
	float radius;
	Material material;

	Sphere(const Vec3f& c, const float r, const Material& m) : center(c), radius(r), material(m) {}

	bool ray_intersect(const Vec3f&, const Vec3f&, float&) const;
};

Vec3f reflect(const Vec3f&, const Vec3f&);

Vec3f refract(const Vec3f&, const Vec3f&, const float, const float eta_i = 1.f);

bool scene_intersect(const Vec3f&, const Vec3f&, const std::vector<Sphere>&, Vec3f&, Vec3f&, Material&);

Vec3f cast_ray(const Vec3f&, const Vec3f&, const std::vector<Sphere>&, const std::vector<Light>&, size_t depth = 0);

void write(int, int, std::vector<Vec3f>*);

void render(int, std::vector<Vec3f>*, const float, const std::vector<Sphere>&, const std::vector<Light>&);

void preRender(const std::vector<Sphere>&, const std::vector<Light>&);

#endif // !DEFINITIONS_H