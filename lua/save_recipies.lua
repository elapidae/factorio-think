-----------------------------------------------------------------------------------------
local save_recipes = function(player)

    recipes_str = "["

    for _, v in pairs(game.recipe_prototypes) do
        if string.sub(recipes_str, -1) == '}' then
	    	recipes_str = recipes_str .. ','
	    end

    	recipes_str = recipes_str .. '{'
				.. '"name":"' .. v.name .. '",'
				.. '"category":"' .. v.category .. '",'
				.. '"time":' .. v.energy .. ','

    	recipes_str = recipes_str .. '"ingredients":['
    	for _, iv in pairs(v.ingredients) do
    		if string.sub(recipes_str, -1) == '}' then
    			recipes_str = recipes_str .. ','
    		end
    		recipes_str = recipes_str .. '{"name":"' .. iv['name'] .. '","amount":' .. iv['amount'] .. '}'
    	end
    	recipes_str = recipes_str .. '],"products":['

    	for _, pv in pairs(v.products) do
    		if string.sub(recipes_str, -1) == '}' then
    			recipes_str = recipes_str .. ','
    		end

    		recipes_str = recipes_str .. '{'
    					.. '"name":"' .. pv['name'] .. '", "'
    					.. 'amount":'

    		if pv['amount'] == nil then 
    			recipes_str = recipes_str
    						.. 'null,'
    						.. '"amount_min":' .. pv['amount_min'] .. ','
    						.. '"amount_max":' .. pv['amount_max'] .. ','
    						.. '"probability":' .. pv['probability']
    		else
    			recipes_str = recipes_str
    						.. pv['amount']
    		end

    		recipes_str = recipes_str .. '}'
    	end -- products
       	recipes_str = recipes_str .. ']'
       	recipes_str = recipes_str .. '}'
    end -- for v as recipe
    recipes_str = recipes_str .. ']'
    game.write_file('recipe.json', recipes_str)
    
    player.print('Dun!')
end --save_recipes
-----------------------------------------------------------------------------------------

