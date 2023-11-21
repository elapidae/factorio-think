data:extend({
  {
    type = "item",
    name = "tes-name",

    item_name = "Test Tes",
    icon_size = 32,
    icon = "__el__/tes/tes.png",

    subgroup = "raw-material",
    order = "aaa",
    stack_size= 13,

    --flags = { "goes-to-main-inventory" },
    --place_result = "tes-name",
  },
})

data:extend({
{
    type = "recipe",
    name = "tes-name",

    --category = "smelting",
    category = "crafting",

    energy_required = 14,
    ingredients = 
    {
      {
        type = "item",
        name = "iron-plate",
        amount = 14,
        amount_catalyst = 0.2,
      }
    },
    result = "tes-name",
    result_count = 3,
},
})

