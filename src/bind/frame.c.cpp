#include <gfx/Api.h>
#include <gfx-ui/Api.h>
#include <frame/Api.h>

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// Shell
	mud::Type* DECL mud_Shell__type() {
		return &mud::type<mud::Shell>();
	}
	mud::Shell* DECL mud_Shell__construct_1(const char* resource_path) {
		return new mud::Shell(resource_path);
	}
	mud::Shell* DECL mud_Shell__construct_2(const char* resource_path, const char* exec_path) {
		return new mud::Shell(resource_path, exec_path);
	}
	mud::Shell* DECL mud_Shell__construct_3(const char* resource_path, const char* exec_path, bool window) {
		return new mud::Shell(resource_path, exec_path, window);
	}
	void DECL mud_Shell_init_0(mud::Shell* self) {
		self->init();
	}
	void DECL mud_Shell_init_1(mud::Shell* self, bool window) {
		self->init(window);
	}
	mud::ShellWindow* DECL mud_Shell_window_2(mud::Shell* self, const char* name, const mud::uvec2* size) {
		return &self->window(name, *size);
	}
	mud::ShellWindow* DECL mud_Shell_window_3(mud::Shell* self, const char* name, const mud::uvec2* size, bool fullscreen) {
		return &self->window(name, *size, fullscreen);
	}
	bool DECL mud_Shell_begin_frame_0(mud::Shell* self) {
		return self->begin_frame();
	}
	void DECL mud_Shell_end_frame_0(mud::Shell* self) {
		self->end_frame();
	}
	bool DECL mud_Shell_pump_0(mud::Shell* self) {
		return self->pump();
	}
	mud::ShellWindow* DECL mud_Shell_main_window_0(mud::Shell* self) {
		return &self->main_window();
	}
	const char* DECL mud_Shell__get_exec_path(mud::Shell* self) {
		return self->m_exec_path.c_str();
	}
	void DECL mud_Shell__set_exec_path(mud::Shell* self, const char* value) {
		self->m_exec_path = value;
	}
	const char* DECL mud_Shell__get_resource_path(mud::Shell* self) {
		return self->m_resource_path.c_str();
	}
	void DECL mud_Shell__set_resource_path(mud::Shell* self, const char* value) {
		self->m_resource_path = value;
	}
	mud::JobSystem* DECL mud_Shell__get_job_system(mud::Shell* self) {
		return &self->m_job_system;
	}
	mud::GfxSystem* DECL mud_Shell__get_gfx(mud::Shell* self) {
		return &self->m_gfx;
	}
	mud::ShellContext* DECL mud_Shell__get_editor(mud::Shell* self) {
		return &self->m_editor;
	}
	void DECL mud_Shell__set_editor(mud::Shell* self, mud::ShellContext* value) {
		self->m_editor = *value;
	}
	void DECL mud_Shell__destroy(mud::Shell* self) {
		delete self;
	}
	// ShellContext
	mud::Type* DECL mud_ShellContext__type() {
		return &mud::type<mud::ShellContext>();
	}
	mud::ShellContext* DECL mud_ShellContext__construct_0() {
		return new mud::ShellContext();
	}
	mud::Widget* DECL mud_ShellContext__get_screen(mud::ShellContext* self) {
		return self->m_screen;
	}
	void DECL mud_ShellContext__set_screen(mud::ShellContext* self, mud::Widget* value) {
		self->m_screen = value;
	}
	mud::Dockbar* DECL mud_ShellContext__get_dockbar(mud::ShellContext* self) {
		return self->m_dockbar;
	}
	void DECL mud_ShellContext__set_dockbar(mud::ShellContext* self, mud::Dockbar* value) {
		self->m_dockbar = value;
	}
	void DECL mud_ShellContext__destroy(mud::ShellContext* self) {
		delete self;
	}
	// ShellWindow
	mud::Type* DECL mud_ShellWindow__type() {
		return &mud::type<mud::ShellWindow>();
	}
	uint32_t DECL mud_ShellWindow__get_index(mud::ShellWindow* self) {
		return self->m_index;
	}
	void DECL mud_ShellWindow__set_index(mud::ShellWindow* self, uint32_t value) {
		self->m_index = value;
	}
	mud::UiWindow* DECL mud_ShellWindow__get_ui_window(mud::ShellWindow* self) {
		return &self->m_ui_window;
	}
	mud::Ui* DECL mud_ShellWindow__get_ui(mud::ShellWindow* self) {
		return self->m_ui;
	}
	void DECL mud_ShellWindow__set_ui(mud::ShellWindow* self, mud::Ui* value) {
		self->m_ui = value;
	}
	void DECL mud_ShellWindow__destroy(mud::ShellWindow* self) {
		delete self;
	}
	
}


