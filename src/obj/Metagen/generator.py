import sys
import os
import imp
import copy
import itertools
import fnmatch
import clang.cindex
import argparse
from mako.template import Template

def update_file(path, content):
    if not os.path.exists(path):
        with open(path, "w") as f:
            pass
        
    with open(path, "r+") as f:
        current = f.read()
        if current != content:
            f.seek(0)
            f.write(content)
            f.truncate()
                
def first_token(cursor):
    for token in cursor.get_tokens():
        return token.spelling

def get_annotations(node):
    return [c.displayname for c in node.get_children()
            if c.kind == clang.cindex.CursorKind.ANNOTATE_ATTR]

def clean_name(name):
    name.replace('const char*', 'cstring')
    return name.replace(' *', '*').replace(' &', '&').replace('> >', '>>')
    
def type_name(type, template = False):
    return clean_name(type.spelling)
    
def class_name(type, template = False):
    if type.kind.name == 'POINTER' :
        return type_name(type.get_pointee())
    if type.kind.name == 'LVALUEREFERENCE' :
        return type_name(type.get_pointee()).replace('const ', '')
    
    return type_name(type, template)

def unqual_type_name(type, template = False):
    if type.kind.name == 'LVALUEREFERENCE' :
        return type_name(type.get_pointee()).replace('const ', '')
        
    return type_name(type, template)
    
def is_template_decl(cursor):
    has_def = False #len([c for c in cursor.get_children()]) > 0
    for c in cursor.get_children():
        if c.kind == clang.cindex.CursorKind.CXX_BASE_SPECIFIER :
            has_def = True
    return not has_def

def template_name(name):
    return name[0:name.find('<')]
    
def template_types(name):
    return name[name.find('<')+1:-1].split(',')
    
def substitute_template(name, template_types, real_types):
    for template_type, real_type in zip(template_types, real_types):
        name = name.replace(template_type, real_type)
    return name

def register_type(module, parent, clsname):
    for name in ['std::vector', 'std::list'] :
        if clsname.find(name) == 0 :
            content_name = clsname[clsname.find('<')+1:-1]
            content_type = module.find_type(parent, content_name.replace('*', ''))
            if content_type :
                print '>>>>>>>>>>>> register_type Sequence', name, content_type.name, content_name
                cls = Sequence(module, name, content_type, content_name.find('*') > -1, module.root.root_namespace)
                module.root.types[clsname] = cls
                return cls
    for name in ['unique_ptr', 'object_ptr'] :
        if clsname.find(name) > -1 :
            cls = Type(module, clsname)
            return cls

def find_default_value(decl, cls, cursor):
    for l in cursor.get_children():
        if l.kind == clang.cindex.CursorKind.CXX_BOOL_LITERAL_EXPR or l.kind == clang.cindex.CursorKind.FLOATING_LITERAL or l.kind == clang.cindex.CursorKind.INTEGER_LITERAL or l.kind == clang.cindex.CursorKind.STRING_LITERAL:
            decl.has_default = True
            decl.default = first_token(l)
        elif l.kind == clang.cindex.CursorKind.CALL_EXPR or l.kind == clang.cindex.CursorKind.DECL_REF_EXPR or l.kind == clang.cindex.CursorKind.UNEXPOSED_EXPR:
            decl.has_default = True
            
     
class Header(object):
    def __init__(self, path):
        self.path = path
        self.depth = 0
        
    def __cmp__(self, other):
        return self.depth < other.depth
     
class Namespace(object):
    def __init__(self, name, parent):
        self.name = name
        self.id = parent.prefix + name if parent else name
        self.parent = parent
        self.prefix = self.id + '::' if self.id != '' else ''
        self.is_template = False
        self.is_templated = False
           
class Root(object):
    def __init__(self):
        self.root_namespace = Namespace('', None)
        self.namespaces = { '' : self.root_namespace }
        self.types = {}
        self.templates = {}
        self.func_templates = {}
        self.base_types = ['void', 'bool', 'int', 'float', 'double', 'char', 'unsigned char', 'short', 'unsigned short', 'int', 'unsigned int', 'long', 'unsigned long', 'long long', 'unsigned long long', 'std::string', 'cstring']
        self.base_aliases = ['uint8_t', 'uint16_t', 'uint32_t', 'uint64_t', 'size_t', 'mud::Id']
        
    def get_namespace(self, name, parent):
        full_name = parent.prefix + name
        if not full_name  in self.namespaces:
            self.namespaces[full_name] = Namespace(name, parent)
        return self.namespaces[full_name]
        
class Module(object):
    def __init__(self, root, name, namespace, preproc_name, subdir, dependencies, rootdir):
        self.root = root
        self.name = name
        self.id = namespace + name.replace('-', '_')
        self.namespace = namespace
        self.preproc_name = preproc_name
        self.export = preproc_name + '_EXPORT'
        self.subdir = subdir
        self.dependencies = dependencies[:]
        self.rootdir = rootdir
        self.modules = dependencies[:]
        self.modules.append(self)
        self.path = os.path.join(self.rootdir, self.subdir) if self.subdir else self.rootdir
        self.has_structs = False
        self.has_generator = False
        
        self.outputPath = os.path.join(self.path, 'Generated')
    
        self.headers = []
        self.sources = []
        
        self.templates = []
        self.types = []
        self.classes = []
        self.enums = []
        self.sequences = []
        self.basetypes = []
        self.functions = []
        self.func_templates = []
        
        print self.path
        
    def get_namespace(self, name, parent):
        return self.root.get_namespace(name, parent)
        
    def template(self, name):
        return self.root.templates[name]
        
    def find_type_in(self, parent, name, warn = True):
        # stupid fix because clang FUCKING doesn't always put the prefix in types ..............
        if name in self.root.types:
            return self.root.types[name]
        elif parent and parent.prefix + name in self.root.types:
            return self.root.types[parent.prefix + name]
        elif parent and parent.parent:
            return self.find_type_in(parent.parent, name, warn)

    def find_type(self, parent, name, warn = True):
        if name in self.root.base_types or name in self.root.base_aliases:
            return TypeProxy(name)
        cls = self.find_type_in(parent, name, warn)
        if not cls :
            for key, namespace in self.root.namespaces.iteritems():
                cls = self.find_type_in(namespace, name, warn)
                if cls:
                    break
        return cls
            
    def get_type(self, parent, name, warn = True):
        cls = self.find_type(parent, name, warn)
        if not cls :
            cls = register_type(self, parent, name)
        if not cls and warn :
            print 'ERROR: Type', name, 'not found', parent.name if parent else 'None'
        return cls
                
    def type(self, name):
        return self.root.types[name]

class Param(object):
    def __init__(self, func, cursor, index, parent):
        self.func = func
        self.index = index
        self.name = cursor.spelling
        self.type = type_name(cursor.type, parent.is_template or parent.is_templated)
        self.clsname = class_name(cursor.type, parent.is_template or parent.is_templated)
        if type(parent) == Class:
            self.type = parent.fix_template(self.type)
            self.clsname = parent.fix_template(self.clsname)
        
        self.pointer = self.type[-1] == '*'
        self.reference = self.type[-1] == '&' and not self.type.find('const') > -1
        self.const_pointer = self.type[0:5] == 'const' and self.type[-1] == '*'
        self.const_reference = self.type[0:5] == 'const' and self.type[-1] == '&'
        
        self.nullable = self.pointer or self.type == "mud::Ref"
        self.output = self.name[:6] == 'output'
        self.input = not self.output
        
        self.has_default = False
        self.default = ''
         
        if not parent or not parent.is_template:
            self.cls = self.func.module.get_type(parent, self.clsname)
            # fixing type because of FUCKING clang.....................
            self.type = self.cls.id
            if self.pointer:
                self.type = self.type + '*'
            if self.reference:
                self.type = self.type + '&'
            if self.const_pointer:
                self.type = 'const' + self.type + '*'
            if self.const_reference:
                self.type = 'const ' + self.type + '&'
                
        find_default_value(self, self.cls, cursor)
            
    def copy(self, index):
        param = copy.copy(self)
        param.index = index
        return param
        
    def equals(self, param):
        return param.name == self.name and param.type == self.type
        
class Function(object):
    def __init__(self, module, cursor, parent = None):
        self.module = module
        self.parent = parent
        self.name = cursor.spelling
        self.id = parent.id + '::' + self.name if parent else self.name
        self.idstr = self.id.replace('::', '_')
        
        if self.name in module.root.func_templates:
            template_type = clean_name(cursor.displayname[cursor.displayname.find('(')+1:-1].split(',')[0])
            print 'Templated Function', template_type
            self.name += '<' + template_type + '>'
            self.id += '<' + template_type + '>'
            self.idstr += '_' + template_type
            
        self.params = []
        self.returnType = type_name(cursor.result_type)
        self.returnPointer = self.returnType[-1] == '*'
        self.returnClsName = class_name(cursor.result_type)
        self.unqualReturnType = unqual_type_name(cursor.result_type)
        self.is_function = cursor.kind == clang.cindex.CursorKind.FUNCTION_DECL
        self.is_template = cursor.kind == clang.cindex.CursorKind.FUNCTION_TEMPLATE or (parent and parent.is_template)
        
        if self.is_function : 
            print 'Function ', cursor.displayname
            module.functions.append(self)
            
        elif self.is_function and self.is_template : 
            print 'Function Template ', cursor.displayname
            module.func_templates.append(self)
            module.root.func_templates[self.name] = self
            
        if not self.is_template :
            for a in cursor.get_children():
                if a.kind == clang.cindex.CursorKind.PARM_DECL :
                    self.params.append(Param(self, a, len(self.params), parent))
        
            self.signature = self.returnType + '(*)(' + ', '.join([p.type for p in self.params]) + ')'
            
            self.returnCls = self.module.get_type(parent, self.returnClsName)
            
            
            
class Method(Function):
    def __init__(self, parent, cursor):
        Function.__init__(self, parent.module, cursor, parent)
        self.expected_params = self.params
        
class Constructor(Method):
    def __init__(self, parent, cursor):
        Method.__init__(self, parent, cursor)

    def createAggregate(self, constructors, components):
        constructor = copy.copy(self)
        constructor.expected_params = [param.copy(i) for i, param in enumerate([param for constr in components for param in constr.params])]
        constructor.params = [param for param in constructor.expected_params if next((p for p in self.params if p.equals(param)), None)]
        constructor.combined = True
        if len(constructor.params) == len(constructor.expected_params) :
            constructors.append(constructor)
            
class Static(object):
    def __init__(self, parent, cursor):
        self.parent = parent
        self.member = cursor.spelling
        self.name = cursor.spelling.replace('m_', '')
        
class Member(object):
    def __init__(self, parent, cursor):
        self.parent = parent
        member_type = cursor.type
        if cursor.kind == clang.cindex.CursorKind.CXX_METHOD :
            self.function = Method(parent, cursor)
            member_type = cursor.result_type
        elif cursor.kind == clang.cindex.CursorKind.FIELD_DECL :
            self.function = None
            member_type = cursor.type
        
        self.clsname = parent.fix_template(class_name(member_type, parent.is_template or parent.is_templated))
        self.type = parent.fix_template(type_name(member_type, parent.is_template or parent.is_templated))
        
        self.member = cursor.spelling
        self.name = cursor.spelling.replace('m_', '')
        self.capname = self.name[0].capitalize() + self.name[1:]  
        
        self.pointer = self.type[-1] == '*'
        self.reference = self.type[-1] == '&' and not self.type.find('const') > -1
        
        self.annotations = get_annotations(cursor)
        self.mutable = 'mutable_attr' in self.annotations
        self.structure = 'structure_attr' in self.annotations
        self.link = 'link_attr' in self.annotations
        
        self.output = False
        self.input = False
        
        print 'Member', self.name, self.type
        
        if not parent.is_template:
            self.cls = self.parent.module.get_type(parent, self.clsname)
        else:
            self.cls = None
            
        self.setter = self.mutable and self.function
        
        for c in parent.cursor.get_children(): 
            if (c.kind == clang.cindex.CursorKind.CXX_METHOD and c.spelling == 'set' + self.capname) :
               self.setter = True

        self.has_default = False
        self.default = ''

        find_default_value(self, self.cls, cursor)
        
class TypeProxy(object):
    def __init__(self, name):
        self.name = name
        self.id = name
        self.struct = True
        
class Type(object):
    def __init__(self, module, name, parent, is_template = False):
        self.module = module
        self.name = clean_name(name)
        self.id = parent.prefix + self.name
        self.prefix = self.id + '::'
        self.parent = parent
        self.nested = type(parent) == Class
        self.struct = True
        self.isProto = False
        self.is_template = is_template
        self.reflect = True
        self.bases = []
        self.deep_bases = []
        self.aliases = []
        if not is_template:
            module.root.types[self.id] = self
            module.types.append(self)
            print 'Type ', self.id
        else:
            module.templates.append(self)
            print 'Template ', self.id
            
class BaseType(Type):
    def __init__(self, module, name):
        Type.__init__(self, module, name, module.root.root_namespace)
        module.basetypes.append(self)
        
class Enum(Type):
    def __init__(self, module, cursor, parent):
        Type.__init__(self, module, cursor.displayname, parent)
        module.enums.append(self)
        self.ids = [c.displayname for c in cursor.get_children() if c.kind == clang.cindex.CursorKind.ENUM_CONSTANT_DECL]
        self.values = [c.enum_value for c in cursor.get_children() if c.kind == clang.cindex.CursorKind.ENUM_CONSTANT_DECL]
        self.scoped = cursor.is_scoped_enum()
        self.enum_type = cursor.enum_type.spelling
        self.prefix = self.name + '::' if self.scoped else (self.parent.name + '::' if self.parent else '')
        self.scoped_ids = [self.prefix + id for id in self.ids]
        self.reflect = 'reflect' in get_annotations(cursor)

class Sequence(Type):
    def __init__(self, module, store, content_type, pointer, parent):
        Type.__init__(self, module, store + '<' + content_type.id + ('*' if pointer else '') + '>', parent)
        self.store = store
        self.contentcls = content_type
        self.content = content_type.id + ('*' if pointer else '')
        module.sequences.append(self)
        
class Class(Type):
    def __init__(self, module, cursor, parent):
        Type.__init__(self, module, cursor.displayname, parent, cursor.kind == clang.cindex.CursorKind.CLASS_TEMPLATE)
        self.idstr = self.name.replace('<', '').replace('>', '')
        self.annotations = get_annotations(cursor)
        self.constructors = []
        self.members = []
        self.methods = []
        self.statics = []
        self.stem = None
        self.struct = 'struct' in self.annotations or cursor.kind == clang.cindex.CursorKind.STRUCT_DECL
        self.isModular = False
        self.isProto = False
        self.serializable = 'serialize' in self.annotations
        self.parts = []
        self.array = False
        self.template_name = template_name(self.name)
        self.is_templated = self.name.find('<') > -1 and not self.is_template
        self.template = module.root.templates[self.template_name] if self.is_templated else None
        self.template_types = template_types(self.name)
        self.template_used = 'reflect' in get_annotations(cursor)
        self.reflect = 'reflect' in get_annotations(cursor)
        self.extern = 'external' in get_annotations(cursor)
        
        if not self.is_template:
            module.classes.append(self)
        else:
            module.root.templates[self.template_name] = self
            
        #if self.is_templated and is_template_decl(cursor):
        #    self.template.template_used = True
            
    def parse_contents(self, cursor):
        print 'Parsing', self.id
        self.cursor = cursor
        
        if self.is_templated and is_template_decl(cursor):
            cursor = self.template.cursor
            
        for c in cursor.get_children():
            self.parse_child(c)
                    
        if self.isProto:
            self.stem = self.module.type(self.members[0].clsname)

        if self.serializable and not self.constructors :
            print '    ERROR : class ', self.name, ' set to serializable without a constructor'
 
        if self.isProto and self.constructors:
            components = [part.constructors[0] for part in self.parts]
            self.constructors[0].createAggregate(self.constructors, components)
        
            
        if 'array_object' in self.annotations :
            self.array = True
            self.array_size = len(self.members)
            self.array_content = self.members[0].cls
    
    def fix_template_element(self, name):
        if self.template and name in self.template.template_types:
            return self.template_types[self.template.template_types.index(name)]
        else:
            return name
    
    def fix_template(self, name):
        # first fix nested template types
        real_types = [self.fix_template_element(t) for t in template_types(name)]
        name = substitute_template(name, template_types(name), real_types)
        # then fix type itself in case it is a template parameter
        return self.fix_template_element(name)
        #print 'substituted template base name: ', name
    
    def parse_child(self, cursor):
        if cursor.kind == clang.cindex.CursorKind.TEMPLATE_TYPE_PARAMETER:
            self.template_types.append(cursor.spelling)
            
        if cursor.kind == clang.cindex.CursorKind.CXX_BASE_SPECIFIER :
            name = class_name(cursor.type)
            
            if name.find('<') > -1:
                name = self.fix_template(name)
                
            elif name == 'mud::Complex':
                self.isModular = True
            elif name == 'mud::Construct':
                self.isProto = True
            
            base = self.module.get_type(self.parent, name, False)
            if base and base.reflect:
                self.bases.append(base)
                self.deep_bases.append(base)
                self.deep_bases.extend(base.bases)
                
        elif cursor.kind == clang.cindex.CursorKind.CONSTRUCTOR :
            if 'constructor' in get_annotations(cursor) :
                self.constructors.append(Constructor(self, cursor))
            
        elif cursor.kind == clang.cindex.CursorKind.CXX_METHOD :
            if 'attribute' in get_annotations(cursor) :
                self.members.append(Member(self, cursor))
            if 'method' in get_annotations(cursor) :
                self.methods.append(Method(self, cursor))

        elif cursor.kind == clang.cindex.CursorKind.FIELD_DECL : 
            if 'attribute' in get_annotations(cursor) :
                self.members.append(Member(self, cursor))
            if 'component' in get_annotations(cursor) :
                m = Member(self, cursor)
                self.parts.append(m.cls)
                
        elif cursor.kind == clang.cindex.CursorKind.VAR_DECL :
            if 'attribute' in get_annotations(cursor) :
                self.statics.append(Static(self, cursor))
                
        elif (cursor.kind == clang.cindex.CursorKind.UNION_DECL
           or cursor.kind == clang.cindex.CursorKind.STRUCT_DECL): 
            for c in cursor.get_children():
                self.parse_child(c)
    

            
class Generator(object):
    def __init__(self):
        self.modules = {}
        self.generator_queue = []
        self.root = Root()
        
    def parse_through(self, module, func):
        print 'Module path : ', module.path
        
        # the code generator can deal with the problem of the includes in two ways :
        #   - forward-declare everything that can be and skip all the includes
        #   - parse all the includes, which means also all the includes of the dependencies which then need to be passed to this generator
        
        # for now we are doing a hybrid approach, just skipping the includes of the external dependencies by wrapping them in a ifdef MUD_GENERATOR_SKIP_INCLUDES block
        
        debug_diagnostic = True
        
        compiler_args = [
            '-x',
            'c++',
            '-std=c++14',
            '-fdelayed-template-parsing',
            '-fms-compatibility',
            '-fms-extensions',
            '-fmsc-version=1900',
            '-Wmicrosoft',
            '-Drefl_=__attribute__((annotate("reflect")))',
            '-Dstruct_=__attribute__((annotate("struct")))',
            '-Dextern_=__attribute__((annotate("external")))',
            '-Dserial_=__attribute__((annotate("serialize")))',
            '-Darray_=__attribute__((annotate("array_object")))',
            '-Dcomp_=__attribute__((annotate("component")))',
            '-Dconstr_=__attribute__((annotate("constructor")))',
            '-Dmeth_=__attribute__((annotate("method")))',
            '-Dfunc_=__attribute__((annotate("function")))',
            '-Dattr_=__attribute__((annotate("attribute")))',
            '-Dmut_=__attribute__((annotate("mutable_attr")))',
            '-Dgraph_=__attribute__((annotate("structure_attr")))',
            '-Dlink_=__attribute__((annotate("link_attr")))',
            '-DMUD_META_GENERATOR',
            '-DMUD_GENERATOR_SKIP_INCLUDES'
        ]
                
        for m in module.modules :
            compiler_args.append('-I' + m.rootdir)
            if m.has_generator :
                compiler_args.append('-include' + os.path.join(m.path, 'Generator.h'))
                
        #print 'Parsing with compiler args: ', compiler_args
                  
        def parse_file(path, file, compiler_args, debug = False):
            fullpath = os.path.join(path, file)
            index = clang.cindex.Index.create()

            print 'Parsing ', file

            # only for debugging : these two ways of parsing don't give the correct output, but can give more diagnostics as to what might be wrong
            #translation_unit = index.parse(fullpath, args=compiler_args)
            #translation_unit = index.parse(fullpath, args=compiler_args, options=clang.cindex.TranslationUnit.PARSE_SKIP_FUNCTION_BODIES)
            
            translation_unit = index.parse(fullpath, args=compiler_args, options=clang.cindex.TranslationUnit.PARSE_SKIP_FUNCTION_BODIES | clang.cindex.TranslationUnit.PARSE_INCOMPLETE)
            
            if debug:
                for diag in translation_unit.diagnostics:
                    print diag.severity
                    print diag.location
                    print diag.spelling
                    print diag.option
                    
            func(translation_unit.cursor, fullpath, module, module.root.root_namespace)
            
        parse_file(os.path.join(module.path, 'Generated'), 'Module.h', compiler_args, debug_diagnostic)

    def render_mako(self, module, name):
        dir_path = os.path.dirname(os.path.realpath(__file__))
        output_path = os.path.join(module.outputPath, name)
        print '  ', output_path
        template_path = os.path.join(dir_path, name.lower() + '.mako')
        template = Template(filename=template_path)
        rendered = template.render(module=module)
        update_file(output_path, rendered)
        
    def generate_module(self, module):
    
        for root, dirnames, filenames in os.walk(module.path):
            for filename in fnmatch.filter(filenames, '*.h'):
                if root.find('Generated') == -1 :
                    relative_path = os.path.relpath(os.path.join(root, filename), module.path)
                    module.headers.append(relative_path.replace('\\', '/'))
                if filename == 'Structs.h':
                    module.has_structs = True
                if filename == 'Generator.h':
                    module.has_generator = True
            for filename in fnmatch.filter(filenames, '*.cpp'):
                relative_path = os.path.relpath(os.path.join(root, filename), module.path)
                module.sources.append(relative_path.replace('\\', '/'))
        
        self.render_mako(module, "Module.h")
        self.render_mako(module, "Module.cpp")
            
        def register_classes(cursor, file, module, parent):
            for c in cursor.get_children():
                if c.location.file.name.find(module.path) == 0 and c.location.file.name.find('Generated') == -1:
                    if c.kind == clang.cindex.CursorKind.NAMESPACE :
                        ns = module.get_namespace(c.spelling, parent)
                        register_classes(c, file, module, ns)
                    elif (c.kind == clang.cindex.CursorKind.CLASS_DECL or c.kind == clang.cindex.CursorKind.STRUCT_DECL or c.kind == clang.cindex.CursorKind.CLASS_TEMPLATE) and (c.is_definition() or c.displayname.find('<') > -1):
                        cl = Class(module, c, parent)
                        register_classes(c, file, module, cl)
                    elif c.is_definition() and c.kind == clang.cindex.CursorKind.ENUM_DECL :
                        Enum(module, c, parent)
                       
        self.parse_through(module, register_classes)
        
        print 'NUM CLASSES : ', len(module.classes)
        self.render_mako(module, "Forward.h")
        
        def build_classes(cursor, file, module, parent):
            for c in cursor.get_children():
                if c.location.file.name.find(module.path) == 0 and c.location.file.name.find('Generated') == -1:
                    if c.kind == clang.cindex.CursorKind.CLASS_TEMPLATE:
                        module.template(template_name(c.displayname)).parse_contents(c)
                    if c.kind == clang.cindex.CursorKind.NAMESPACE :
                        ns = module.get_namespace(c.spelling, parent)
                        build_classes(c, file, module, ns)
                    if (c.kind == clang.cindex.CursorKind.CLASS_DECL or c.kind == clang.cindex.CursorKind.STRUCT_DECL) and (c.is_definition() or c.displayname.find('<') > -1):
                        name = parent.prefix + clean_name(c.displayname)
                        cl = module.type(name)
                        cl.parse_contents(c)
                        build_classes(c, file, module, cl)
                    #elif c.kind == clang.cindex.CursorKind.ENUM_DECL :
                    #    Enum(module, c, parent)
                    elif 'function' in get_annotations(c) :
                        if c.kind == clang.cindex.CursorKind.FUNCTION_DECL or c.kind == clang.cindex.CursorKind.FUNCTION_TEMPLATE:
                            Function(module, c, parent)
                            
        self.parse_through(module, build_classes)
        
        def cmp_types(first, other):
            # negative means self before other, positive means self after other
            bases = cmp(first.deep_bases, other.deep_bases)
            if other.isProto and not first.isProto : 
                return -1
            elif first.isProto and not other.isProto :
                return 1
            elif other.deep_bases and not first.deep_bases : 
                return -1
            elif first.deep_bases and not other.deep_bases :
                return 1
            elif other.deep_bases and first.deep_bases and bases != 0 :
                return bases
            elif first in other.deep_bases:
                return -1
            elif other in first.deep_bases:
                return 1
            else:
                return cmp(first.name, other.name)
            
        module.classes.sort(cmp_types)
        module.types.sort(cmp_types)
        module.enums.sort(cmp_types)
        module.sequences.sort(cmp_types)
        module.basetypes.sort(cmp_types)
            
        if not len(module.classes) > 0 and not len(module.enums) > 0 :
            return

        if not os.path.exists(module.outputPath) :
            os.makedirs(module.outputPath)
            
        print 'Generating output templates :'
        for name in ('Types.h', 'Types.cpp', 'Convert.h', 'Meta.h', 'amalgam.h.json', 'amalgam.cpp.json') :
            self.render_mako(module, name)
    
    def add_module(self, module_name, module_def_path):
        dir_path = os.path.dirname(module_def_path)
        root_path = os.path.dirname(dir_path)

        print 'Adding module', module_name, module_def_path
        module_def = imp.load_source(module_name + '_generator', module_def_path)

        dependencies = []
        for dependency_name in module_def.dependencies :
            dependencies.append(self.modules[dependency_name])
            
        module = Module(self.root, module_def.name, module_def.namespace, module_def.preproc_name, module_def.subdir, dependencies, root_path)
        
        self.modules[module_name] = module
        self.generator_queue.append(module)
        
        if hasattr(module_def, 'basetypes'):
            for basetypeid in module_def.basetypes :
                BaseType(module, basetypeid)

        if hasattr(module_def, 'aliases'):
            for alias, type in module_def.aliases.iteritems(): 
                self.root.types[alias] = self.root.types[type]

    def generate_all_modules(self):
        clang.cindex.Config.set_library_file('C:\\Program Files (x86)\\LLVM\\bin\\libclang.dll')

        for module in self.generator_queue:
            self.generate_module(module)
            
instance = Generator()

def add_module(module_name, module_def_path):
    instance.add_module(module_name, module_def_path)
    
def generate_all_modules():
    instance.generate_all_modules()
    
    
parser = argparse.ArgumentParser(description='Generate reflection for N modules.')
parser.add_argument('modules', nargs='+', help='path of the module.py files for which to generate reflection')
args = parser.parse_args()
print(args.modules)

for module in args.modules:
    add_module(os.path.basename(os.path.dirname(module)), module)
    
generate_all_modules()
