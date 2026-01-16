local M = {}
local mbar = require('moonbar')
local deferred = require('deferred')

function M.get_number_of_aur_updates(cb)
  mbar.exec_shell(
    { "paru -Qua | wc -l" }, 
    function(data)
      cb(data)
    end,
    function(err)
      cb(nil, err)
    end)
end

function M.get_number_of_official_updates(cb)
  mbar.exec_shell(
    { "checkupdates | wc -l" },
    function(data)
      print('data: ' .. data)
      cb(data)
    end,
    function(err)
      print('error: ' .. er)
      cb(nil, err)
    end)
end

function M.get_number_of_updates(cb)
  local d = deferred.new()
  mbar.exec_shell(
    { "paru -Qet | wc -l" }, 
    function(data)
      d:resolve(data)
    end,
    function(err)
      d:reject(err)
    end)
  return d
end

return M
