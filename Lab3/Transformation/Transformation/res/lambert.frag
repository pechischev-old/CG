varying vec3 v;

void main(void)
{
    vec3 dir1 = vec3(v.x + 0.05f, v.y, v.z) - v;
	vec3 dir2 = vec3(v.x, v.y + 0.05f, v.z) - v;

	vec3 normal = normalize(cross(dir1, dir2));

    gl_FragColor = gl_FrontLightModelProduct.sceneColor + normal;
}
