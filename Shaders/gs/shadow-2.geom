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
		vec4 P = gl_in[i].gl_Position;
		P.y = boundingBoxMin.y;
		gl_Position = modelViewProjectionMatrix*P;
		EmitVertex();
	}
    EndPrimitive();
	gfrontColor = vec4(0.0,1.0,1.0,1.0);
	if (gl_PrimitiveIDIn == 0) 
	{
		vec3 C = vec3((boundingBoxMax.x+boundingBoxMin.x)/2, (boundingBoxMax.y+boundingBoxMin.y)/2, (boundingBoxMax.z+boundingBoxMin.z)/2);
		gl_Position = modelViewProjectionMatrix*vec4(0.0,(0.01 + boundingBoxMin.y),1.0,1.0); EmitVertex();
		gl_Position = modelViewProjectionMatrix*vec4(0.0,(0.01 + boundingBoxMin.y),1.0,1.0); EmitVertex();
		gl_Position = modelViewProjectionMatrix*vec4(0.0,(0.01 + boundingBoxMin.y),1.0,1.0); EmitVertex();
		gl_Position = modelViewProjectionMatrix*vec4(0.0,(0.01 + boundingBoxMin.y),1.0,1.0); EmitVertex();
    	EndPrimitive();

	}
}
