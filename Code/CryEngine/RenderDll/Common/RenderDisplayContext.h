// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include "SwapChain.h"

class CRenderOutput;

//////////////////////////////////////////////////////////////////////////
//! Display Context represent a target rendering context
//////////////////////////////////////////////////////////////////////////
class CRenderDisplayContext
{
	friend class CD3D9Renderer;
	friend class CRenderOutput;
	friend class CRenderView;

public:
	using TexSmartPtr =    _smart_ptr<CTexture>;
	using OutputSmartPtr = std::shared_ptr<CRenderOutput>;

protected:
	// Unique id to identify each context
	uint32                   m_uniqueId;

	// Denotes if context refers to main viewport
	bool                     m_bMainViewport = true;
	// Denotes if input is HDR content
	bool                     m_bHDRRendering = false;
	// Description of the DisplayContext
	IRenderer::SDisplayContextDescription m_desc;

	// Number of samples per output (real offscreen) pixel used in X/Y
	int                      m_nSSSamplesX = 1;
	int                      m_nSSSamplesY = 1;

	// Dimensions of viewport on output to render content into
	uint32_t                 m_DisplayWidth = 0;
	uint32_t                 m_DisplayHeight = 0;

	// Render output for this display context;
	OutputSmartPtr           m_pRenderOutput = nullptr;
	TexSmartPtr              m_pColorTarget = nullptr;
	TexSmartPtr              m_pDepthTarget = nullptr;
	float                    m_aspectRatio = 1.0f;
	int                      m_backbufferCount = 2;

	SRenderViewport          m_viewport;

	bool                     m_bVSync = false;

protected:
	CRenderDisplayContext(IRenderer::SDisplayContextDescription desc, uint32 uniqueId) : m_uniqueId(uniqueId), m_desc(desc)
	{
		m_pRenderOutput = std::make_shared<CRenderOutput>(this);
	}

	CRenderDisplayContext(CRenderDisplayContext &&) = default;
	CRenderDisplayContext &operator=(CRenderDisplayContext &&) = default;

	virtual void         ReleaseResources();

	void                 SetDisplayResolutionAndRecreateTargets(uint32_t displayWidth, uint32_t displayHeight, const SRenderViewport& vp);
	void                 SetVSyncHint(bool enable) { m_bVSync = enable; }

	virtual void         ChangeDisplayResolution(uint32_t displayWidth, uint32_t displayHeight, const SRenderViewport& vp);
	void                 ChangeDisplayResolution(uint32_t displayWidth, uint32_t displayHeight)
	{
		ChangeDisplayResolution(displayWidth, displayHeight, SRenderViewport(0, 0, displayWidth, displayHeight));
	}

public:
	virtual ~CRenderDisplayContext() noexcept {}

	virtual bool         IsSwapChainBacked() const { return false; }

	void                 BeginRendering(bool isHighDynamicRangeEnabled);
	void                 EndRendering();

	virtual void         PrePresent() {}
	virtual void         PostPresent() {}
	virtual CTexture*    GetCurrentBackBuffer() const = 0;
	virtual CTexture*    GetPresentedBackBuffer() const = 0;
	virtual CTexture*    GetStorableColorOutput() = 0;
	int                  GetBackBufferCount()      const { return m_backbufferCount; }
	void                 SetBackBufferCount(int count) { m_backbufferCount = count; }

	uint32_t             GetID() const { return m_uniqueId; }
	OutputSmartPtr       GetRenderOutput() const { return m_pRenderOutput; };
	Vec2_tpl<uint32_t>   GetDisplayResolution() const { return Vec2_tpl<uint32_t>(m_DisplayWidth, m_DisplayHeight); }
	const SRenderViewport& GetViewport() const { return m_viewport; }
	float                GetAspectRatio() const { return m_aspectRatio; }

	bool                 IsMainViewport() const { return m_bMainViewport; }
	bool                 IsMainContext() const { return IsMainViewport(); }
	bool                 IsEditorDisplay() const { return m_uniqueId != 0 || gRenDev->IsEditorMode(); }
	bool                 IsScalable() const { return IsMainViewport() && !IsEditorDisplay(); }
	bool                 IsHighDynamicRange() const { return m_bHDRRendering; /* SHDF_ALLOWHDR */ }
	bool                 IsDeferredShadeable() const { return IsMainViewport(); }
	bool                 IsSuperSamplingEnabled() const { return m_nSSSamplesX * m_nSSSamplesY > 1; }
	bool                 IsNativeScalingEnabled() const { return GetRenderOutput() ? GetDisplayResolution() != GetRenderOutput()->GetOutputResolution() : false; }
	bool                 NeedsDepthStencil() const { return (m_desc.renderFlags & (FRT_OVERLAY_DEPTH | FRT_OVERLAY_STENCIL)) != 0; }
	bool                 GetVSyncHint() const { return m_bVSync; }

	CTexture* GetCurrentColorOutput() const
	{
		if (IsHighDynamicRange())
		{
			CRY_ASSERT(m_pColorTarget);
			return m_pColorTarget.get();
		}

		return GetCurrentBackBuffer();
	}

	CTexture* GetCurrentDepthOutput() const
	{
		CRY_ASSERT(m_pDepthTarget || !NeedsDepthStencil());
		return m_pDepthTarget.get();
	}
	CTexture* GetStorableDepthOutput() const { return GetCurrentDepthOutput(); }

private:
	void AllocateColorTarget();
	void AllocateDepthTarget();
};

using CRenderDisplayContextPtr = std::shared_ptr<CRenderDisplayContext>;


class CSwapChainBackedRenderDisplayContext : public CRenderDisplayContext
{
	friend class CD3D9Renderer;

private:
	// Handle and a pointer to WIN32 window
	HWND                     m_hWnd = 0;

	CSwapChain               m_swapChain;
	DXGIOutput*              m_pOutput = nullptr;

	std::vector<TexSmartPtr> m_backBuffersArray;
	CTexture*                m_pBackBufferPresented = nullptr;
	TexSmartPtr              m_pBackBufferProxy = nullptr;
	bool                     m_bSwapProxy = true;
	bool                     m_fullscreen = false;

private:
	void                 SetHWND(HWND hWnd);
	void                 CreateOutput();
	void                 ShutDown();
	void                 ReleaseResources() override;
#if CRY_PLATFORM_WINDOWS
	void                 EnforceFullscreenPreemption();
#endif
	void                 ChangeOutputIfNecessary(bool isFullscreen);
	void                 ChangeDisplayResolution(uint32_t displayWidth, uint32_t displayHeight, const SRenderViewport& vp) override;
	void                 ChangeDisplayResolution(uint32_t displayWidth, uint32_t displayHeight)
	{
		ChangeDisplayResolution(displayWidth, displayHeight, SRenderViewport(0, 0, displayWidth, displayHeight));
	}

	CSwapChain&          GetSwapChain() { return m_swapChain; }
	const CSwapChain&    GetSwapChain() const { return m_swapChain; }
	void                 SetSwapChain(CSwapChain &&sc) { m_swapChain = std::move(sc); }

public:
	CSwapChainBackedRenderDisplayContext(IRenderer::SDisplayContextDescription desc, uint32 uniqueId) : CRenderDisplayContext(desc, uniqueId) {}
	~CSwapChainBackedRenderDisplayContext() { ShutDown(); }

	CSwapChainBackedRenderDisplayContext(CSwapChainBackedRenderDisplayContext &&) = default;
	CSwapChainBackedRenderDisplayContext &operator=(CSwapChainBackedRenderDisplayContext &&) = default;

	bool                 IsSwapChainBacked() const override final { return true; }

	void                 PrePresent() override;
	void                 PostPresent() override;
	CTexture*            GetCurrentBackBuffer() const override;
	CTexture*            GetPresentedBackBuffer() const override { return m_pBackBufferPresented; }
	CTexture*            GetStorableColorOutput() override;

	HWND                 GetWindowHandle() const { return m_hWnd; }
	//! Gets the resolution of the monitor that this context's window is currently present on
	RectI                GetCurrentMonitorBounds() const;

	void                 SetFullscreenState(bool isFullscreen);
	bool                 IsFullscreen() const { return m_fullscreen; }

#if defined(SUPPORT_DEVICE_INFO)
	uint32               GetRefreshRateNumerator() const { return m_swapChain.GetRefreshRateNumerator(); }
	uint32               GetRefreshRateDemoninator() const { return m_swapChain.GetRefreshRateDemoninator(); }
#endif

private:
	void ReleaseBackBuffers();
	void AllocateBackBuffers();
};


class CCustomRenderDisplayContext : public CRenderDisplayContext
{
private:
	uint32_t                 m_swapChainIndex = 0;
	std::vector<TexSmartPtr> m_backBuffersArray;
	CTexture*                m_pBackBufferPresented = nullptr;
	TexSmartPtr              m_pBackBufferProxy = nullptr;

public:
	// Creates a display context with manual control of the swapchain
	CCustomRenderDisplayContext(IRenderer::SDisplayContextDescription desc, uint32 uniqueId, std::vector<TexSmartPtr> &&backBuffersArray, uint32_t initialSwapChainIndex = 0)
		: CRenderDisplayContext(desc, uniqueId)
		, m_swapChainIndex(initialSwapChainIndex)
	{
		CRY_ASSERT(backBuffersArray.size());
		this->m_backBuffersArray = std::move(backBuffersArray);

		const auto &tex = *this->m_backBuffersArray.begin();
		this->ChangeDisplayResolution(tex->GetWidth(), tex->GetHeight());
	}

	CCustomRenderDisplayContext(CCustomRenderDisplayContext &&) = default;
	CCustomRenderDisplayContext &operator=(CCustomRenderDisplayContext &&) = default;

	void             SetSwapChainIndex(uint32_t index) 
	{
		CRY_ASSERT(index < m_backBuffersArray.size());
		m_swapChainIndex = index;
		m_pRenderOutput->ReinspectDisplayContext();
	}

	void             PrePresent() override;
	CTexture*        GetCurrentBackBuffer() const override { return this->m_backBuffersArray[m_swapChainIndex]; }
	CTexture*        GetPresentedBackBuffer() const override { return m_pBackBufferPresented; }
	CTexture*        GetStorableColorOutput() override;
};
