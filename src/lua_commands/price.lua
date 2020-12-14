local cmd = {}

function cmd.logic(arguments, chat_id)
    ticker = arguments[2]
    local price = check_price(ticker)
    local msg = "Price of " .. ticker .. " " .. price .. "$"
    send_message(msg, chat_id)
end

function cmd.num_arguments()
    return 1
end

function cmd.help()
     return "/lprice <ticker>"
end

function cmd.instructions()
    return "Price command implemented in lua."
end

commands["/lprice"] = cmd