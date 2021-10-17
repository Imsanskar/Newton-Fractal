#version 440 core

#define MAX_ITERATION 500

out vec4 color;

uniform vec2 rectMin;
uniform vec2 rectMax;
uniform float width;
uniform float height;

struct Complex{
	float real, imag;
}; 

// #define magnitude(a) sqrt(a.x * a.x + a.y * a.y)

float magnitude(vec2 v){
	return pow(v.x * v.x + v.y * v.y, 0.5f);
}

#define mulitply(a, b) vec2(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x)
#define divide(a, b) vec2(a.x * b.x + a.y * b.y, - a.x * b.y + a.y * b.x) / (b.x * b.x + b.y * b.y)

vec2 cpow(vec2 v, float e){
	float radius = magnitude(v);
	radius = pow(radius, e);
	float theta = atan(v.y / v.x);
	theta *= e;
	vec2 res;
	res.x = radius * cos(theta);
	res.y = radius * sin(theta);

	return res;
}

vec2 func(vec2 c){
	vec2 res = mulitply(c, c);
	res = mulitply(res, c) - vec2(1.0f, 0.0f);
	return res;
}

vec2 derivative(vec2 c){
	vec2 res = 3 * mulitply(c, c);
	return res;
}


out vec2 z;

uniform vec2 roots[3];
uniform vec3 colors[3];


vec3 newtonFractal(inout vec2 z, inout int iteration){
	iteration = 0;
	while(iteration < MAX_ITERATION){
		z = z - divide(func(z), derivative(z));

		double tolerance = 0.0000000001;

		for(int i = 0; i < 3; i++){
			vec2 diff = z - roots[i];

			//If the current iteration is close enough to a root, color the pixel.
			if (magnitude(diff) < tolerance){
				return colors[i]; //Return the color corresponding to the root
			}
		}

		iteration += 1;
	}

	return vec3(0.3, 0.3, 0.3);	
}



void main(){
	vec2 st = vec2(gl_FragCoord.x / width, gl_FragCoord.y / height);
	float aspectRatio = width / height;
	int iteration = 0;
	z = rectMin + (rectMax - rectMin) * st * vec2(aspectRatio, 1);
	vec3 fractalColor = newtonFractal(z, iteration);
	color = vec4(fractalColor / iteration * 10 , 1.0f);
}