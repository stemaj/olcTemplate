-- kind:
--
-- IDLE = 0,
-- MOVERIGHT = 1,
-- MOVEUP = 2,
-- MOVELEFT = 3,
-- MOVEDOWN = 4

function GetSpriteSheetData()
	data:clear()

  local p = SpriteSheetData:new()
	p.kind = 0
	p.spriteWidth = 342
  p.spriteHeight = 476
  p.ox = 0.5
  p.oy = 0.9
  p.singlePics = { { 3,2 }, { 4,1 }, { 4,2 } }
  data:add(p)

  p = SpriteSheetData:new()
	p.kind = 1
	p.spriteWidth = 342
  p.spriteHeight = 476
  p.ox = 0.5
  p.oy = 0.9
  p.singlePics = { { 2,0 }, { 3,0 }, { 2,1 } }
  data:add(p)

  p = SpriteSheetData:new()
	p.kind = 2
	p.spriteWidth = 342
  p.spriteHeight = 476
  p.ox = 0.5
  p.oy = 0.9
  p.singlePics = { { 1,0 }, { 1,1 }, { 1,2 } }
  data:add(p)

  return data
end


  {
    x = 1
    y = 0
  }
  singlePicPos[1]
  {
    x = 1
    y = 1
  }
  singlePicPos[2]
  {
    x = 1
    y = 2
  }
}
animation[3]
{
  name = moveleft
  spriteWidth = 342
  spriteHeight = 476
  ox = 0.5
  oy = 0.9
  singlePics = 3
  singlePicPos[0]
  {
    x = 3
    y = 1
  }
  singlePicPos[1]
  {
    x = 4
    y = 0
  }
  singlePicPos[2]
  {
    x = 2
    y = 2
  }
}
animation[4]
{
  name = movedown
  spriteWidth = 342
  spriteHeight = 476
  ox = 0.5
  oy = 0.9
  singlePics = 3
  singlePicPos[0]
  {
    x = 0
    y = 0
  }
  singlePicPos[1]
  {
    x = 0
    y = 1
  }
  singlePicPos[2]
  {
    x = 0
    y = 2
  }
}





-- Stage 7: New Stuff
function CreatePlayer1() 

	io.write("[LUA S7] CreatePlayer1() called\n")

	local p = Player:new()

	p.Name = "Saladin"
	p.Family = "Sheffield"
	p.Title = "King"
	p.Level = 35 

	return p
end


// Step 7) Map C++ Types to Lua "Types"
	lua.new_usertype<Player>("Player",
		sol::constructors<Player()>(),
		"Name", sol::property(&Player::name),
		"Family", sol::property(&Player::family),
		"Title", sol::property(&Player::title),
		"Level", sol::property(&Player::level));


	Player player1 = lua["CreatePlayer1"]();

	std::cout << "[CPP S7] player1 = " << player1.title << " " << player1.name << " of "
		<< player1.family << " [Lvl: " << player1.level << "]\n";




-- Stage 8: Create X players
function CreatePlayer2(n)

	io.write("[LUA S8] CreatePlayer2() called\n")

	allPlayers:clear()

	for i=1,n do
		allPlayers:add(CreatePlayer1())
	end
end


// Step 8) Use C++ Containers in Lua
	std::vector<Player> vecPlayers;
	lua["allPlayers"] = &vecPlayers;

	std::cout << "[CPP S9] vecPlayers.size() = " << vecPlayers.size() << "\n";
	lua["CreatePlayer2"](13);
	std::cout << "[CPP S9] vecPlayers.size() = " << vecPlayers.size() << "\n";

	for (const auto& p : vecPlayers)
		std::cout << "[CPP S9] player1 = " << p.title << " " << p.name << " of "
		<< p.family << " [Lvl: " << p.level << "]\n";


