uniform sampler2D texture;

float amount = 0.70; // suitable range = 0.00 - 1.00
float power = 0.7; // suitable range = 0.0 - 1.0

void main()
{
  vec3 color = texture2D(texture, gl_TexCoord[0].xy).xyz;
  vec4 sum = vec4(0);
  vec3 bloom;
  
  for(int i= -3 ;i < 3; i++)
  {
    sum += texture2D(texture, gl_TexCoord[0].xy + vec2(-1, i)*0.004) * amount;
    sum += texture2D(texture, gl_TexCoord[0].xy + vec2(0, i)*0.004) * amount;
    sum += texture2D(texture, gl_TexCoord[0].xy + vec2(1, i)*0.004) * amount;
  }
      
  if (color.r < 0.3 && color.g < 0.3 && color.b < 0.3)
  {
    bloom = sum.xyz*sum.xyz*0.012 + color;
  }
  else
  {
    if (color.r < 0.5 && color.g < 0.5 && color.b < 0.5)
      {
         bloom = sum.xyz*sum.xyz*0.009 + color;
      }
    else
      {
        bloom = sum.xyz*sum.xyz*0.0075 + color;
      }
  }

  color = mix(color, bloom, power);
  gl_FragColor.rgb = color;
  
}