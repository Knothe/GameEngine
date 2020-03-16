moveX = 0
moveY = 0

lastX = 0
lastY = 0

function Input(key)

	if key == 119 then moveY = -2 end
	if key == 97 then moveX = -5 end
	if key == 115 then moveY = 2 end
	if key == 100 then moveX = 5 end
end

function Update(pointer)

	Translate(pointer,moveX, moveY);
	currentX = GetX(pointer);
	currentY = GetY(pointer);

	lastX = moveX
	lastY = moveY

	moveX = 0
	moveY = 0
end

function CollisionEnter(pointer1, pointer2)
	Translate(pointer1, -lastX, -lastY)
end