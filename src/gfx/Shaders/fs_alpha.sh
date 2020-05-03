    float alpha = matalpha.alpha;
    if(u_alpha_map)
        alpha *= texture2D(s_alpha, uv).r;
