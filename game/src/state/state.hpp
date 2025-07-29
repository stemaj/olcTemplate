#ifndef __STATE_HPP
#define __STATE_HPP

#include <olcTemplate/game/src/render/render.hpp>
#include <olcTemplate/game/input.hpp>
#include <optional>
#include <memory>

namespace stemaj {

class State
{
public:
  virtual ~State() = default;
  virtual std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) = 0;
  virtual Render* GetRender() = 0;

  virtual void setNext(std::unique_ptr<State> onNext) = 0;
  virtual void setAgain(std::unique_ptr<State> onAgain) = 0;

protected:
  std::unique_ptr<State> _onNext = nullptr;
  std::unique_ptr<State> _onAgain = nullptr;
};

} // namespace stemaj

#endif //__STATE_HPP