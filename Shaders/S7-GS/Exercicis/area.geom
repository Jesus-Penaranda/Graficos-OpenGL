#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
uniform mat4 projectionMatrix;
const float areamax = 0.0005;

void main( void )
{
	vec3 v = gl_in[0].gl_Position.xyz - gl_in[1].gl_Position.xyz;
	vec3 u = gl_in[0].gl_Position.xyz - gl_in[2].gl_Position.xyz;
	float area = (length(cross(u,v))/2);
	area /= areamax;
	float area_norm = clamp(area, 0.0, 1.0);
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vec4(mix(vec3(1.0,0.0,0.0), vec3(1.0,1.0,0.0), area_norm),1.0);
		gl_Position = projectionMatrix*gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
	

}
