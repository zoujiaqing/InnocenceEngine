#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec4 thefrag_WorldSpacePos;
layout(location = 1) in vec4 thefrag_ClipSpacePos_current;
layout(location = 2) in vec4 thefrag_ClipSpacePos_previous;
layout(location = 3) in vec2 thefrag_TexCoord;
layout(location = 4) in vec3 thefrag_Normal;
layout(location = 5) in float thefrag_UUID;

layout(location = 0) out vec4 opaquePassRT0;
layout(location = 1) out vec4 opaquePassRT1;
layout(location = 2) out vec4 opaquePassRT2;
layout(location = 3) out vec4 opaquePassRT3;

void main() {
	opaquePassRT0 = vec4(thefrag_WorldSpacePos.xyz, 1.0);
	opaquePassRT1 = vec4(thefrag_Normal.xyz, 1.0);
	opaquePassRT2 = vec4(thefrag_Normal.xyz, 1.0);
	vec4 motionVec = (thefrag_ClipSpacePos_current / thefrag_ClipSpacePos_current.w - thefrag_ClipSpacePos_previous / thefrag_ClipSpacePos_previous.w);
	opaquePassRT3 = vec4(motionVec.xy * 0.5, thefrag_UUID, 1.0);
}
