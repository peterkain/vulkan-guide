#version 450

layout(location = 0) out vec4 fragColor;

vec2 resolution = vec2(256.0, 256.0);

float noise(vec2 pos) {
	return fract(sin(dot(pos.xy, vec2(12.34, 56.789))));
}

void main() {
	vec2 pos = gl_FragCoord.xy/resolution.xy;
	float color = noise(pos);

	//fragColor = vec4(vec3(clamp(color * 2, 0.0, 0.5), 0.2, 0.0), 1.0);
	fragColor = vec4(0.0, sin(gl_FragCoord.x) / 3, cos(gl_FragCoord.y) / 2, 1.0);
}