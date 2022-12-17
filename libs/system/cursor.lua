local _cursor = {}

function _cursor.NewCursor()
	local cursor = {}
		cursor.x = player.collider.x
		cursor.y = player.collider.y
		cursor.delay = 0
		cursor.maxDelay = 10
		
	function cursor:Update()
		self.distanceX = getDistanceX(floor((lm.getX() +player.camera.x)/32) *32, player.collider.x +(player.collider.w/2))
		self.distanceY = getDistanceY(floor((lm.getY() +player.camera.y)/32) *32, player.collider.y +(player.collider.h/2))
		
		if lm.isDown(1) and self.distanceX < 4 *game.world.width and self.distanceY < 4 *game.world.height then
			self.delay = self.delay -1
			if inventory.slots[inventory.selectedSlot].info.name and not world:checkDirection(floor((lm.getX() +player.camera.x)/game.world.width) *game.world.width, floor((lm.getY() +player.camera.y)/game.world.height) *game.world.height, 1, 1)
			and not world:checkCollision(player.collider.x, player.collider.y, player.collider.w, player.collider.h,
			floor((lm.getX() +player.camera.x)/game.world.width) *game.world.width, floor((lm.getY() +player.camera.y)/game.world.height) *game.world.height, 
			game.world.width, game.world.height) then
				if self.delay <= 0 then
					self.y = floor((lm.getY() +player.camera.y)/game.world.height)
					self.x = floor((lm.getX() +player.camera.x)/game.world.width)
					
					if inventory.slots[inventory.selectedSlot].info.type == "placeable" then
						world:AddEntity(self.x *game.world.width, self.y *game.world.height, game.world.width, 
						inventory.slots[inventory.selectedSlot].info.height, inventory.slots[inventory.selectedSlot].info.subType)
					end
								
					self.delay = self.maxDelay
				end
			elseif inventory.slots[inventory.selectedSlot].info.type == "pickaxe" then
				if self.delay <= 0 then
					self.y = floor((lm.getY() +player.camera.y)/game.world.height)
					self.x = floor((lm.getX() +player.camera.x)/game.world.width)
					
					world:RemoveEntity(self.x *game.world.width, self.y *game.world.height)
					self.delay = self.maxDelay
				end
			end
		else
			self.delay = self.maxDelay
		end
	end
	
	function cursor:Draw()
		
	end
		
	return cursor
end

return _cursor