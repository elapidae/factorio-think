-- https://lua-api.factorio.com/latest/Libraries.html
-- globals: https://lua-api.factorio.com/latest/index.html
-----------------------------------------------------------------------------------------
local on_load = function()
    print( '---------' )
    print( "on_load" )
    rcon.print( "on_load" )
    print( '---------' )
end
script.on_load( on_load )
-----------------------------------------------------------------------------------------
local save_items = function(player)

    items = "["

        for _, v in pairs(game.item_prototypes) do
            if string.sub(items, -1) == '}' then
                items = items .. ','
	        end

    	    items = items .. '{'
				.. '"name":"'       .. v.name           .. '",'
				.. '"item-type":"'  .. v.type           .. '",'
				.. '"order":"'      .. v.order          .. '",'
				.. '"group":"'      .. v.group.name     .. '",'
				.. '"subgroup":"'   .. v.subgroup.name  .. '",'
				.. '"stack_size":'  .. v.stack_size     .. ','
                .. '"type":"item"'
    		items = items .. '}'
    	end -- for item
   	items = items .. ']'
    game.write_file('items.json', items)
    
    player.print('Dun!')
end --save_items
-----------------------------------------------------------------------------------------
--[[ on_player_main_inventory_changed
local on_player_main_inventory_changed = function(event)
    local player = game.get_player( event.player_index )
    save_items( player )

--    entities = game.entity_prototypes
--    for _, v in pairs(entities) do
--        j = game.table_to_json(v)
--        game.write_file('entities.json', j)
--        return
--    end -- for
--    j = game.table_to_json()
--    game.write_file('entities.json', j)
--
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
    local player = game.get_player(event.player_index) -- get the player
    --player.print( 'stack changed' )
end
--script.on_event( defines.events.on_player_cursor_stack_changed,
  --                              on_player_cursor_stack_changed )
-----------------------------------------------------------------------------------------
local on_built_entity = function(event)
    local player = game.get_player(event.player_index) -- get the player
    player.print( 'on_built_entity -- ' .. 'event.name: ' .. event.name )

    local entity = event.created_entity
--    player.print( 'entity name: ' .. entity.name .. ' , event.name: ' .. event.name )
    --print( '--- , entity.help: ' .. entity.help() )
    player.print( 'entity radius: ' .. entity.get_radius() )
    player.print( 'entity bbox: ' .. serpent.line(entity.bounding_box) )
    player.print( 'tile h, w: ' .. entity.tile_height .. ',' .. entity.tile_width )

    local prototype = entity.prototype
    player.print( 'prototype:' )
    player.print( 'col mask: ' .. serpent.line(prototype.collision_mask) )
    player.print( 'col mask w f: ' .. serpent.line(prototype.collision_mask_with_flags) )
    player.print( 'type, name: ' .. prototype.type .. ', ' .. prototype.name )

    print( prototype.help() )

    local item = event.item
    if item then player.print( "item.name: " .. item.name ) 
    else player.print( "no item" ) end
    player.print( '=====================================' )

    
end
--script.on_event( defines.events.on_built_entity,
  --                              on_built_entity )
-----------------------------------------------------------------------------------------
--[[
additional_pastable_entities [R]

active_energy_usage [R]
adjacent_tile_collision_box [R]
adjacent_tile_collision_mask [R]
adjacent_tile_collision_test [R]
affected_by_tiles [R]
air_resistance [R]
alert_icon_scale [R]
alert_icon_shift [R]
alert_when_attacking [R]
alert_when_damaged [R]
allow_access_to_all_forces [R]
allow_burner_leech [R]
allow_copy_paste [R]
allow_custom_vectors [R]
allow_passengers [R]
allow_run_time_change_of_is_military_target [R]
allowed_effects [R]
always_on [R]
ammo_category [R]
animation_speed_coefficient [R]
attack_parameters [R]
attack_result [R]
automated_ammo_count [R]
automatic_weapon_cycling [R]
autoplace_specification [R]
base_productivity [R]
belt_distance [R]
belt_length [R]
belt_speed [R]
braking_force [R]
build_base_evolution_requirement [R]
build_distance [R]
building_grid_bit_shift [R]
burner_prototype [R]
burns_fluid [R]
call_for_help_radius [R]
can_open_gates [R]
center_collision_mask [R]
chain_shooting_cooldown_modifier [R]
character_corpse [R]
chunk_exploration_radius [R]
cliff_explosive_prototype [R]
collision_box [R]
collision_mask [R]
collision_mask_collides_with_self [R]
collision_mask_collides_with_tiles_only [R]
collision_mask_considers_tile_transitions [R]
collision_mask_with_flags [R]
color [R]
construction_radius [R]
consumption [R]
container_distance [R]
corpses [R]
count_as_rock_for_filtered_deconstruction [R]
crafting_categories [R]
crafting_speed [R]
create_ghost_on_death [R]
created_effect [R]
created_smoke [R]
damage_hit_tint [R]
darkness_for_all_lamps_off [R]
darkness_for_all_lamps_on [R]
default_collision_mask_with_flags [R]
destroy_non_fuel_fluid [R]
distraction_cooldown [R]
distribution_effectivity [R]
door_opening_speed [R]
draw_cargo [R]
drawing_box [R]
drop_item_distance [R]
dying_speed [R]
effectivity [R]
electric_energy_source_prototype [R]
emissions_per_second [R]
enemy_map_color [R]
energy_per_hit_point [R]
energy_per_move [R]
energy_per_tick [R]
energy_usage [R]
engine_starting_speed [R]
enter_vehicle_distance [R]
explosion_beam [R]
explosion_rotate [R]
fast_replaceable_group [R]
filter_count [R]
final_attack_result [R]
fixed_recipe [R]
flags [R]
fluid [R]
fluid_capacity [R]
fluid_energy_source_prototype [R]
fluid_usage_per_tick [R]
fluidbox_prototypes [R]
flying_acceleration [R]
flying_speed [R]
friction_force [R]
friendly_map_color [R]
grid_prototype [R]
group [R]
guns [R]
has_belt_immunity [R]
healing_per_tick [R]
heat_buffer_prototype [R]
heat_energy_source_prototype [R]
height [R]
idle_energy_usage [R]
indexed_guns [R]
infinite_depletion_resource_amount [R]
infinite_resource [R]
ingredient_count [R]
inserter_chases_belt_items [R]
inserter_drop_position [R]
inserter_extension_speed [R]
inserter_pickup_position [R]
inserter_rotation_speed [R]
inserter_stack_size_bonus [R]
instruments [R]
is_building [R]
is_entity_with_owner [R]
is_military_target [R]
isluaobject [R]
item_pickup_distance [R]
item_slot_count [R]
items_to_place_this [R]
lab_inputs [R]
lamp_energy_usage [R]
launch_wait_time [R]
light_blinking_speed [R]
localised_description [R]
localised_name [R]
logistic_mode [R]
logistic_parameters [R]
logistic_radius [R]
loot [R]
loot_pickup_distance [R]
manual_range_modifier [R]
map_color [R]
map_generator_bounding_box [R]
max_circuit_wire_distance [R]
max_count_of_owned_units [R]
max_darkness_to_spawn [R]
max_distance_of_nearby_sector_revealed [R]
max_distance_of_sector_revealed [R]
max_energy [R]
max_energy_production [R]
max_energy_usage [R]
max_friends_around_to_spawn [R]
max_health [R]
max_payload_size [R]
max_polyphony [R]
max_power_output [R]
max_pursue_distance [R]
max_speed [R]
max_to_charge [R]
max_underground_distance [R]
max_wire_distance [R]
maximum_corner_sliding_distance [R]
maximum_temperature [R]
min_darkness_to_spawn [R]
min_pursue_time [R]
min_to_charge [R]
mineable_properties [R]
minimum_resource_amount [R]
mining_drill_radius [R]
mining_speed [R]
module_inventory_size [R]
move_while_shooting [R]
name [R]
neighbour_bonus [R]
next_upgrade [R]
normal_resource_amount [R]
object_name [R]
order [R]
pollution_to_join_attack [R]
protected_from_tile_building [R]
pumping_speed [R]
radar_range [R]
radius [R]
reach_distance [R]
reach_resource_distance [R]
related_underground_belt [R]
remains_when_mined [R]
remove_decoratives [R]
repair_speed_modifier [R]
researching_speed [R]
resistances [R]
resource_categories [R]
resource_category [R]
respawn_time [R]
result_units [R]
rising_speed [R]
rocket_entity_prototype [R]
rocket_parts_required [R]
rocket_rising_delay [R]
rotation_speed [R]
running_speed [R]
scale_fluid_usage [R]
secondary_collision_box [R]
selectable_in_game [R]
selection_box [R]
selection_priority [R]
shooting_cursor_size [R]
spawn_cooldown [R]
spawning_radius [R]
spawning_spacing [R]
spawning_time_modifier [R]
speed [R]
speed_multiplier_when_out_of_energy [R]
stack [R]
sticker_box [R]
subgroup [R]
supply_area_distance [R]
supports_direction [R]
tank_driving [R]
target_temperature [R]
terrain_friction_modifier [R]
ticks_to_keep_aiming_direction [R]
ticks_to_keep_gun [R]
ticks_to_stay_in_combat [R]
tile_height [R]
tile_width [R]
time_to_live [R]
timeout [R]
torso_bob_speed [R]
torso_rotation_speed [R]
tree_color_count [R]
trigger_collision_mask [R]
turret_range [R]
turret_rotation_speed [R]
type [R]
use_exact_mode [R]
valid [R]
vision_distance [R]
void_energy_source_prototype [R]
weight [R]


]]--



