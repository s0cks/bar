local mbar = require("moonbar")
local arch = require("moonbar.arch")
local mem = require("memory")
local Label = require("moonbar.label")
local Button = require("moonbar.button")

local function create_updates_counter()
	local counter = Label.new()
	mbar.next_tick(function()
		arch.get_number_of_updates():next(function(data)
			counter:set_text(data .. "")
		end, function(err)
			print("error getting updates: " .. err)
		end)
	end)
	return counter
end

return {
	style = "style.css",
	init = function()
		--- TODO(@s0cks): investigate why this needs to be wrapped in a next_tick
		mbar.next_tick(function()
			local b = Button.new("󰣇")
			b:add_class("os")
			b:add_class("arch")
			b:on("clicked", function()
				print("button clicked")
			end)
			mbar.append_left(b)

			local updates_counter = create_updates_counter()
			mbar.append_left(updates_counter)

			local total_mem = Label.new()
			mbar.append_left(total_mem)
			mem.read_mem_info(function(data)
				total_mem:set_text(data["MemFree"] .. "/" .. data["MemTotal"])
			end, function(error)
				print("error: " .. error)
			end)
		end)
	end,
}
