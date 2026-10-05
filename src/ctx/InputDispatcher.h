//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ctx/Forward.h>
#include <ctx/KeyCode.h>
#include <ctx/InputEvent.h>

namespace two
{
	/*
	The dispatch of the input events by node index

	Before, every node of a tree receiving events (every widget) was a ControlNode, with two virtuals and two members:
	- control_event(event): the node finds the receiver of the event under itself. A widget transforms the event to its own space (the
	  m_relative position of a mouse event), then: if the m_mask of its ModalControl has the device of the event, the receiver is found by its
	  m_modal node; else for a mouse event, by the child pinpointed under the cursor, if there is one other than itself; else it's the widget.
	- receive_event(event): called on the receiver once found. A widget transforms the event to its own space, unless it's consumed already.
	- m_events: the EventBatch of the node in the frame, taken from the dispatcher when the node receives its first event: for each device and
	  event type the last event the node received, and for each key the last keyed event (key events) of each device and event type.
	- m_control: the ModalControl of the node: the node it took its modality from (m_parent), the node it gave it to (m_modal) for the devices
	  of m_mask.
	EventDispatcher::dispatch_event(event, top) took top as the receiver if given, else the result of control_event(event) on the root, then
	called receive_event(event) on the receiver and stored the event in its batch. update(), at the end of the frame, cleared the batches and the
	m_events of their nodes. mouse_event(device, type, modifier, consume) on a node returned a copy of the event of its batch for the device and
	type if its modifiers fit, the stored event consumed by the node if asked; key_event(code, type, modifier) the keyed event of the keyboard
	for the type and code if its modifiers fit. The mouse buttons kept the node they pressed, the events their receiver, consumer and drop
	target, as ControlNode*. The destructor of a widget cleared the node of its batch, gave its modal control up (set_modal(nullptr) if it had a
	modal node, yield_modal() if it was modal) and gave the presses it held back to the root.

	Now there is no ControlNode, a node is a ControlId: its index in the tree of the dispatcher. The dispatcher is the single object of the tree
	(the Ui), it finds the receiver of an event and gives it the event by index:
	- route(event) is control_event(event) on the root, iterated: from the root, each node transforms the event, then the receiver is found by
	  its modal node, or by the child pinpointed, until a node keeps the event.
	- receive(event, receiver) is receive_event(event) on the receiver.
	- the events received in the frame are a single list of (receiver, event), in the order they were received. The last event of the list
	  received by a node for a device and type is the one its batch held for them, and the last one for a key the one its keyed table held:
	  received() looks the list up from its end. update() clears the list, as it cleared the batches.
	- mouse_event / key_event are the widget's, they look the events up with received(), and keep the same modifier and consume logic.
	- the ModalControl of a widget is a state of its node, holding node indices. A widget without one has the default: no parent, no modal
	  node, no mask.
	- a widget going away, in release(), while its states are still there, forgets the events it received (forget()): its index can be reused
	  for a new widget in the same frame, which receives no event, as it had no batch. It gives its modal control up and its presses back to
	  the root, as its destructor did.

	These are strictly equivalent: every event reaches the same receiver, transformed the same, and every query returns the same event, with
	these exceptions, where the old behavior was undefined:
	- a node modal for a device without a modal node (clear_focus() leaves the keyboard in the mask): the old routing called control_event on a
	  null node, the new one ignores the mask.
	- the descendants of a Ui are destroyed in its destructor, while its dispatcher and its devices are still there, instead of in the
	  destructor of its root widget, after them.
	- the old dispatcher had batches for 100 receivers in a frame, the list has no limit.
	*/
	export_ class TWO_CTX_EXPORT EventDispatcher
	{
	public:
		EventDispatcher();
		virtual ~EventDispatcher() {}

		// the node receiving the event, found from the root of the tree
		virtual ControlId route(InputEvent& event) = 0;
		// the receiver is given the event
		virtual void receive(InputEvent& event, ControlId receiver) = 0;

		void update();

		ControlId dispatch_event(InputEvent& event, ControlId top_receiver = {});

		// the last event the node received in this frame, for the device and type, or for the device, type and key
		InputEvent* received(ControlId receiver, DeviceType device, EventType type);
		InputEvent* received(ControlId receiver, DeviceType device, EventType type, int key);

		// the node is going away: the events it received are forgotten
		void forget(ControlId receiver);

		struct Received { ControlId m_receiver; InputEvent* m_event; };
		vector<Received> m_received;
	};
}
