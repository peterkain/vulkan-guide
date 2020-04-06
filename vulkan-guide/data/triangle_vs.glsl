#version 450
#extension GL_ARB_separate_shader_objects : enable

vec2 positions[3] = vec2[](
	vec2( 0.0, -0.5),
	vec2( 0.5,  0.5),
	vec2(-0.5,  0.5)
);

layout(location = 0) out vec3 color;

int dummyTime = 0;

void main() {
	gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
	color = vec3(sin(dummyTime), cos(dummyTime), tan(dummyTime));
	if (++dummyTime == 360) {
		dummyTime = 0;
	}
}