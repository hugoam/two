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

def type_get(c):
    return 'type<' + c.id + '>()'

def type_get_pt(c):
    return '&type<' + c.id + '>()'

def base_offset_get(c, base):
    return 'base_offset<' + c.id + ', ' + base.id + '>()'

def type_var(name, c, pointer, value = ''):
    if name == 'void':
        return 'Var()'
    elif name == 'mud::Ref':
        return 'Ref()'
    elif pointer or not c.struct:
        return 'Ref(' + type_get(c) + ')'
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
    flags = [('Member::Pointer' if member.pointer else None),
             ('Member::Value' if member.cls.struct and not member.pointer else None),
             ('Member::Mutable' if member.mutable else None),
             ('Member::Structure' if member.structure else None),
             ('Member::Link' if member.link or member.pointer else None)]
    flags = [flag for flag in flags if flag is not None]
    if len(flags) == 0: return 'Member::None'
    elif len(flags) == 1: return flags[0]
    else: return 'Member::Flags(' + '|'.join(flags) + ')'

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
    
# @todo investigate why the explicit lambdas incur such a big size difference (bloat)
# mud_d.dll 5487kb vs 5304kb mud_gfx_d.dll 16084kb vs 15796kb wasm 8049kb vs 6037kb
def member_getter_explicit(c, member):
    if member.function:
        return '[](Ref object, Var& v) { set<' + member_type(member) + '>(v, val<' + c.id + '>(object).' + member.member + '()); }'
    else:
        return '[](Ref object, Var& v) { set<' + member_type(member) + '>(v, val<' + c.id + '>(object).' + member.member + '); }'
    
def member_getter(c, member):
    if member.reference and not member.function:
        return '[](Ref object, Var& v) { set<' + member.cls.id + '>(v, val<' + c.id + '>(object).' + member.member + '); }'
    else:
        return 'member_getter<' + member_type(member) + '>(&' + c.id + '::' + member.member + ')'
    
def member_setter_explicit(c, member):
    if member.mutable and member.setter:
        return '[](Ref object, const Var& v) { val<' + c.id + '>(object).set' + member.capname + '(val<' + member_type(member) + '>(v)); }'
    elif member.mutable:
        return '[](Ref object, const Var& v) { val<' + c.id + '>(object).' + member.member + ' = val<' + member_type(member) + '>(v); }'
    else:
        return 'nullptr'
        
def member_setter(c, member):
    if member.mutable and member.setter:
        return 'member_setter<' + member_type(member) + '>(&' + c.id + '::set' + member.capname + ')'
    elif member.mutable:
        return 'member_setter<' + member_type(member) + '>(&' + c.id + '::' + member.member + ')'
    else:
        return 'nullptr'
        
def member_default(c, member):
    if member.cls.struct and not member.pointer:
        return 'var(' + member_type(member) + '(' + member.default + '))'
    else:
        return 'Ref(' + type_get(member.cls) + ')'
 
def method_func(c, method):
    call = 'val<' + c.id + '>(object).' + method.name + '(' + get_args(method.params) + ')'
    if method.returnType == "void" :
        return '[](Ref object, array<Var> args, Var& result) { UNUSED(result); ' + unused_args(method) + call + '; }'
    else:
        return '[](Ref object, array<Var> args, Var& result) { ' + unused_args(method) + value_assign(method.returnCls, 'result', method.returnPointer, call) + '; }'

%>

#pragma once

#ifndef MUD_MODULES
#include <meta/${ module.subdir }/Module.h>

#include <obj/Any.h>
#include <obj/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void ${ module.id }_meta(Module& m)
    {   
    // Base Types
% for b in module.basetypes :
    {
        static Meta meta = { ${ type_get(b) }, ${ namespace(b) }, "${ b.name }", ${ 'sizeof(' + b.name + ')' if not b.name == 'void' else '0' }, TypeClass::BaseType };
        meta_basetype<${ b.name }>();
    }
    
% endfor
    
    // Enums
% for e in module.enums :
    % if e.reflect :
    {
        static Meta meta = { ${ type_get(e) }, ${ namespace(e) }, "${ e.name }", sizeof(${ e.id }), TypeClass::Enum };
        static Enum enu = { ${ type_get(e) },
            ${ 'true' if e.scoped else 'false' },
            { "${ '", "'.join(e.ids) }" },
            { ${ ', '.join(map(str, e.values)) } },
            { var(${ '), var('.join(e.scoped_ids) }) }
        };
        meta_enum<${ e.id }>();
    }
    
    % endif
% endfor
    
    // Sequences
% for s in module.sequences :
    {
        static Meta meta = { ${ type_get(s) }, ${ namespace(s) }, "${ s.name }", sizeof(${ s.id }), TypeClass::Sequence };
        static Class cls = { ${ type_get(s) } };
        cls.m_content = ${ type_get_pt(s.contentcls) };
        meta_sequence<${ s.id }, ${ s.content }>();
    }
    
% endfor
    
    
% for c in module.classes :
    
    % if c.reflect :
        
    // ${ c.id }
    {
        static Meta meta = { ${ type_get(c) }, ${ namespace(c) }, "${ c.name }", sizeof(${ c.id }), ${ type_class(c) } };
        static Class cls = { ${ type_get(c) },
            // bases
            { ${ ', '.join(map(type_get_pt, c.bases)) } },
            { ${ ', '.join([base_offset_get(c, base) for base in c.bases]) } },
            // constructors
            {
            % for constr in c.constructors :
                { ${ type_get(c) }, [](Ref ref, array<Var> args) { ${ unused_args(constr) }new(&val<${ c.id }>(ref)) ${ c.id }( ${ get_args(constr.params) } ); }, ${ params_def(constr.expected_params) } }${ "," if not loop.last else "" }
            % endfor
            },
            // copy constructor
            {
            % if c.struct:
                { ${ type_get(c) }, [](Ref ref, Ref other) { new(&val<${ c.id }>(ref)) ${ c.id }(val<${ c.id }>(other)); } }
            % endif
            },
            // members
            {
            % for m in c.members :
                { ${ type_get(c) }, ${ member_identity(c, m) }, ${ type_get(m.cls) }, "${ m.name }", ${ member_default(c, m) }, ${ member_flags(c, m) } }${ "," if not loop.last else "" }
            % endfor
            },
            // methods
            {
            % for m in c.methods :
                { ${ type_get(c) }, "${ m.name }", ${ method_identity(c, m) }, ${ method_func(c, m) }, ${ params_def(m.params) }, ${ function_return_def(m) } }${ "," if not loop.last else "" }
            % endfor
            },
            // static members
            {
            % for m in c.statics :
                { ${ type_get(c) }, "${ m.name }", Ref(&${ c.id }::${ m.member }) }${ "," if not loop.last else "" }
            % endfor
            }
        };
        
        % if c.isProto :
        cls.m_root = &${ type_get(c.stem) };
        % endif
        
        ${ 'init_pool<' + c.id + '>(); ' if c.constructors and not c.struct else '' }
        ${ 'init_string<' + c.id + '>(); ' if c.array else ''}
        meta_class<${ c.id }>();
    }
    
        % endif
    % endfor

    
    % for t in module.types :
        % if t.reflect :
        m.m_types.push_back(&${ type_get(t) });
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
            static Function f = { ${ namespace(f) }, "${ f.name }", ${ function_identity(f) }, func, params, ${ function_return_def(f) } };
            m.m_functions.push_back(&f);
        }
    % endfor
    }
}
