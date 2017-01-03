uniform float TWIST;

void main()
{
    // Calculate rotation angle
    float angle = gl_Vertex.x ;
        

	float radius = (1 + sin(angle)) * (1 + 0.9 * cos(8 * angle)) * (1 + 0.1 * cos(24 * angle)) * (0.5 + 0.05 * cos(140 * angle));
    float x = cos(angle) * radius;
    float y = sin(angle) * radius;
	

	vec4 twistedCoord = vec4(
        gl_Vertex.x * (1 - TWIST) + x * TWIST,
        gl_Vertex.y * (1 - TWIST) + y * TWIST,
        gl_Vertex.z,
        gl_Vertex.w
    );
	
    vec4 position = gl_ModelViewProjectionMatrix * twistedCoord;
    // Transform twisted coordinate
    gl_Position = position;
    gl_FrontColor = (position + vec4(1.0)) * 0.5;
}
