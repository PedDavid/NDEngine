#version 330

layout (location = 0) out vec4 color;

in vec3 face_normal;
in vec3 light_dir;
in vec3 view_dir;

uniform float metalness;
uniform float roughness;
uniform vec3 diffuse;

float PI = 3.141592653589793238462643383;
float a;

/* Schlick GGX Geometry Factor Helper function*/
float Gsub(vec3 n, vec3 v) {
	float k = a / 2;
	float NoV = dot(n, v);
	return NoV / (NoV * (1.0 - k) + k);
}

/* Schlick GGX Geometry Factor */
float G(vec3 n, vec3 l, vec3 v, vec3 h){
	return Gsub(n, v) * Gsub(n, l);
	//return min(1, min(2 * dot(n, h) * dot(n, v) / dot(v, h), 2 * dot(n, h) * dot(n, l) / dot(v, h)));
}

/* Trowbridge-Reitz GGX Normal Distribution Function (m = h) */
float D(vec3 n, vec3 m) {
	float a2 = a * a;
	float NoM = dot(n, m);
	float coefficient_ = NoM * NoM * (a2 - 1.0) + 1.0;
	return a2 / (PI * coefficient_ * coefficient_);
}

/* Schlick Fresnel Approximation for microfacet BRDFs (m = h) */
vec3 F(vec3 cspec, vec3 l, vec3 m) {
	float base = 1 - clamp(dot(l, m), 0.0, 1.0);
	return cspec + (1.0 - cspec) * pow(base, 5.0);
}

/* Lambert model for diffuse term */
vec3 subSurfaceReflection() {
	return diffuse / PI;
}

void main() {
	a = ((1 + roughness)/2) * ((1 + roughness)/2);
	vec3 unit_normal = normalize(face_normal);
	vec3 unit_light = normalize(light_dir);
	vec3 unit_view = normalize(view_dir);

	float NoL = dot(unit_normal, unit_light);
	float NoV = dot(unit_normal, unit_view);
	vec3 h = normalize(unit_view + unit_light);

	vec3 colora = F(vec3(metalness), unit_light, h) * D(unit_normal, h); // * G(unit_normal, unit_light, unit_view, h) / (4 * NoL * NoV); + subSurfaceReflection();
	color = vec4(colora, 1.0);
}