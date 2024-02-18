class paddle : public vec2{
	public:
		paddle(float x);
		paddle(float x, float y);
		~paddle();
		void move_up();
		void move_down();
		void draw();
		void erase();
};

paddle::paddle(float x) : vec2(x, window_height / 2.0f){
	
}

paddle::paddle(float x, float y) : vec2(x, y){
	
}

paddle::~paddle(){

}

void paddle::move_up(){
	this->mod_y(this->get_y() - global_velocity);
}

void paddle::move_down(){
	this->mod_y(this->get_y() + global_velocity);
}

void paddle::draw(){
	for(int x = this->get_x() - paddle_width / 2; x < this->get_x() + paddle_width / 2; x++){
		draw_line(x, this->get_y() - paddle_height / 2, x, this->get_y() + paddle_height / 2);
	}
}

void paddle::erase(){
	for(int x = this->get_x() - paddle_width / 2; x < this->get_x() + paddle_width / 2; x++){
		draw_line(x, this->get_y() - paddle_height / 2, x, this->get_y() + paddle_height / 2, black);
	}
}
