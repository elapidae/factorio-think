
--[[
script.on_event(defines.events.on_player_changed_position,
  function(event)
    local player = game.get_player(event.player_index) -- get the player that moved            
    -- if they're wearing our armor
    if player.character and player.get_inventory(defines.inventory.character_armor).get_item_count("fire-armor") >= 1 then
       -- create the fire where they're standing
       player.surface.create_entity{name="fire-flame", position=player.position, force="neutral"} 
    end
  end
)
--]]

moved_changed = true
local func = function(event)
    if moved_changed then return end
    moved_changed = true

    local player = game.get_player(event.player_index) -- get the player that moved            
    for n, v in pairs(event) do
        player.print( n )    
    end

    player.print( '---------' )
    player.print( type(defines.events) )

    
    for name, code in pairs(defines.events) do
        if name == 'on_tick' then goto continue end
        if name == 'on_chunk_charted' then goto continue end
        if name == 'on_sector_scanned' then goto continue end
        if name == 'on_entity_died' then goto continue end
        if name == 'on_post_entity_died' then goto continue end
        if name == 'on_player_changed_position' then goto continue end
        if name == 'on_ai_command_completed' then goto continue end
        if name:find('train') then goto continue end
        if name:find('damaged') then goto continue end
        if name == 'on_entity_spawned' then goto continue end
        if name == 'on_unit_added_to_group' then goto continue end
        if name == 'on_unit_group_created' then goto continue end
        if name == 'on_unit_removed_from_group' then goto continue end
        if name == 'on_resource_depleted' then goto continue end
        if name == 'on_robot_built_entity' then goto continue end


        cb = function( event )
            -- local player = game.get_player( event.player_index )
            player.print( name )
        end -- cb

        script.on_event( code, cb )

        ::continue::
    end

--    
--    player.surface.create_entity{name="fire-flame", position=player.position, force="neutral"} 
end
script.on_event( defines.events.on_player_changed_position, func )


-----------------------------------------------------------------------------------------

--[[
on_player_alt_reverse_selected_area
on_player_reverse_selected_area
on_equipment_removed	number
on_equipment_inserted	number
on_entity_logistic_slot_changed	number
on_spider_command_completed	number
on_player_used_spider_remote	number
on_player_configured_spider_remote	number
on_cutscene_cancelled	number
on_permission_group_added	number
on_permission_group_deleted	number
on_pre_permission_group_deleted	number
on_permission_string_imported	number
on_pre_permission_string_imported	number
on_permission_group_edited	number
on_player_flushed_fluid	number
on_player_clicked_gps_tag	number
on_entity_destroyed	number
on_script_inventory_resized	number
on_pre_script_inventory_resized	number
on_pre_player_toggled_map_editor	number
on_player_set_quick_bar_slot	number
on_script_trigger_effect	number
on_string_translated	number
on_force_cease_fire_changed	number
on_force_friends_changed	number
on_gui_switch_state_changed	number
on_gui_selected_tab_changed	number
on_gui_location_changed	number
on_gui_confirmed	number
on_chart_tag_removed	number
on_chart_tag_modified	number
on_chart_tag_added	number
on_trigger_fired_artillery	number
on_build_base_arrived	number
on_unit_group_finished_gathering	number
on_unit_removed_from_group	number
on_unit_added_to_group	number
on_unit_group_created	number
on_pre_player_removed	number
on_entity_spawned	number
on_post_entity_died	number
on_robot_exploded_cliff	number
on_pre_robot_exploded_cliff	number
on_pre_chunk_deleted	number
on_player_fast_transferred	number
on_player_repaired_entity	number
on_player_toggled_alt_mode	number
on_surface_renamed	number
on_surface_imported	number
on_game_created_from_scenario	number
on_brush_cloned	number
on_area_cloned	number
on_entity_cloned	number
on_player_toggled_map_editor	number
on_cancelled_upgrade	number
on_marked_for_upgrade	number
on_ai_command_completed	number
on_script_path_request_finished	number
on_rocket_launch_ordered	number
on_player_unbanned	number
on_player_kicked	number
on_player_banned	number
on_train_schedule_changed	number
on_chunk_deleted	number
on_pre_surface_cleared	number
on_surface_cleared	number
on_pre_player_left_game	number
on_player_trash_inventory_changed	number
on_forces_merged	number
on_land_mine_armed	number
on_force_reset	number
on_technology_effects_reset	number
on_chunk_charted	number
on_entity_damaged	number
on_player_cancelled_crafting	number
on_pre_player_crafted_item	number
on_player_display_scale_changed	number
on_player_display_resolution_changed	number
on_player_pipette	number
on_pre_ghost_upgraded	number
on_pre_ghost_deconstructed	number
on_character_corpse_expired	number
on_player_cheat_mode_disabled	number
on_player_cheat_mode_enabled	number
on_player_unmuted	number
on_player_muted	number
on_gui_value_changed	number
on_gui_closed	number
on_gui_opened	number
on_mod_item_opened	number
on_player_changed_position	number
on_worker_robot_expired	number
on_combat_robot_expired	number
script_raised_set_tiles	number
script_raised_revive	number
script_raised_destroy	number
script_raised_built	number
on_player_demoted	number
on_player_promoted	number
on_player_used_capsule	number
on_player_removed	number
on_console_command	number
on_console_chat	number
on_player_configured_blueprint	number
on_player_deconstructed_area	number
on_player_setup_blueprint	number
on_gui_elem_changed	number
on_train_created	number
on_player_mined_entity	number
on_robot_mined_entity	number
on_pre_surface_deleted	number
on_surface_deleted	number
on_surface_created	number
on_difficulty_settings_changed	number
on_runtime_mod_setting_changed	number
on_gui_selection_state_changed	number
on_entity_renamed	number
on_player_changed_force	number
on_biter_base_built	number
on_player_dropped_item	number
on_market_item_purchased	number
on_selected_entity_changed	number
on_player_changed_surface	number
on_player_alt_selected_area	number
on_player_selected_area	number
on_robot_mined_tile	number
on_robot_built_tile	number
on_player_mined_tile	number
on_player_built_tile	number
on_player_left_game	number
on_player_joined_game	number
on_player_respawned	number
on_player_died	number
on_pre_player_died	number
on_player_removed_equipment	number
on_player_placed_equipment	number
on_player_gun_inventory_changed	number
on_player_ammo_inventory_changed	number
on_player_armor_inventory_changed	number
on_lua_shortcut	number
on_cutscene_waypoint_reached	number

on_entity_settings_pasted	number
on_pre_entity_settings_pasted	number
on_player_cursor_stack_changed	number
on_forces_merging	number
on_force_created	number
on_player_driving_changed_state	number
on_resource_depleted	number
on_player_created	number
on_train_changed_state	number
on_trigger_created_entity	number
on_cancelled_deconstruction	number
on_marked_for_deconstruction	number
on_player_rotated_entity	number
on_research_cancelled	number
on_research_reversed	number
on_research_finished	number
on_research_started	number
on_robot_mined	number
on_robot_pre_mined	number
on_robot_built_entity	number
on_player_crafted_item	number
on_chunk_generated	number
on_pre_player_mined_item	number
on_rocket_launched	number
on_pre_build	number
on_player_mined_item	number
on_sector_scanned	number
on_built_entity	number
on_picked_up_item	number
on_entity_died	number
on_gui_checked_state_changed	number
on_gui_text_changed	number
on_gui_click	number
on_tick	number
--]]
a=42

