#ifndef __PALETTE_HPP
#define __PALETTE_HPP

namespace stemaj {

class Palette
{
public:
	static Palette& get();
	Palette(Palette const&) = delete;
	void operator=(Palette const&) = delete;

private:
  Palette();
  virtual ~Palette();
};

#define PA Palette::get()

} // stemaj

#endif // __PALETTE_HPP
