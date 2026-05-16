#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

in vec3 N[];
uniform float time;
const float speed = 1.2;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main( void )
{
	vec3 normal_media = vec3((N[0].x + N[1].x + N[2].x)/3, 
						(N[0].y + N[1].y + N[2].y)/3,
						(N[0].z + N[1].z + N[2].z)/3);
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		vec4 traslacion = vec4(vec3(gl_in[i].gl_Position.xyz + vec3(speed*time*normal_media)),1.0);
		gl_Position = modelViewProjectionMatrix*traslacion;
		EmitVertex();
	}
    EndPrimitive();
}
