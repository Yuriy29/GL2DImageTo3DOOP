#version 330

uniform mat4 mWorld;
uniform mat4 mView;
uniform mat4 mProjection;
uniform vec3 vLightPos[5];
uniform vec3 vLightColor[5];

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTex;

smooth out vec3 theColor;
out vec2 texCoord;

out vec3 norm;
out vec3 tolight;

void main()
{
	gl_Position = mProjection * mView * mWorld * vec4(inPosition, 1.0);

    vec3 lightpos = vec3 (1.0, 1.0, 1.0);

    norm = mat3( mWorld ) * inNormal;
    tolight = lightpos - inPosition;

	vec3 color = vec3(1.0, 1.0, 0.7);

	for (int i=0; i<2; i++)
		color+=dot(normalize(inNormal),normalize(vLightPos[i]-inPosition) )*vLightColor[i]*0.5f;
    
	theColor = color;
    texCoord = inTex;
}