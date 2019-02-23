#ifdef INSTANCING
    mat4 model = mat4_from_vec4(i_data0, i_data1, i_data2, i_data3);
    mat4 modelView = mul(u_view, model);
#else
    mat4 model = u_model[0];
    mat4 modelView = u_modelView;
#endif

#ifdef BILLBOARD
    modelView[0] = vec4(1.0, 0.0, 0.0, modelView[0][3]);
    modelView[1] = vec4(0.0, 1.0, 0.0, modelView[1][3]);
    modelView[2] = vec4(0.0, 0.0, 1.0, modelView[2][3]);
#endif

#ifdef SKELETON
    highp mat4 skeleton = skeleton_matrix(s_skeleton, ivec4(a_indices), a_weight);
	modelView = mul(modelView, skeleton);
#endif

