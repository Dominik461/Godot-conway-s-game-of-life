extends Node2D

@export var grid_size: Vector2i = Vector2i(40, 40)
@export var cell_size: Vector2i = Vector2i(10, 10)
@export var tick_rate: float = 0.1  # Time in seconds between each tick

var cells = []

func _ready():
	$TickTimer.stop()
	var grid_container = $GridContainer
	grid_container.columns = grid_size.x
	grid_container.custom_minimum_size = grid_size * cell_size

	for y in range(grid_size.y):
		var row = []
		for x in range(grid_size.x):
			var cell = load("res://scenes/sce_cellGdScript.tscn.tscn").instantiate()
			cell.custom_minimum_size = cell_size
			grid_container.add_child(cell)
			row.append(cell)
		cells.append(row)

	$StartButton.connect("pressed", self._on_start_pressed.bind())
	$ResetButton.connect("pressed", self._on_reset_pressed.bind())
	$TickTimer.connect("timeout", self._on_tick_timeout.bind())
	$TickTimer.wait_time = tick_rate

	$PatternOptionButton.connect("item_selected", self._on_pattern_selected.bind())
	$PatternOptionButton.add_item("Clear")
	$PatternOptionButton.add_item("Pattern 1")
	$PatternOptionButton.add_item("Pattern 2")

func _on_pattern_selected(index):
	clear_grid()
	match index:
		0:  # Clear
			pass
		1:  # Pattern 1
			set_pattern1()
		2:  # Pattern 2
			set_pattern2()


func clear_grid():
	for row in cells:
		for cell in row:
			cell.is_alive = false
			cell.update_visuals()


func _on_start_pressed():
	$TickTimer.start()

func _on_reset_pressed():
	print("Reset is pressed")
	$TickTimer.stop()
	clear_grid()

func set_pattern1():
	# Define your pattern 1 here
	var pattern = [		
		[0, 0, 1, 0, 0],
		[0, 1, 1, 1, 0],
		[0, 0, 1, 0, 0],
		[0, 0, 1, 0, 0],
		[0, 1, 0, 1, 0],
		[1, 0, 0, 0, 1],
		[1, 1, 1, 1, 1],
		[1, 0, 0, 0, 1],
		[1, 0, 0, 0, 1],
		[1, 0, 0, 0, 1],
		[1, 1, 1, 1, 1]
	]
	set_pattern(pattern, 32, 20)  # Place pattern at (5, 5)

func set_pattern2():
	# Define your pattern 2 here
	var pattern = [
		[0, 1, 1, 0, 0, 1, 1, 0],
		[1, 0, 0, 1, 1, 0, 0, 1],
		[1, 0, 0, 0, 0, 0, 0, 1],
		[0, 1, 0, 0, 0, 0, 1, 0],
		[0, 0, 1, 0, 0, 1, 0, 0],
		[0, 0, 0, 1, 1, 0, 0, 0]
	]
	set_pattern(pattern, 32, 15)  # Place pattern at (10, 10)

func set_pattern(pattern, offset_x, offset_y):
	for y in range(pattern.size()):
		for x in range(pattern[y].size()):
			if y + offset_y < grid_size.y and x + offset_x < grid_size.x:
				var cell = cells[y + offset_y][x + offset_x]
				cell.is_alive = pattern[y][x] == 1
				cell.update_visuals()

func _on_tick_timeout():
	var start_time = Time.get_unix_time_from_system() * 1000
	print(start_time)
	
	var new_states = []
	for y in range(grid_size.y):
		var new_row = []
		for x in range(grid_size.x):
			var alive_neighbors = count_alive_neighbors(x, y)
			var cell = cells[y][x]
			if cell.is_alive:
				if alive_neighbors < 2 or alive_neighbors > 3:
					new_row.append(false)
				else:
					new_row.append(true)
			else:
				if alive_neighbors == 3:
					new_row.append(true)
				else:
					new_row.append(false)
		new_states.append(new_row)
	

	for y in range(grid_size.y):
		for x in range(grid_size.x):
			cells[y][x].is_alive = new_states[y][x]
			cells[y][x].update_visuals()
	
	var end_time = Time.get_unix_time_from_system() * 1000
	$UpdateCycleLabel.text = "Tick Duration: \n" + str(end_time - start_time) + "ms"
	print(end_time)
	print("GDScript Tick Duration: \n" + str(end_time - start_time) + "ms")


func count_alive_neighbors(x, y):
	var alive_neighbors = 0
	for i in range(-1, 2):
		for j in range(-1, 2):
			if i == 0 and j == 0:
				continue
			var nx = x + i
			var ny = y + j
			if nx >= 0 and nx < grid_size.x and ny >= 0 and ny < grid_size.y:
				if cells[ny][nx].is_alive:
					alive_neighbors += 1
	return alive_neighbors
