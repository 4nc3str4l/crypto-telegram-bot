local cmd = {}

function cmd.logic(arguments, chat_id)
    send_message("Hello World!!", chat_id)
end

function cmd.num_arguments()
    return 0
end

function cmd.help()
     return "/test"
end

function cmd.instructions()
    return "Test extension command."
end

commands["/test"] = cmd