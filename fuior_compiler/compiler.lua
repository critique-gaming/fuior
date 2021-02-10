local compiler = _G.fuior_compiler

local function compile_string(data, filename)
  if not compiler then
    error("Fuior native extension not present")
  end
  local func_string = compiler.compile(data, filename)
  local chunk = assert(loadstring(func_string, filename))
  return chunk()
end

local function compile(filename)
  local precompiled_data = sys.load_resource(filename .. ".precompiled.lua")
  if precompiled_data then
    local chunk = assert(loadstring(precompiled_data, filename))
    return chunk()
  end

  local data = assert(sys.load_resource(filename))
  return compile_string(data, filename)
end

return {
  compile = compile,
  compile_string = compile_string,
}
