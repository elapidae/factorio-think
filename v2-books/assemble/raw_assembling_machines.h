//=======================================================================================
static auto raw_assembling_machines = R"(0eNrdWtuOozgQ/ZWVn2EEvnCJ9mW+Y9SKCLgTS2BYLr3bavHva6CbeIxJMGRGE166ZYOrXMd16mLyAU5pQ4uS8RocPgCLc16Bw48PULEzj9Jurn4vKDgAVtMMWIBHWTeKqopmp5Txs51F8YVxarugtQDjCf0PHNzWWiMCSiLgOhFIEoEWiKgKShM7y5MmpdJS3L5YgPKa1YwOgPSD9yNvshMthYWjhDQX6i+RWJfYjFe0rMVzCxR5JRbnvNPcmYPxN2KBd7EyhN+I0CSgrss8PZ7oJXpjedm9GLMyblh9FM+ScfUrK6v6OLHjjZV1I2aupvRv2BF/rwUUZzDoqOqoO1unG2RFVEZ1pwr8DdrhOadxp6jqJLvdn3NJKZdNZomAMmhf2rbDU8EBbsAB7QgHNKq/ZXv4k+0aMViC88yqmsV2fKFVbZf0n0b8vyd2cK3Pl4+vLBUrBv/9YuZtCndQNB1OxBGGTvdHjI872KXbextw2JPb+6P6L1220HNivNczhYE4C9xBdtuVeejTix0pI73o9h+Mkl4jwbIbB0jQPe6Ga7grid3GXXjlLsTd7r7yqD7VjS/jQEt01zH1cAKfmekYzni4624AAu0JCGjKdfzLuQ4lrrtG1ada902EQH3AcJGxO3hPzQs85w54AxBoT0CQe2F5UguQEQjyGfNjVtxIZ1Od1/qjyqI0tdMoK3Sa/FET1ict95rBM5qwJrNpKvAoRfIq8j5P3JA57J5Tdr6c8qZnMXS02SQwxig0wAhqMQqXYUTcexhBxxQjSaYGI4E5RDqYoGsKk1Q+3IcJ6WCCcCFM5C5MyBgmYu5KEBtj5M9hpCSBqS6yqKu7yvd6+Qkrh5Ai+gSdVM8wkeJr4PQfkUhZmXO7SKNaznyhUfrsRZxpVNr/XihNJTnE6AZn8JCcd7XyEPklUUi6ydEmY+gbdt3+nm5egg09qK86Kt4NLOESn5AC9CLOImd9o/sQzor2kaYT0sI/m7TW1v7dlS9ktdduW7qzpyfBbK+G4CISoGcOjPPGo+WXOmQ+DECdaLy+B/Z/Qw8MH9ED43s9MFpUFklll7+jdg95G/re5484s7AY3wQHj2XGzaREzL5MJm8Rj8Wh3hI0x41g7ha4EjhEZ3q7QA2+oFh2HDCQttBP+MqEp4yJukAZu8oYhcoEdnrDH3FPrf/EhMINdW2w27oWb6hAg9+Qemz407eWh5i8pbgLdlvcYWgeYqRSzzDE4ElEUEMGUt9wJxOOGkTQtiCC7gURjNYXar+KLUhmC3HW0mXeL/AKv/DX+gVSMwtSU4uL1QmkuoG6BHsGfqH/njnjD2RD1RbstmrD3vqq7SE0mWlBttBjsPXFGjQdpB+4WSCNTlRsBnwf2fnXJzsr8fRNbHpo/QIX+yH0Ay90kIPb9n/AsTNE)";
//=======================================================================================
// Include:
// - assembing-machine-1;
// - const-comb with RCP values for recipe;
// - const-comb with CNT values for count marker;
// - inserter to storage-chest, linked to chest;
// - for long-handed-inserters to AM1, linked to chest;
// Need to replace:
// -- recipe in AM1;
// -- item in storage-chest;
// -- control-behavior in each inserter;
// -- recipe in ccomb;
// -- count in ccomb;
static auto raw_AM1_recipe_for_first_stages =
        R"(0eNrdlk1vozAQhv/LnKHiMwS0t95XVbW3qkIGXDISGNY20UYR/71jaCkiNGraXDYX0ID9zryPPeAjZFXHW4lCQ3IEzBuhIHk6gsJSsMo804eWQwKoeQ0WCFabiCnF66xCUdo1y3couO1CbwGKgv+DxO2fLeBCo0Y+6g3BIRVdnXFJAyalqiGNHaN5hY1CcanpvQVto2hyI0wFJOi77l1owQESzwvuQspElWrZVGnGd2yPjTQDc5R5hzqld8U0+wWl0umJnz1K3dGTqZBxhM33XB40OSphzKI0M3BCx0R1yyTTJhv8gn4cIHhucikj7ppLKTkXc9dYQBL3zz1NOCHh/YBEeFMk/PO7a4WEN5GIBhKS5zhYaulm68YuZdOJAlaSBT/AHg/JCpSj3UHsVhYhnAp4z2VTmgzFkGYFi7/AsgbiBSuC+smH5TPnj6Phzrh1Z18W6wKN+1UN7yKNh1UN3/A7xbeZZp/bSt4XmP2Pmyf6flP5zg031fbbTfWG5WpNdX+Fpvp9hab6c0lTxbNtVaLSmNv5jittK8LHSn62xT4Ifm0Ng1kBJo4W8WYRe4vYHTzQr+hvRyWm81V6pz3ZWfymJiIOadABajhyJbMTmgW0cdVg09u6QRR70XYTO74T9P0rU91Rzg==)";
//=======================================================================================
