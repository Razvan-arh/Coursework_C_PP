make: drawings.c graphics.c robot.c robot_main.c
	gcc -o square drawings.c graphics.c robot.c robot_main.c -lm -I.