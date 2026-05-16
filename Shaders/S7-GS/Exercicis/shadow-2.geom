#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix*gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();

	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vec4(0.0,0.0,0.0,1.0);
		vec3 pos = vec3(gl_in[i].gl_Position.x, boundingBoxMin.y, gl_in[i].gl_Position.z);
		gl_Position = modelViewProjectionMatrix*vec4(pos,1.0);
		EmitVertex();
	}
    EndPrimitive();

	if (gl_PrimitiveIDIn == 0) 
	{
		vec3 Centro = (boundingBoxMax + boundingBoxMin)/2;
		float r = distance(boundingBoxMax, boundingBoxMin)/2;
		vec3 A = vec3(Centro.x - r , boundingBoxMin.y - 0.01, Centro.z - r);
		vec3 B = vec3(Centro.x + r , boundingBoxMin.y - 0.01, Centro.z - r);
		vec3 C = vec3(Centro.x - r , boundingBoxMin.y - 0.01, Centro.z + r);
		vec3 D = vec3(Centro.x + r , boundingBoxMin.y - 0.01, Centro.z + r);
		gfrontColor = vec4(0.0,1.0,1.0,1.0);
		gl_Position = modelViewProjectionMatrix*vec4(A,1.0);
		EmitVertex();
		gfrontColor = vec4(0.0,1.0,1.0,1.0);
		gl_Position = modelViewProjectionMatrix*vec4(B,1.0);
		EmitVertex();
		gfrontColor = vec4(0.0,1.0,1.0,1.0);
		gl_Position = modelViewProjectionMatrix*vec4(C,1.0);
		EmitVertex();
		gfrontColor = vec4(0.0,1.0,1.0,1.0);
		gl_Position = modelViewProjectionMatrix*vec4(D,1.0);
		EmitVertex();


	}
}
