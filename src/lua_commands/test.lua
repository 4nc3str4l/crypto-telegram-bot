-- Command Logic

local price_cmd = {}

function price_cmd.logic(arguments, chat_id)
    send_message("Hello World!!", chat_id)
end

function price_cmd.num_arguments()
    return 0
end

function price_cmd.help()
     return "/test"
end

commands["/test"] = price_cmd