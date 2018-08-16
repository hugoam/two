#include <mud/mud.h>
#include <12_ui/12_ui.h>

#include <01_shapes/01_shapes.h>
#include <03_materials/03_materials.h>

using namespace mud;

namespace game
{
	struct Item
	{
		string m_name;
		string m_description;
	};

	struct Trait
	{
		string m_name;
		uint8_t m_value;
	};

	struct Skill
	{
		string m_name;
		uint8_t m_level;
	};

	struct Inventory
	{
		void add_item(Item item, size_t slot) { m_items.push_back(item); m_slots[slot] = &m_items.back(); }
		std::vector<Item> m_items;
		std::vector<Item*> m_slots;
	};

	struct Character
	{
		string m_name;
		std::vector<Trait> m_traits;
		std::vector<Skill> m_skills;
		Inventory m_inventory;
	};

	struct GameStyles
	{
		Style character_sheet = { "CharacterSheet", styles().sheet, {}, {} };
		Style inventory_sheet = { "InventorySheet", styles().sheet, {}, {} };
		Style inventory_slot = { "InventorySlot", styles().item, [](Layout& l) { l.m_size = vec2{ 40.f, 40.f }; },
																 [](InkStyle& l) { l.m_empty = false; l.m_border_width = vec4(1.f); l.m_border_colour = Colour::AlphaGrey; } };
	};

	GameStyles& game_styles() { static GameStyles styles; return styles; }

	void character_sheet(Widget& parent, Character& character)
	{
		Widget& modal = ui::modal(parent);
		//Widget& sheet = ui::sheet(modal);
		Widget& sheet = ui::widget(modal, game_styles().character_sheet);

		Widget& skills = ui::stack(sheet);
		ui::label(skills, "Skills");
		for(Skill& skill : character.m_skills)
		{
			Widget& row = ui::row(skills);
			ui::label(row, skill.m_name.c_str());
			ui::label(row, to_string(skill.m_level).c_str());
		}

		Widget& traits = ui::stack(sheet);
		ui::label(traits, "Traits");
		for(Trait& trait : character.m_traits)
		{
			Widget& row = ui::row(traits);
			ui::label(row, trait.m_name.c_str());
			ui::label(row, to_string(trait.m_value).c_str());
		}

		//if(!modal.m_open)
		//	parent.close();
	}

	void inventory_sheet(Widget& parent, Inventory& inventory)
	{
		Widget& modal = ui::modal(parent);
		//Widget& sheet = ui::sheet(modal);
		Widget& sheet = ui::widget(modal, game_styles().inventory_sheet);
		ui::label(sheet, "Inventory");

		//for(Item* slot : inventory.m_slots)
		for(size_t y = 0; y < 2; ++y)
		{
			Widget& row = ui::row(sheet);

			for(size_t x = 0; x < 10; ++x)
			{
				Item* slot = inventory.m_slots[x + y * 10];

				Widget& slot_widget = ui::item(row, game_styles().inventory_slot, "(inventory_slot)");
				if(slot)
					ui::icon(slot_widget, ("(" + string(slot->m_name) + ")").c_str());
			}
		}

		//if(!modal.m_open)
		//	parent.close();
	}

	Character create_character()
	{
		std::vector<Trait> traits = { { "Force", 7 }, { "Agility", 10 }, { "Charisma", 3 }, { "Blood", 100 } };
		std::vector<Skill> skills = { { "Hacking", 1 }, { "Firearms", 2 } };
		Character character = { "Marc Citrus", traits, skills, {} };
		character.m_inventory.m_slots.resize(20);
		character.m_inventory.m_items.reserve(20);
		character.m_inventory.add_item({ "Gun", "" }, 1);
		character.m_inventory.add_item({ "Bandages", "" }, 4);
		return character;
	}
}

void edit_styles(Widget& parent)
{
	static std::vector<Style*> styles = { &game::game_styles().character_sheet, &game::game_styles().inventory_sheet, &game::game_styles().inventory_slot };
	static std::vector<cstring> style_names = { "Character Sheet", "Inventory Sheet", "Inventory Slot" };

	Widget& layout = ui::layout_span(parent, 0.3f);
	ScrollSheet& scroll_sheet = ui::scroll_sheet(layout);
	Widget& self = ui::sheet(*scroll_sheet.m_body);

	static size_t selected_style = 0;
	ui::dropdown_input(self, style_names, selected_style);

	Style* edited_style = styles[selected_style];
	object_edit(parent, Ref(&edited_style->layout()));
	object_edit(parent, Ref(&edited_style->skin()));
}

enum InteractionSwitch
{
	CONTEXT_MENU = 1 << 0,
	CHARACTER_SHEET = 1 << 1,
	INVENTORY_SHEET = 1 << 2

};

void ex_12_ui(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app); UNUSED(dockbar);
	Widget& umain = ui::board(parent);

	SceneViewer& viewer = ui::scene_viewer(umain);
	ui::orbit_controller(viewer);

	edit_styles(umain);

	Gnode& scene = viewer.m_scene->begin();

	Material& material = milky_white(viewer.m_gfx_system);

	gfx::directional_light_node(scene);
	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::None);

	gfx::shape(scene, Cube(), Symbol(), ITEM_SELECTABLE, &material);

	static game::Character character = game::create_character();

	static Item* selected = nullptr;
	if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::MouseRight, EventType::Stroked))
	{
		auto callback = [&](Item* item) { selected = item; umain.m_switch |= CONTEXT_MENU; };
		viewer.picker(0).pick_point(viewer.m_viewport, mouse_event.m_relative, callback, ITEM_SELECTABLE);
	}

	UNUSED(selected);

	if((umain.m_switch & CONTEXT_MENU) != 0)
	{
		Widget& popup = ui::popup(viewer, ui::PopupFlags::Modal);
		if(ui::button(popup, "character").activated())
			umain.m_switch |= CHARACTER_SHEET;
		if(ui::button(popup, "inventory").activated())
			umain.m_switch |= INVENTORY_SHEET;
		if((umain.m_switch & CHARACTER_SHEET) != 0
			|| (umain.m_switch & INVENTORY_SHEET) != 0
			|| !popup.m_open)
			umain.m_switch &= ~(CONTEXT_MENU);
	}

	if((umain.m_switch & CHARACTER_SHEET) != 0)
		game::character_sheet(umain, character);

	if((umain.m_switch & INVENTORY_SHEET) != 0)
		game::inventory_sheet(umain, character.m_inventory);
}

#ifdef _12_UI_EXE
void pump(Shell& app)
{
	edit_context(app.m_ui->begin(), app.m_editor, true);
	ex_12_ui(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(cstrarray(MUD_RESOURCE_PATH), argc, argv);
	app.run(pump);
}
#endif
