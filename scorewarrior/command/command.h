#ifndef SCOREWARRIOR_COMMAND_COMMAND_H_
#define SCOREWARRIOR_COMMAND_COMMAND_H_

#include <cstdint>
#include <functional>
#include <memory>

namespace scorewarrior::command {

/**
 * Команда.
 */
class Command {
public:
  Command();
  Command(const Command&) = delete;
  virtual ~Command() = default;

  Command& operator =(const Command&) = delete;

  /**
   * Делает одну итерацию команды на момент времени @param current_time
   * @param current_time текущее время в тиках.
   */
  void operator()(uint32_t current_time);

  /**
   * Завершено ли исполнение данной команды (т.е. дяльнейшие вызовы
   * operator()(uint32_t) не приведут ни к каким действиям)
   * @return true если команда завершена и false иначе
   */
  [[nodiscard]] bool is_done() const { return is_done_; };
  /**
   * Время, с которой команда была вызвана в прошлый раз.
   * @return время в тиках.
   */
  [[nodiscard]] uint32_t previous_call_tick() const { return last_known_tick_; }

  /**
   * Установить оработчик, который будет вызван в момент первого исполнения команды.
   * @param on_begin обработчик
   */
  void OnBegin(const std::function<void(Command*)>& on_begin) { on_begin_ = on_begin; }
  /**
   * Установить обработчик, который будет вызван в момент сразу после завершения команды.
   * @param on_done
   */
  void OnDone(const std::function<void(Command*)>& on_done) { on_done_ = on_done; }

  /**
   * Установить команду, которая будет следовать непосредственно за этой.
   * @param then команда
   */
  void Then(std::unique_ptr<Command> then) { then_ = std::move(then); }
  /**
   * Получить следующую в цепочке команду.
   * @return Следующая в цепочке команда. Если таковой нет, будет возвращён nullptr
   */
  std::unique_ptr<Command> Then() { return std::move(then_); }
private:
  virtual void Init(uint32_t current_time) {}
  virtual bool Execute(uint32_t current_time) = 0;

  void CallOnBegin() { if (on_begin_) on_begin_(this); }
  void CallOnDone() { if (on_done_) on_done_(this); }

  uint32_t last_known_tick_;
  bool called_once_;
  bool is_done_;

  std::function<void(Command*)> on_begin_;
  std::function<void(Command*)> on_done_;

  std::unique_ptr<Command> then_;
};

} // namespace scorewarrior::command

#endif // SCOREWARRIOR_COMMAND_COMMAND_H_
