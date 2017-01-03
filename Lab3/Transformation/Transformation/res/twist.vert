uniform float TWIST;
varying vec3 vertex;
varying vec3 normal;

float GetSurfaceY(float x, float z, float step)
{
	return mix(x * x + z * z, x * x - z * z, step) - 10.0;
}

vec4 GetSurfaceVertex(float x, float z, float w, float step)
{
	return vec4(x, GetSurfaceY(x, z, step), z, w);
}

void main()
{ 
	float phase = abs(TWIST) / 2.0;

    vec4 twistedCoord = GetSurfaceVertex(gl_Vertex.x, gl_Vertex.z, gl_Vertex.w, phase);

    vec4 position = gl_ModelViewProjectionMatrix * twistedCoord;
 
	vec4 twistedCoord1 = GetSurfaceVertex(gl_Vertex.x + 0.1, gl_Vertex.z, gl_Vertex.w, phase);
	vec4 twistedCoord2 = GetSurfaceVertex(gl_Vertex.x, gl_Vertex.z + 0.1, gl_Vertex.w, phase);

	vec3 v1 = twistedCoord1.xyz - twistedCoord.xyz;
	vec3 v2 = twistedCoord2.xyz - twistedCoord.xyz;
	vec3 norm = normalize(cross(v1, v2));

	vertex = vec3(gl_ModelViewMatrix * twistedCoord);	
	normal = normalize(gl_NormalMatrix * norm);
    gl_Position = position;
    gl_FrontColor = (position + vec4(1.0)) * 0.5;
}
