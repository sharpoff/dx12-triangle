//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

#pragma once

#include "DXSample.h"

using namespace DirectX;

// Note that while ComPtr is used to manage the lifetime of resources on the CPU,
// it has no understanding of the lifetime of resources on the GPU. Apps must account
// for the GPU lifetime of resources to avoid destroying objects that may still be
// referenced by the GPU.
// An example of this can be found in the class method: OnDestroy().
using Microsoft::WRL::ComPtr;

class D3D12HelloTriangle : public DXSample
{
public:
    D3D12HelloTriangle(UINT width, UINT height, std::wstring name);

    virtual void OnInit();
    virtual void OnUpdate();
    virtual void OnRender();
    virtual void OnDestroy();

private:
    static const UINT FrameCount = 2;

    struct Vertex
    {
        XMFLOAT3 position;
        XMFLOAT4 color;
    };

    struct ConstantBufferData
    {
        float time;
    };

    // Pipeline objects.
    D3D12_VIEWPORT m_viewport = {};
    D3D12_RECT m_scissorRect = {};
    ComPtr<IDXGISwapChain3> m_swapChain = nullptr;
    ComPtr<ID3D12Device> m_device = nullptr;
    ComPtr<ID3D12Resource> m_renderTargets[FrameCount] = {};
    ComPtr<ID3D12CommandAllocator> m_commandAllocator = nullptr;
    ComPtr<ID3D12CommandQueue> m_commandQueue = nullptr;
    ComPtr<ID3D12RootSignature> m_rootSignature = nullptr;
    ComPtr<ID3D12DescriptorHeap> m_rtvHeap = nullptr;
    ComPtr<ID3D12DescriptorHeap> m_cbvHeap;
    ComPtr<ID3D12PipelineState> m_pipelineState = nullptr;
    ComPtr<ID3D12GraphicsCommandList> m_commandList = nullptr;
    UINT m_rtvDescriptorSize = 0;

    // App resources.
    ComPtr<ID3D12Resource> m_vertexBuffer = nullptr;
    D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView = {};
    ComPtr<ID3D12Resource> m_constantBuffer;
    ConstantBufferData m_constantBufferData;
    UINT8* m_pCbvDataBegin;

    // Synchronization objects.
    UINT m_frameIndex = 0;
    HANDLE m_fenceEvent = INVALID_HANDLE_VALUE;
    ComPtr<ID3D12Fence> m_fence = nullptr;
    UINT64 m_fenceValue = 0;

    void LoadPipeline();
    void LoadAssets();
    void PopulateCommandList();
    void WaitForPreviousFrame();
};