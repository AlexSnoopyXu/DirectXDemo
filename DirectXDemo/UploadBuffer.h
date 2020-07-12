#pragma once

#include "../Common/DirectXHelper.h"
#include "../Common/d3dx12.h"

template<class T>
class UploadBuffer
{
private:
	Microsoft::WRL::ComPtr<ID3D12Resource> mUploadBuffer;
	BYTE* mMappedData = nullptr;

	UINT mElementByteSize = 0;
	bool mIsConstantBuffer = false;

public:
	UploadBuffer(ID3D12Device* device, UINT elementCount, bool isConstantBuffer) : mIsConstantBuffer(isConstantBuffer)
	{
		mElementByteSize = sizeof(T);
		if (isConstantBuffer)
		{
			// 常量缓冲区大小必须为256b的整数倍
			mElementByteSize = (mElementByteSize + 255) & ~255;
		}

		// 创建上传堆
		ThrowIfFailed(device->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(elementCount * mElementByteSize),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr, IID_PPV_ARGS(&UploadBuffer)
		));

		// 复制数据
		D3D12_RANGE range(0, 0);
		ThrowIfFailed(mUploadBuffer->Map(0, &range, reinterpret_cast<void**>(&mMappedData)));
	}

	UploadBuffer(const UploadBuffer& rhs) = delete;
	UploadBuffer& operator= (const UploadBuffer& rhs) = delete;
	~UploadBuffer()
	{
		if (mUploadBuffer != nullptr) {
			mUploadBuffer->Unmap(0, nullptr);
		}

		mMappedData = nullptr;
	}

	ID3D12Resource* Recource()const
	{
		return mUploadBuffer.Get();
	}

	void CopyData(int elementIndex, const T& data)
	{
		memset(&mMappedData[elementIndex * mElementByteSize], &data, sizeof(T));
	}
};