function SetScene(pointer)
	AddGameObject(pointer, "player", 100, 100);
	AddComponent(pointer, "player", "Image", "Board", true, "board")
	AddComponent(pointer, "player", "Animation", "Coin", true, "coin");
	--AddComponent(pointer, "player", "Collider", "Col1", true, true, true, 16)
	--AddComponent(pointer, "player", "Collider", "Col1", true, true, false, 32, 16)
	AddGameObject(pointer, "enemy", 200, 200);
	AddComponent(pointer, "enemy", "Circle", "c", true, 10)
	AddComponent(pointer, "enemy", "Square", "c", true, 10, 20)

end