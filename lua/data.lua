--require("tes.tes")

print( 'Hello elapidae!')
for n, v in pairs(data["raw"]) do
  print( n, type(v) )
end

data:extend{
    {
        type = 'custom-input',
        name = 'elapidae-key-1',
        key_sequence = 'N',
        enabled_while_spectating = true,
    },
}

--[[
script.on_event(defines.events.on_player_created, function(event)
    pcall(function()
        local player = game.get_player(event.player_index)
        player.print("Hi player") -- works
        --player.print(player) -- does not work. Any error message would be nice
    end)
end)
--]]

local fireArmor = table.deepcopy(data.raw["armor"]["heavy-armor"]) -- copy the table that defines the heavy armor item into the fireArmor variable

fireArmor.name = "fire-armor"
fireArmor.icons = {
  {
    icon = fireArmor.icon,
    tint = {r=1,g=0,b=0,a=0.3}
  },
}

fireArmor.resistances = {
  {
    type = "physical",
    decrease = 6,
    percent = 10
  },
  {
    type = "explosion",
    decrease = 10,
    percent = 30
  },
  {
    type = "acid",
    decrease = 5,
    percent = 30
  },
  {
    type = "fire",
    decrease = 0,
    percent = 100
  }
}

local recipe = table.deepcopy(data.raw["recipe"]["heavy-armor"])
recipe.enabled = true
recipe.name = "fire-armor"
recipe.ingredients = {{"copper-plate",200},{"steel-plate",50}}
recipe.result = "fire-armor"

data:extend{fireArmor,recipe}

