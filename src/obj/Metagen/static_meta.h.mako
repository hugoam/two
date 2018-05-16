<%!
def location(e):
    return e.parent.id.split('::') if e.parent.id != '' else []
    
def namespace_begin(n):
    str = ''
    while n.parent != None and n.parent.name != '' :
        str += 'namespace {\n'
        n = n.parent
    return str
    
def namespace_end(n):
    str = ''
    while n.parent != None and n.parent.name != '' :
        str += '}\n'
        n = n.parent
    return str

def namespace(e):
    if e.parent.id == '':
        return '&namspc({})'
    else:
        return '&namspc({ "' + '", "'.join([n for n in location(e)]) + '" })'

def class_get(c):
    return 'cls<' + c.id + '>()'

def class_get_pt(c):
    return '&cls<' + c.id + '>()'

def base_offset_get(c, base):
    return 'base_offset<' + c.id + ', ' + base.id + '>()'

def type_var(name, c, pointer, value = ''):
    if name == 'void':
        return 'Var()'
    elif name == 'mud::Ref':
        return 'Ref()'
    elif pointer or not c.struct:
        return 'Ref(' + class_get(c) + ')'
    else:
        return 'var(' + c.id + '(' + value + '))'
        
def value_var(c, pointer, value = ''):
    if c.id == 'mud::Ref':
        return value
    elif c.struct and not pointer:
        return 'var(' + value + ')'
    else:
        return 'Ref(' + ('&' if not pointer else '') + value + ')'
        
def value_assign(c, var, pointer, value):
    if c.id == 'mud::Ref':
        return var + ' = ' + value
    elif c.struct and not pointer:
        return 'val<' + c.id + '>(' + var + ') = ' + value
    else:
        return var + ' = Ref(' + ('&' if not pointer else '') + value + ')'
   
def param_default(param):
    return type_var(param.cls.id, param.cls, param.pointer, param.default)
    
def param_refget(param, index):
    if param.cls.id == 'mud::Ref':
        return 'args[' + str(index) + ']'
    elif param.pointer:
        return '&val<' + param.cls.id + '>(args[' + str(index) + '])'
    else:
        return 'val<' + param.cls.id + '>(args[' + str(index) + '])'

def param_forward(param, index):
    return 'std::move(' + param_refget(param, index) + ')' if (param.type.find('unique_ptr') > -1 or param.type.find('object_ptr') > -1 ) else param_refget(param, index)
    
def param_flags(param):
    flags = [('Param::Nullable' if param.nullable else None),
             ('Param::Output' if param.output else None),
             ('Param::Default' if param.has_default else None)]
    flags = [flag for flag in flags if flag is not None]
    if len(flags) == 0: return ''
    elif len(flags) == 1: return ', ' + flags[0]
    else: return ', Param::Flags(' + '|'.join(flags) + ')'
    
def param_decl(param):
    return '{ "' + param.name + '", ' + param_default(param) + param_flags(param) + ' }'

def function_identity(func):
    return 'function_id<' + func.signature + '>(&' + func.id + ')'

def function_return_def(func):
    return type_var(func.returnType, func.returnCls, func.returnPointer)

def params_def(params):
    return '{ ' + ', '.join([param_decl(param) for param in params]) + ' }' if params else '{}'

def get_args(params):
    return ', '.join([param_forward(param, param.index) for param in params])

def method_identity(c, method):
    return 'member_address(&' + c.id + '::' + method.name + ')'

def field_identity(c, member):
    return 'member_address(&' + c.id + '::' + member.member + ')' if not member.reference else 'Address()'
    
def member_identity(c, member):
    return method_identity(c, member) if member.function else field_identity(c, member)

def member_flags(c, member):
    flags = [('MEMBER_VALUE' if member.cls.struct and not member.pointer else None),
             ('MEMBER_MUTABLE' if member.mutable else None),
             ('MEMBER_STRUCTURE' if member.structure else None),
             ('MEMBER_LINK' if member.link or member.pointer else None)]
    flags = [flag for flag in flags if flag is not None]
    return '|'.join(flags) if len(flags) > 0 else '0'

def unused_args(func):
    return 'UNUSED(args);' if len(func.params) == 0 else ''
    
def type_class(c):
    if c.struct:
        return 'TypeClass::Struct'
    elif c.isModular:
        return 'TypeClass::Complex'
    else:
        return 'TypeClass::Object'

def member_type(member):
    return member.cls.id + ('*' if member.pointer else '')
    
def member_getter(c, member):
    if member.function:
        return '[](Ref object, Var& v) { set<' + member_type(member) + '>(v, val<' + c.id + '>(object).' + member.member + '()); }'
    else:
        return '[](Ref object, Var& v) { set<' + member_type(member) + '>(v, val<' + c.id + '>(object).' + member.member + '); }'
    
def member_setter(c, member):
    if member.mutable and member.setter:
        return '[](Ref object, const Var& v) { val<' + c.id + '>(object).set' + member.capname + '(val<' + member_type(member) + '>(v)); }'
    elif member.mutable:
        return '[](Ref object, const Var& v) { val<' + c.id + '>(object).' + member.member + ' = val<' + member_type(member) + '>(v); }'
    else:
        return 'nullptr'
        


def member_default(c, member):
    if member.cls.struct and not member.pointer:
        return 'var(' + member_type(member) + '(' + member.default + '))'
    else:
        return 'Ref(' + class_get(member.cls) + ')'
 
def method_func(c, method):
    call = 'val<' + c.id + '>(object).' + method.name + '(' + get_args(method.params) + ')'
    if method.returnType == "void" :
        return '[](Ref object, array<Var> args, Var& result) { UNUSED(result); ' + unused_args(method) + call + '; }'
    else:
        return '[](Ref object, array<Var> args, Var& result) { ' + unused_args(method) + value_assign(method.returnCls, 'result', method.returnPointer, call) + '; }'

%>

#pragma once

#include <${ module.subdir }/Generated/Module.h>

#include <obj/Any.h>
#include <obj/Reflect/MetaDecl.h>
#include <obj/System/System.h>

namespace mud
{
    // Base Types
    % for b in module.basetypes :
    template <>
    struct Reflection<${ b.name }> : public Meta
    {
        Namespace* m_namespace = ${ namespace(b) };
        cstring m_name = "${ b.name }";
        size_t m_size = ${ 'sizeof(' + b.name + ')' if not b.name == 'void' else '0' };
        TypeClass m_type_class = TypeClass::BaseType;
        
        Reflection() : Meta(${ class_get(b) }) { meta_basetype<${ b.name }>(*this, *this); }
    };
    
    % endfor
    
    // Enums
    % for e in module.enums :
        % if e.reflect :
    template <>
    struct Reflection<${ e.id }> : public Meta
    {
        Namespace* m_namespace = ${ namespace(e) };
        cstring m_name = "${ e.name }";
        size_t m_size = sizeof(${ e.id });
        TypeClass m_type_class = TypeClass::Enum;
        bool m_scoped_enum = ${ 'true' if e.scoped else 'false' };
        std::vector<cstring> m_enum_names = { "${ '", "'.join(e.ids) }" };
        std::vector<size_t> m_enum_indices = { ${ ', '.join(map(str, e.values)) } };
        std::vector<Var> m_enum_values = { var(${ '), var('.join(e.scoped_ids) }) };
        
        Reflection() : Meta(${ class_get(e) }) { meta_enum<${ e.id }>(*this, *this); }
    };
    
        % endif
    % endfor
    
    // Sequences
    % for s in module.sequences :
    template <>
    struct Reflection<${ s.id }> : public Meta
    {
        Namespace* m_namespace = ${ namespace(s) };
        cstring m_name = "${ s.name }";
        size_t m_size = sizeof(${ s.id });
        TypeClass m_type_class = TypeClass::Sequence;
        Type* m_content = ${ class_get_pt(s.contentcls) };
        
        Reflection() : Meta(${ class_get(s) }) { meta_sequence<${ s.id }, ${ s.content }>(*this, *this); }
    };
    
    % endfor
    
    
    % for c in module.classes :
    
        % if c.reflect :
        
    // ${ c.id }
    template <>
    struct Reflection<${ c.id }> : public Meta
    {
        Namespace* m_namespace = ${ namespace(c) };
        cstring m_name = "${ c.name }";
        size_t m_size = sizeof(${ c.id });
        TypeClass m_type_class = ${ type_class(c) };
        % if len(c.bases) > 0 :
        std::vector<Type*> m_bases = { &${ ', &'.join(map(class_get, c.bases)) } };
        std::vector<uintptr_t> m_bases_offsets = { ${ ', '.join([base_offset_get(c, base) for base in c.bases]) } };
        % endif
        bool m_serializable = ${ str(c.serializable).lower() };
        % if len(c.members) > 0 :
        struct {
            % for m in c.members :
            Member ${ m.member } = { ${ class_get(c) }, ${ member_identity(c, m) }, ${ class_get(m.cls) }, "${ m.name }", ${ member_getter(c, m) }, ${ member_setter(c, m) }, ${ member_default(c, m) }, ${ member_flags(c, m) } };
            % endfor
        } members;
        % endif
        % if len(c.methods) > 0 :
        struct {
            % for m in c.methods :
            Method ${ m.name } = { ${ class_get(c) }, "${ m.name }", ${ method_identity(c, m) }, ${ method_func(c, m) }, ${ params_def(m.params) }, ${ function_return_def(m) } };
            % endfor
        } methods;
        % endif
        % if len(c.constructors) > 0 or c.struct :
        struct {
            % for i, constr in enumerate(c.constructors) :
            ConstructorFunc construct_${ i } = [](Ref ref, array<Var> args) { ${ unused_args(constr) }new(&val<${ c.id }>(ref)) ${ c.id }( ${ get_args(constr.params) } ); };
            Constructor constructor_${ i } = { ${ class_get(c) }, construct_${ i }, ${ params_def(constr.expected_params) } };
            % endfor
            % if c.struct:
            CopyConstructor copy_constructor = { ${ class_get(c) }, [](Ref ref, Ref other) { new(&val<${ c.id }>(ref)) ${ c.id }(val<${ c.id }>(other)); } };
            % endif
        } constructors;
        % endif
        % if len(c.statics) > 0 :
        struct {
            % for m in c.statics :
            Static ${ m.member } = { ${ class_get(c) }, "${ m.name }", Ref(&${ c.id }::${ m.member }) };
            % endfor
        } static_members;
        % endif
        % if len(c.members) > 0 :
        std::vector<Member> m_members = { ${ ', '.join(['members.' + m.member for m in c.members]) } };
        % endif
        % if len(c.methods) > 0 :
        std::vector<Method> m_methods = { ${ ', '.join(['methods.' + m.name for m in c.methods]) } };
        % endif
        % if len(c.constructors) > 0 :
        std::vector<Constructor> m_constructors = { ${ ', '.join(['constructors.constructor_' + str(i) for i, constr in enumerate(c.constructors)]) } };
        % endif
        % if c.struct:
        std::vector<CopyConstructor> m_copy_constructors = { constructors.copy_constructor };
        % endif
        % if len(c.statics) > 0 :
        std::vector<Static> m_static_members = { ${ ', '.join(['static_members.' + m.member for m in c.statics]) } };
        % endif
        % if c.isProto :
        Type* m_root = &${ class_get(c.stem) };
        % endif
        
        Reflection() : Meta(${ class_get(c) }) { ${ 'init_pool<' + c.id + '>(*this); ' if c.constructors and not c.struct else '' }${ 'init_string<' + c.id + '>(*this); ' if c.array else ''}meta_class<${ c.id }>(*this, *this); }
    };
    
        % endif
    % endfor

    
#ifdef ${ module.preproc_name }_REFLECTION_IMPL
    void ${ module.name }_meta(Module& module)
    {   
    % for t in module.types :
        % if t.reflect :
        rfl<${ t.id }>();
        module.m_types.push_back(&${ class_get(t) });
        % endif
    % endfor
    
    % for f in module.functions :
        {
        % if f.returnType == "void" :
            auto func = [](array<Var> args, Var& result) { UNUSED(result); ${ unused_args(f) } ${ f.id }(${ get_args(f.params) }); };
        % else :
            auto func = [](array<Var> args, Var& result) { ${ unused_args(f) } ${ value_assign(f.returnCls, 'result', f.returnPointer, f.id + '(' + get_args(f.params) + ')') }; };
        % endif
            std::vector<Param> params = ${ params_def(f.params) };
            module.m_functions.push_back({ ${ namespace(f) }, "${ f.name }", ${ function_identity(f) }, func, params, ${ function_return_def(f) } });
        }
    % endfor
    }
#endif

}
