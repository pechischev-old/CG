uniform float TWIST;

void main()
{
    // Calculate rotation angle
    float angle = gl_Vertex.y * TWIST;
    // calculate sin(angle) and cos(angle)
    float sa = sin(angle);
    float ca = cos(angle);
	//float radius = (1+sin(angle))*(1+0.9*cos(8*angle))*(1+0.1*cos(24*angle))*(0.5+0.05*cos(140*angle));
    /*
      Rotate vertex around Y axis:
      x' = x * cos(angle) - z * sin(angle)
      y' = y;
      z' = x * sin(angle) + z * cos(angle);
      w' = w;
    */
	vec4 twistedCoord = vec4(
        radius * ca,
        radius * sa,
        gl_Vertex.z,
        gl_Vertex.w
    );
	
    vec4 position = gl_ModelViewProjectionMatrix * twistedCoord;
    // Transform twisted coordinate
    gl_Position = position;
    gl_FrontColor = (position + vec4(1.0)) * 0.5;
}
