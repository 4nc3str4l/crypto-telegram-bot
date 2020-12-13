-- Command Logic

local price_cmd = {}

function price_cmd.logic(arguments, chat_id)
    ticker = arguments[2]
    print(ticker)
    local price = check_price(ticker)
    local msg = "Price of " .. ticker .. " " .. price .. "$"
    send_message(msg, chat_id)
end

function price_cmd.num_arguments()
    return 1
end

function price_cmd.help()
     return "/lprice <ticker>"
end

commands["/lprice"] = price_cmd