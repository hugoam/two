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
	mud::Shell* DECL mud_Shell_Shell_1(const char* resource_path) {
		return new mud::Shell(resource_path);
	}
	mud::Shell* DECL mud_Shell_Shell_2(const char* resource_path, const char* exec_path) {
		return new mud::Shell(resource_path, exec_path);
	}
	bool DECL mud_Shell_pump_0(mud::Shell* self) {
		return self->pump();
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
	mud::GfxSystem* DECL mud_Shell__get_gfx_system(mud::Shell* self) {
		return &self->m_gfx_system;
	}
	mud::ShellContext* DECL mud_Shell__get_editor(mud::Shell* self) {
		static mud::ShellContext temp;
		return (temp = self->m_editor, &temp);
	}
	void DECL mud_Shell__set_editor(mud::Shell* self, mud::ShellContext* value) {
		self->m_editor = *value;
	}
	mud::Ui* DECL mud_Shell__get_ui(mud::Shell* self) {
		return self->m_ui;
	}
	void DECL mud_Shell__set_ui(mud::Shell* self, mud::Ui* value) {
		self->m_ui = value;
	}
	void DECL mud_Shell__destroy(mud::Shell* self) {
		delete self;
	}
	// ShellContext
	mud::Type* DECL mud_ShellContext__type() {
		return &mud::type<mud::ShellContext>();
	}
	mud::ShellContext* DECL mud_ShellContext_ShellContext_0() {
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
	
}


