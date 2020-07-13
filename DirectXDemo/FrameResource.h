#pragma once

#include "../Common/DirectXHelper.h"
#include "../pch.h"
#include "UploadBuffer.h"

struct FrameResource
{
public:
	FrameResource(ID3D12Device* device, UINT passCount, UINT objectCount);
	FrameResource(const FrameResource& rhs) = delete;
	FrameResource& operator=(const FrameResource& rhs) = delete;
	~FrameResource();

	// ÿ֡�����Լ������������
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdListAlloc;
};

FrameResource::FrameResource(ID3D12Device* device, UINT passCount, UINT objectCount) {

}

FrameResource::~FrameResource(){}