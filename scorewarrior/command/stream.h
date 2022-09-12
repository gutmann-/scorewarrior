#ifndef SCOREWARRIOR_COMMAND_STREAM_H_
#define SCOREWARRIOR_COMMAND_STREAM_H_

#include "scorewarrior/command/command.h"

#include <memory>

namespace scorewarrior::command {

class Factory;

/**
 * Поток из которого можно читать команды.
 * Похож на std::istream, но только для команд.
 */
class Stream {
public:
  Stream() : factory_(nullptr) {}
  virtual ~Stream() = default;

  /**
   * Извлечь следующую из потока команду
   * @return команда или null, если поток кончился
   */
  virtual std::unique_ptr<Command> Pull() = 0;
  /**
   * Кончился ли поток?
   * @return true если поток закончился и false иначе
   */
  [[nodiscard]] virtual bool eof() const = 0;

  /**
   * Использовать фабрику @param factory для создания команд
   * @param factory фабрика команд
   */
  void UseFactory(Factory* factory) { factory_ = factory; }
protected:
  Factory* factory() { return factory_; }
private:
  Factory* factory_;
};

} // scorewarrior::command

#endif // SCOREWARRIOR_COMMAND_STREAM_H_