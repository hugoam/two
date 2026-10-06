//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Handles.h>
#include <gfx/Graph.h>
#include <gfx/Scene.h>
#include <gfx/Node3.h>
#include <gfx/Item.h>
#include <gfx/Light.h>
#include <gfx/Animated.h>
#include <gfx/Particles.h>

namespace two
{
	GnodeHandle::GnodeHandle(Gnode node) : m_graph(node.m_graph), m_handle(node ? node.m_graph->handle(node.m_index) : 0) {}

	Gnode GnodeHandle::get() const { return m_graph ? m_graph->resolve(m_handle) : Gnode(); }
	Gnode GnodeHandle::gnode() const { return this->get(); }
	GnodeHandle::operator Gnode() const { return this->get(); }
	Gnode GnodeHandle::operator->() const { return this->get(); }
	Gnode GnodeHandle::operator*() const { return this->get(); }
	GnodeHandle::operator bool() const { return bool(this->get()); }

	Node3Handle::Node3Handle(Gnode self) : GnodeHandle(self) {}
	Gnode Node3Handle::self() const { return this->get(); }
	Node3& Node3Handle::node() const { return *this->get().find_state<Node3>(); }
	Node3* Node3Handle::operator->() const { return &this->node(); }
	Node3& Node3Handle::operator*() const { return this->node(); }

	ItemHandle::ItemHandle(Gnode self) : GnodeHandle(self) {}
	ItemHandle::ItemHandle(Scene& scene, ItemIndex index) : GnodeHandle(scene.node(scene.store<Item>().node(index))) {}
	Gnode ItemHandle::self() const { return this->get(); }
	Item& ItemHandle::item() const { return *this->get().find_state<Item>(); }
	Item* ItemHandle::operator->() const { return &this->item(); }
	Item& ItemHandle::operator*() const { return this->item(); }

	BatchHandle::BatchHandle(Gnode self) : GnodeHandle(self) {}
	Gnode BatchHandle::self() const { return this->get(); }
	Batch& BatchHandle::batch() const { return *this->get().find_state<Batch>(); }
	Batch* BatchHandle::operator->() const { return &this->batch(); }
	Batch& BatchHandle::operator*() const { return this->batch(); }

	LightHandle::LightHandle(Gnode self) : GnodeHandle(self) {}
	LightHandle::LightHandle(Scene& scene, LightIndex index) : GnodeHandle(scene.node(scene.store<Light>().node(index))) {}
	Gnode LightHandle::self() const { return this->get(); }
	Light& LightHandle::light() const { return *this->get().find_state<Light>(); }
	Light* LightHandle::operator->() const { return &this->light(); }
	Light& LightHandle::operator*() const { return this->light(); }

	MimeHandle::MimeHandle(Gnode self) : GnodeHandle(self) {}
	Gnode MimeHandle::self() const { return this->get(); }
	Mime& MimeHandle::mime() const { return *this->get().find_state<Mime>(); }
	Mime* MimeHandle::operator->() const { return &this->mime(); }
	Mime& MimeHandle::operator*() const { return this->mime(); }

	FlareHandle::FlareHandle(Gnode self) : GnodeHandle(self) {}
	Gnode FlareHandle::self() const { return this->get(); }
	Flare& FlareHandle::flare() const { return *this->get().find_state<Flare>(); }
	Flare* FlareHandle::operator->() const { return &this->flare(); }
	Flare& FlareHandle::operator*() const { return this->flare(); }
}
