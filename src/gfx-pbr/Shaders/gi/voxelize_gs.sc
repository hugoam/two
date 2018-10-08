$input v_view, v_position, v_normal, v_tangent, v_color, v_texcoord0/*, v_texcoord1*/, v_binormal
//    geom.ins = vert.outs
$output v_voxposition, v_wnormal, v_vcolor, v_texcoord0

void main()
{
    vec3 p1 = voxpositionGeom[1] - voxpositionGeom[0];
    vec3 p2 = voxpositionGeom[2] - voxpositionGeom[0];
    vec3 p = abs(cross(p1, p2));
    for (uint i = 0; i < 3; ++i) {
        v_voxposition = voxpositionGeom[i];
        v_wnormal = wnormalGeom[i];
        v_vcolor = vcolorGeom[i];
        v_texCoord = texCoordGeom[i];
        if (p.z > p.x && p.z > p.y) {
            gl_Position = vec4(voxposition.x, voxposition.y, 0.0, 1.0);
        }
        else if (p.x > p.y && p.x > p.z) {
            gl_Position = vec4(voxposition.y, voxposition.z, 0.0, 1.0);
        }
        else {
            gl_Position = vec4(voxposition.x, voxposition.z, 0.0, 1.0);
        }
        EmitVertex();
    }
    EndPrimitive();
}
