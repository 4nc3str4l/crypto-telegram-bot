#pragma once

#include <vector>
#include <string>
#include <cstdint>

#include <tgbot/tgbot.h>

struct Investor;

class Command 
{
public:

  Command(const std::string& command, const unsigned short numArguments,
   const TgBot::Bot& bot, const std::int64_t chatId);
  bool isNumArgmentsCorrect();
  void execute(const std::vector<std::string>& arguments, const Investor& caller);

protected:
  void send(const std::string& message);
  double getDouble();
  int getInteger();
  const std::string& getString();

  // Abstract functions
  virtual void sendInstructions() = 0;
  virtual const std::string& getDescription() = 0;
  virtual void commandLogic() = 0;
  void printError(const std::string& error);
  void printMsg(const std::string& msg);
  
protected:
  std::string m_command;
  TgBot::Bot* m_bot;
  std::int64_t m_chatId;
  unsigned short m_numArguments;
  unsigned short m_indexRead = 1;
  std::vector<std::string> m_arguments;
};
