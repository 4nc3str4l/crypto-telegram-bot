-- Command Logic
function logic(arguments, chat_id)
    print(arguments)
    local msg = "Price of " .. "EGLD" .. " " .. check_price("EGLD") .. "$"
    send_message(msg, chat_id)
end

function num_arguments()
    return 2
end

function send_help()
    
end