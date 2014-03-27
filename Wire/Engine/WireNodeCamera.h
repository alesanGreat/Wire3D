// Wire3D by Roman Rath (antibyte@gmail.com)
// http://wire3d.googlecode.com
// Copyright(c) 2009-2014. All rights reserved.
// 
// The Wire3D source code is supplied under the terms of the LGPL and
// may not be copied or disclosed except in accordance with the terms of
// that agreement.

#pragma once
#ifndef WIRENODECAMERA_H
#define WIRENODECAMERA_H

#include "WireNode.h"
#include "WireColorRGBA.h"

namespace Wire
{

class Camera;

class NodeCamera : public Node
{
	WIRE_DECLARE_RTTI;

public:
	enum ClearFlag
	{
		CF_ALL,
		CF_Z_ONLY,
		CF_NONE,
		SBM_QUANTITY
	};

	// The node's world transformation is used as the camera's transformation.
	// The camera's transformation is only updated if the node's Enabled flag
	// is true.
	//
	// On construction, the node's local transformation is set to the
	// camera's current coordinate system.
	//   local translation       = camera position
	//   local rotation column 0 = camera forward vector
	//   local rotation column 1 = camera up vector
	//   local rotation column 2 = camera right vector
	NodeCamera(Camera* pCamera = NULL);
	virtual ~NodeCamera();

	// When you set the camera, the node's local transformation is set to the
	// camera's current coordinate system as described above. When the node's
	// world transformation is computed, the camera's position and orientation
	// is set to use the node's world transformation.
	void Set(Camera* pCamera);
	inline Camera* Get();
	inline const Camera* Get() const;

	inline void SetEnabled(Bool enabled);
	inline Bool IsEnabled() const;

	inline void SetDepth(Int depth);
	inline Int GetDepth() const;

	inline void SetClearColor(const ColorRGBA& clearColor);
	inline ColorRGBA GetClearColor() const;

	inline void SetClearFlag(ClearFlag clearFlag);
	inline ClearFlag GetClearFlag() const;

	inline void SetSkybox(Node* pSkybox);
	inline Node* GetSkybox() const;

	inline void SetSupportsLensFlare(Bool supportsLensFlare);
	inline Bool SupportsLensFlare() const;

	static void Draw(TArray<NodeCamera*>& rNodeCameras, Spatial* pRoot,
		Culler& rCuller, Renderer* pRenderer);
	static void SortByDepth(TArray<NodeCamera*>& rCameras);

protected:
	// geometric updates
	virtual void UpdateWorldData(Double appTime, Bool updateControllers);

private:
	void CameraToLocalTransform();
	Pointer<Camera> mspCamera;

	NodePtr mspSkybox;
	Int mDepth;
	ColorRGBA mClearColor;
	ClearFlag mClearFlag;
	Bool mEnabled;
	Bool mSupportsLensFlare;
};

typedef Pointer<NodeCamera> NodeCameraPtr;
#include "WireNodeCamera.inl"

}

#endif
