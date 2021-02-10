// Extension lib defines
#define EXTENSION_NAME fuior_compiler
#define LIB_NAME "fuior_compiler"
#define MODULE_NAME LIB_NAME

#include <dmsdk/sdk.h>

#include "fuior.h"

static int compile(lua_State *L) {
    const char *input = luaL_checkstring(L, 1);
    const char *filename = NULL;
    if (!lua_isnoneornil(L, 2)) {
        filename = luaL_checkstring(L, 2);
    }

    fuior_results * results = fuior_compile(input, lua_strlen(L, 1), filename);

    for (size_t i = 0; i < results->warning_count; i++) {
        dmLogWarning("%s", results->warnings[i]);
    }

    for (size_t i = 0; i < results->error_count; i++) {
        dmLogError("%s", results->errors[i]);
    }

    if (!results->output || results->error_count) {
        lua_pushstring(L, results->error_count ? results->errors[0] : "fuior produced no output");
        fuior_results_free(results);
        lua_error(L);
        return 0;
    }

    lua_pushstring(L, results->output);
    fuior_results_free(results);
    return 1;
}

static const luaL_reg Module_methods[] =
{
    {"compile", compile},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);

    // Register lua names
    luaL_register(L, MODULE_NAME, Module_methods);

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

static dmExtension::Result AppInitializeExtension(dmExtension::AppParams* params) {
    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeExtension(dmExtension::Params* params) {
    LuaInit(params->m_L);
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeExtension(dmExtension::AppParams* params) {
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeExtension(dmExtension::Params* params) {
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, AppInitializeExtension, AppFinalizeExtension, InitializeExtension, 0, 0, FinalizeExtension)
