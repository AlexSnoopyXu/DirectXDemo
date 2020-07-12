// 存储用于构成几何图形的三个基本列优先矩阵的常量缓冲区。
//cbuffer ModelViewProjectionConstantBuffer : register(b0)
//{
//	matrix model;
//	matrix view;
//	matrix projection;
//	float2 timer;
//};

// 通过像素着色器传递的每个像素的颜色数据。
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float3 color : COLOR0;
};

// (内插)颜色数据的传递函数。
float4 main(PixelShaderInput input) : SV_TARGET
{
	// clip(input.color - 0.5f);

	/*const float pi = 3.1415926;
	float s = 0.5f * sin(2 * timer.x - 0.25f * pi) + 0.5f;
	float3 c = lerp(input.color, 0.5f, s);
	return float4(c, 1.0f);*/

	return float4(input.color, 1.0f);
}
