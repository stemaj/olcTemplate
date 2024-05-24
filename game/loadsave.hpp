#ifndef __LOADSAVE_HPP
#define __LOADSAVE_HPP

namespace stemaj {

class LoadSave
{
public:
	static LoadSave& get();
	LoadSave(LoadSave const&) = delete;
	void operator=(LoadSave const&) = delete;
private:
  LoadSave() = default;
  virtual ~LoadSave();
};

#define LS LoadSave::get()

} // stemaj

#endif // __LOADSAVE_HPP