/*******************************************************
*  Fixed.vert Fixed Function Equivalent Vertex Shader  *
*   Automatically Generated by 3Dlabs GLSL ShaderGen   *
*             http://developer.3dlabs.com              *
*******************************************************/

uniform bool uIsPointLightOn;
uniform bool uIsSpotLightOn;
uniform bool uIsDirectionalLightOn;

void main(void)
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

/*
vec4 Ambient;
vec4 Diffuse;
vec4 Specular;

void pointLight(in int i, in vec3 normal, in vec3 eye, in vec3 ecPosition3, in float shininess)
{
   float nDotVP;       // normal . light direction
   float nDotHV;       // normal . light half vector
   float pf;           // power factor
   float attenuation;  // computed attenuation factor
   float d;            // distance from surface to light source
   vec3  VP;           // direction from surface to light position
   vec3  halfVector;   // direction of maximum highlights

   // Compute vector from surface to light position
   VP = vec3 (gl_LightSource[i].position) - ecPosition3;

   // Compute distance between surface and light position
   d = length(VP);

   // Normalize the vector from surface to light position
   VP = normalize(VP);

   // Compute attenuation
   attenuation = 1.0 / (gl_LightSource[i].constantAttenuation +
       gl_LightSource[i].linearAttenuation * d +
       gl_LightSource[i].quadraticAttenuation * d * d);

   halfVector = normalize(VP + eye);

   nDotVP = max(0.0, dot(normal, VP));
   nDotHV = max(0.0, dot(normal, halfVector));

   if (nDotVP == 0.0)
   {
       pf = 0.0;
   }
   else
   {
       pf = pow(nDotHV, shininess);

   }
   Ambient  += gl_LightSource[i].ambient * attenuation;
   Diffuse  += gl_LightSource[i].diffuse * nDotVP * attenuation;
   Specular += gl_LightSource[i].specular * pf * attenuation;
}

void spotLight(in int i, in vec3 normal, in vec3 eye, in vec3 ecPosition3, in float shininess)
{
   float nDotVP;            // normal . light direction
   float nDotHV;            // normal . light half vector
   float pf;                // power factor
   float spotDot;           // cosine of angle between spotlight
   float spotAttenuation;   // spotlight attenuation factor
   float attenuation;       // computed attenuation factor
   float d;                 // distance from surface to light source
   vec3  VP;                // direction from surface to light position
   vec3  halfVector;        // direction of maximum highlights

   // Compute vector from surface to light position
   VP = vec3 (gl_LightSource[i].position) - ecPosition3;

   // Compute distance between surface and light position
   d = length(VP);

   // Normalize the vector from surface to light position
   VP = normalize(VP);

   // Compute attenuation
   attenuation = 1.0 / (gl_LightSource[i].constantAttenuation +
       gl_LightSource[i].linearAttenuation * d +
       gl_LightSource[i].quadraticAttenuation * d * d);

   // See if point on surface is inside cone of illumination
   spotDot = dot(-VP, normalize(gl_LightSource[i].spotDirection));

   if (spotDot < gl_LightSource[i].spotCosCutoff)
   {
       spotAttenuation = 0.0; // light adds no contribution
   }
   else
   {
       spotAttenuation = pow(spotDot, gl_LightSource[i].spotExponent);

   }
   // Combine the spotlight and distance attenuation.
   attenuation *= spotAttenuation;

   halfVector = normalize(VP + eye);

   nDotVP = max(0.0, dot(normal, VP));
   nDotHV = max(0.0, dot(normal, halfVector));

   if (nDotVP == 0.0)
   {
       pf = 0.0;
   }
   else
   {
       pf = pow(nDotHV, shininess);

   }
   Ambient  += gl_LightSource[i].ambient * attenuation;
   Diffuse  += gl_LightSource[i].diffuse * nDotVP * attenuation;
   Specular += gl_LightSource[i].specular * pf * attenuation;

}

void directionalLight(in int i, in vec3 normal, in float shininess)
{
   float nDotVP;         // normal . light direction
   float nDotHV;         // normal . light half vector
   float pf;             // power factor

   nDotVP = max(0.0, dot(normal, normalize(vec3 (gl_LightSource[i].position))));
   nDotHV = max(0.0, dot(normal, vec3 (gl_LightSource[i].halfVector)));

   if (nDotVP == 0.0)
   {
       pf = 0.0;
   }
   else
   {
       pf = pow(nDotHV, shininess);

   }
   Ambient  += gl_LightSource[i].ambient;
   Diffuse  += gl_LightSource[i].diffuse * nDotVP;
   Specular += gl_LightSource[i].specular * pf;
}

float ffog(in float ecDistance)
{
    return(abs(ecDistance));
}

vec3 fnormal(void)
{
    //Compute the normal 
    vec3 normal = gl_NormalMatrix * gl_Normal;
    normal = normalize(normal);
    return normal;
}

void ftexgen(in vec3 normal, in vec4 ecPosition)
{
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_TexCoord[1] = gl_MultiTexCoord1;
    gl_TexCoord[2] = gl_MultiTexCoord2;
}

void computeLightContributions(in vec3 normal, in vec3 ecPosition3, in vec3 eye, in float shininess)
{
	// Clear ambient, diffuse and specular contributions
    Ambient  = vec4(0.0);
    Diffuse  = vec4(0.0);
    Specular = vec4(0.0);
    
    if ( uIsPointLightOn )
		pointLight(0, normal, eye, ecPosition3, shininess);

	if ( uIsSpotLightOn )
		spotLight(1, normal, eye, ecPosition3, shininess);

	if ( uIsDirectionalLightOn )
		directionalLight(2, normal, shininess);
}

void frontLightning(in vec3 normal, in vec3 ecPosition3, in vec3 eye, in float alphaFade)
{
    computeLightContributions(normal, ecPosition3, eye, gl_FrontMaterial.shininess);
    vec4 color = clamp(gl_FrontLightModelProduct.sceneColor +
                       Ambient * gl_FrontMaterial.ambient +
                       Diffuse * gl_FrontMaterial.diffuse,
                       0.0, 1.0);
    
    gl_FrontColor = color;
    gl_FrontColor.a *= alphaFade;
    gl_FrontSecondaryColor = Specular * gl_FrontMaterial.specular;
}

void backLightning(in vec3 normal, in vec3 ecPosition3, in vec3 eye, in float alphaFade)
{
    computeLightContributions(normal, ecPosition3, eye, gl_BackMaterial.shininess);
    vec4 color = clamp(gl_BackLightModelProduct.sceneColor +
		               Ambient * gl_BackMaterial.ambient +
                       Diffuse * gl_BackMaterial.diffuse,
                       0.0, 1.0);
    
    gl_BackColor = color;
    gl_BackColor.a *= alphaFade;
    gl_BackSecondaryColor = Specular * gl_BackMaterial.specular;
}

void light(in vec3 frontNormal, in vec4 ecPosition, in float alphaFade)
{
    vec3 backNormal = -frontNormal;
    vec3 eye = vec3 (0.0, 0.0, 1.0);
    vec3 ecPosition3 = (vec3 (ecPosition)) / ecPosition.w;

	frontLightning(frontNormal, ecPosition3, eye, alphaFade);
	backLightning(backNormal, ecPosition3, eye, alphaFade);
}

void main (void)
{
    vec3  transformedNormal;
    float alphaFade = 1.0;

    // Eye-coordinate position of vertex, needed in various calculations
    vec4 ecPosition = gl_ModelViewMatrix * gl_Vertex;

    // Do fixed functionality vertex transform
    gl_Position = ftransform();
    transformedNormal = fnormal();
    
    light(transformedNormal, ecPosition, alphaFade);
    
    gl_FogFragCoord = ffog(ecPosition.z);
    ftexgen(transformedNormal, ecPosition);
}
*/