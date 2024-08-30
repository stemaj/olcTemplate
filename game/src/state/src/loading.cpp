#include <olcTemplate/game/src/render/loadingRender.hpp>
#include <olcTemplate/game/src/state/loading.hpp>
#include <olcTemplate/game/src/render/logoRender.hpp>
#include <olcTemplate/game/src/state/logoState.hpp>
#include <olcTemplate/game/assets.hpp>
#include <olcTemplate/game/animation.hpp>
#include <olcTemplate/game/fonts.hpp>
#include <optional>

using namespace stemaj;

Loading::Loading() : _render(std::make_unique<LoadingRender>())
{
}

Render* Loading::GetRender()
{
  return _render.get();
}

std::optional<std::unique_ptr<State>> Loading::Update(const Input& input, float fElapsedTime)
{
  if (_firstStart && !_loadingStarted)
  {
    // give it a little bit to render the loading screen before loading asset stuff
    _firstStart = false;
    return std::nullopt;
  }

  if (!_loadingStarted)
  {
    AS.Load();
    AN.Load();
    FT.Load();
    _loadingStarted = true;
  }

  if (AS.Loaded && AN.Loaded && FT.Loaded)
  {
    return std::make_unique<LogoState>();
  }
  return std::nullopt;
}
