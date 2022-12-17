local _player = {}

function _player.NewPlayer(x, y, sprite)
	local player = {}
		player.sprite = sprite
		player.w = 16
		player.h = 24
		player.collider = _collision.NewCollider(x, y, player.w, player.h, "player")
		player.status = {}
			player.status.jumpForce = (2 *(game.world.height /2))*4
			player.status.maxJumpForce = (2 *(game.world.height /2))*11
			player.status.speed = 200 -- Max Speed: 280
		player.camera = {}
			player.camera.x = -player.collider.x +_W
			player.camera.y = -player.collider.y +_H
		
	function player:Update(dt)
		self.collider:Update(dt)
		
		if lk.isDown("a") then
			self.collider.vx =-1
		elseif lk.isDown("d") then
			self.collider.vx = 1
		end
		
		if lk.isDown("space") and self.collider.isOnGround and self.status.jumpForce <= self.status.maxJumpForce then
			if self.collider.gravity -self.status.jumpForce > -self.status.maxJumpForce then
				self.collider.gravity = min(self.status.maxJumpForce, self.collider.gravity -self.status.jumpForce)
			else
				self.collider.isOnGround = false
			end
		elseif not self.collider.isOnGround or lk.isDown("s") and world:getTypeDirection(self.collider, self.collider.x, 
		self.collider.y +1) == "platform" and self.collider.isOnGround
		or not world:checkDirection(self.collider.x, self.collider.y +1, self.collider.w, self.collider.h) then
			self.collider.isOnGround = false
			self.collider.gravity = min(self.collider.gravity +game.gravity *dt, 400)
		elseif self.collider.gravity ~= 0 then
			self.collider.isOnGround = false
		end
		
		self.collider.x = clamp(0, floor(self.collider.x +(self.collider.vx *(self.status.speed)) *dt), 
		(game.world.limitx *game.world.width) +self.collider.w/2 +8)
		self.collider.y = clamp(0, floor(self.collider.y +self.collider.gravity *dt), 
		(game.world.limity *game.world.height) +self.collider.h/2)
		
		self.collider.vx = 0
	end
	
	function player:Draw()
		lg.push("all")
			if self.sprite then
				lg.draw(self.sprite, self.collider.x, self.collider.y)
			else
				lg.setColor(0, 1, 0)
				lg.rectangle("fill", self.collider.x, self.collider.y, self.collider.w, self.collider.h)
			end
		lg.pop()
	end
	
	function player:DrawHUD()
		inventory:DrawAll()
	end
	
	return player
end

return _player