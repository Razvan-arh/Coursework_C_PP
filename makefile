make: drawings.c graphics.c robot.c robot_navigation.c read.c
	gcc -o square drawings.c graphics.c robot.c robot_navigation.c read.c -lm -I.