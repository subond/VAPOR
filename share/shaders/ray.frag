#version 330 core

#include RayMath.frag

uniform mat4 MVP;
// uniform vec2 resolution;
uniform vec3 cameraPos;
uniform vec3 dataBoundsMin;
uniform vec3 dataBoundsMax;
uniform float LUTMin;
uniform float LUTMax;

uniform sampler3D data;
uniform sampler1D LUT;

in vec2 ST;

out vec4 fragColor;

void main(void)
{
    vec2 screen = ST*2-1;
    vec4 world = inverse(MVP) * vec4(screen, 1, 1);
    world /= world.w;
    vec3 dir = normalize(world.xyz - cameraPos);
    
    vec4 accum = vec4(0);
    float t0, t1;
    
    float random = fract(sin(gl_FragCoord.x * 12.989 + gl_FragCoord.y * 78.233) * 43758.5453) * 0.01 + 1; // fract(sin(gl_FragCoord.x * 12.9898 + gl_FragCoord.y * 78.233) * 43758.5453);
    
    if (IntersectRayBoundingBox(cameraPos, dir, dataBoundsMin, dataBoundsMax, t0, t1)) {
        
        float step = max(((t1-t0)/100.f)*1.01, 0.05);
        for (float t = t1; t > t0; t -= step) {
            vec3 hit = cameraPos + dir * t * random;
            vec3 dataSTR = (hit - dataBoundsMin) / (dataBoundsMax-dataBoundsMin);
            float dataNorm = (texture(data, dataSTR).r - LUTMin) / (LUTMax - LUTMin);
            vec4 color = texture(LUT, dataNorm);
            
            accum = vec4((color.rgb*color.a) + accum.rgb*(1-color.a), accum.a*(1-color.a) + color.a);
        }
        fragColor = accum;
    }
        
    if (accum.a < 0.1)
        discard;
}