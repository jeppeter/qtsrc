#version 150 core

// TODO: Replace with a struct
uniform vec3 kd;            // Diffuse reflectivity
uniform vec3 ks;            // Specular reflectivity
uniform vec3 kblue;         // Cool color
uniform vec3 kyellow;       // Warm color
uniform float alpha;        // Fraction of diffuse added to kblue
uniform float beta;         // Fraction of diffuse added to kyellow
uniform float shininess;    // Specular shininess factor

uniform vec3 eyePosition;

in vec3 worldPosition;
in vec3 worldNormal;

out vec4 fragColor;

#pragma include light.inc.frag

vec3 goochModel( const in vec3 pos, const in vec3 n )
{
    // Based upon the original Gooch lighting model paper at:
    // http://www.cs.northwestern.edu/~ago820/SIG98/abstract.html

    // Calculate kcool and kwarm from equation (3)
    vec3 kcool = clamp(kblue + alpha * kd, 0.0, 1.0);
    vec3 kwarm = clamp(kyellow + beta * kd, 0.0, 1.0);

    vec3 result = vec3(0.0);
    int i;
    for (i = 0; i < lightCount; ++i) {
        // Calculate the vector from the light to the fragment
        vec3 s = normalize( vec3( lights[i].position ) - pos );

        // Calculate the cos theta factor mapped onto the range [0,1]
        float sDotNFactor = ( 1.0 + dot( s, n ) ) / 2.0;

        // Calculate the tone by blending the kcool and kwarm contributions
        // as per equation (2)
        vec3 intensity = mix( kcool, kwarm, sDotNFactor );

        // Calculate the vector from the fragment to the eye position
        vec3 v = normalize( eyePosition - pos );

        // Reflect the light beam using the normal at this fragment
        vec3 r = reflect( -s, n );

        // Calculate the specular component
        float specular = 0.0;
        if ( dot( s, n ) > 0.0 )
            specular = pow( max( dot( r, v ), 0.0 ), shininess );

        // Sum the blended tone and specular highlight
        result += intensity + ks * specular;
    }

    return result;
}

void main()
{
    fragColor = vec4( goochModel( worldPosition, normalize( worldNormal ) ), 1.0 );
}
