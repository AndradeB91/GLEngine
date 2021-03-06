#version 330

flat in vec3 normal;
in vec3 fragPos;
in vec4 vCol;

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

uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform DirectionalLight directionalLight;

uniform sampler2D theTexture;
uniform Material material;
uniform vec3 eyePosition;

uniform vec3 modelColour;

vec4 calcLightByDirection(Light light, vec3 direction)
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

	return (ambientColour + diffuseColour + specularColour);
}

vec4 calcDirectionalLight()
{
    return calcLightByDirection(directionalLight.base, directionalLight.direction);
}

vec4 calcPointLight(PointLight pointLight)
{
    vec3 direction = fragPos - pointLight.position;

    float distance = length(direction);
    direction = normalize(direction);

    vec4 colour = calcLightByDirection(pointLight.base, direction);

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


    colour = vec4(modelColour, 1.0f) * finalColour;
}
