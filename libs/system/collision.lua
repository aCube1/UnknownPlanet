local  _collision = {}

function _collision.NewCollider(x, y, w, h, _type)
	local collider = {}
		collider.x = x
		collider.y = y
		collider.vx = 0
		collider.vy = 0
		collider.w = w
		collider.h = h
		collider.isOnGround = false
		collider.type = _type or "wall"
		collider.gravity = 0
		collider.last = {}
			collider.last.x = x
			collider.last.y = y
	
	function collider:CheckCollision(e)
		return self.x +self.w > e.x and self.x < e.x +e.w
		   and self.y +self.h > e.y and self.y < e.y +e.h
	end
	
	function collider:VerticalAlign(e)
		return self.last.y < e.y +e.h and self.last.y +self.h > e.y 
	end
	
	function collider:HorizontalAlign(e)
		return self.last.x < e.x +e.w and self.last.x +self.w > e.x 
	end
	
	function collider:Update(dt)
		self.last.x = self.x
		self.last.y = self.y
	end
	
	function collider:collide(e, direction)
		if direction == "left" then
			local pushback = (e.x +e.w) -self.x
			self.x = self.x +pushback
			self.vx = 0
		elseif direction == "right" then
			local pushback = (self.x +self.w) -e.x
			self.x = self.x -pushback
			self.vx = 0
		elseif direction == "bottom" then
			local pushback = (self.y +self.h) -e.y
			self.y = self.y -pushback
			self.vy = 0
			self.gravity = 0
		elseif direction == "top" then
			local pushback = (e.y +e.h) -self.y
			self.y = self.y +pushback
			self.vy = 0
			self.gravity = 0
			self.isOnGround = false
		end
	end
	
	function collider:checkResolve(e, direction)
		if direction == "bottom" then
			self.isOnGround = true
		end
		
		if self.type == "platform" and (direction ~= "top" or lk.isDown("s")) then
			self.isOnGround = false
			return false
		end
		
		return true
	end
	
	function collider:ResolveCollision(e)
		if self:CheckCollision(e) then
			if self:VerticalAlign(e) then
				if self.x +(self.w/2) < e.x +(e.w/2) then
					local a = self:checkResolve(e, "right")
					local b = e:checkResolve(self, "left")
					
					if a and b then
						self:collide(e, "right")
					end
				else
					local a = self:checkResolve(e, "left")
					local b = e:checkResolve(self, "right")
					
					if a and b then
						self:collide(e, "left")
					end
				end
			elseif self:HorizontalAlign(e) then
				if self.y +(self.h/2) < e.y +(e.h/2) then
					local a = self:checkResolve(e, "bottom")
					local b = e:checkResolve(self, "top")
					
					if a and b then
						self:collide(e, "bottom")
					end
				else
					local a = self:checkResolve(e, "top")
					local b = e:checkResolve(self, "bottom")
					
					if a and b then
						self:collide(e, "top")
					end
				end
			end
		end
	end
	
	function collider:Draw(mode)
		lg.rectangle(mode or "line", self.x, self.y, self.w, self.h)
	end
		
	return collider
end

return _collision