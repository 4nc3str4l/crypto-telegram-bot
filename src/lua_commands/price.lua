-- Command Logic

local price_cmd ={}

function price_cmd.logic(arguments, chat_id)
    print(arguments)
    local price = check_price("ETH")
    local msg = "Price of " .. "ETH" .. " " .. price .. "$"
    send_message(msg, chat_id)
end

function price_cmd.num_arguments()
    return 2
end

function price_cmd.send_help()
     
end

commands["/price"] = price_cmd