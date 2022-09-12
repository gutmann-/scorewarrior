#ifndef SCOREWARRIOR_COMMAND_EXECUTOR_H_
#define SCOREWARRIOR_COMMAND_EXECUTOR_H_

#include "scorewarrior/command/command.h"

#include <memory>
#include <vector>

namespace scorewarrior::command {

/**
 * @brief Исполнитель игровых комманд.
 * Как только команда выполнена (Command::is_done() == true), она удаляется из очереди.
 */
class Executor {
public:
  Executor();

  /**
   * @brief Исполняет следующую незавершённую команду и переходит к следующей.
   * @param current_time текущее время в тиках.
   */
  void operator()(uint32_t current_time);

  /**
   * @brief Добавляет команду в очередь комманд.
   * @param command указатель на команду, в случае добавления nullptr не происходит ничего.
   */
  void PushCommand(std::unique_ptr<Command> command);

  /**
   * Принудительно возвращается в начало очереди команд. Далее выполнение
   * происходит по тем же правилам начиная с первой в очереди.
   */
  void Rewind();

  /**
   * @brief Все ли команды завершены?
   * @return true?, если завершены все команды и false иначе.
   */
  [[nodiscard]] bool all_is_done() const;
  /**
   * Количество незавершённых команд в очереди.
   * @return
   */
  [[nodiscard]] size_t number_of_not_finished_commands() const;
private:
  using CommandVector = std::vector<std::unique_ptr<Command>>;
  using CommandIterator = CommandVector::iterator;

  /**
   * Очищает очередь от выполненных команд. Указатель следующей команды при
   * этом остаётся без изменений. Не следует вызывать эту функцию без последующего пересчёта
   * позиции указателя.
   */
  void CleanFinishedCommands();
  /**
   * Выполняет команду и если она завершена, берёт следующую команду в её цепочке
   * и выполняет и так до тех пор пока очередная команда завершается.
   *
   * @param command команда
   * @param current_time текущее время в тиках
   * @return команда
   */
  std::unique_ptr<Command> Execute(std::unique_ptr<Command> command, uint32_t current_time);

  /**
   * Возвращает следующщую команду для исполнения.
   * @return следующая команда для исполнения.
   */
  CommandIterator NextCommand();
  /**
   * Возвращает следуюущую не завершённую команду.
   * @return следующая не завершённая команда для исполнения
   */
  CommandIterator NextNotDoneCommand();
  /**
   * Конец очереди команд (работает аналогично вызову end() контейнеров из stl).
   * @return конец очереди команд.
   */
  CommandIterator End() { return commands_.end(); }

  std::vector<std::unique_ptr<Command>> commands_; // очередь команд
  off_t next_command_index_; // индекс следующей команды на попытку исполнения

  size_t number_of_not_finished_commands_; // количество ещё не завершённых команд
};

} // namespace scorewarrior::command

#endif // SCOREWARRIOR_COMMAND_EXECUTOR_H_
