lg = love.graphics
lk = love.keyboard
lt = love.touch
lp = love.physics
lm = love.mouse

W, H = lg.getDimensions() --Screen Dimensions
_W, _H = W/2, H/2 --Half Of Screen Dimensions

format = string.format
floor = math.floor
cos, sin = math.cos, math.sin
atan2 = math.atan2
sqrt = math.sqrt
abs = math.abs
max, min = math.max, math.min
random = math.random
getPercent = function(n, max, div)
	--[[
	n = number to get percentage
	max = max number to get percentage
	div = number to divide to get a percentage
	--]]
	
	assert(type(n) == "number" and type(max) == "number" and type(div) == "number", "Number Expected!!!")
	return (n/max)*div
end
Camera = function(tox, toy, _function)
	lg.push("all")
		lg.translate(-tox, -toy)
		_function()
	lg.pop()
end
getDistance = function(x1, y1, x2, y2)
	return sqrt(((x1 -x2)^2) +((y1 -y2)^2))
end
getDistanceX = function(x1, x2)
	return sqrt((x1 -x2)^2)
end
getDistanceY = function(y1, y2)
	return sqrt((y1 -y2)^2)
end
clamp = function(low, n, high)
	return min(max(low, n), high)
end

function love.load()
	math.randomseed(os.time())
	
	game = {}
		game.gravity = 600
		game.state = "game"
		game.pause = false
		game.time = 0
		game.lastMouse = {} -- Last Info of mouse
			game.lastMouse.x = 0
			game.lastMouse.y = 0
		game.osTime = os.time()/math.random(os.time()) -- For Random Noise
		game.seed = love.math.getRandomSeed()
		game.version = "0.9.20 I Feel Good"
		game.debug = {}
			game.debug.active = false
			game.debug.lastPressedKey = {}
			game.debug.OS = love.system.getOS()
		game.world = {}
			game.world.width = 32
			game.world.height = 32
			game.world.limitx = 48
			game.world.limity = 48
		
	Font = lg.setNewFont("andybold.ttf", 14)
	
	_inventory = require("libs/system/inventory")
	_collision = require("libs/system/collision")
	_map = require("libs/system/map")
	_button = require("libs/system/button")
	_player = require("libs/player")
	_cursor = require("libs/system/cursor")
	_debug = require("libs/system/debug")
	
	inventory = _inventory.NewInventory()
	player = _player.NewPlayer((game.world.limitx/2) *game.world.width, 16 *game.world.height)
	world = _map.NewWorld(game.world.limitx, game.world.limity, game.world.width, game.world.height)
	cursor = _cursor.NewCursor()
	
	time = 0
end
	
function love.update(dt)
	if not game.pause then
		game.time = game.time +dt
		time = time +1
		
		player:Update(dt)
		world:Update()
		cursor:Update()
		inventory:Update()
		
		_debug.Update()
	end
	
	game.pause = love.window.isMinimized()
	
	 
	if #game.debug.lastPressedKey > 3 or time%60 == 59 then
		table.remove(game.debug.lastPressedKey, 1)
	end
end
	
function love.draw()
	Camera(player.camera.x, player.camera.y, function()
		player:Draw()
		world:Draw()
		player.collider:Draw()
		cursor:Draw()
		_debug.DrawCamera()
	end)
	
	if not game.pause then
		player:DrawHUD()
		
		_debug.Draw()
	end
end

function love.mousepressed(x, y, id)
	if id == 1 then
		inventory.click = true
		game.lastMouse.x = x
		game.lastMouse.y = y
	end
end

function love.mousereleased(x, y, id)
	if id == 1 then
		inventory.released = true
	end
end

function love.keyreleased(key)
	
end

function love.keypressed(key)
	if key == "escape" then
		love.event.quit()
	elseif key == "e" then
		inventory.active = not inventory.active
		inventory.selectedSlot = inventory.lastHotbarSlot
	end
	
	if type(tonumber(key)) == "number" and key ~= "0" then
		inventory.selectedSlot = (1 -1) *40 +tonumber(key)
	end
	
	table.insert(game.debug.lastPressedKey, key)
end