

#pragma once

#ifndef MUD_MODULES
#include <meta/gfx-ui/Module.h>

#include <obj/Any.h>
#include <obj/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void mud_gfx_ui_meta(Module& m)
    {   
    // Base Types
    
    // Enums
    
    // Sequences
    
    
    
    
        
    // mud::ViewerController
    {
        static Meta meta = { type<mud::ViewerController>(), &namspc({ "mud" }), "ViewerController", sizeof(mud::ViewerController), TypeClass::Object };
        static Class cls = { type<mud::ViewerController>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ViewerController>();
    }
    
    
    
        
    // mud::SceneViewer
    {
        static Meta meta = { type<mud::SceneViewer>(), &namspc({ "mud" }), "SceneViewer", sizeof(mud::SceneViewer), TypeClass::Object };
        static Class cls = { type<mud::SceneViewer>(),
            // bases
            { &type<mud::Scene>(), &type<mud::Viewer>() },
            { base_offset<mud::SceneViewer, mud::Scene>(), base_offset<mud::SceneViewer, mud::Viewer>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::SceneViewer>();
    }
    
    
        
    // mud::Viewer
    {
        static Meta meta = { type<mud::Viewer>(), &namspc({ "mud" }), "Viewer", sizeof(mud::Viewer), TypeClass::Object };
        static Class cls = { type<mud::Viewer>(),
            // bases
            { &type<mud::Widget>() },
            { base_offset<mud::Viewer, mud::Widget>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::Viewer>(), member_address(&mud::Viewer::m_scene), type<mud::Scene>(), "scene", Ref(type<mud::Scene>()), Member::Flags(Member::Pointer|Member::Link) },
                { type<mud::Viewer>(), member_address(&mud::Viewer::m_viewport), type<mud::Viewport>(), "viewport", Ref(type<mud::Viewport>()), Member::None },
                { type<mud::Viewer>(), member_address(&mud::Viewer::m_position), type<mud::vec2>(), "position", var(mud::vec2()), Member::Value },
                { type<mud::Viewer>(), member_address(&mud::Viewer::m_size), type<mud::vec2>(), "size", var(mud::vec2()), Member::Value }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Viewer>();
    }
    
    
        
    // mud::SpaceSheet
    {
        static Meta meta = { type<mud::SpaceSheet>(), &namspc({ "mud" }), "SpaceSheet", sizeof(mud::SpaceSheet), TypeClass::Object };
        static Class cls = { type<mud::SpaceSheet>(),
            // bases
            { &type<mud::RootSheet>() },
            { base_offset<mud::SpaceSheet, mud::RootSheet>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::SpaceSheet>();
    }
    
    
    

    
        m.m_types.push_back(&type<mud::ViewerController>());
        m.m_types.push_back(&type<mud::SceneViewer>());
        m.m_types.push_back(&type<mud::Viewer>());
        m.m_types.push_back(&type<mud::SpaceSheet>());
    
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::viewer(val<mud::Widget>(args[0]), val<mud::Scene>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "scene", Ref(type<mud::Scene>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "viewer", function_id<mud::Viewer&(*)(mud::Widget&, mud::Scene&)>(&mud::ui::viewer), func, params, Ref(type<mud::Viewer>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::scene_viewer(val<mud::Widget>(args[0]), val<mud::vec2>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "size", var(mud::vec2()), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "scene_viewer", function_id<mud::SceneViewer&(*)(mud::Widget&, const mud::vec2&)>(&mud::ui::scene_viewer), func, params, Ref(type<mud::SceneViewer>()) };
            m.m_functions.push_back(&f);
        }
    }
}
