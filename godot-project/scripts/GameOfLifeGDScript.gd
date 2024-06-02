extends Node2D

@export var grid_size: Vector2i = Vector2i(40, 40)
@export var cell_size: Vector2i = Vector2i(10, 10)
@export var tick_rate: float = 1.5  # Time in seconds between each tick

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

func _on_start_pressed():
	$TickTimer.start()

func _on_reset_pressed():
	print("Reset is pressed")
	$TickTimer.stop()
	for row in cells:
		for cell in row:
			cell.is_alive = false
			cell.update_visuals()

func _on_tick_timeout():
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
