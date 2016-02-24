#version 120

varying vec3 normal0;
uniform vec3 lightVector;

void main()
{
	float angle = acos(dot(normal0, lightVector));
	if (angle < 0.523599)
		gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
	else if (angle < 1.5708)
		gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);
	else
		gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	//gl_FragColor = vec4(mod(dot(normal0, lightVector), 1.0f) , 0.0, 0.0, 1.0);
}
