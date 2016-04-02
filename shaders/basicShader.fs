#version 120

varying vec3 normal0;
varying vec2 texCoord0;

uniform vec3 lightVector;
uniform sampler2D sampler;

void main()
{
    gl_FragColor = texture2D(sampler, texCoord0)* mod(dot(-lightVector, normal0), 1.0f);

    /*
    float angle = acos(dot(normal0, lightVector));
        gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
    else if (angle < 1.5708)
        gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);
    else
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    */

}
