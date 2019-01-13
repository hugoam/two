#include <infra/Api.h>
#include <type/Api.h>
#include <emscripten.h>


extern "C" {
	
	// Not using size_t for array indices as the values used by the javascript code are signed.
	void array_bounds_check(const int array_size, const int array_idx) {
		  if (array_idx < 0 || array_idx >= array_size) {
			    EM_ASM({
				      throw 'Array index ' + $0 + ' out of bounds: [0,' + $1 + ')';
				    }, array_idx, array_size);
			  }
	}
	// Index
	mud::Indexer* EMSCRIPTEN_KEEPALIVE Index_indexer_1(mud::Index* self, mud::Type* type) {
		return &self->indexer(*type);
	}
	void EMSCRIPTEN_KEEPALIVE Index___destroy__(mud::Index* self) {
		delete self;
	}
	// Indexer
	mud::Type* EMSCRIPTEN_KEEPALIVE Indexer_get_type(mud::Indexer* self) {
		return &&self->m_type;
	}
	std::vector<mud::Ref>* EMSCRIPTEN_KEEPALIVE Indexer_get_objects(mud::Indexer* self) {
		static std::vector<mud::Ref> temp;
		return (temp = &self->m_objects, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Indexer___destroy__(mud::Indexer* self) {
		delete self;
	}
	// Ref
	void EMSCRIPTEN_KEEPALIVE Ref___destroy__(mud::Ref* self) {
		delete self;
	}
	// Type
	mud::Id EMSCRIPTEN_KEEPALIVE Type_get_id(mud::Type* self) {
		return self->m_id;
	}
	const char* EMSCRIPTEN_KEEPALIVE Type_get_name(mud::Type* self) {
		return self->m_name;
	}
	size_t EMSCRIPTEN_KEEPALIVE Type_get_size(mud::Type* self) {
		return self->m_size;
	}
	mud::Type* EMSCRIPTEN_KEEPALIVE Type_get_base(mud::Type* self) {
		return self->m_base;
	}
	void EMSCRIPTEN_KEEPALIVE Type___destroy__(mud::Type* self) {
		delete self;
	}
	// Var
	void EMSCRIPTEN_KEEPALIVE Var___destroy__(mud::Var* self) {
		delete self;
	}
	
}


