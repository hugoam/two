#include <gfx/Api.h>
#include <gfx-ui/Api.h>
#include <frame/Api.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// ShellContext
	two::Type* DECL two_ShellContext__type() {
		return &two::type<two::ShellContext>();
	}
	two::ShellContext* DECL two_ShellContext__construct_0() {
		return new two::ShellContext();
	}
	two::Widget* DECL two_ShellContext__get_screen(two::ShellContext* self) {
		return self->m_screen;
	}
	void DECL two_ShellContext__set_screen(two::ShellContext* self, two::Widget* value) {
		self->m_screen = value;
	}
	two::Dockbar* DECL two_ShellContext__get_dockbar(two::ShellContext* self) {
		return self->m_dockbar;
	}
	void DECL two_ShellContext__set_dockbar(two::ShellContext* self, two::Dockbar* value) {
		self->m_dockbar = value;
	}
	void DECL two_ShellContext__destroy(two::ShellContext* self) {
		delete self;
	}
	// ShellWindow
	two::Type* DECL two_ShellWindow__type() {
		return &two::type<two::ShellWindow>();
	}
	uint32_t DECL two_ShellWindow__get_index(two::ShellWindow* self) {
		return self->m_index;
	}
	void DECL two_ShellWindow__set_index(two::ShellWindow* self, uint32_t value) {
		self->m_index = value;
	}
	two::UiWindow* DECL two_ShellWindow__get_ui_window(two::ShellWindow* self) {
		return &self->m_ui_window;
	}
	two::Ui* DECL two_ShellWindow__get_ui(two::ShellWindow* self) {
		return self->m_ui;
	}
	void DECL two_ShellWindow__set_ui(two::ShellWindow* self, two::Ui* value) {
		self->m_ui = value;
	}
	void DECL two_ShellWindow__destroy(two::ShellWindow* self) {
		delete self;
	}
	// Shell
	two::Type* DECL two_Shell__type() {
		return &two::type<two::Shell>();
	}
	two::Shell* DECL two_Shell__construct_1(const char* resource_path) {
		return new two::Shell(resource_path);
	}
	two::Shell* DECL two_Shell__construct_2(const char* resource_path, const char* exec_path) {
		return new two::Shell(resource_path, exec_path);
	}
	two::Shell* DECL two_Shell__construct_3(const char* resource_path, const char* exec_path, bool window) {
		return new two::Shell(resource_path, exec_path, window);
	}
	void DECL two_Shell_init_0(two::Shell* self) {
		self->init();
	}
	void DECL two_Shell_init_1(two::Shell* self, bool window) {
		self->init(window);
	}
	two::ShellWindow* DECL two_Shell_window_2(two::Shell* self, const char* name, const two::uvec2* size) {
		return &self->window(name, *size);
	}
	two::ShellWindow* DECL two_Shell_window_3(two::Shell* self, const char* name, const two::uvec2* size, bool fullscreen) {
		return &self->window(name, *size, fullscreen);
	}
	void DECL two_Shell_add_file_2(two::Shell* self, const char* path, uchar* data, int data_size) {
		self->add_file(path, { (uint8_t*)data, data_size / (sizeof(uint8_t) / sizeof(uchar)) });
	}
	bool DECL two_Shell_begin_frame_0(two::Shell* self) {
		return self->begin_frame();
	}
	void DECL two_Shell_end_frame_0(two::Shell* self) {
		self->end_frame();
	}
	bool DECL two_Shell_pump_0(two::Shell* self) {
		return self->pump();
	}
	two::ShellWindow* DECL two_Shell_main_window_0(two::Shell* self) {
		return &self->main_window();
	}
	const char* DECL two_Shell__get_exec_path(two::Shell* self) {
		return self->m_exec_path.c_str();
	}
	void DECL two_Shell__set_exec_path(two::Shell* self, const char* value) {
		self->m_exec_path = value;
	}
	const char* DECL two_Shell__get_resource_path(two::Shell* self) {
		return self->m_resource_path.c_str();
	}
	void DECL two_Shell__set_resource_path(two::Shell* self, const char* value) {
		self->m_resource_path = value;
	}
	two::JobSystem* DECL two_Shell__get_job_system(two::Shell* self) {
		return &self->m_job_system;
	}
	two::GfxSystem* DECL two_Shell__get_gfx(two::Shell* self) {
		return &self->m_gfx;
	}
	two::ShellContext* DECL two_Shell__get_editor(two::Shell* self) {
		return &self->m_editor;
	}
	void DECL two_Shell__set_editor(two::Shell* self, two::ShellContext* value) {
		self->m_editor = *value;
	}
	void DECL two_Shell__destroy(two::Shell* self) {
		delete self;
	}
	
}


