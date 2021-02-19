// Extension lib defines
#define EXTENSION_NAME fuior_compiler
#define LIB_NAME "fuior_compiler"
#define MODULE_NAME LIB_NAME

#include <dmsdk/sdk.h>

#include "fuior.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int compile(lua_State *L) {
    const char *input = luaL_checkstring(L, 1);
    const char *filename = NULL;
    if (!lua_isnoneornil(L, 2)) {
        filename = luaL_checkstring(L, 2);
    }

    fuior_results * results = fuior_compile(input, lua_strlen(L, 1), filename);

    for (size_t i = 0; i < results->warning_count; i++) {
        fuior_message *msg = results->warnings[i];
        dmLogWarning("%s:%u:%u %s", msg->filename, msg->start_row + 1, msg->start_column + 1, msg->message);
    }

    for (size_t i = 0; i < results->error_count; i++) {
        fuior_message *msg = results->errors[i];
        dmLogError("%s:%u:%u %s", msg->filename, msg->start_row + 1, msg->start_column + 1, msg->message);
    }

    if (!results->output) {
        lua_pushstring(L, "fuior produced no output");
        fuior_results_free(results);
        lua_error(L);
        return 0;
    }

    if (results->error_count != 0) {
        fuior_message *msg = results->errors[0];
        size_t msg_size = sprintf(NULL, "%s:%u:%u %s", msg->filename, msg->start_row + 1, msg->start_column + 1, msg->message);
        char *msg_str = (char*)malloc(msg_size + 1);
        sprintf(msg_str, "%s:%u:%u %s", msg->filename, msg->start_row + 1, msg->start_column + 1, msg->message);
        lua_pushstring(L, msg_str);
        free(msg_str);

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
