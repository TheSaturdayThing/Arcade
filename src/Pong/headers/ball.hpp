class ball : public vec2{
	public:
		ball();
		ball(float x, float y);
		ball(float x, float y, vec2 vel);
		~ball();
		void init_vel();
		vec2 get_vel();
		bool is_wall_colliding();
		void update_vel_wall();
		bool is_paddle_colliding(paddle *left_paddle, paddle *right_paddle);
		void update_vel_paddle(paddle *left_paddle, paddle *right_paddle);
		void update_pos();
		void draw();
		void erase();
	private:
		vec2 vel;
};

ball::ball() : vec2(window_width / 2.0f, window_height / 2.0f){
	this->init_vel();
}

ball::ball(float x, float y) : vec2(x, y){
	this->init_vel();
}

ball::ball(float x, float y, vec2 vel) : vec2(x, y){
	this->vel = vel;
}

ball::~ball(){
	
}

void ball::init_vel(){
	float poss_speed_x[6] = {-global_velocity, -global_velocity + global_velocity / 6.0f, -global_velocity + global_velocity / 3.0f, global_velocity, global_velocity - global_velocity / 6.0f, global_velocity - global_velocity / 3.0f};
	float v_x1 = poss_speed_x[rand()%6];
	float v_x = this->get_x() + v_x1;
	float poss_speed_y[4] = {-global_velocity / 2.0f, -global_velocity / 2.0f + global_velocity / 6.0f, global_velocity / 2.0f, global_velocity / 2.0f - global_velocity / 6.0f};
	float v_y1 = poss_speed_y[rand()%4];
	float v_y = this->get_y() + v_y1;
	vel.mod_coords(v_x, v_y);
}

vec2 ball::get_vel(){
	return vel;
}

bool ball::is_wall_colliding(){
	float y = vel.get_y() - this->get_y();
	if(this->get_y() + y < 2.0f * ball_radius){
		return true;
	}
	else if(this->get_y() + y > window_height - 2.0f * ball_radius){
		return true;
	}
	return false;
}

void ball::update_vel_wall(){
	vel.mod_y(vel.get_y() - 2.0f * (vel.get_y() - this->get_y()));
}

bool ball::is_paddle_colliding(paddle *left_paddle, paddle *right_paddle){
	if(this->get_x() < left_paddle->get_x() + ball_radius && this->get_x() > left_paddle->get_x() - ball_radius){
		if(this->get_y() + ball_radius < left_paddle->get_y() + paddle_height / 2 && this->get_y() - ball_radius > left_paddle->get_y() - paddle_height / 2){
			this->mod_x(left_paddle->get_x() + ball_radius);
			return true;
		}
	}
	else if(this->get_x() > right_paddle->get_x() - ball_radius && this->get_x() < right_paddle->get_x() + ball_radius){
		if(this->get_y() + ball_radius < right_paddle->get_y() + paddle_height / 2 && this->get_y() - ball_radius > right_paddle->get_y() - paddle_height / 2){
			this->mod_x(right_paddle->get_x() - ball_radius);
			return true;
 		}
	}
	return false;
}

void ball::update_vel_paddle(paddle *left_paddle, paddle *right_paddle){
	if(this->get_x() == left_paddle->get_x() + ball_radius){
		float alpha_degrees = ((left_paddle->get_x() - this->get_x()) * 90.0f) / (paddle_height / 2.0f);
		float alpha_radians = (alpha_degrees * Pi) / 180.0f;
		if(this->get_y() <= left_paddle->get_y()){
			vel.mod_x(this->get_x() + global_velocity * cos(-alpha_radians));
			vel.mod_y(this->get_y() - global_velocity * sin(-alpha_radians));
		}
		else{
			vel.mod_x(this->get_x() + global_velocity * cos(alpha_radians));
			vel.mod_y(this->get_y() - global_velocity * sin(alpha_radians));
		}
	}
	else if(this->get_x() == right_paddle->get_x() - ball_radius){
		float alpha_degrees = ((right_paddle->get_x() - this->get_x()) * 90.0f) / (paddle_height / 2.0f);
		float alpha_radians = ((180.0f + alpha_degrees) * Pi) / 180.0f;
		if(this->get_y() <= right_paddle->get_y()){
			vel.mod_x(this->get_x() + global_velocity * cos(-alpha_radians));
			vel.mod_y(this->get_y() - global_velocity * sin(-alpha_radians));
		}
		else{
			vel.mod_x(this->get_x() + global_velocity * cos(alpha_radians));
			vel.mod_y(this->get_y() - global_velocity * sin(alpha_radians));
		}
	}
}

void ball::update_pos(){
	float x = vel.get_x() - this->get_x();
	float y = vel.get_y() - this->get_y();
	this->mod_coords(this->get_x() + x, this->get_y() + y);
	vel.mod_coords(vel.get_x() + x, vel.get_y() + y);
}

void ball::draw(){
	draw_ball(this->get_x(), this->get_y());
}

void ball::erase(){
	draw_ball(this->get_x(), this->get_y(), black);
}
