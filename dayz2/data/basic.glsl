#version 430 core

layout(location = 0) in vec4 vertex;

uniform mat4 mvp;

void main(){
	gl_Position = mvp * vertex;
}

@

#version 430 core

out vec4 color;
 
void main(){
    color = vec4(1, 0.7, 0.5, 0.5);
}