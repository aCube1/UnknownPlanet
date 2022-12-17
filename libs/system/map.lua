local _map = {}

function _map.NewWorld(limitx, limity, width, height, _type)
	local world = {}
		world.limitx = limitx
		world.limity = limity
		world.width = width
		world.height = height
		world.type = _type or "player"
		world.entity = {}
	
	assert(limitx > 16 or limity > 16, "LIMIT IS LOW")
	assert(limitx < 500 or limity < 500, "YOU TRYING BREAK THE GAME?")
	
	for i = 0, limitx do
		for j = 0, limity do
			local noise = love.math.noise(i/16 +game.osTime, j/16 +game.osTime)
			
			if j == limity or (j > 16 and noise >= 0.20) then
				table.insert(world.entity, _collision.NewCollider(i *width, j *height, width, height))
			end
		end
	end
	
	function world:RemoveEntity(x, y)
		for i, collider in pairs(self.entity) do
			if x == collider.x and y == collider.y then
				table.remove(self.entity, i)
			end
		end
	end
	
	function world:AddEntity(x, y, width, height, _type)
		for i, collider in pairs(self.entity) do
			if x == collider.x and y == collider.y then
				return nil
			end
		end
		table.insert(self.entity, _collision.NewCollider(x, y, width, height, _type))
	end
	
	function world:Draw()
		for i, collider in pairs(self.entity) do
			if collider.x > (player.camera.x) -(width) and collider.x < player.camera.x +W +width and
			   collider.y > (player.camera.y) -(height) and collider.y < player.camera.y +H +height then
				lg.setColor(60/255, 40/255, 40/255)
				collider:Draw("fill")
			end
		end
	end
	
	function world:getTypeDirection(item, x, y) -- get the type of item on direction
		for i, collider in pairs(self.entity) do
			if x +item.w > collider.x and x < collider.x +collider.w and y +item.h > collider.y and y < collider.y +collider.h then
				return collider.type
			end
		end
		
		return ""
	end
	
	function world:checkCollision(x, y, w, h, x2, y2, w2, h2)
		return x +w > x2 and x < x2 +w2 and y +h > y2 and y < y2 +h2
	end
	
	function world:checkDirection(x, y, w, h) -- get item of the direction
		for i, collider in pairs(self.entity) do
			if x +w > collider.x and x < collider.x +collider.w and y +h > collider.y and y < collider.y +collider.h then
				return true
			end
		end
		
		return false
	end
	
	function world:Update()
		for i, collider in pairs(self.entity) do
			local distance = getDistance(player.collider.x +(player.w/2), player.collider.y +(player.h/2), collider.x +(collider.w/2), collider.y +(collider.h/2))
				
			if distance < 2 *26 then
				player.collider:ResolveCollision(collider)
			end
			
			-- CAMERA
			player.camera.x = clamp(0, floor(player.collider.x -_W), (game.world.limitx *game.world.width) -W +32)
			player.camera.y = clamp(0, floor(player.collider.y -_H), (game.world.limity *game.world.height) -H)
			-- END
		end
	end
	
	return world
end

return _map