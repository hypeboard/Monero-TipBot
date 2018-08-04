/*
Copyright(C) 2018 Brandan Tyler Lasley

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
*/
#pragma once
#include "chaiscript/chaiscript.hpp"
#include "ScriptDefs.h"
#include "Poco/Logger.h"

/*
=================================================================================
Engine Defs
=================================================================================
*/
#define MODULE_ADD_TYPE_FULL_EASY(type)                     m->add(chaiscript::user_type<type>(), #type), chaiscript::bootstrap::basic_constructors<type>(#type, *m);
#define MODULE_ADD_TYPE_BASIC_EASY(type)                    m->add(chaiscript::user_type<type>(), #type);
#define MODULE_ADD_GLOBAL_CONST_EASY(obj)                   m->add_global_const(chaiscript::const_var(obj), #obj);
#define MODULE_EASY_FUNC(type)                              m->add(chaiscript::fun(&type), #type);

#define MODULE_ADD(type, name)                              m->add(chaiscript::fun(&type), name);
#define MODULE_ADD_LAMBDA(lambda, name)                     m->add(chaiscript::fun(lambda), name);
#define MODULE_ADD_OVERLOAD(type, func, obj, params, name)  m->add(chaiscript::fun<void (type::*)(params)>(&func, &obj), name);
#define MODULE_ADD_OVERLOAD_BASE(type, func, params, name)  m->add(chaiscript::fun<void (type::*)(params)>(&func), name);
#define MODULE_ADD_CLASS(type, obj, name)                   m->add(chaiscript::fun(&type, &obj), name);
#define MODULE_ADD_TYPE_FULL(type, name)                    m->add(chaiscript::user_type<type>(), name), m->add(chaiscript::bootstrap::basic_constructors<type>(name));
#define MODULE_ADD_TYPE_BASIC(type, name)                   m->add(chaiscript::user_type<type>(), name);
#define MODULE_ADD_GLOBAL_CONST(obj, name)                  m->add_global_const(chaiscript::const_var(obj), name);
#define MODULE_ADD_CONVERSION_UNIQUE_PTR(obj)               m->add(chaiscript::fun(&std::unique_ptr<obj>::get), "get");

#define ENGINE_ADD_VECTOR_STL(engine, type, name)           engine->add(chaiscript::bootstrap::standard_library::vector_type<type>(name));
#define ENGINE_ADD_GLOBAL(engine, obj, name)                engine->add_global(chaiscript::var(std::ref(obj)), name);
#define ENGINE_ADD_GLOBAL_EASY(engine, obj)                 engine->add_global(chaiscript::var(std::ref(obj)), #obj);

class TIPBOT;

class ScriptEngine
{
public:
    ScriptEngine() : shutdown(false), shutdown_complete(false) {}
    std::string                 path;
    chaiscript::ChaiScript *    engine;
    bool                        shutdown;
    bool                        shutdown_complete;
};

class Script
{
public:
    Script(TIPBOT * DPTR);
    ~Script();
    void preinit_engine();

    bool add_script(const std::string& scriptPath);
    void remove_script(const std::string& scriptPath);
    bool is_script_loaded(const std::string& scriptPath);

    void clearAll();
    size_t count() const;
    const std::vector<class ScriptEngine> & getScripts();
private:
    TIPBOT *                        DiscordPtr;
    Poco::Logger*                   PLog;
    std::vector<class ScriptEngine> scripts;
    ScriptDefs                      tipbotdefs;
    chaiscript::ModulePtr           mathscrdata;

    bool reinit_engine(class ScriptEngine& sEngine);

    void init_engine(class ScriptEngine& sEngine);
    void script_exception(const chaiscript::exception::eval_error & ee);
};