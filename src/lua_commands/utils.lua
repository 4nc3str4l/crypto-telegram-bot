-- Returns a string with all the commands
function utils.get_commands()
    local help_str = "*Custom Commands*\n"
    for i, v in pairs(commands) do
        help_str = help_str .. "*" .. i .. "* " .. v["instructions"]() .. "\n"
    end
    return help_str
end