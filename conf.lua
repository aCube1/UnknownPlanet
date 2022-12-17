function love.conf(c)

	c.identity = "unknownplanet"
	c.version = "11.3"
	c.console = true
	
	c.window.title = "Unknown Planet"
	c.window.icon = "icon.png"
	c.window.width = 800
	c.window.height = 600
	c.window.bordeless = false
	c.window.resizable = true
	
	c.modules.audio = false
	c.modules.data = false
	c.modules.event = true
	c.modules.font = true
	c.modules.graphics = true
	c.modules.image = true
	c.modules.joystick = false
	c.modules.keyboard = true
	c.modules.math = true
	c.modules.mouse = true
	c.modules.physics = true
	c.modules.sound = false
	c.modules.system = true
	c.modules.thread = false
	c.modules.timer = true
	c.modules.touch = true
	c.modules.video = true
	c.modules.window = true
	
end