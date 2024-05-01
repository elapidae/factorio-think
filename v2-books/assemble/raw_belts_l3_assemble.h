
//=======================================================================================
static auto belts_L3_assemble = R"(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)";
//=======================================================================================
