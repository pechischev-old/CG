uniform float TWIST;
varying vec3 vertex;
varying vec3 normal;

void main()
{ 
	float a = abs(TWIST) / 2.0;

    vec4 twistedCoord = vec4(
        gl_Vertex.x,
        (gl_Vertex.x * gl_Vertex.x + gl_Vertex.z * gl_Vertex.z) * a + (gl_Vertex.x * gl_Vertex.x - gl_Vertex.z * gl_Vertex.z) * (1 - a) - 10.0,
        gl_Vertex.z,
        gl_Vertex.w
    );

    vec4 position = gl_ModelViewProjectionMatrix * twistedCoord;
 
	vertex = vec3(gl_ModelViewMatrix * twistedCoord);


	float u = gl_Vertex.x + 0.1;
	float v = gl_Vertex.z + 0.1;

	vec4 twistedCoord1 = vec4(
        u,
        (u * u + gl_Vertex.z * gl_Vertex.z) * a + (u * u - gl_Vertex.z * gl_Vertex.z) * (1 - a) - 10.0,
        gl_Vertex.z,
        gl_Vertex.w
    );

	 vec4 twistedCoord2 = vec4(
        gl_Vertex.x,
        (gl_Vertex.x * gl_Vertex.x + v * v) * a + (gl_Vertex.x * gl_Vertex.x - v * v) * (1 - a) - 10.0,
        v,
        gl_Vertex.w
    );

	vec3 v1 = vec3(twistedCoord1.x, twistedCoord1.y, twistedCoord1.z) - vec3(twistedCoord.x, twistedCoord.y, twistedCoord.z);
	vec3 v2 = vec3(twistedCoord2.x, twistedCoord2.y, twistedCoord2.z) - vec3(twistedCoord.x, twistedCoord.y, twistedCoord.z);

	vec3 norm = normalize(cross(v1, v2));
	normal = normalize(gl_NormalMatrix * norm);

    gl_Position = position;
    gl_FrontColor = (position + vec4(1.0)) * 0.5;
}
