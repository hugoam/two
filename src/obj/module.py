name = 'obj'
namespace = 'mud'
preproc_name = 'MUD_OBJ'
subdir = 'obj'
dependencies = ['infra']
basetypes = ['void', 'bool', 'short', 'int', 'long', 'long long', 'float', 'double', 'char', 'unsigned char', 'unsigned short', 'unsigned int', 'unsigned long', 'unsigned long long', 'std::string', 'cstring']
aliases = { 'mud::string' : 'std::string', 'string' : 'std::string', 'mud::cstring' : 'cstring' }
