local _inventory = {}

function _inventory.NewInventory()
	local inventory = {}
		inventory.slots = {}
		inventory.selectedSlot = 1
		inventory.lastSelectedSlot = 1
		inventory.lastHotbarSlot = 1
		inventory.selectedItem = 0
		inventory.active = false
		inventory.click = false
		inventory.released = false
		inventory.selectedSlotIndex = {}
		
	do
		for i = 1, 5 do
			for ii = 1, 9 do
				local tabl = {
				index = (i -1) *44 +ii,
				x = (ii -0.5) *44,
				y = (i -0.5) *44,
				info = {},
				}
				
				if tabl.index == (1 -1) *44 +1 then
					tabl.info.name = "pickaxe"
					tabl.info.type = "pickaxe"
				elseif tabl.index == (1 -1) *44 +2 then
					tabl.info.name = "wall"
					tabl.info.type = "placeable"
					tabl.info.subType = "wall"
					tabl.info.height = 32
				elseif tabl.index == (1 -1) *44 +3 then
					tabl.info.name = "platform"
					tabl.info.type = "placeable"
					tabl.info.subType = "platform"
					tabl.info.height = 8
				end
			
				table.insert(inventory.slots, (i -1) *44 +ii, tabl)
			end
		end
	end
	
	function inventory:checkPosition(x, y, x2, y2, w2, h2)
		return x +1 > x2 and x < x2 +w2 and y +1 > y2 and y < y2 +h2
	end
	
	function inventory:getIndex(x, y, x2, y2)
		for i = 1, 5 do
			for ii = 1, 9 do
				local slot = self.slots[(i -1) *44 +ii]
				if x +1 > (ii -0.5) *44 and x < ((ii -0.5) *44) +44 and y +1 > (i -0.5) *44 and y < ((i -0.5) *44) +44 then
					if slot.index > (1 -1) *44 +9 and not self.active then
						return 0
					else
						return slot.index
					end
				end
			end
		end
		
		return 0
	end
	
	function inventory:SelectItem(sx, sy, slot)
		if lm.isDown(1) and slot.info.name then
			if self:checkPosition(lm.getX(), lm.getY(), sx, sy, 44, 44) and self.selectedItem == 0
			and self:getIndex(lm.getX(), lm.getY()) ~= 0 and self:checkPosition(game.lastMouse.x, game.lastMouse.y, sx, sy, 44, 44) then
				self.selectedItem = self:getIndex(lm.getX(), lm.getY())
			end
				
			if self.selectedItem == slot.index then
				self.lastSelectedSlot = slot.index
				sx, sy = lm.getPosition()
			end
		else
			self:MoveItem()
		end
		
		return sx, sy
	end
	
	function inventory:MoveItem()
		if self.released and self.selectedItem ~= 0 and self:getIndex(lm.getX(), lm.getY()) ~= 0 then
			self.slots[self.selectedItem].info, self.slots[self:getIndex(lm.getX(), lm.getY())].info = 
			self.slots[self:getIndex(lm.getX(), lm.getY())].info, self.slots[self.selectedItem].info
			if self.selectedSlot <= (1 -1) *44 +9 and not self.active then
				self.lastHotbarSlot = self:getIndex(lm.getX(), lm.getY())
			else
				self.lastSelectedSlot = self:getIndex(lm.getX(), lm.getY())
			end
		end
	end
	
	function inventory:Update()
		for i = 1, 5 do
			for ii = 1, 9 do
				local slot = self.slots[(i -1) *44 +ii]
				local x, y = (ii -0.5) *44, (i -0.5) *44
				
				if self.click and self.selectedSlot <= (1 -1) *44 +9 and not self.active and self:getIndex(lm.getX(), lm.getY()) ~= 0 then
					self.lastHotbarSlot = self:getIndex(lm.getX(), lm.getY())
				elseif self.click and self:getIndex(lm.getX(), lm.getY()) ~= 0 then
					self.lastSelectedSlot = self:getIndex(lm.getX(), lm.getY())
				end
				
				slot.x, slot.y = self:SelectItem(x, y, slot)
				
				if lm.isDown(1) and self:getIndex(lm.getX(), lm.getY()) ~= 0 then
					if self.active then
						self.selectedSlot = self:getIndex(lm.getX(), lm.getY())
					elseif self:getIndex(lm.getX(), lm.getY()) <= (1 -1) *44 +9 then
						self.selectedSlot = self:getIndex(lm.getX(), lm.getY())
					end
				elseif self:getIndex(lm.getX(), lm.getY()) ~= 0 then
					if self.release then
						self.lastSelectedSlot = self:getIndex(lm.getX(), lm.getY())
					end
					
					if self.selectedSlot <= (1 -1) *44 +9 and not self.active then
						self.selectedSlot = self.lastHotbarSlot
					elseif self.click then
						self.selectedSlot = self.lastSelectedSlot
					end
				elseif self.selectedItem ~= 0 then
					self.selectedSlot = self.selectedItem
				end
				
				if self.selectedSlot == 0 then
					self.selectedSlot = self.lastSelectedSlot
				end
			end
		end
		
		if self.released then
			self.selectedItem = 0
		end
		
		self.released = false
		self.click = false
	end
	
	function inventory:Draw(_function)
		for i = 1, 5 do
			for ii = 1, 9 do
				local slot = self.slots[(i -1) *44 +ii]
				if _function(slot, ii, i) then
					return nil
				end
			end
		end
	end
	
	function inventory:DrawAll()
		self:Draw(function(slot, ii, i)
			local x, y = (ii -0.5) *44, (i -0.5) *44
					
			lg.push("all")
				if self.selectedSlot == slot.index then
					lg.setColor(0, 0, 0.5)
				else
					lg.setColor(0, 0, 0.3)
				end
						
				lg.rectangle("fill", x, y, 44, 44)
			lg.pop()
			
			if not self.active and slot.index == (1 -1) *44 +9 then
				return true
			end
		end)
		
		self:Draw(function(slot)
			if slot.info.sprite then
				lg.draw(slot.info.sprite, slot.x, slot.y)
			else
				lg.printf(slot.info.name or "", slot.x, slot.y, 44, "center")
			end
					
			if not self.active and slot.index == (1 -1) *44 +9 then
				return true
			end
		end)
	end
	
	return inventory
end

return _inventory