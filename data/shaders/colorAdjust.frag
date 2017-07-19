uniform float gameGamma;
uniform float gameSaturation;
uniform float gameHue;
uniform float gameBrightness;
uniform float gameContrast;

uniform sampler2D Tex0;
varying vec2 TexCoord;


vec3 rgb2hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}


void main(void)
{

	vec4 finalColor = texture2D(Tex0,TexCoord);

	if(finalColor.r>0.15||finalColor.g>0.15||finalColor.b>0.15)finalColor = pow(finalColor, vec4(1.0/gameGamma));

	vec3 luminanceCoefficient = vec3(0.2125, 0.7154, 0.0721);
	vec3 averageLuminance = vec3(0.5, 0.5, 0.5);
	vec3 brightnessAdjustedColor = finalColor.rgb * gameBrightness;
	vec3 intensity = vec3(dot(brightnessAdjustedColor, luminanceCoefficient));
	vec3 saturationAdjustedColor = mix(intensity, brightnessAdjustedColor, gameSaturation);
	vec3 contrastAdjustedColor = mix(averageLuminance, saturationAdjustedColor, gameContrast);
	
	vec3 hsv = rgb2hsv(contrastAdjustedColor);
	hsv.x *= min(gameHue,1.0);
	
	finalColor.rgb = hsv2rgb(hsv);

	gl_FragColor = finalColor;

}
