uniform float TWIST;
varying vec3 v;

void main()
{
     // Calculate rotation angle
    float angle = gl_Vertex.y * TWIST;
    // calculate sin(angle) and cos(angle)
    float sa = sin(angle);
    float ca = cos(angle);
    /*
      Rotate vertex around Y axis:
      x' = x * cos(angle) - z * sin(angle)
      y' = y;
      z' = x * sin(angle) + z * cos(angle);
      w' = w;
    */
	float a = abs(TWIST) / 2.0;

    vec4 twistedCoord = vec4(
        gl_Vertex.x,
        (gl_Vertex.x * gl_Vertex.x + gl_Vertex.z * gl_Vertex.z) * a + (gl_Vertex.x * gl_Vertex.x - gl_Vertex.z * gl_Vertex.z) * (1 - a) - 10.0,
        gl_Vertex.z,
        gl_Vertex.w
    );

	v = vec3(gl_ModelViewMatrix * twistedCoord);

    vec4 position = gl_ModelViewProjectionMatrix * twistedCoord;
    // Transform twisted coordinate



    gl_Position = position;
    gl_FrontColor = (position + vec4(1.0)) * 0.5;
}
