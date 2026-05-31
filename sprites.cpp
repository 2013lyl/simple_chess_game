#include <graphics.h>
#include <string>

using namespace std;

class Piece{
public:
	IMAGE* img;
	IMAGE* img_mask;
	int x, y, grid_x, grid_y, GRIDWIDTH, GRIDHEIGHT;
	bool is_clicked;
	string name;
	int id;

	Piece(): img(nullptr), img_mask(nullptr), x(0), y(0), grid_x(0), grid_y(0), GRIDWIDTH(0), GRIDHEIGHT(0), is_clicked(false), name(nullptr), id(-1) {}

	Piece(IMAGE* image, IMAGE* image_mask, int x_pos, int y_pos, int grid_x_pos, int grid_y_pos, int GRIDWIDTH, int GRIDHEIGHT, string piece_name, int id) : img(image), img_mask(image_mask), x(x_pos), y(y_pos), grid_x(grid_x_pos), grid_y(grid_y_pos), GRIDWIDTH(GRIDWIDTH), GRIDHEIGHT(GRIDHEIGHT), name(piece_name), id(id){}	

	void draw(){
		putimage(x, y, img_mask, SRCAND);
		putimage(x, y, img, SRCPAINT);

		if (is_clicked) {
            setlinecolor(RGB(255, 255, 0));  // 黄色边框
            setlinestyle(PS_SOLID, 3);       // 3像素粗线
            rectangle(x, y, x + GRIDWIDTH, y + GRIDHEIGHT);
            setlinestyle(PS_SOLID, 1);       // 恢复默认
        }
	}
};

class Circle{
public:
	IMAGE* img;
	IMAGE* img_mask;
	int x, y, grid_x, grid_y;
	int piece_id;
	string circle_kind;

	Circle(): img(nullptr), img_mask(nullptr), x(0), y(0), grid_x(0), grid_y(0), piece_id(-1), circle_kind(nullptr) {}

	Circle(IMAGE* image, IMAGE* image_mask, int x_pos, int y_pos, int grid_x_pos, int grid_y_pos, int piece_id, string circle_kind) : img(image), img_mask(image_mask), x(x_pos), y(y_pos), grid_x(grid_x_pos), grid_y(grid_y_pos), piece_id(piece_id), circle_kind(circle_kind){}

	void draw(){
		putimage(x, y, img_mask, SRCAND);
		putimage(x, y, img, SRCPAINT);
	}
};
