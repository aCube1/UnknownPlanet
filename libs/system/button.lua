local _button = {}

function _button.NewButton(x, y, w, h, _function, game_state, label)
	local button = {}
		button.x = x
		button.y = y
		button.w = w
		button.h = h
		button.label = label
		button.state = game.state or "game" --State to Draw Button
		button.mode = "fill"
		button.f = _function or function() end
		if label then
			button.w = Font:getWidth(label)
			button.x = button.x -(button.w/2) 
		end
	
	function button:Update(x, y, button)
		if x and y and button then
			if x +1 > self.x and x < self.x +self.w and y +1 > self.y and y < self.y +self.h and button == 1 then
				return self.f()
			end
		else
			local x, y = lm.getPosition()
			if x +1 > self.x and x < self.x +self.w and y +1 > self.y and y < self.y +self.h
			and lm.isDown(1) then
				return self.f()
			end
		end
	end
	
	function button:Draw()
		local x, y = lm.getPosition()
		
		if x +1 > self.x and x < self.x +self.w and y +1 > self.y and y < self.y +self.h then
			self.mode = "line"
		end
		
		if self.label then
			lg.push("all")
				lg.setColor(0.3, 0.3, 0.3)
				lg.rectangle(self.mode, self.x, self.y, self.w, self.h)
			lg.pop()
			lg.printf(self.label, self.x, self.y, self.w, "center")
		else
			lg.push("all")
				lg.setColor(0.3, 0.3, 0.3)
				lg.rectangle(self.mode, self.x, self.y, self.w, self.h)
			lg.pop()
		end
		self.mode = "fill"
	end
	
	return button
end

return _button