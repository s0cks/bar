local M = BoxLib

local HORIZONTAL = 0
function M.new_horizontal()
  return M.new(HORIZONTAL)
end

local VERTICAL = 1
function M.new_vertical()
  return M.new(VERTICAL)
end

return M
