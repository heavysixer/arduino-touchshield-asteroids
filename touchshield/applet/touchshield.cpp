#include "WProgram.h"
void setup();
void draw_background();
void loop();
struct Asteroid{
public:
	float x;
	float y;
	float radius;
	int sides;
	int rotation;
	int direction;
	int speed;
	int rotation_speed;
	void tick(){
		rotation += rotation_speed;
		
		if(rotation > 360) rotation = rotation % 360;
		if(rotation < 0) rotation = rotation + 360;
		
		int x_velocity = (cos(convert_to_radians(direction)) * speed) * -1;
		int y_velocity = (sin(convert_to_radians(direction)) * speed) * -1;
		
		x += x_velocity;
		y += y_velocity;
		
		if(x < 3) x = 125;
		if(x > 125) x = 3;
		if(y < 3) y = 125;
		if(y > 125) y = 3;
	};
	void render(){
		stroke(255, 255, 255);
		fill(0, 0, 0);
		
		float plot_x, plot_y;
		float old_plot_x = -129.0, old_plot_y = -129.0;
		
		for(int point_index = 0; point_index <= 360; point_index += 360 / sides){
			plot_x = sin(convert_to_radians(point_index + rotation)) * radius;
			plot_y = cos(convert_to_radians(point_index + rotation)) * radius;
			
			plot_x = drawing_constraints(plot_x + x);
			plot_y = drawing_constraints(plot_y + y);
			
			if(old_plot_x != -129.0){
				line(old_plot_x, old_plot_y, plot_x, plot_y);
			};
			old_plot_x = plot_x;
			old_plot_y = plot_y;
		};
	};
private:
	float convert_to_radians(float deg){
		// these is terrible, can't handle values greater than 720
		if(deg > 360.0) deg = deg - 360.0;
		if(deg < 0.0) deg = deg + 360.0;
		
		return 3.1415 / 180.0 * deg;
	};
	float drawing_constraints(float coord){
		coord = coord > 0.0 ? coord : 0.0;
		coord = coord < 128.0 ? coord : 128.0;
		return coord;
	};
};

int i;

const int asteroids_count = 6;
Asteroid asteroids[asteroids_count];

void setup(){
	draw_background();
	
	for(i = 0; i < asteroids_count; i++){
		asteroids[i] = (Asteroid){random(20, 108), random(20, 108), random(4, 9), (int)random(5, 9), random(360), random(360), random(3, 6), random(4, 20)};
	};
};

void draw_background(){
	stroke(0, 0, 0);
	fill(0, 0, 0);
	rect(0, 0, 128, 128);
};

void loop(){
	draw_background();
	
	for(i = 0; i < asteroids_count; i++){
		asteroids[i].tick();
		asteroids[i].render();
	};
};

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

