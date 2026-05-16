#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec3 vvertex[];
in vec4 vfrontColor[];
out vec4 gfrontColor;
out vec3 gnormal;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float step = 0.1;

void print(vec3 p, vec3 N) 
{
    gfrontColor = vec4(0.8,0.8,0.8,1.0);
    gnormal = N;
    gl_Position = modelViewProjectionMatrix*vec4(p,1.0);
	EmitVertex();
}

void main( void )
{
    vec3 N;
    vec3 bar = ((vvertex[0]+vvertex[1]+vvertex[2])/3);
    bar /= step;
    bar = vec3(floor(bar.x+0.5), floor(bar.y+0.5), floor(bar.z+0.5));
    bar *= step;
	float stp = float(step)/2.0;
	 
	vec3 B = bar + vec3(-stp, stp, -stp);
	vec3 C = bar + vec3(stp, stp, -stp);
	vec3 F = bar + vec3(-stp, -stp, -stp);
	vec3 G = bar + vec3(stp, -stp, -stp);
	vec3 H = bar + vec3(stp, -stp, stp);
	vec3 D = bar + vec3(stp, stp, stp);
	vec3 A = bar + vec3(-stp, stp, stp);
	vec3 E = bar + vec3(-stp, -stp, stp);
	
	N = normalMatrix*vec3(0,0,1);
	print(A,N); 
	print(D,N); 
	print(E,N); 
	print(H,N);
	EndPrimitive();
	
	N = normalMatrix*vec3(0,1,0);
	print(A,N); 
	print(D,N); 
	print(B,N); 
	print(C,N);
	EndPrimitive();
	
	N = normalMatrix*vec3(0,0,-1);
	print(B,N); 
	print(C,N); 
	print(F,N); 
	print(G,N);
	EndPrimitive();

	N = normalMatrix*vec3(0,-1,0);
	print(F,N); 
	print(G,N); 
	print(E,N); 
	print(H,N);
	EndPrimitive();
	
	N = normalMatrix*vec3(1,0,0);
	print(C,N); 
	print(D,N); 
	print(G,N); 
	print(H,N);
	EndPrimitive();
	
	N = normalMatrix*vec3(-1,0,0);
	print(A,N); 
	print(B,N); 
	print(E,N); 
	print(F,N);
	EndPrimitive();
}