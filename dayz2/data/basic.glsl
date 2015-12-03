#version 430 core

layout(location = 0) in vec4 vertex;
layout(location = 1) in vec2 uv;

uniform mat4 mvp;
out vec2 v_uv;

void main(){
	gl_Position = mvp * vertex;
	v_uv = uv;
}

@

#version 430 core

out vec4 color;
in vec2 v_uv;
uniform vec2 b[8];
uniform int a;
uniform sampler2D u_textureSampler;

void main(){
	color= texture(u_textureSampler,v_uv);
}
