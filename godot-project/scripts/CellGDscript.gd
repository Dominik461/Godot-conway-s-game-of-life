extends Button

var is_alive = false:
	get:
		return is_alive
	set(value):
		is_alive = value
		update_visuals()

func _ready():
	update_visuals()
	connect("pressed", self._on_pressed.bind())

func _on_pressed():
	print("Cell script:")
	print(is_alive)
	is_alive = !is_alive
	print(is_alive)
	update_visuals()



func update_visuals():
	#print("Alive Status for update_visuals: " + str(is_alive))
	if is_alive:
		self.text = ""
		self.modulate = Color(0, 255, 0)
	else:
		self.text = ""
		self.modulate = Color(255, 0, 255)
