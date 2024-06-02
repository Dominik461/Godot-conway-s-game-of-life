extends CanvasLayer

# References to the labels
@onready var cpu_label = $CPULabel
@onready var memory_label = $MemoryLabel
@onready var frame_time_label = $FrameTimeLabel

func _process(delta):
	# Update CPU usage
	var cpu_usage = OS.get_processor_usage() * 100
	cpu_label.text = "CPU Usage: %.2f%%" % cpu_usage
	
	# Update memory usage
	var memory_usage = OS.get_static_memory_usage() / 1024 / 1024 # Convert bytes to MB
	memory_label.text = "Memory Usage: %.2f MB" % memory_usage
	
	# Update average frame time
	var frame_time = Engine.get_frames_per_second()
	frame_time_label.text = "FPS: %.2f" % frame_time
