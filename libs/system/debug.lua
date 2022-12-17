local _debug = {}

function _debug.Update()
	if game.debug.lastPressedKey[#game.debug.lastPressedKey -1] == "return" 
	and game.debug.lastPressedKey[#game.debug.lastPressedKey] == "\\" then
		game.debug.active = not game.debug.active
		game.debug.lastPressedKey = {}
	end

	_debug.debugs = {
	format("Seed: %s", game.seed),
	format("Last Key Pressed: %s", game.debug.lastPressedKey[#game.debug.lastPressedKey]),
	format("OS/Operation System: %s", game.debug.OS),
	format("CURSORX: %.2f, CURSORY: %.2f", cursor.x, cursor.y),
	format("Player Gravity: %.2f", player.collider.gravity),
	format("Player On Ground: %s", player.collider.isOnGround),
	format("Mouse Slot Index: %i", inventory:getIndex(lm.getX(), lm.getY())),
	format("Index Of Selected Item: %i", inventory.selectedItem),
	format("Index Of Selected Slot: %i", inventory.selectedSlot),
	format("OS Time: %.2f", game.osTime),
	format("PLAYERX: %.2f, PLAYERY: %.2f", player.collider.x, player.collider.y),
	format("CAMERAX: %.2f, CAMERAY: %.2f", player.camera.x, player.camera.y),
	format("FPS: %i", love.timer.getFPS()),
	format("Time: %.2f", game.time),
	format("Version: %s", game.version),
	} 
end

function _debug.Draw()
	if game.debug.active then
		for i = #_debug.debugs, 1, -1 do
			local string = _debug.debugs[i] 
			lg.printf(string, 0, H -(i *14), W, "left")
		end
	end
end

function _debug.DrawCamera() -- Debug Drawed Inside The Camera Function
	if game.debug.active then
		
	end
end

return _debug