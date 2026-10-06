//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Forward.h>

namespace two
{
	// the index of a state in its store, valid for a frame: see TypeIndex
	export_ enum class ItemIndex : uint32_t {};
	export_ enum class LightIndex : uint32_t {};
	export_ enum class MimeIndex : uint32_t {};
	export_ enum class FlareIndex : uint32_t {};

	template <> struct TypeIndex<Item> { using Index = ItemIndex; };
	template <> struct TypeIndex<Light> { using Index = LightIndex; };
	template <> struct TypeIndex<Mime> { using Index = MimeIndex; };
	template <> struct TypeIndex<Flare> { using Index = FlareIndex; };

	// a handle to a gfx node, kept from one frame to the next: the graph of the node, and its node index packed with the generation of the index
	// it resolves to the node while it's there, and to nothing once it's gone, even if another node took its index
	// the bodies are in Handles.hpp, where the nodes and their objects are complete
	export_ struct refl_ struct_ TWO_GFX_EXPORT GnodeHandle
	{
		GnodeHandle() {}
		GnodeHandle(nullptr_t) {}
		inline GnodeHandle(Gnode node);

		PooledGraph<Gnode>* m_graph = nullptr;
		uint32_t m_handle = 0;

		// the node, or null if it's gone
		inline Gnode get() const;

		attr_ inline Gnode gnode() const;

		inline operator Gnode() const;
		inline Gnode operator->() const;
		inline Gnode operator*() const;
		inline explicit operator bool() const;
		bool operator==(const GnodeHandle& other) const { return m_handle == other.m_handle && m_graph == other.m_graph; }
	};

	// a handle to the node of a transform, the transform in its state reached through ->
	export_ struct refl_ struct_ Node3Handle : public GnodeHandle
	{
		Node3Handle() {}
		Node3Handle(nullptr_t) {}
		inline explicit Node3Handle(Gnode self);

		attr_ inline Gnode self() const;
		attr_ inline Node3& node() const;

		inline Node3* operator->() const;
		inline Node3& operator*() const;
	};

	// a handle to the node of an item, the item in its state reached through ->
	export_ struct refl_ struct_ ItemHandle : public GnodeHandle
	{
		ItemHandle() {}
		ItemHandle(nullptr_t) {}
		inline explicit ItemHandle(Gnode self);
		inline ItemHandle(Scene& scene, ItemIndex index);

		attr_ inline Gnode self() const;
		attr_ inline Item& item() const;

		inline Item* operator->() const;
		inline Item& operator*() const;
	};

	// a handle to the node of a batch, the batch in its state reached through ->
	export_ struct refl_ struct_ BatchHandle : public GnodeHandle
	{
		BatchHandle() {}
		BatchHandle(nullptr_t) {}
		inline explicit BatchHandle(Gnode self);

		attr_ inline Gnode self() const;
		attr_ inline Batch& batch() const;

		inline Batch* operator->() const;
		inline Batch& operator*() const;
	};

	// a handle to the node of a light, the light in its state reached through ->
	export_ struct refl_ struct_ LightHandle : public GnodeHandle
	{
		LightHandle() {}
		LightHandle(nullptr_t) {}
		inline explicit LightHandle(Gnode self);
		inline LightHandle(Scene& scene, LightIndex index);

		attr_ inline Gnode self() const;
		attr_ inline Light& light() const;

		inline Light* operator->() const;
		inline Light& operator*() const;
	};

	// a handle to the node of an animated rig, the mime in its state reached through ->
	export_ struct refl_ struct_ MimeHandle : public GnodeHandle
	{
		MimeHandle() {}
		MimeHandle(nullptr_t) {}
		inline explicit MimeHandle(Gnode self);

		attr_ inline Gnode self() const;
		attr_ inline Mime& mime() const;

		inline Mime* operator->() const;
		inline Mime& operator*() const;
	};

	// a handle to the node of a particle emitter, the flare in its state reached through ->
	export_ struct refl_ struct_ FlareHandle : public GnodeHandle
	{
		FlareHandle() {}
		FlareHandle(nullptr_t) {}
		inline explicit FlareHandle(Gnode self);

		attr_ inline Gnode self() const;
		attr_ inline Flare& flare() const;

		inline Flare* operator->() const;
		inline Flare& operator*() const;
	};
}
