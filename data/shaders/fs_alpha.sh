#ifdef ALPHA_MAP
    float alpha = texture2D(s_alpha, uv).r;
#else
    float alpha = 1.0;
#endif
