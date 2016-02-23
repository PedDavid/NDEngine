#version 330
#define PI 3.141592653589793238462643383

layout (location = 0) out vec4 color;

in vec3 face_normal;
in vec3 light_dir;
in vec3 view_dir;

uniform float metalness;
uniform float roughness;
uniform vec3 diffuse;

/* Schlick GGX Geometry Factor Helper function*/
float Gsub(vec3 n, vec3 v) {
	float k = roughness * roughness / 2;
	float NoV = dot(n, v);
	return NoV / (NoV * (1 - k) + k);
}

/* Schlick GGX Geometry Factor */
float G(vec3 n, vec3 l, vec3 v){
	return Gsub(n, v) * Gsub(n, l);
}

/* Trowbridge-Reitz GGX Normal Distribution Function (m = h) */
float D(vec3 n, vec3 m) {
	float a = roughness * roughness;
	float a2 = a * a;
	float NoM = dot(n, m);
	float coefficient_ = NoM * NoM * (a2 - 1) + 1;
	return a2 / PI * coefficient_ * coefficient_;
}

/* Schlick Fresnel Approximation for microfacet BRDFs (m = h) */
float F(float cspec, vec3 l, vec3 m) {
	float base = 1 - dot(l, m);
	return cspec + (1 - cspec) * pow(1 - dot(l, m), 5.0);
}

/* Lambert model for diffuse term */
vec3 subSurfaceReflection() {
	return vec3(diffuse/PI);
}

void main() {
	float NoL = dot(face_normal, light_dir);
	vec3 h = normalize(view_dir + light_dir);
	vec3 colora = F(metalness, light_dir, h) * D(face_normal, h) * G(face_normal, light_dir, view_dir) / (4 * NoL * dot(face_normal, view_dir)) * subSurfaceReflection();
	color = vec4(colora, 1.0);
}