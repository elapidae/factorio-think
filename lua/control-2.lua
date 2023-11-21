-- https://lua-api.factorio.com/latest/Libraries.html
-- globals: https://lua-api.factorio.com/latest/index.html
-----------------------------------------------------------------------------------------
local on_init = function()
    print( '---------' )
    print( "on_init" )
    rcon.print( "on_init" )
    print( '---------' )
end
script.on_init( on_init )
-----------------------------------------------------------------------------------------
local on_load = function()
    print( '---------' )
    print( "on_load" )
    rcon.print( "on_load" )
    print( '---------' )
end
script.on_load( on_load )
-----------------------------------------------------------------------------------------
--[[ on_player_main_inventory_changed	
local on_player_main_inventory_changed
 = function(event)
    local player = game.get_player(event.player_index)
    msg = 'main ic i=' .. event.player_index .. ", n=" .. event.name .. ", t=" .. event.tick
    log( msg )
end
script.on_event( defines.events.on_player_main_inventory_changed, 
                                on_player_main_inventory_changed )
--]]
-----------------------------------------------------------------------------------------
local msg_MapPosition = function( p )
    return '('..p.x..','..p.y..')'
end
-----------------------------------------------------------------------------------------
local msg_defines_direction = function( d )
    if not d then return '' end
    return 'dir:'..d
end
-----------------------------------------------------------------------------------------
local msg_Tags = function( t )
    if not t then return '' end
    return '<tags+>'
end
-----------------------------------------------------------------------------------------
local msg_dictionary = function( d )
end
-----------------------------------------------------------------------------------------
-- https://lua-api.factorio.com/latest/Concepts.html#BlueprintEntity
local msg_BlueprintEntity = function( e )
    msg = e.entity_number .. '. ' .. e.name
    msg = msg .. ' ' .. msg_MapPosition( e.position )
    msg = msg .. ' ' .. msg_defines_direction( e.direction )
    msg = msg .. ' ' .. msg_Tags( e.tags )
--    msg = msg .. ' ' .. e.items -- dictionary[string → uint]?
--    msg = msg .. ' ' .. e.connections -- BlueprintCircuitConnection?
--    msg = msg .. ' ' .. e.control_behavior -- BlueprintControlBehavior?
--    msg = msg .. ' ' .. e.schedule -- array[TrainScheduleRecord]?
    return msg
end


local think_entity = function( e )
    pos = '(' .. e.position.x .. ',' .. e.position.y .. ')'
    msg = e.entity_number .. ' ' .. e.name .. ' ' .. pos

    dir = e.direction
    if dir then msg = msg .. dir end 
    player.print( msg )
end
-----------------------------------------------------------------------------------------
-- on_player_cursor_stack_changed
local on_player_cursor_stack_changed = function(event)

    print( game.help() )
    return 42

    -- player = game.get_player( event.player_index )
    -- stack = player.cursor_stack
    -- if not stack.valid_for_read then return end    
    -- if stack.type ~= 'blueprint' then return end
    -- if not stack.is_blueprint_setup() then return end

    -- -- let's define tiles under entity
    -- entities = stack.get_blueprint_entities() -- array[BlueprintEntity]?
    -- for i = 1, #entities do
    --     e = entities[i]
    --     print( '=========================' )
    --     print( e.help() )
    -- end -- for each i entity

--[[
    tiles = stack.get_blueprint_tiles()
    if not tiles then return end
    for i = 1, #tiles do
        t = tiles[i]
        name = t.name
        if name ~= 'landfill' then error('not landfill') end

        pos = '(' .. t.position.x .. ',' .. t.position.y .. ')'
        msg = pos
        player.print( msg )
    end -- for each i tile
--]]

end

script.on_event( defines.events.on_player_cursor_stack_changed,
                                on_player_cursor_stack_changed )


-----------------------------------------------------------------------------------------

