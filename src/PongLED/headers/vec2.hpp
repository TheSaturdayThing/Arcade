class vec2{
	public:
		vec2();
		vec2(float x, float y);
		~vec2();
		float get_x();
		float get_y();
		void mod_x(float x);
		void mod_y(float y);
		void mod_coords(float x, float y);
		void operator = (vec2 other){
			this->x = other.get_x();
			this->y = other.get_y();
		}
	private:
		float x, y;
};

vec2::vec2(){
	this->x = 0.0f;
	this->y = 0.0f;
}

vec2::vec2(float x, float y){
	this->x = x;
	this->y = y;
}

vec2::~vec2(){
	this->x = 0.0f;
	this->y = 0.0f;
}

float vec2::get_x(){
	return this->x;
}

float vec2::get_y(){
	return this->y;
}

void vec2::mod_x(float x){
	this->x = x;
}

void vec2::mod_y(float y){
	this->y = y;
}

void vec2::mod_coords(float x, float y){
	this->x = x;
	this->y = y;
}
