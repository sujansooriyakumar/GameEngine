#version 450 core



uniform mat4 view;
uniform mat4 proj;
uniform vec3 pos;
uniform vec3 test;
uniform float size;

out vec3 colour;

void main()
{
	colour = test;

	vec4 tmp = view * vec4(pos, 1.0f);
	float dist = length(vec3(tmp.xyz));
	float atten = inversesqrt(dist * 0.1f);
	gl_PointSize = size * atten;
	gl_Position = proj * view  * vec4(pos, 1.0f);



}