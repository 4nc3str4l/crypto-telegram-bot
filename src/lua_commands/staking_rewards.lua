local cmd = {}

-- Computes the staking rewards for an asset given the amount a ticker and the apy
function cmd.logic(arguments, chat_id)
    amount = to_double(arguments[2])
    ticker = arguments[3]
    apy = to_double(arguments[4])
    price = check_price(ticker)
    
    total = amount * price 
    year_yield = total * apy / 100
    day = year_yield / 365
    month = year_yield / 12
    week = day * 7
    hour = day / 24

    -- TODO: I need to get the fiat symbol
    msg = "Return year=" .. year_yield .. " month=" .. month .. "$ week=" .. week .. "$ day =" .. day .. "$ hour=" .. hour .. "$."
    send_message(msg, chat_id)
end

function cmd.num_arguments()
    return 3
end

function cmd.help()
     return "/srewards <amount> <ticker> <apy>"
end

function cmd.instructions()
    return "Computes stacking rewards based on a quantity and the apy."
end

commands["/srewards"] = cmd