local mbar = require("moonbar")
local utils = require("utils")

local M = {}

function M.read_mem_info(on_data, on_error, on_finished)
  local is_error = false
  local data = {}

  local function next(line)
    local parts = {}
    for part in string.gmatch(line, "([^:]+)") do
      table.insert(parts, part)
    end
    data[utils.trim(parts[1])] = utils.trim(parts[2])
  end

  local function err(error)
    is_error = true
    if on_error then
      on_error(error)
    end
  end

  local function finished()
    if not is_error then
      on_data(data)
    end

    if on_finished then
      on_finished()
    end
  end
  mbar.read_lines("/proc/meminfo", next, err, finished)
end

return M
