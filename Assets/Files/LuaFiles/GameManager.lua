function Start(pointer)
	AddState(pointer, "test1", "Scene1.lua")
	AddState(pointer, "test2", "Scene2.lua")

	AddFile(pointer, "Texture", "Board.png", "board", 1)
	AddFile(pointer, "Texture", "Coin.png", "coin", 4)

	FirstState(pointer, "test1")
end