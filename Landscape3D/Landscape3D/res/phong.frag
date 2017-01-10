#version 130
// GLSL version 130 enabled with OpenGL Core Profile 3.0.
//  - `varying` renamed to `in` for fragment shader

struct LightSource
{
    // (x, y, z, 1) means positioned light.
    // (x, y, z, 0) means directed light.
    vec4 position;
    vec4 diffuse;
    vec4 specular;
};

struct LightFactors
{
    float diffuse;
    float specular;
};

struct Material
{
    vec4 diffuse;
    vec4 specular;
    vec4 emissive;
};

const float SHININESS = 10.0;
const float AMBIENT_DIFFUSE = 0.2;

uniform LightSource light0;
uniform Material material;
uniform sampler2D textureDiffuseMap;
uniform mat4 view;

in vec2 fragTextureUV;
in vec3 fragNormal;
in vec3 fragPosInViewSpace;


LightFactors GetLight0Factors()
{
    vec3 viewDirection = normalize(-fragPosInViewSpace);
	vec3 fixedNormal = normalize(fragNormal);

    // Fix lightDirection for both directed and undirected light sources.
    vec3 delta = light0.position.w * viewDirection;
    vec4 lightPosInViewSpace = view * light0.position;
    vec3 lightDirection = normalize(lightPosInViewSpace.xyz + delta);

    vec3 reflectDirection = normalize(-reflect(lightDirection, fixedNormal));

	vec3 eyeDirection = normalize(-fragPosInViewSpace);

    LightFactors result;
    result.diffuse = max(dot(fixedNormal, viewDirection), AMBIENT_DIFFUSE);
    float base = max(dot(reflectDirection, viewDirection), 0.0);
    result.specular = pow(base, SHININESS);

    result.diffuse = clamp(result.diffuse, 0.0, 1.0);
    result.specular = clamp(result.specular, 0.0, 1.0);

    return result;
}

void main()
{
    LightFactors factors = GetLight0Factors();
       
    vec4 matDiffuse = material.diffuse * texture2D(textureDiffuseMap, fragTextureUV.st);

    vec4 diffuseIntensity = matDiffuse * factors.diffuse * light0.diffuse;
	vec4 specularIntensity = material.specular * factors.specular * light0.specular;

    gl_FragColor = diffuseIntensity + specularIntensity + material.emissive;
}
