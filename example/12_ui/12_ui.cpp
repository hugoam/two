#include <infra/Cpp20.h>
import two.frame;

#include <12_ui/12_ui.h>
#include <01_shapes/01_shapes.h>
#include <03_materials/03_materials.h>

using namespace two;

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

	void character_sheet(Widget parent, Character& character)
	{
		Widget modal = ui::modal(key(), parent);
		//Widget sheet = ui::sheet(key(), modal);
		Widget sheet = ui::widget(key(), modal, game_styles().character_sheet);

		Widget skills = ui::stack(key(), sheet);
		ui::label(key(), skills, "Skills");
		for(Skill& skill : character.m_skills)
		{
			Widget row = ui::row(key(), skills);
			ui::label(key(), row, skill.m_name.c_str());
			ui::label(key(), row, to_string(skill.m_level).c_str());
		}

		Widget traits = ui::stack(key(), sheet);
		ui::label(key(), traits, "Traits");
		for(Trait& trait : character.m_traits)
		{
			Widget row = ui::row(key(), traits);
			ui::label(key(), row, trait.m_name.c_str());
			ui::label(key(), row, to_string(trait.m_value).c_str());
		}

		//if(!modal.open())
		//	parent.close();
	}

	void inventory_sheet(Widget parent, Inventory& inventory)
	{
		Widget modal = ui::modal(key(), parent);
		//Widget sheet = ui::sheet(key(), modal);
		Widget sheet = ui::widget(key(), modal, game_styles().inventory_sheet);
		ui::label(key(), sheet, "Inventory");

		//for(Item* slot : inventory.m_slots)
		for(size_t y = 0; y < 2; ++y)
		{
			Widget row = ui::row(key(), sheet);

			for(size_t x = 0; x < 10; ++x)
			{
				Item* slot = inventory.m_slots[x + y * 10];

				Widget slot_widget = ui::item(key(), row, game_styles().inventory_slot, "(inventory_slot)");
				if(slot)
					ui::icon(key(), slot_widget, ("(" + string(slot->m_name) + ")").c_str());
			}
		}

		//if(!modal.open())
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

void edit_styles(Widget parent)
{
	static std::vector<Style*> styles = { &game::game_styles().character_sheet, &game::game_styles().inventory_sheet, &game::game_styles().inventory_slot };
	static std::vector<cstring> style_names = { "Character Sheet", "Inventory Sheet", "Inventory Slot" };

	Widget layout = ui::layout_span(key(), parent, 0.3f);
	ScrollSheet scroll_sheet = ui::scroll_sheet(key(), layout);
	Widget self = ui::sheet(key(), scroll_sheet.body);

	static uint32_t selected_style = 0;
	ui::dropdown_input(key(), self, style_names, selected_style);

	Style* edited_style = styles[selected_style];
	object_edit(parent, Ref(&edited_style->layout()));
	object_edit(parent, Ref(&edited_style->skin()));
}

void ex_12_ui(Shell& app, Widget parent, DockbarHandle dockbar)
{
	enum Modes
	{
		Context = 1 << 0,
		Character = 1 << 1,
		Inventory = 1 << 2
	};

	UNUSED(app); UNUSED(dockbar);
	Widget umain = ui::board(key(), parent);

	SceneViewerHandle viewer = ui::scene_viewer(key(), umain);
	ui::orbit_controller(viewer);

	edit_styles(umain);

	Gnode scene = viewer->m_scene->begin();

	Material& material = milky_white(viewer->m_gfx_system);

	gfx::direct_light_node(scene);
	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::None);

	gfx::shape(scene, Cube(), Symbol(), ItemFlag::Default | ItemFlag::Selectable, &material);

	static game::Character character = game::create_character();

	static ItemHandle selected;
	if(MouseEvent mouse_event = viewer.self().mouse_event(DeviceType::MouseRight, EventType::Stroked))
	{
		auto callback = [&](ItemHandle item) { selected = item; umain.data().m_switch |= Context; };
		viewer->picker(0).pick_point(viewer->m_viewport, mouse_event.m_relative, callback, ItemFlag::Default | ItemFlag::Selectable);
	}

	UNUSED(selected);

	if((umain.data().m_switch & Context) != 0)
	{
		Widget popup = ui::popup(key(), viewer.self(), ui::PopupFlags::Modal);
		if(ui::button(key(), popup, "character").activated())
			umain.data().m_switch |= Character;
		if(ui::button(key(), popup, "inventory").activated())
			umain.data().m_switch |= Inventory;
		if((umain.data().m_switch & Character) != 0
			|| (umain.data().m_switch & Inventory) != 0
			|| !popup.open())
			umain.data().m_switch &= ~(Context);
	}

	if((umain.data().m_switch & Character) != 0)
		game::character_sheet(umain, character);

	if((umain.data().m_switch & Inventory) != 0)
		game::inventory_sheet(umain, character.m_inventory);
}

#ifdef _12_UI_EXE
void pump(Shell& app)
{
	shell_context(app.m_ui->begin(), app.m_editor);
	ex_12_ui(app, *app.m_editor.m_screen, app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(cstrarray(TWO_RESOURCE_PATH), argc, argv);
	System::instance().load_modules({ &mud_ui::m() });
	app.m_gfx_system.init_pipeline(pipeline_minimal);
	app.run(pump);
}
#endif
