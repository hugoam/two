#ifdef ALPHA_MAP
    float alpha = matalpha.alpha * texture2D(s_alpha, uv).r;
#else
    float alpha = matalpha.alpha;
#endif
