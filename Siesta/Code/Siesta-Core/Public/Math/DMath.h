#pragma once

#include "DirectXMath.h"
#include "DirectXPackedVector.h"
#include "DirectXColors.h"

namespace Math = DirectX;

using TColor = Math::XMVECTORF32;
using TVector2 = Math::XMFLOAT2;
using TVector3 = Math::XMFLOAT3;
using TVector4 = Math::XMFLOAT4;

using TIntVector2 = Math::XMINT2;
using TIntVector3 = Math::XMINT3;
using TIntVector4 = Math::XMINT4;

using TUIntVector2 = Math::XMUINT2;
using TUIntVector3 = Math::XMUINT3;
using TUIntVector4 = Math::XMUINT4;

using TPackedVector = Math::XMVECTOR;
using TMatrix = Math::XMMATRIX;

namespace MathOps
{
	inline TPackedVector VectorPack(float X)
	{
		return Math::XMVectorSet(X, X, X, X);
	}

	inline TPackedVector VectorPack(TVector2 X)
	{
		return Math::XMLoadFloat2(&X);
	}

	inline TPackedVector VectorPack(TVector3 X)
	{
		return Math::XMLoadFloat3(&X);
	}

	inline TPackedVector VectorPack(TVector4 X)
	{
		return Math::XMLoadFloat4(&X);
	}

	inline TPackedVector VectorPack(TIntVector2 X)
	{
		return Math::XMLoadSInt2(&X);
	}

	inline TPackedVector VectorPack(TIntVector3 X)
	{
		return Math::XMLoadSInt3(&X);
	}

	inline TPackedVector VectorPack(TIntVector4 X)
	{
		return Math::XMLoadSInt4(&X);
	}

	inline TPackedVector VectorPack(uint32 X)
	{
		return Math::XMVectorSetInt(X, X, X, X);
	}

	inline TPackedVector VectorPack(TUIntVector2 X)
	{
		return Math::XMLoadUInt2(&X);
	}

	inline TPackedVector VectorPack(TUIntVector3 X)
	{
		return Math::XMLoadUInt3(&X);
	}

	inline TPackedVector VectorPack(TUIntVector4 X)
	{
		return Math::XMLoadUInt4(&X);
	}

	template <typename T>
	void VectorUnpack(TPackedVector Vector, T& OutVector)
	{
		static_assert(false);
	}

	template <>
	void VectorUnpack(TPackedVector Vector, TVector2& Out)
	{
		Math::XMStoreFloat2(&Out, Vector);
	}

	template <>
	void VectorUnpack(TPackedVector Vector, TVector3& Out)
	{
		Math::XMStoreFloat3(&Out, Vector);
	}

	template <>
	void VectorUnpack(TPackedVector Vector, TVector4& Out)
	{
		Math::XMStoreFloat4(&Out, Vector);
	}

	template <>
	void VectorUnpack(TPackedVector Vector, TIntVector2& Out)
	{
		Math::XMStoreSInt2(&Out, Vector);
	}

	template <>
	void VectorUnpack(TPackedVector Vector, TIntVector3& Out)
	{
		Math::XMStoreSInt3(&Out, Vector);
	}

	template <>
	void VectorUnpack(TPackedVector Vector, TIntVector4& Out)
	{
		Math::XMStoreSInt4(&Out, Vector);
	}

	template <>
	void VectorUnpack(TPackedVector Vector, TUIntVector2& Out)
	{
		Math::XMStoreUInt2(&Out, Vector);
	}

	template <>
	void VectorUnpack(TPackedVector Vector, TUIntVector3& Out)
	{
		Math::XMStoreUInt3(&Out, Vector);
	}

	template <>
	void VectorUnpack(TPackedVector Vector, TUIntVector4& Out)
	{
		Math::XMStoreUInt4(&Out, Vector);
	}
} // namespace MathOps

#define S_VectorPack MathOps::VectorPack
#define S_VectorUnpack MathOps::VectorUnpack