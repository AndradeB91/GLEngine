#version 330

in vec4 vCol;
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;
in vec4 directionalLightSpacePos;

out vec4 colour;

const int MAX_POINT_LIGHTS = 8;
const int MAX_SPOT_LIGHTS = 8;

struct Light 
{
    vec3 colour;
    float ambientIntensity;
    float diffuseIntensity;
};

struct DirectionalLight 
{
    Light base;
    vec3 direction;
};

struct PointLight 
{
    Light base;
    vec3 position;
    float constant;
    float linear;
    float exponent;
};

struct SpotLight
{
    PointLight base;
    vec3 direction;
    float edge;
};

struct Material 
{
    float specularIntensity;
    float shininess;
};

uniform int pointLightsCount;
uniform int spotLightsCount;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform sampler2D theTexture;
uniform sampler2D directionalShadowMap;

uniform Material material;

uniform vec3 eyePosition;

float calcDirectionalShadowFactor(DirectionalLight light) 
{
    vec3 projCoords = directionalLightSpacePos.xyz / directionalLightSpacePos.w;
    projCoords = (projCoords * 0.5) + 0.5;

    float current = projCoords.z;

    vec3 _normal = normalize(normal);
	vec3 lightDir = normalize(light.direction);

    float bias = max(0.003 * (1.0 - dot(_normal, lightDir)), 0.00003);

    float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(directionalShadowMap, 0);

    int shadowSamples = 4;
    int totalSamples = (2 * shadowSamples + 1) * (2 * shadowSamples + 1);
    float shadowContribution = 1.0 / totalSamples;
    
	for(int x = -shadowSamples; x <= shadowSamples; ++x)
	{
		for(int y = -shadowSamples; y <= shadowSamples; ++y)
		{
			float pcfDepth = texture(directionalShadowMap, projCoords.xy + vec2(x,y) * texelSize).r;
			shadow += current - bias > pcfDepth ? shadowContribution : 0.0;
		}
	}
	
	if(projCoords.z > 1.0)
	{
		shadow = 0.0;
	}									
	
	return shadow;
}

vec4 calcLightByDirection(Light light, vec3 direction, float shadowFactor)
{
    vec4 ambientColour = vec4(light.colour, 1.0f) * light.ambientIntensity;

    float diffuseFactor = max(dot(normalize(normal), normalize(direction)), 0.0f);
    vec4 diffuseColour = vec4(light.colour, 1.0f) * light.diffuseIntensity * diffuseFactor;

    vec4 specularColour = vec4(0, 0, 0, 0);

    if(diffuseFactor > 0.0f)
    {
        vec3 fragToEye = normalize(eyePosition - fragPos);
        vec3 reflectedVector = normalize(reflect(direction, normalize(normal)));

        float specularFactor = dot(fragToEye, reflectedVector);

        if(specularFactor > 0.0f)
        {
            specularFactor = pow(specularFactor, material.shininess);
            specularColour = vec4(light.colour * material.specularIntensity * specularFactor, 1.0f);
        }
    }

	return (ambientColour + (1.0 - shadowFactor) * (diffuseColour + specularColour));
}

vec4 calcDirectionalLight()
{
    float shadowFactor = calcDirectionalShadowFactor(directionalLight);
    return calcLightByDirection(directionalLight.base, directionalLight.direction, shadowFactor);
}

vec4 calcPointLight(PointLight pointLight)
{
    vec3 direction = fragPos - pointLight.position;

    float distance = length(direction);
    direction = normalize(direction);

    vec4 colour = calcLightByDirection(pointLight.base, direction, 0.0f);

    float attenuation = pointLight.exponent * distance * distance +
                        pointLight.linear * distance +
                        pointLight.constant;

    return (colour / attenuation);
}

vec4 calcSpotLight(SpotLight spotLight)
{
    vec3 rayDirection = normalize(fragPos - spotLight.base.position);
    float spotLightFactor = dot(rayDirection, spotLight.direction);

    if(spotLightFactor > spotLight.edge) 
    {
        vec4 colour = calcPointLight(spotLight.base);

        return colour * (1.0f - (1.0f - spotLightFactor)*(1.0f/(1.0f - spotLight.edge)));
    } 
    else 
    {
        return vec4(0, 0, 0, 0);
    }
}

vec4 calcPointLights()
{
    vec4 totalColour = vec4(0, 0, 0, 0);

    for(int i = 0; i < pointLightsCount; i++)
    {
        totalColour += calcPointLight(pointLights[i]);
    }

    return totalColour;
}

vec4 calcSpotLights() 
{
    vec4 totalColour = vec4(0, 0, 0, 0);

    for(int i = 0; i < spotLightsCount; i++)
    {
        totalColour += calcSpotLight(spotLights[i]);
    }

    return totalColour;  
}

void main() 
{
    vec4 finalColour = calcDirectionalLight() + 
                       calcPointLights() + 
                       calcSpotLights();

    colour = texture(theTexture, texCoord) * finalColour;
}
