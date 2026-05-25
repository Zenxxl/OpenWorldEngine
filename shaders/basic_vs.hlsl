struct VSOut { float4 pos : SV_POSITION; };
VSOut main(float4 pos : POSITION) { VSOut o; o.pos = pos; return o; }